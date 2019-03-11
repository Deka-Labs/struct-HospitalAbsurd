#include "patientlistwindow.hpp"
#include "../globaldatabase.hpp"
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

    m_ui->tableView->setModel(&g_DATABASE->getPatientsModel());
    m_ui->tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
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
    Patient newPat;
    NewPatientWindow wnd(newPat, this);
    auto code = wnd.exec();
    if (code == QDialog::Accepted) {
        g_DATABASE->addPatient(newPat);
    }
}

void PatientListWindow::deleteButtonPressed()
{
    auto index = m_ui->tableView->currentIndex();
    if (index.isValid()) {
        if (QMessageBox::question(this, "Удалить?", "Вы действительно хотите удалить эту запись?") == QMessageBox::Yes) {
            auto toDel = g_DATABASE->getPatientsModel().getPatient(index);
            g_DATABASE->delPatinet(toDel.key());
        }
    } else {
        QMessageBox::warning(this, "Неверное действие.", "Необходмо выбрать элемент для удаления.");
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
        g_DATABASE->delAllPatients();
    }
}

void PatientListWindow::helpButtonPressed()
{
    //TODO! HEEEEEEEELP ME
}
