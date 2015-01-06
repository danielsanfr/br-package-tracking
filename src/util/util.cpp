/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: util,cpp
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

#include "util.h"

#include <QFile>
#include <QDebug>
#include <QStringRef>
#include <QXmlStreamReader>

namespace brpackagetracking {
namespace util {

Util::Util() :
    QObject()
{
    if (loadServices() && loadCountriesInfos())
        debug(__FILE__, __func__, __LINE__, "Successfully started");
    else
        debug(__FILE__, __func__, __LINE__, "It was not successfully initialized");
}

void Util::debug(const char *file, const char *func, int line, const QVariant &message)
{
    QStringList fileSplited = QString::fromLatin1(file).split('/');
    QString msg = "[File: " + fileSplited.at(fileSplited.size() -1) + " | Method: "
            + QString::fromLatin1(func) + " | Line: " + QString::number(line) + ']';
    qDebug() << msg << message;
}

QString Util::serviceNameByCode(const QString &serviceCode)
{
    return m_services.take(serviceCode);
}

QMap<QString, QString> Util::countryInfosByAcronym(const QString &countryAcronym)
{
    return m_countries.take(countryAcronym);
}

bool Util::loadServices()
{
    QString servicesXml = loadFile(":/post-office-sevices.xml");
    if (servicesXml.isEmpty())
        return false;

    parseXml(servicesXml, [this] (const QStringList &stringList) -> void {
        m_services.insert(stringList.at(0), stringList.at(1));
    });

    return true;
}

bool Util::loadCountriesInfos()
{
    QString contriesXml = loadFile(":/countries-infos.xml");
    if (contriesXml.isEmpty())
        return false;

    parseXml(contriesXml, [this] (const QStringList &stringList) -> void {
        QMap<QString, QString> countryMap;
        countryMap.insert("ord", stringList.at(0));
        countryMap.insert("country_name", stringList.at(1));
        countryMap.insert("triple_acronym", stringList.at(3));
        countryMap.insert("code", stringList.at(4));
        m_countries.insert(stringList.at(2), countryMap);
    });

    return true;
}

QString Util::loadFile(const QString &fileName)
{
    QFile file(fileName);
    QString xml;

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        while (!file.atEnd())
            xml.append(file.readLine());
    }

    return xml;
}

void Util::parseXml(const QString &xml, std::function<void (const QStringList &)> populateHash)
{
    QXmlStreamReader xmlStreamReader(xml);
    while (!xmlStreamReader.atEnd() && !xmlStreamReader.hasError()) {
        /* Read next element.*/
        QXmlStreamReader::TokenType token = xmlStreamReader.readNext();
        /* If token is just StartDocument, we'll go to next.*/
        if(token == QXmlStreamReader::StartDocument) {
            continue;
        }
        /* If token is StartElement, we'll see if we can read it.*/
        if(token == QXmlStreamReader::StartElement) {
            /* If it's named persons, we'll go to the next.*/
            if(xmlStreamReader.name().compare("table", Qt::CaseInsensitive) == 0) {
                continue;
            }
            /* If it's named person, we'll dig the information from there.*/
            if(xmlStreamReader.name().compare("tr", Qt::CaseInsensitive) == 0) {
                xmlStreamReader.readNext();
                QStringList stringList;
                while(!(xmlStreamReader.tokenType() == QXmlStreamReader::EndElement &&
                        xmlStreamReader.name().compare("tr", Qt::CaseInsensitive) == 0)) {// && i < 2) {
                    if(xmlStreamReader.tokenType() == QXmlStreamReader::StartElement) {
                        xmlStreamReader.readNext();
                        stringList << xmlStreamReader.text().toString();
                    }
                    xmlStreamReader.readNext();
                }
                populateHash(stringList);
            }
        }
    }
}

}
}
