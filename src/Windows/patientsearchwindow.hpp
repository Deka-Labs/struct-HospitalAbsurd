#ifndef PATIENTSEARCHWINDOW_HPP
#define PATIENTSEARCHWINDOW_HPP

#include "ui_searchform.h"

#include <QDialog>

class PatientSearchWindow : public QDialog {
    Q_OBJECT
  private:
    Ui::PatientSearchForm* m_ui;

  public:
    explicit PatientSearchWindow(QWidget* parent = nullptr);
    PatientSearchWindow(const PatientSearchWindow&) = delete;
    ~PatientSearchWindow();

  public slots:
    void okButtonPressed();
    void comboBoxChanged(const QString& text);

  private:
    bool validate();
};

#endif // PATIENTSEARCHWINDOW_HPP
