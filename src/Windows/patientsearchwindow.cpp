#include "patientsearchwindow.hpp"

#include "../globaldatabase.hpp"
#include "../models/searchpatientbyfullname.hpp"
#include "../models/searchpatientbyregid.hpp"
#include "data/hospital/patient.hpp"
#include "searchresults.hpp"
#include "utils.hpp"

#include <QMessageBox>

PatientSearchWindow::PatientSearchWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr) {
    m_ui = new Ui::PatientSearchForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &PatientSearchWindow::okButtonPressed);
    connect(m_ui->comboBox_type, &QComboBox::currentTextChanged, this, &PatientSearchWindow::comboBoxChanged);

    this->setWindowTitle("Поиск больного");
    m_ui->comboBox_type->addItem("Регистрационный №");
    m_ui->comboBox_type->addItem("ФИО");
    m_ui->comboBox_type->setCurrentIndex(0);
}

PatientSearchWindow::~PatientSearchWindow() {
    delete m_ui;
}

void PatientSearchWindow::okButtonPressed() {
    if (validate()) {
        auto request = m_ui->lineEdit_request->text();
        auto id      = m_ui->comboBox_type->currentIndex();

        switch (id) {
            case 0: {
                Patient result;
                if (g_DATABASE->getPatientsModel().getPatient(PatientHashKey(request), &result)) {
                    SearchPatientByRegID model(result);
                    SearchResults resWindow("Результаты поиска пациента по рег. номеру", &model, this);
                    resWindow.exec();
                } else {
                    QMessageBox::warning(this, "Поиск не успешен", "Поиск не дал результатов");
                }
                break;
            }

            case 1: {
                auto list = g_DATABASE->getPatientsModel().getAllPatientsWithName(request);
                if (list.size() > 0) {
                    SearchPatientByFullname model(std::move(list));
                    SearchResults resWindow("Результаты поиска пациента по ФИО", &model);
                    resWindow.exec();
                } else {
                    QMessageBox::warning(this, "Поиск не успешен", "Поиск не дал результатов");
                }
                break;
            }
            default:
                return;
        }

    } else {
        QMessageBox::warning(this, "Неверный ввод", "Поле поиска не соотвествует формату записи");
    }
}

void PatientSearchWindow::comboBoxChanged(const QString& text) {
    if (text == "Регистрационный №") {
        m_ui->lineEdit_request->setInputMask("99-999999");
    } else if (text == "ФИО") {
        m_ui->lineEdit_request->setInputMask("");
        m_ui->lineEdit_request->setMaxLength(MAX_PATIENT_FULLNAME_STRING_SIZE);
    }
}

bool PatientSearchWindow::validate() {
    auto id = m_ui->comboBox_type->currentIndex();

    switch (id) {
        case 0:
            if (!TemplateValidate(PATIENT_REGID_TEMPLATE, m_ui->lineEdit_request->text()))
                return false;
            break;
        case 1:
            if (m_ui->lineEdit_request->text().size() > MAX_PATIENT_FULLNAME_STRING_SIZE)
                return false;
            break;
        default:
            return false;
    }

    return true;
}
