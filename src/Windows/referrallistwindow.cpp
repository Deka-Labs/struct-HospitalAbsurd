#include "referrallistwindow.hpp"
#include "newreferralwindow.hpp"
#include <QMessageBox>

ReferralListWindow::ReferralListWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr)
{
    m_ui = new Ui::ReferralsForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_add, &QPushButton::clicked, this, &ReferralListWindow::addButtonPressed);
    connect(m_ui->pushButton_remove, &QPushButton::clicked, this, &ReferralListWindow::deleteButtonPressed);
}

ReferralListWindow::~ReferralListWindow()
{
    delete m_ui;
}

void ReferralListWindow::addButtonPressed()
{
    NewReferralWindow wnd(this);
    auto code = wnd.exec();
    if (code == QDialog::Accepted) {
        //TODO! add to database
    }
}

void ReferralListWindow::deleteButtonPressed()
{
    if (QMessageBox::question(this, "Удалить?", "Вы действительно хотите удалить эту запись?") == QMessageBox::Yes) {
        //TODO! Delete from database selected
    }
}
