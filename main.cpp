#include "cluttermask.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClutterMask w;

    w.show();
    return a.exec();
}
