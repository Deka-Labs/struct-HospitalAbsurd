#include "MainWindow.hpp"
#include "doctorlistwindow.hpp"
#include "patientlistwindow.hpp"
#include "referrallistwindow.hpp"
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
    , m_ui(nullptr)
{
    m_ui = new Ui::MainWindow();
    m_ui->setupUi(this);

    connect(m_ui->pushButton_patients, &QPushButton::clicked, this, &MainWindow::patientsButtonPressed);
    connect(m_ui->pushButton_doctors, &QPushButton::clicked, this, &MainWindow::doctorsButtonPressed);
    connect(m_ui->pushButton_referral, &QPushButton::clicked, this, &MainWindow::referralsButtonPressed);
    connect(m_ui->pushButton_exit, &QPushButton::clicked, this, &MainWindow::exitButtonPressed);
    connect(this, &QWidget::destroyed, this, &MainWindow::onClose);

    if (!g_DATABASE)
        g_DATABASE = new Database();

    g_DATABASE->loadData(SAVE_FILE);
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
    this->close();
}

void MainWindow::onClose()
{
    auto res = QMessageBox::question(this, "Сохранить?", "Вы хотите сохранить изменения за текущий сеанс?");
    if (res == QMessageBox::Yes) {
        g_DATABASE->saveTo(SAVE_FILE);
    }
    if (g_DATABASE) {
        delete g_DATABASE;
        g_DATABASE = nullptr;
    }
}
