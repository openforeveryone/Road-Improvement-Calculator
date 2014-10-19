#include <QCoreApplication>
#include "SchoolFander.h"
#include "roadfinder.h"
#include "historylookup.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    QString filename = "/home/matt/hackuna/OSM/congo-democratic-republic-latest.osm";
//    QString filename = "/home/matt/hackuna/OSM/TheHague.osm";
    QString filename = "/home/matt/hackuna/OSM/Kigoma.osm";
//    RoadFinder parser(filename);
      HistoryLookup lookup;
    return a.exec();
}
