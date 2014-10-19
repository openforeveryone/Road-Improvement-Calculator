#include "historylookup.h"
#include <QFile>
#include <QDebug>

HistoryLookup::HistoryLookup(QObject *parent) :
    QObject(parent)
{
    qDebug() << "HistoryLookup";
    currentroad=0;
    QString fileName = "/home/matt/hackuna/OSM/output";
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << QString("HistoryLookup: Cannot read file %1:\n%2.")
                    .arg(fileName)
                    .arg(file.errorString());
        return;
    }
    while(!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString lineString = QString(line);
        QStringList keyPair = lineString.split(',');
        QString ID = keyPair.first().trimmed();
        QString CurrentType = keyPair.last().trimmed();
        roads.insert(ID, CurrentType);
    }
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
    //Make the first request:
    makeRequest();
}

void HistoryLookup::makeRequest()
{
    QString WayID = roads.keys().at(currentroad);
    QString url = QString("http://api.openstreetmap.org/api/0.6/way/").append(WayID).append("/history");
    qDebug() << "Making Request" << currentroad << WayID  << url;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("User-Agent", "RoadImprovementCalculator 0.1");
    manager->get(request);
}


void HistoryLookup::replyFinished(QNetworkReply* reply)
{
    qDebug() << "Request Finished";
    if (reply->error())
    {
        qDebug() << "error" <<reply->errorString();
        return;
    }
    QByteArray response = reply->readAll();
    qDebug() << response;
    parse(response);
    currentroad++;
//    if (currentroad < roads.keys().count())
//        QTimer::singleShot(1000, this, SLOT(makeRequest()));
//    else
//        qDebug() << "Job Finished";
}


void HistoryLookup::parse(QByteArray data)
{
    qDebug() << "Parsing Data";
    QBuffer buffer(&data);
    xml.setDevice(&buffer);
    if (xml.readNextStartElement()) {
        if (xml.name() != "osm")
        {
            xml.raiseError(QObject::tr("The file is not an OSM file."));
            return;
        }
    }

    Q_ASSERT(xml.isStartElement() && xml.name() == "osm");
    qDebug() << xml.attributes().value("timestamp").toString();
    ways=0;
    while (xml.readNextStartElement()) {
        if (xml.name() == "way")
            readWay();
        else
            xml.skipCurrentElement();
    }

    qDebug() << "Data Parsed" << ways << "versions";

}

void HistoryLookup::readWay()
{
    qDebug() << "Way found";
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
//            if (key == "highway")
//            {
//                isRoad=true;
//                Type=value;
//            }
//            else if (key == "name")
//                Name=value;
//            else if (key == "ref")
//                Ref=value;
//            else if (key == "surface")
//            {
//                SurfaceType=value;
//                int existingCount = surfaceTypeCounts.value(value, 0);
//                surfaceTypeCounts.insert(value, existingCount+1);
////                surfaceTypeList.insert(value);
//            }
            xml.skipCurrentElement();
        }
        else
            xml.skipCurrentElement();
    }
    if (isRoad)
    {

    }
}

