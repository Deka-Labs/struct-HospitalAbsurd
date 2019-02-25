#include "newreferralwindow.hpp"

NewReferralWindow::NewReferralWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
{
    m_ui = new Ui::NewReferralForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_ok, &QPushButton::clicked, this, &NewReferralWindow::okButtonPressed);

    //TODO! Init comboboxes
}

NewReferralWindow::~NewReferralWindow()
{
    delete m_ui;
}

void NewReferralWindow::okButtonPressed()
{
    if (validate())
        this->accept();
    else {
        //TODO! mark invalid values
    }
}

bool NewReferralWindow::validate()
{
    //TODO! Validate input
    return true;
}
