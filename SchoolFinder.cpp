
#include <QFile>
#include <QDebug>
#include <QMap>
#include "SchoolFander.h"

SchoolFinder::SchoolFinder(QString fileName, QObject *parent) :
    QObject(parent)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << QString("Cannot read file %1:\n%2.")
                    .arg(fileName)
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
}

void SchoolFinder::readXML()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == "osm");
    qDebug() << xml.attributes().value("timestamp").toString();
    nodes=0;
    ways=0;
    while (xml.readNextStartElement()) {
        if (xml.name() == "node")
            readNode();
        else if (xml.name() == "way")
            readWay();
        else
            xml.skipCurrentElement();
    }

    qDebug() << schoolList;
    qDebug() << schoolList.count();
    qDebug() << "Finished";
}

void SchoolFinder::readNode()
{
    nodes++;
//    if (nodes%10000 == 0)
//        qDebug() << nodes << "nodes";
    bool isSchool;
    QString Name;
    while (xml.readNextStartElement()) {
//        qDebug() << xml.name();
        if (xml.name() == "tag")
        {
            QString key = xml.attributes().value("k").toString();
            QString value = xml.attributes().value("v").toString();
            if (value == "school")
                isSchool=true;
            if (key == "name")
                Name=value;
            xml.skipCurrentElement();
        }
        else
            xml.skipCurrentElement();
    }
    if (isSchool)
    {
        qDebug() << "School Found" << Name;
        schoolList.insert(Name);
    }
//    qDebug() <<"test" << xml.name();
}

void SchoolFinder::readWay()
{
    ways++;
    if (ways%1000 == 0)
        qDebug() << ways << "ways";
//    qDebug() << "way";
    QMap<QString, QString> tags;
    bool isSchool;
    QString Name;
    while (xml.readNextStartElement()) {
//        qDebug() <<xml.name();
        if (xml.name() == "tag")
        {
            QString key = xml.attributes().value("k").toString();
            QString value = xml.attributes().value("v").toString();
            if (value == "school")
                isSchool=true;
            xml.skipCurrentElement();
        }
        else
            xml.skipCurrentElement();
    }
    if (isSchool)
        qDebug() << "School Found" << Name;
}
