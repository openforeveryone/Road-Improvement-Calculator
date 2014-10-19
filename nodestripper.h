#ifndef NODESTRIPPER_H
#define NODESTRIPPER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QSet>

class NodeStripper : public QObject
{
    Q_OBJECT
public:
    explicit NodeStripper(QString fileName, QObject *parent = 0);
    void readXML();
    void readNode();
    void readWay();
    int nodes;
    int ways;
    QSet<QString> schoolList;
    QXmlStreamReader xml;
signals:

public slots:

};

#endif // NODESTRIPPER_H
