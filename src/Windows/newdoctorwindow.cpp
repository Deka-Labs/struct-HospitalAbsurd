#include "newdoctorwindow.hpp"
#include "../globaldatabase.hpp"
#include <QMessageBox>
#include <stdexcept>

NewDoctorWindow::NewDoctorWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
    , m_toEdit()
    , m_errMsg("")
{
    m_ui = new Ui::NewDoctorForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &NewDoctorWindow::okButtonPressed);

    m_ui->lineEdit_fullName->setToolTip("Строка размером до " + QString("%1").arg(MAX_DOCTOR_FULLNAME_STRING_SIZE));
    m_ui->lineEdit_post->setToolTip("Строка размером до " + QString("%1").arg(MAX_DOCTOR_POST_STRING_SIZE));
    m_ui->spinBox_cabNumber->setToolTip("Число от 0 до " + QString("%1").arg(MAX_DOCTOR_CABINET));
    m_ui->lineEdit_grafik->setToolTip("Строка размером до " + QString("%1").arg(MAX_DOCTOR_SCHEDULE_STRING_SIZE));
}

NewDoctorWindow::~NewDoctorWindow()
{
    delete m_ui;
}

void NewDoctorWindow::okButtonPressed()
{
    if (validate()) {
        auto res = g_DATABASE->addDoctor(m_toEdit);
        switch (res) {
        case StatusCode_OK:
            accept();
            return;
        case StatusCode_AlreadyExist:
            QMessageBox::warning(this, "Ошибка добавления в БД", "Доктор с таким полем ФИО уже существует.\n"
                                                                 "Увольте старого доктора или откажите в приеме новому доктору.\n");
            return;
        default:
            throw std::runtime_error("Not implemented");
        }

    } else {
        QMessageBox::warning(this, "Неверный ввод", m_errMsg + "\nПовторите ввод.");
    }
}

bool NewDoctorWindow::validate()
{
    bool result = true;
    m_errMsg = "";

    if (!m_toEdit.setFullname(m_ui->lineEdit_fullName->text())) {
        m_errMsg += "Неверно указано имя\n";
        result = false;
    }

    if (!m_toEdit.setPost(m_ui->lineEdit_post->text())) {
        m_errMsg += "Неверно указана должность\n";
        result = false;
    }

    if (!m_toEdit.setCabinet(static_cast<unsigned>(m_ui->spinBox_cabNumber->value()))) {
        m_errMsg += "Неверно указан кабинет\n";
        result = false;
    }

    if (!m_toEdit.setSchedule(m_ui->lineEdit_grafik->text())) {
        m_errMsg += "Неверно указан график\n";
        result = false;
    }

    return result;
}
