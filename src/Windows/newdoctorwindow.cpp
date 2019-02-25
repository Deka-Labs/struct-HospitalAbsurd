#include "newdoctorwindow.hpp"

NewDoctorWindow::NewDoctorWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
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
        //TODO! mark invalid values
    }
}

bool NewDoctorWindow::validate()
{
    //TODO! Validate input
    return true;
}
