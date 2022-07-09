#include <QApplication>
#include "ChessGUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChessGUI w;
    w.show();

    return QApplication::exec();
}
