#ifndef NEWPATIENTWINDOW_HPP
#define NEWPATIENTWINDOW_HPP

#include "ui_newpatient.h"
#include <QDialog>

class NewPatientWindow : public QDialog {
    Q_OBJECT
private:
    Ui::NewPatientForm* m_ui;

public:
    NewPatientWindow(QWidget* parent = nullptr);
    NewPatientWindow(const NewPatientWindow&) = delete;
    ~NewPatientWindow();

public slots:
    void okButtonPressed();

private:
    bool validate();
};

#endif // NEWPATIENTWINDOW_HPP
