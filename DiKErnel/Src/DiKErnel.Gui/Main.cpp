#include <QApplication>

#include "MainWindow.h"

using namespace DiKErnel::Gui;

int main(
    int argc,
    char* argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return QApplication::exec();
}
