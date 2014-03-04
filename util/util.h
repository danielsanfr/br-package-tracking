#ifndef UTIL_H
#define UTIL_H

#include <QMap>
#include <QFile>
#include <QHash>
#include <QList>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QStringRef>
#include <QIODevice>
#include <QtXml/QXmlStreamReader>

namespace brpackagetracking {
namespace util {
class Util : public QObject {
    Q_OBJECT
public:
    static Util *getInstance(QObject *parent = 0) {
        static Util *util;
        if (!util)
            util = new Util(parent);
        return util;
    }
    QString serviceNameByServiceCode(QString serviceCode);
    QMap<QString, QString> countryInfosByCountryAcronym(QString countryAcronym);
signals:
public slots:
private:
    explicit Util(QObject *parent = 0);
    void loadData();
    QHash<QString, QString> m_services;
    QHash<QString, QMap<QString, QString> > m_countries;
};
}
}

#endif // UTIL_H
