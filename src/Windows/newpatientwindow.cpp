#include "newpatientwindow.hpp"
#include <QMessageBox>

NewPatientWindow::NewPatientWindow(Patient& toEdit, QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
    , m_toEdit(toEdit)
    , m_errMsg("")
{
    m_ui = new Ui::NewPatientForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &NewPatientWindow::okButtonPressed);
}

NewPatientWindow::~NewPatientWindow()
{
    delete m_ui;
}

void NewPatientWindow::okButtonPressed()
{
    if (validate())
        this->accept();
    else {
        QMessageBox::warning(this, "Неверный ввод", m_errMsg + "\nПовторите ввод.");
    }
}

bool NewPatientWindow::validate()
{
    bool result = true;
    m_errMsg = "";
    if (!m_toEdit.setRegID(m_ui->lineEdit_regID->text())) {
        m_errMsg += "Неверно указан регестрационный номер.\n";
        result = false;
    }

    if (!m_toEdit.setFullName(m_ui->lineEdit_fullName->text())) {
        m_errMsg += "Неверно указано ФИО.\n";
        result = false;
    }

    if (!m_toEdit.setYearOfBirth(static_cast<unsigned>(m_ui->spinBox_year->value()))) {
        m_errMsg += "Неверно указан год рождения.\n";
        result = false;
    }

    if (!m_toEdit.setAddress(m_ui->lineEdit_address->text())) {
        m_errMsg += "Неверно указан адрес.\n";
        result = false;
    }

    if (!m_toEdit.setWorkPlace(m_ui->lineEdit_workplace->text())) {
        m_errMsg += "Неверно указано место работы.\n";
        result = false;
    }
    return result;
}
