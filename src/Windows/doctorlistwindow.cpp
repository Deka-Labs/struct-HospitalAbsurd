#include "doctorlistwindow.hpp"
#include "../globaldatabase.hpp"
#include "doctorsearchwindow.hpp"
#include "newdoctorwindow.hpp"
#include <QMessageBox>

DoctorListWindow::DoctorListWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
{
    m_ui = new Ui::ListForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_add, &QPushButton::clicked, this, &DoctorListWindow::addButtonPressed);
    connect(m_ui->pushButton_delete, &QPushButton::clicked, this, &DoctorListWindow::deleteButtonPressed);
    connect(m_ui->pushButton_search, &QPushButton::clicked, this, &DoctorListWindow::searchButtonPressed);
    connect(m_ui->pushButton_purgeAll, &QPushButton::clicked, this, &DoctorListWindow::purgeAllButtonPressed);
    connect(m_ui->pushButton_help, &QPushButton::clicked, this, &DoctorListWindow::helpButtonPressed);

    this->setWindowTitle("Список врачей");
    m_ui->tableView->setModel(&g_DATABASE->getDoctorsModel());
    m_ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

DoctorListWindow::~DoctorListWindow()
{
    delete m_ui;
}

void DoctorListWindow::addButtonPressed()
{
    Doctor doc;
    NewDoctorWindow wnd(doc, this);
    auto code = wnd.exec();
    if (code == QDialog::Accepted) {
        g_DATABASE->addDoctor(doc);
    }
}

void DoctorListWindow::deleteButtonPressed()
{
    auto index = m_ui->tableView->currentIndex();
    if (index.isValid()) {
        if (QMessageBox::question(this, "Удалить?", "Вы действительно хотите удалить эту запись?") == QMessageBox::Yes) {
            auto toDel = g_DATABASE->getDoctorsModel().getDoctor(index);
            g_DATABASE->delDoctor(toDel.key());
        }
    } else {
        QMessageBox::warning(this, "Неверное действие.", "Необходмо выбрать элемент для удаления.");
    }
}

void DoctorListWindow::searchButtonPressed()
{
    DoctorSearchWindow wnd(this);
    wnd.exec();
}

void DoctorListWindow::purgeAllButtonPressed()
{
    if (QMessageBox::question(this, "Очистить все?", "Вы действительно хотите удалить все записи?") == QMessageBox::Yes) {
        g_DATABASE->delAllDoctors();
    }
}

void DoctorListWindow::helpButtonPressed()
{
    //TODO! HEEEEEEEELP ME
}
