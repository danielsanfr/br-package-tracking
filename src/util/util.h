/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: util,h
 *     Author: daniel
 * Created on: 23/12/2014
 *    Version:
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
 *
 ***************************************************************************/

#ifndef UTIL_H
#define UTIL_H

#include <QMap>
#include <QHash>
#include <QObject>
#include <QString>
#include <QPointer>
#include <QVariant>
#include <QStringList>

#include <functional>

namespace brpackagetracking {
namespace util {

class Util : public QObject {
    Q_OBJECT
public:
    /**
     * @brief instance
     * @return A singleton instance of this class.
     * This method is based on QTestRootObject:
     * {PATH_TO_QT}/Qt{VERION}/{VERSION}/Src/qtdeclarative/src/qmltest/quicktest.cpp
     */
    inline static Util *instance() {
        static QPointer<Util> s_instance = new Util;
        if (!s_instance)
            s_instance = new Util;
        return s_instance;
    }
//    static Util *instance(QObject *parent = 0) {
//        static Util *util;
//        if (!util)
//            util = new Util(parent);
//        return util;
//    }
    void debug(const char *file, const char *func, int line, const QVariant &message);
    QString serviceNameByCode(const QString &serviceCode);
    QMap<QString, QString> countryInfosByAcronym(const QString &countryAcronym);
signals:
public slots:
private:
    Util();
    bool loadServices();
    bool loadCountriesInfos();
    QString loadFile(const QString &fileName);
    void parseXml(const QString &xml, std::function<void(const QStringList &)> populateHash);
    QHash<QString, QString> m_services;
    QHash<QString, QMap<QString, QString> > m_countries;
};

}
}

#endif // UTIL_H
