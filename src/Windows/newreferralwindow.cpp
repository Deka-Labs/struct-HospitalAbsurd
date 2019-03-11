#include "newreferralwindow.hpp"
#include "../globaldatabase.hpp"
#include <QMessageBox>

NewReferralWindow::NewReferralWindow(Referral& toEdit, QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
    , m_toEdit(toEdit)
    , m_errMsg("")
{
    m_ui = new Ui::NewReferralForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &NewReferralWindow::okButtonPressed);

    //TODO! Init comboboxes
    auto listPat = g_DATABASE->getPatientsModel().getAllPatients();
    for (unsigned pos = 0; pos < listPat.size(); pos++) {
        m_ui->comboBox_regID->addItem(listPat.at(pos).regID());
    }

    auto listDoc = g_DATABASE->getDoctorsModel().getAllDoctors();
    for (unsigned pos = 0; pos < listDoc.size(); pos++) {
        m_ui->comboBox->addItem(listDoc.at(pos).fullname());
    }
}

NewReferralWindow::~NewReferralWindow()
{
    delete m_ui;
}

void NewReferralWindow::okButtonPressed()
{
    if (validate())
        this->accept();
    else {
        QMessageBox::warning(this, "Неверный ввод", m_errMsg + "\nПовторите ввод.");
    }
}

bool NewReferralWindow::validate()
{
    m_errMsg = "";
    bool result = true;

    if (!m_toEdit.setRegID(m_ui->comboBox_regID->currentText())) {
        result = false;
        m_errMsg += "Неверный ввод регестрационного номера\n";
    }
    if (!m_toEdit.setDoctorFullname(m_ui->comboBox->currentText())) {
        result = false;
        m_errMsg += "Неверный ввод ФИО врача\n";
    }

    if (!m_toEdit.setDate(m_ui->dateEdit->date().toString("dd.MM.yyyy"))) {
        result = false;
        m_errMsg += "Неверный ввод даты\n";
    }

    if (!m_toEdit.setTime(m_ui->timeEdit->time().toString("hh:mm"))) {
        result = false;
        m_errMsg += "Неверный ввод времени\n";
    }

    return result;
}
