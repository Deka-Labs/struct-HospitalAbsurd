#ifndef NEWREFERRALWINDOW_HPP
#define NEWREFERRALWINDOW_HPP

#include "ui_newreferral.h"
#include <QDialog>
class NewReferralWindow : public QDialog {
    Q_OBJECT
private:
    Ui::NewReferralForm* m_ui;

public:
    NewReferralWindow(QWidget* widget = nullptr);
    NewReferralWindow(const NewReferralWindow&) = delete;
    ~NewReferralWindow();

public slots:
    void okButtonPressed();

private:
    bool validate();
};

#endif // NEWREFERRALWINDOW_HPP
