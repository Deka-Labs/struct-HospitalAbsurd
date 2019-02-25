#include "patientlistwindow.hpp"
#include "newpatientwindow.hpp"
#include "patientsearchwindow.hpp"
#include <QMessageBox>
#include <stdexcept>

PatientListWindow::PatientListWindow(QWidget* parent)
    : QDialog(parent)

    , m_ui(nullptr)
{
    m_ui = new Ui::ListForm();
    m_ui->setupUi(this);

    //TODO! set model for tableView
    this->setWindowTitle("Список больных");

    connect(m_ui->pushButton_add, &QPushButton::clicked, this, &PatientListWindow::addButtonPressed);
    connect(m_ui->pushButton_delete, &QPushButton::clicked, this, &PatientListWindow::deleteButtonPressed);
    connect(m_ui->pushButton_search, &QPushButton::clicked, this, &PatientListWindow::searchButtonPressed);
    connect(m_ui->pushButton_purgeAll, &QPushButton::clicked, this, &PatientListWindow::purgeAllButtonPressed);
    connect(m_ui->pushButton_help, &QPushButton::clicked, this, &PatientListWindow::helpButtonPressed);
}

PatientListWindow::~PatientListWindow()
{
    delete m_ui;
}

void PatientListWindow::addButtonPressed()
{
    NewPatientWindow wnd(this);
    auto code = wnd.exec();
    if (code == QDialog::Accepted) {
        //TODO! add to database
    }
}

void PatientListWindow::deleteButtonPressed()
{
    if (QMessageBox::question(this, "Удалить?", "Вы действительно хотите удалить эту запись?") == QMessageBox::Yes) {
        //TODO! Delete from database selected
    }
}

void PatientListWindow::searchButtonPressed()
{
    PatientSearchWindow wnd(this);
    wnd.exec();
}

void PatientListWindow::purgeAllButtonPressed()
{
    if (QMessageBox::question(this, "Очистить все?", "Вы действительно хотите удалить все записи?") == QMessageBox::Yes) {
        //TODO! Delete from database all
    }
}

void PatientListWindow::helpButtonPressed()
{
    //TODO! HEEEEEEEELP ME
}
