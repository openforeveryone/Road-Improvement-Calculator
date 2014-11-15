#include <QCoreApplication>
#include "SchoolFander.h"
#include "roadfinder.h"
#include "historylookup.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filename = a.arguments().first();
    qDebug() << "About to process" << filename;
    RoadFinder parser(filename, true);
    HistoryLookup lookup(true);
    return a.exec();
}
