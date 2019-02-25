#include "doctorsearchwindow.hpp"

DoctorSearchWindow::DoctorSearchWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
{
    m_ui = new Ui::PatientSearchForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &DoctorSearchWindow::okButtonPressed);
    connect(m_ui->comboBox_type, &QComboBox::currentTextChanged, this, &DoctorSearchWindow::comboBoxChanged);

    this->setWindowTitle("Поиск врача");
    m_ui->comboBox_type->addItem("ФИО");
    m_ui->comboBox_type->addItem("Должность");
    m_ui->comboBox_type->setCurrentIndex(0); //Обновляем поле ввода
}

DoctorSearchWindow::~DoctorSearchWindow()
{
    delete m_ui;
}

void DoctorSearchWindow::okButtonPressed()
{
    if (validate()) {
        //TODO! Open results
    } else {
        //TODO! tell what
    }
}

void DoctorSearchWindow::comboBoxChanged(const QString& text)
{
    if (text == "ФИО") {
        m_ui->lineEdit_request->setMaxLength(25); //TODO! Set const
    } else if (text == "Должность") {
        m_ui->lineEdit_request->setMaxLength(100); //TODO! Set const
    }
}

bool DoctorSearchWindow::validate()
{
    //TODO! validate!
    return true;
}
