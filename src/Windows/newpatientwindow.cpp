#include "newpatientwindow.hpp"

NewPatientWindow::NewPatientWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
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
        //TODO! mark invalid values
    }
}

bool NewPatientWindow::validate()
{
    //TODO! Validate input
    return true;
}
