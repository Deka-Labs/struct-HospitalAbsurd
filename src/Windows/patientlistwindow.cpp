#include "patientlistwindow.hpp"

#include "../globaldatabase.hpp"
#include "newpatientwindow.hpp"
#include "patientsearchwindow.hpp"

#include <QMessageBox>
#include <stdexcept>

PatientListWindow::PatientListWindow(QWidget* parent)
    : QDialog(parent)

    , m_ui(nullptr) {
    m_ui = new Ui::ListForm();
    m_ui->setupUi(this);

    m_ui->tableView->setModel(&g_DATABASE->getPatientsModel());
    m_ui->tableView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(m_ui->pushButton_add, &QPushButton::clicked, this, &PatientListWindow::addButtonPressed);
    connect(m_ui->pushButton_delete, &QPushButton::clicked, this, &PatientListWindow::deleteButtonPressed);
    connect(m_ui->pushButton_search, &QPushButton::clicked, this, &PatientListWindow::searchButtonPressed);
    connect(m_ui->pushButton_purgeAll, &QPushButton::clicked, this, &PatientListWindow::purgeAllButtonPressed);
}

PatientListWindow::~PatientListWindow() {
    delete m_ui;
}

void PatientListWindow::addButtonPressed() {
    NewPatientWindow wnd(this);
    wnd.exec();
}

void PatientListWindow::deleteButtonPressed() {
    auto index = m_ui->tableView->currentIndex();
    if (index.isValid()) {
        if (QMessageBox::question(this, "Удалить?", "Вы действительно хотите удалить эту запись?") ==
            QMessageBox::Yes) {
            auto toDel = g_DATABASE->getPatientsModel().getPatient(index);
            g_DATABASE->delPatinet(toDel.key());
        }
    } else {
        QMessageBox::warning(this, "Неверное действие.", "Необходимо выбрать элемент для удаления.");
    }
}

void PatientListWindow::searchButtonPressed() {
    PatientSearchWindow wnd(this);
    wnd.exec();
}

void PatientListWindow::purgeAllButtonPressed() {
    if (QMessageBox::question(this, "Очистить все?", "Вы действительно хотите удалить все записи?") ==
        QMessageBox::Yes) {
        g_DATABASE->delAllPatients();
    }
}
