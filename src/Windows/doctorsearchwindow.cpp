#include "doctorsearchwindow.hpp"

#include "../models/searchdoctorbyfullname.hpp"
#include "../models/searchdoctorbypost.hpp"
#include "data/hospital/doctor.hpp"
#include "searchresults.hpp"
#include "utils.hpp"

#include <QMessageBox>

DoctorSearchWindow::DoctorSearchWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr) {
    m_ui = new Ui::PatientSearchForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &DoctorSearchWindow::okButtonPressed);
    connect(m_ui->comboBox_type, &QComboBox::currentTextChanged, this, &DoctorSearchWindow::comboBoxChanged);

    this->setWindowTitle("Поиск врача");
    m_ui->comboBox_type->addItem("ФИО");
    m_ui->comboBox_type->addItem("Должность");
    m_ui->comboBox_type->setCurrentIndex(0); //Обновляем поле ввода
}

DoctorSearchWindow::~DoctorSearchWindow() {
    delete m_ui;
}

void DoctorSearchWindow::okButtonPressed() {
    if (validate()) {
        auto request = m_ui->lineEdit_request->text();
        auto id      = m_ui->comboBox_type->currentIndex();
        switch (id) {
            case 0: {
                Doctor doc;
                if (g_DATABASE->getDoctorsModel().getDoctor(request, &doc)) {
                    SearchDoctorByFullname model(doc);
                    SearchResults resWindow("Результаты поиска доктора по ФИО", &model, this);
                    resWindow.exec();
                } else {
                    QMessageBox::warning(this, "Поиск не успешен", "Поиск не дал результатов");
                }
                break;
            }
            case 1: {
                auto list = g_DATABASE->getDoctorsModel().getAllDoctors();
                for (unsigned pos = 0; pos < list.size(); pos++) {
                    if (!QStringSearch(request, list.at(pos).post())) {
                        list.remove(pos);
                        pos--; //Возвращаемся назад, чтобы не проскачить элемент
                    }
                }
                if (list.size() > 0) {
                    SearchDoctorByPost model(std::move(list));
                    SearchResults resWindow("Результаты поиска доктора по фрагмента должности", &model);
                    resWindow.exec();
                } else {
                    QMessageBox::warning(this, "Поиск не успешен", "Поиск не дал результатов");
                }
                break;
            }
            default: { break; }
        }
    } else {
        QMessageBox::warning(this, "Неверный ввод", "Поле поиска не соотвествует формату записи");
    }
}

void DoctorSearchWindow::comboBoxChanged(const QString& text) {
    if (text == "ФИО") {
        m_ui->lineEdit_request->setMaxLength(MAX_DOCTOR_FULLNAME_STRING_SIZE);
    } else if (text == "Должность") {
        m_ui->lineEdit_request->setMaxLength(MAX_DOCTOR_POST_STRING_SIZE);
    }
}

bool DoctorSearchWindow::validate() {
    return true;
}
