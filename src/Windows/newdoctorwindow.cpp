#include "newdoctorwindow.hpp"
#include <QMessageBox>

NewDoctorWindow::NewDoctorWindow(Doctor& toEdit, QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
    , m_toEdit(toEdit)
    , m_errMsg("")
{
    m_ui = new Ui::NewDoctorForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &NewDoctorWindow::okButtonPressed);
}

NewDoctorWindow::~NewDoctorWindow()
{
    delete m_ui;
}

void NewDoctorWindow::okButtonPressed()
{
    if (validate())
        this->accept();
    else {
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
