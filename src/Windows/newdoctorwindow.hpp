#ifndef NEWDOCTORWINDOW_HPP
#define NEWDOCTORWINDOW_HPP

#include "data/hospital/doctor.hpp"
#include "ui_newdoctor.h"
#include <QDialog>

class NewDoctorWindow : public QDialog {
    Q_OBJECT
private:
    Ui::NewDoctorForm* m_ui;
    Doctor m_toEdit;
    QString m_errMsg;

public:
    explicit NewDoctorWindow(QWidget* parent = nullptr);
    NewDoctorWindow(const NewDoctorWindow&) = delete;
    ~NewDoctorWindow();

public slots:
    void okButtonPressed();

private:
    bool validate();
};

#endif // NEWDOCTORWINDOW_HPP
