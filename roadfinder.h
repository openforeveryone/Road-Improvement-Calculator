#ifndef ROADFINDER_H
#define ROADFINDER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QSet>
#include <QMap>
#include <QFile>

class RoadFinder : public QObject
{
    Q_OBJECT
public:
    explicit RoadFinder(QString fileName, bool useTypes, QObject *parent = 0);
private:
    void readXML();
    void readNode();
    void readWay();
    int nodes;
    int ways;
    int roads;
    int pavedroads;
    QSet<QString> roadTypeList;
    QMap<QString, int> roadTypeCounts;
    QSet<QString> surfaceTypeList;
    QMap<QString, int> surfaceTypeCounts;
    QXmlStreamReader xml;
    QFile output;
    bool useTypes;

signals:

public slots:

};

#endif // ROADFINDER_H
