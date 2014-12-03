#include "roadfinder.h"
#include <QDebug>
#include <QMap>
#include <QStringList>

RoadFinder::RoadFinder(QString fileName, bool useTypes, QObject *parent) :
    QObject(parent)
{
    this->useTypes=useTypes;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << QString("Cannot read file %1:\n%2.")
                    .arg(fileName)
                    .arg(file.errorString());
        return;
    }
    QString outputFilename("./output");
    output.setFileName(outputFilename);
    if (!output.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << QString("Cannot read file %1:\n%2.")
                    .arg(outputFilename)
                    .arg(file.errorString());
        return;
    }
    xml.setDevice(&file);
    if (xml.readNextStartElement()) {
        if (xml.name() == "osm")
            readXML();
        else
            xml.raiseError(QObject::tr("The file is not an OSM file."));
    }
    output.close();
}


void RoadFinder::readXML()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "osm");
    qDebug() << xml.attributes().value("timestamp").toString();
    nodes=0;
    ways=0;
    roads=0;
    pavedroads=0;
    while (xml.readNextStartElement()) {
        if (xml.name() == "node")
            readNode();
        else if (xml.name() == "way")
            readWay();
        else
            xml.skipCurrentElement();
    }

    qDebug() << roads;
    qDebug() << roadTypeCounts;
    qDebug() << surfaceTypeCounts;
    qDebug() << "Finished";
}

void RoadFinder::readNode()
{
    nodes++;
    if (nodes%10000 == 0)
        qDebug() << nodes << "nodes";
    while (xml.readNextStartElement()) {
//        qDebug() << xml.name();
        if (xml.name() == "tag")
        {
//            QString key = xml.attributes().value("k").toString();
//            QString value = xml.attributes().value("v").toString();
//            if (value == "school")
//                isSchool=true;
//            if (key == "name")
//                Name=value;
            xml.skipCurrentElement();
        }
        else
            xml.skipCurrentElement();
    }
//    if (isSchool)
//    {
////        qDebug() << "School Found" << Name;
//        schoolList.insert(Name);
//    }
//    qDebug() <<"test" << xml.name();
}

void RoadFinder::readWay()
{
    ways++;
//    if (ways%1000 == 0)
//        qDebug() << ways << "ways";
    QMap<QString, QString> tags;
    bool isRoad;
    QString Type;
    QString SurfaceType;
    QString Name;
    QString Ref;
    QString id = xml.attributes().value("id").toString();
    while (xml.readNextStartElement()) {
//        qDebug() <<xml.name();
        if (xml.name() == "tag")
        {
            QString key = xml.attributes().value("k").toString();
            QString value = xml.attributes().value("v").toString();
            if (key == "highway")
            {
                isRoad=true;
                Type=value;
            }
            else if (key == "name")
                Name=value;
            else if (key == "ref")
                Ref=value;
            else if (key == "surface")
            {
                SurfaceType=value;
                int existingCount = surfaceTypeCounts.value(value, 0);
                surfaceTypeCounts.insert(value, existingCount+1);
//                surfaceTypeList.insert(value);
            }
            xml.skipCurrentElement();
        }
        else
            xml.skipCurrentElement();
    }
    if (isRoad)
    {
//        qDebug() << "Road Found" << Type;
//        roadTypeList.insert(Type);
        int existingCount = roadTypeCounts.value(Type, 0);
        roadTypeCounts.insert(Type, existingCount+1);
        roads++;
        if (!useTypes && (SurfaceType=="asphalt" || SurfaceType=="paved"))
        {
            pavedroads++;
            QString outputLine = id.append(", ").append(SurfaceType).append("\r\n");
            qDebug() << outputLine;
            output.write(outputLine.toUtf8());
        }
        if (useTypes)
        {
            QStringList allowedTypes;
            allowedTypes << "primary"<< "residential" << "road"<<"secondary" << "service"<< "tertiary" << "trunk";
            if (allowedTypes.contains(Type))
            {
                QString outputLine = id.append(", ").append(Type).append("\r\n");
                qDebug() << outputLine;
                output.write(outputLine.toUtf8());
            }
        }
    }
}
