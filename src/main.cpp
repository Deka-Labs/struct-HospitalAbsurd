
#include "Windows/MainWindow.hpp"
#include <QApplication>
#include <QMessageBox>

Database* g_DATABASE = nullptr;

int main(int argc, char** argv)
{
    try {
        QApplication app(argc, argv);

        MainWindow wnd;
        wnd.show();

        return app.exec();
    } catch (std::exception& e) {
        QMessageBox::critical(nullptr, "Критическая ошибка!", "Необработаное исключение: " + QString(e.what()));
    }
}
