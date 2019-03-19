#ifndef NEWPATIENTWINDOW_HPP
#define NEWPATIENTWINDOW_HPP

#include "data/hospital/patient.hpp"
#include "ui_newpatient.h"

#include <QDialog>

class NewPatientWindow : public QDialog {
    Q_OBJECT
  private:
    Ui::NewPatientForm* m_ui;
    Patient             m_toEdit;
    QString             m_errMsg;

  public:
    explicit NewPatientWindow(QWidget* parent = nullptr);
    NewPatientWindow(const NewPatientWindow&) = delete;
    ~NewPatientWindow();

  public slots:
    void okButtonPressed();

  private:
    bool validate();
};

#endif // NEWPATIENTWINDOW_HPP
