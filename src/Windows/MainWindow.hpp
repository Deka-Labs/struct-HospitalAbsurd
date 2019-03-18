#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "../globaldatabase.hpp"
#include "database.hpp"
#include "ui_mainwindow.h"
#include <QWidget>

#define SAVE_FILE "db"

class MainWindow : public QWidget {
    Q_OBJECT
private:
    Ui::MainWindow* m_ui;

public:
    explicit MainWindow(QWidget* parent = nullptr);
    MainWindow(const MainWindow&) = delete;
    ~MainWindow();

public slots:
    void patientsButtonPressed();
    void doctorsButtonPressed();
    void referralsButtonPressed();
    void exitButtonPressed();

    void onClose();
};

#endif //!MAINWINDOW_HPP
