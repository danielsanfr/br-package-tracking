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

#ifndef HTMLPARSER_H
#define HTMLPARSER_H

#include <QMap>
#include <QList>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QStringRef>
#include <QtXml/QXmlStreamReader>

#include "model/information.h"

namespace brpackagetracking {
namespace core {
class HtmlParser : public QObject {
    Q_OBJECT
public:
    explicit HtmlParser(QObject *parent = 0);
    QList< brpackagetracking::model::Information > parse(QString html);
signals:
public slots:
private:
    brpackagetracking::model::Information parseCheckpoint(QXmlStreamReader &xmlStreamReader);
    void changeFromHtmlToXml(QString html);
    QString m_xml;
};
}
}

#endif // HTMLPARSER_H
