#ifndef DOCTORSEARCHWINDOW_HPP
#define DOCTORSEARCHWINDOW_HPP

#include "ui_searchform.h"

#include <QDialog>

class DoctorSearchWindow : public QDialog {
    Q_OBJECT
  private:
    Ui::PatientSearchForm* m_ui;

  public:
    explicit DoctorSearchWindow(QWidget* parent = nullptr);
    DoctorSearchWindow(const DoctorSearchWindow&) = delete;
    ~DoctorSearchWindow();

  public slots:

    void okButtonPressed();
    void comboBoxChanged(const QString& text);

  private:
    bool validate();
};

#endif // DOCTORSEARCHWINDOW_HPP
