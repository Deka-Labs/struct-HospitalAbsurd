#ifndef NEWDOCTORWINDOW_HPP
#define NEWDOCTORWINDOW_HPP

#include "ui_newdoctor.h"
#include <QDialog>

class NewDoctorWindow : public QDialog {
    Q_OBJECT
private:
    Ui::NewDoctorForm* m_ui;

public:
    NewDoctorWindow(QWidget* parent = nullptr);
    NewDoctorWindow(const NewDoctorWindow&) = delete;
    ~NewDoctorWindow();

public slots:
    void okButtonPressed();

private:
    bool validate();
};

#endif // NEWDOCTORWINDOW_HPP
