#ifndef HISTORYLOOKUP_H
#define HISTORYLOOKUP_H

#include <QObject>
#include <QStringList>
#include <QPair>
#include <QMap>
#include <QtNetwork>
#include <QXmlStreamReader>

class HistoryLookup : public QObject
{
    Q_OBJECT
public:
    explicit HistoryLookup(bool useTypes, QObject *parent = 0);
    QMap<QString, QString> roads;
    void parse(QByteArray data);
    void readWay();
    int ways;
    QStringList upgradedRoads;
    bool useTypes;
private:
    QNetworkAccessManager *manager;
    int currentroad;
    QXmlStreamReader xml;
signals:

public slots:
    void replyFinished(QNetworkReply *reply);
    void makeRequest();

};

#endif // HISTORYLOOKUP_H
