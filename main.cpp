#include "sleepmonitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SleepMonitor w;
    w.show();
    return a.exec();
}
