#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <QMap>
#include <QList>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QStringRef>
#include <QtXml/QXmlStreamReader>

#include "packageinfomodel.h"

class HtmlParser : public QObject
{
    Q_OBJECT
public:
    explicit HtmlParser(QObject *parent = 0);
    QList< PackageInfoModel > parse(QString html);
signals:
public slots:
private:
    PackageInfoModel parseCheckpoint(QXmlStreamReader &xmlStreamReader);
    void changeFromHtmlToXml(QString html);
    QString m_xml;
};

#endif // HTMLPARSER_H
