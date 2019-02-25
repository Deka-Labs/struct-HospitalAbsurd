#ifndef DOCTORLISTWINDOW_HPP
#define DOCTORLISTWINDOW_HPP

#include "ui_listview.h"
#include <QDialog>

class DoctorListWindow : public QDialog {
    Q_OBJECT
private:
    Ui::ListForm* m_ui;

public:
    DoctorListWindow(QWidget* parent = nullptr);
    DoctorListWindow(const DoctorListWindow&) = delete;
    ~DoctorListWindow();

public slots:
    void addButtonPressed();
    void deleteButtonPressed();
    void searchButtonPressed();
    void purgeAllButtonPressed();
    void helpButtonPressed();
};

#endif // DOCTORLISTWINDOW_HPP