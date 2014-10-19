#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include <QSet>

class SchoolFinder : public QObject
{
    Q_OBJECT
    void readXML();
    void readNode();
    void readWay();
    int nodes;
    int ways;
    QSet<QString> schoolList;
    QXmlStreamReader xml;
public:
    explicit SchoolFinder(QString fileName, QObject *parent = 0);
signals:

public slots:

};

#endif // PARSER_H
