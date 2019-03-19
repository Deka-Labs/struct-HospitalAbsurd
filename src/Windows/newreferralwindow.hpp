#ifndef NEWREFERRALWINDOW_HPP
#define NEWREFERRALWINDOW_HPP

#include "data/hospital/referral.hpp"
#include "ui_newreferral.h"

#include <QDialog>

class NewReferralWindow : public QDialog {
    Q_OBJECT
  private:
    Ui::NewReferralForm* m_ui;
    Referral             m_toEdit;
    QString              m_errMsg;

  public:
    explicit NewReferralWindow(QWidget* widget = nullptr);
    NewReferralWindow(const NewReferralWindow&) = delete;
    ~NewReferralWindow();

  public slots:
    void okButtonPressed();

  private:
    bool validate();
};

#endif // NEWREFERRALWINDOW_HPP
