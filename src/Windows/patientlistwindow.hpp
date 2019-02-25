#ifndef PATIENTLISTWINDOW_HPP
#define PATIENTLISTWINDOW_HPP

#include "ui_listview.h"
#include <QDialog>

class PatientListWindow : public QDialog {
    Q_OBJECT
private:
    Ui::ListForm* m_ui;

public:
    PatientListWindow(QWidget* parent = nullptr);
    PatientListWindow(const PatientListWindow&) = delete;
    ~PatientListWindow();

public slots:
    void addButtonPressed();
    void deleteButtonPressed();
    void searchButtonPressed();
    void purgeAllButtonPressed();
    void helpButtonPressed();
};

#endif // PATIENTLISTWINDOW_HPP
