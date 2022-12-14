#include "newreferralwindow.hpp"

#include "../globaldatabase.hpp"

#include <QMessageBox>

NewReferralWindow::NewReferralWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
    , m_toEdit()
    , m_errMsg("") {
    m_ui = new Ui::NewReferralForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &NewReferralWindow::okButtonPressed);

    auto listPat = g_DATABASE->getPatientsModel().getAllPatients();
    for (unsigned pos = 0; pos < listPat.size(); pos++) {
        m_ui->comboBox_regID->addItem(listPat.at(pos).regID());
    }

    auto listDoc = g_DATABASE->getDoctorsModel().getAllDoctors();
    for (unsigned pos = 0; pos < listDoc.size(); pos++) {
        m_ui->comboBox->addItem(listDoc.at(pos).fullname());
    }

    m_ui->comboBox_regID->setToolTip("Регистрационный номер пациента");
    m_ui->comboBox->setToolTip("ФИО врача");
    m_ui->dateEdit->setToolTip("Дата направления");
    m_ui->timeEdit->setToolTip("Время направления");
}

NewReferralWindow::~NewReferralWindow() {
    delete m_ui;
}

void NewReferralWindow::okButtonPressed() {
    if (validate()) {
        auto res = g_DATABASE->addReferral(m_toEdit);
        switch (res) {
            case StatusCode_OK:
                this->accept();
                return;
            case StatusCode_InvalidObject:
                QMessageBox::warning(this, "Не удалось добавить запись",
                                     "Неверно указан регистрационный номер или ФИО врача.");
                return;
            case StatusCode_AlreadyExist:
                QMessageBox::warning(this, "Не удалось добавить запись",
                                     "На эту дату и время к этому врачу уже назначен пациент");
                return;
            default:
                throw std::runtime_error("Not implemented");
        }
    } else {
        QMessageBox::warning(this, "Неверный ввод", m_errMsg + "\nПовторите ввод.");
    }
}

bool NewReferralWindow::validate() {
    m_errMsg    = "";
    bool result = true;

    if (!m_toEdit.setRegID(m_ui->comboBox_regID->currentText())) {
        result = false;
        m_errMsg += "Неверный ввод регистрационного номера\n";
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
