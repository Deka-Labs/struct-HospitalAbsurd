#include "referrallistwindow.hpp"

#include "../globaldatabase.hpp"
#include "data/hospital/referral.hpp"
#include "newreferralwindow.hpp"

#include <QMessageBox>

ReferralListWindow::ReferralListWindow(QWidget* parent)
    : QDialog(parent)
    , m_ui(nullptr) {
    m_ui = new Ui::ReferralsForm;
    m_ui->setupUi(this);

    connect(m_ui->pushButton_add, &QPushButton::clicked, this, &ReferralListWindow::addButtonPressed);
    connect(m_ui->pushButton_remove, &QPushButton::clicked, this, &ReferralListWindow::deleteButtonPressed);

    m_ui->tableView->setModel(&g_DATABASE->getReferralsModel());
    m_ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

ReferralListWindow::~ReferralListWindow() {
    delete m_ui;
}

void ReferralListWindow::addButtonPressed() {
    NewReferralWindow wnd(this);
    wnd.exec();
}

void ReferralListWindow::deleteButtonPressed() {
    auto index = m_ui->tableView->currentIndex();
    if (index.isValid()) {
        if (QMessageBox::question(this, "Удалить?", "Вы действительно хотите удалить эту запись?") ==
            QMessageBox::Yes) {
            auto ref = g_DATABASE->getReferralsModel().getReferral(index);
            g_DATABASE->delReferral(ref);
        }
    } else {
        QMessageBox::warning(this, "Неверное действие.", "Необходимо выбрать элемент для удаления.");
    }
}
