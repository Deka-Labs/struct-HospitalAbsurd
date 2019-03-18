#ifndef REFERRALLISTWINDOW_HPP
#define REFERRALLISTWINDOW_HPP

#include "ui_referralslist.h"
#include <QDialog>

class ReferralListWindow : public QDialog {
    Q_OBJECT
private:
    Ui::ReferralsForm* m_ui;

public:
    explicit ReferralListWindow(QWidget* parent = nullptr);
    ReferralListWindow(const ReferralListWindow&) = delete;
    ~ReferralListWindow();

public slots:
    void addButtonPressed();
    void deleteButtonPressed();
};

#endif // REFERRALLISTWINDOW_HPP
