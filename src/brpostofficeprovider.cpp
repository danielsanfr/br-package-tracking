/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: brpostofficeprovider.cpp
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

#include "brpostofficeprovider.h"

#include <QUrl>
#include <QMap>
#include <QDebug>
#include <QDateTime>
#include <QStringRef>

#include "util/downloadhtml.h"

#define BR_POST_OFFICE_URL QString("http://websro.correios.com.br/sro_bin/txect01$.QueryList?P_ITEMCODE=&P_LINGUA=001&P_TESTE=&P_TIPO=001&P_COD_UNI=")
#define BR_POST_OFFICE_URL_M QString("http://websro.correios.com.br/sro_bin/txect01$.QueryList?P_LINGUA=001&P_TIPO=001&P_COD_UNI=")

namespace brpackagetracking {

using namespace util;

BrPostOfficeProvider::BrPostOfficeProvider(QObject *parent) : ShippingCarrierProvider(parent)
{
    m_download = new DownloadHtml(this);
    bool ok = connect(m_download, &DownloadHtml::downloadError,
                      this, &BrPostOfficeProvider::onDownloadError);
    Q_ASSERT(ok);
    ok = connect(m_download, &DownloadHtml::donwloadFinished,
                 this, &BrPostOfficeProvider::onDownloadFinished);
    Q_ASSERT(ok);
}

BrPostOfficeProvider::~BrPostOfficeProvider()
{
}

bool BrPostOfficeProvider::getCheckpoints(const QString &code)
{
    if (code.isEmpty())
        return false;
    m_code = code;
    m_download->download(QUrl(BR_POST_OFFICE_URL.append(m_code)));
    return true;
}

void BrPostOfficeProvider::onDownloadError(QString error)
{
}

void BrPostOfficeProvider::onDownloadFinished(QString html)
{
    if (html.isEmpty()) {
        return;
    }

    QString xml = convertHtmlToXml(html);
    if (xml.isEmpty()) {
        return;
    }
    QList<Checkpoint> checkpoints;
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
            if(xmlStreamReader.name() == "table") {
                continue;
            }
            /* If it's named person, we'll dig the information from there.*/
            if(xmlStreamReader.name() == "tr") {
                checkpoints.append(parseCheckpoint(xmlStreamReader));
            }
        }
    }

    checkpoints.removeAt(0);
    int length = checkpoints.length();
    for (int i = length - 1; i > 0; --i) {
        if (checkpoints.at(i).dateTime().isValid())
            continue;
        Checkpoint checkpoint = checkpoints.at(i);
        checkpoint.setDateTime(checkpoints.at(i - 1).dateTime());
        checkpoint.setLocation(checkpoints.at(i - 1).location());
        checkpoints.replace(i, checkpoint);
    }

    Q_EMIT finished(checkpoints);
}

QString BrPostOfficeProvider::convertHtmlToXml(const QString &html)
{
    QString xml = html;
    // ============== remove espacos em braco do html ==============
    xml.replace("\n", "");
    // ============== remove partes inrelevantes do html ==============
    {
        int posInit = xml.indexOf("<table", Qt::CaseInsensitive);
        int posEnd = xml.indexOf("</table>", posInit, Qt::CaseInsensitive);
        QStringRef subString(new QString(xml), posInit, 8 + posEnd - posInit);
        xml.clear();
        xml.append(subString.toString());
    }
    // ============== remove partes inrelevantes do html ==============
    {
        int posInit = xml.indexOf("><", Qt::CaseInsensitive);
        int posEnd = xml.indexOf("<tr>", posInit, Qt::CaseInsensitive);
        xml.replace(posInit + 1, posEnd - (posInit + 1), "");
    }
    // ============== remove atributos inrelevantes do html ==============
    {
        int lenght = xml.length();
        for (int i = 0; i < lenght; ++i) {
            if (xml.at(i) == '<') {
                bool haveAttributes = false;
                int index = -1;
                for (int j = i + 1; j < lenght; ++j) {
                    if (xml.at(j) == ' ' && index == -1) {
                        haveAttributes = true;
                        index = j;
                    } else if (xml.at(j) == '>') {
                        if (haveAttributes) {
                            xml.replace(index, j - index, "");
                            lenght = xml.length();
                        }
                        break;
                    }
                }
            }
        }
    }
    // ============== remove tags font e b do html ==============
    xml.replace("<font>", "", Qt::CaseInsensitive);
    xml.replace("</font>", "", Qt::CaseInsensitive);
    xml.replace("<b>", "", Qt::CaseInsensitive);
    xml.replace("</b>", "", Qt::CaseInsensitive);
    // ============== adiciona cabecalho xml ==============
    xml.insert(0, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    return xml;
}

Checkpoint BrPostOfficeProvider::parseCheckpoint(QXmlStreamReader &xmlStreamReader)
{
    Checkpoint checkpoint;
    /* Let's check that we're really getting a person. */
    if(xmlStreamReader.tokenType() != QXmlStreamReader::StartElement &&
            xmlStreamReader.name() == "tr") {
        return checkpoint;
    }
    /* Next element... */
    xmlStreamReader.readNext();
    int i = 0;
    /*
     * We're going to loop over the things because the order might change.
     * We'll continue the loop until we hit an EndElement named person.
     */
    while(!(xmlStreamReader.tokenType() == QXmlStreamReader::EndElement &&
            xmlStreamReader.name() == "tr") && i < 3) {
        if(xmlStreamReader.tokenType() == QXmlStreamReader::StartElement) {
            xmlStreamReader.readNext();
            switch(i) {
            case 0: {
                QString text = xmlStreamReader.text().toString();
                checkpoint.setDateTime(text);
                if (!checkpoint.dateTime().isValid())
                    checkpoint.setSituation(text);
            }
                break;
            case 1:
                checkpoint.setLocation(xmlStreamReader.text().toString());
                break;
            case 2:
                checkpoint.setSituation(xmlStreamReader.text().toString());
                break;
            }
            ++i;
        }
        xmlStreamReader.readNext();
    }

    return checkpoint;
}

}
