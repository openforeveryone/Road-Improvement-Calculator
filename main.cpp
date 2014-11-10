#include <QCoreApplication>
#include "SchoolFander.h"
#include "roadfinder.h"
#include "historylookup.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString filename = a.arguments().first();
//    QString filename = "/home/matt/hackuna/OSM/congo-democratic-republic-latest.osm";
//    QString filename = "/home/matt/hackuna/OSM/TheHague.osm";
//    QString filename = "/home/matt/hackuna/OSM/Kigoma.osm";
//    QString filename = "/home/matt/hackuna/OSM/Uvinza.osm";
//    QString filename = "/home/matt/hackuna/OSM/Mpanda.osm";
    qDebug() << "About to process" << filename;
    RoadFinder parser(filename, true);
    HistoryLookup lookup(true);
    return a.exec();
}
