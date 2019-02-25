#include "doctorlistwindow.hpp"
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
}

DoctorListWindow::~DoctorListWindow()
{
    delete m_ui;
}

void DoctorListWindow::addButtonPressed()
{
    NewDoctorWindow wnd(this);
    auto code = wnd.exec();
    if (code == QDialog::Accepted) {
        //TODO! add to database
    }
}

void DoctorListWindow::deleteButtonPressed()
{
    if (QMessageBox::question(this, "Удалить?", "Вы действительно хотите удалить эту запись?") == QMessageBox::Yes) {
        //TODO! Delete from database selected
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
        //TODO! Delete from database all
    }
}

void DoctorListWindow::helpButtonPressed()
{
    //TODO! HEEEEEEEELP ME
}
