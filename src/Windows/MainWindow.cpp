#include "MainWindow.hpp"
#include "doctorlistwindow.hpp"
#include "patientlistwindow.hpp"
#include "referrallistwindow.hpp"

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_ui(nullptr)
{
    m_ui = new Ui::MainWindow();
    m_ui->setupUi(this);

    connect(m_ui->pushButton_patients, &QPushButton::clicked, this, &MainWindow::patientsButtonPressed);
    connect(m_ui->pushButton_doctors, &QPushButton::clicked, this, &MainWindow::doctorsButtonPressed);
    connect(m_ui->pushButton_referral, &QPushButton::clicked, this, &MainWindow::referralsButtonPressed);
    connect(m_ui->pushButton_saveandexit, &QPushButton::clicked, this, &MainWindow::exitButtonPressed);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::patientsButtonPressed()
{
    PatientListWindow patWnd(this);
    patWnd.exec();
}

void MainWindow::doctorsButtonPressed()
{
    DoctorListWindow docWnd(this);
    docWnd.exec();
}

void MainWindow::referralsButtonPressed()
{
    ReferralListWindow refWnd(this);
    refWnd.exec();
}

void MainWindow::exitButtonPressed()
{
    //TODO! save database
    this->close();
}
