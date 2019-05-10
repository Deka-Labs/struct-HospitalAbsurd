#include "newpatientwindow.hpp"

#include "../globaldatabase.hpp"

#include <QMessageBox>

NewPatientWindow::NewPatientWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
    , m_toEdit()
    , m_errMsg("") {
    m_ui = new Ui::NewPatientForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &NewPatientWindow::okButtonPressed);

    m_ui->lineEdit_regID->setToolTip("Строка формата dd-dddddd; где d - число от 0 до 9");

    m_ui->lineEdit_fullName->setMaxLength(MAX_PATIENT_FULLNAME_STRING_SIZE);
    m_ui->lineEdit_fullName->setToolTip("Строка размером от " + QString("%1").arg(MIN_PATIENT_FULLNAME_STRING_SIZE) +
                                        " до " + QString("%1").arg(MAX_PATIENT_FULLNAME_STRING_SIZE));

    m_ui->spinBox_year->setMinimum(MIN_PATIENT_YEAR);
    m_ui->spinBox_year->setMaximum(MAX_PATIENT_YEAR);
    m_ui->spinBox_year->setToolTip("Год рождения - число от " + QString("%1").arg(MIN_PATIENT_YEAR) + " до " +
                                   QString("%1").arg(MAX_PATIENT_YEAR));

    m_ui->lineEdit_address->setMaxLength(MAX_PATIENT_ADDRESS_STRING_SIZE);
    m_ui->lineEdit_address->setToolTip("Строка размером от " + QString("%1").arg(MIN_PATIENT_ADDRESS_STRING_SIZE) +
                                       " до " + QString("%1").arg(MAX_PATIENT_ADDRESS_STRING_SIZE));

    m_ui->lineEdit_workplace->setMaxLength(MAX_PATIENT_WORKPLACE_STRING_SIZE);
    m_ui->lineEdit_workplace->setToolTip("Строка размером от " + QString("%1").arg(MIN_PATIENT_WORKPLACE_STRING_SIZE) +
                                         " до " + QString("%1").arg(MAX_PATIENT_WORKPLACE_STRING_SIZE));
}

NewPatientWindow::~NewPatientWindow() {
    delete m_ui;
}

void NewPatientWindow::okButtonPressed() {
    if (validate()) {
        auto res = g_DATABASE->addPatient(m_toEdit);
        switch (res) {
            case StatusCode_OK:
                accept();
                return;
            case StatusCode_Overloaded:
                QMessageBox::warning(
                    this, "Невозможно добавить запись",
                    "Данную запись невозможно добавить, так как в таблице нет места для этого регистрационного номера.\n"
                    "Попробуйте выбрать другой номер");
                return;
            case StatusCode_AlreadyExist:
                QMessageBox::warning(this, "Невозможно добавить запись",
                                     "Запись с таким регистрационный номером уже существует.");
                return;
            default:
                throw std::runtime_error("Not implemented");
        }
    } else {
        QMessageBox::warning(this, "Неверный ввод", m_errMsg + "\nПовторите ввод.");
    }
}

bool NewPatientWindow::validate() {
    bool result = true;
    m_errMsg    = "";
    if (!m_toEdit.setRegID(m_ui->lineEdit_regID->text())) {
        m_errMsg += "Неверно указан регистрационный номер.\n";
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
