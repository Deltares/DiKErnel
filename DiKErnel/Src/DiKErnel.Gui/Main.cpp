#include <QApplication>

#include "MainWindow.h"

int main(
    int argc,
    char* argv[])
{
    QApplication app(argc, argv);

    DiKErnel::Gui::MainWindow window;
    window.show();

    return app.exec();
}
