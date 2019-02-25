#include "patientsearchwindow.hpp"

PatientSearchWindow::PatientSearchWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
{
    m_ui = new Ui::PatientSearchForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &PatientSearchWindow::okButtonPressed);
    connect(m_ui->comboBox_type, &QComboBox::currentTextChanged, this, &PatientSearchWindow::comboBoxChanged);

    this->setWindowTitle("Поиск больного");
    m_ui->comboBox_type->addItem("Регистрационный №");
    m_ui->comboBox_type->addItem("ФИО");
    m_ui->comboBox_type->setCurrentIndex(0);
}

PatientSearchWindow::~PatientSearchWindow()
{
    delete m_ui;
}

void PatientSearchWindow::okButtonPressed()
{
    if (validate()) {
        //TODO! Open results
    } else {
        //TODO! tell what
    }
}

void PatientSearchWindow::comboBoxChanged(const QString& text)
{
    if (text == "Регистрационный №") {
        m_ui->lineEdit_request->setInputMask("99-999999");
    } else if (text == "ФИО") {
        m_ui->lineEdit_request->setInputMask("");
        m_ui->lineEdit_request->setMaxLength(100); //TODO! Set const
    }
}

bool PatientSearchWindow::validate()
{
    //TODO! validate!
    return true;
}
