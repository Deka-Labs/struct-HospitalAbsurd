#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "ui_mainwindow.h"
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT
private:
    Ui::MainWindow* m_ui;

public:
    MainWindow(QWidget* parent = nullptr);
    MainWindow(const MainWindow&) = delete;
    ~MainWindow();

public slots:
    void patientsButtonPressed();
    void doctorsButtonPressed();
    void referralsButtonPressed();
    void exitButtonPressed();
};

#endif //!MAINWINDOW_HPP
