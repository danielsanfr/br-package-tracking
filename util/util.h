/* Copyright (c) 2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
