#include "htmlparser.h"

HtmlParser::HtmlParser(QObject *parent) :
    QObject(parent) {
}

QList< PackageInfoModel > HtmlParser::parse(QString html) {
    changeFromHtmlToXml(html);
    QList< PackageInfoModel > checkPointsList;
    if (!m_xml.isEmpty()) {
        QXmlStreamReader xmlStreamReader(m_xml);
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
                    checkPointsList.append(parseCheckpoint(xmlStreamReader));
                }
            }
        }
    }
    checkPointsList.removeAt(0);
    int length = checkPointsList.length();
    for (int i = length - 1; i > 0; --i) {
        bool isChanget = false;
        PackageInfoModel checkpoint;
        if (checkPointsList.at(i).date().isEmpty()) {
            checkpoint.setDate(checkPointsList.at(i - 1).date());
            isChanget = true;
        }
        if (checkPointsList.at(i).location().isEmpty()) {
            checkpoint.setLocation(checkPointsList.at(i - 1).location());
            isChanget = true;
        }
        if (isChanget) {
            checkpoint.setSituation(checkPointsList.at(i).situation());
            checkPointsList.removeAt(i);
            checkPointsList.insert(i, checkpoint);
        }
    }
    return checkPointsList;
}

PackageInfoModel HtmlParser::parseCheckpoint(QXmlStreamReader &xmlStreamReader) {
    PackageInfoModel checkpoint;
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
            case 0:
                checkpoint.setDate(xmlStreamReader.text().toString());
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
    if (i == 1) {
        QString situation = checkpoint.date();
        checkpoint.setDate("");
        checkpoint.setSituation(situation);
    }
    return checkpoint;
}

void HtmlParser::changeFromHtmlToXml(QString html) {
    m_xml = html;
    // ============== remove espacos em braco do html ==============
    m_xml.replace("\n", "");
    // ============== remove partes inrelevantes do html ==============
    {
        int posInit = m_xml.indexOf("<table", Qt::CaseInsensitive);
        int posEnd = m_xml.indexOf("</table>", posInit, Qt::CaseInsensitive);
        QStringRef subString(new QString(m_xml), posInit, 8 + posEnd - posInit);
        m_xml.clear();
        m_xml.append(subString.toString());
    }
    // ============== remove partes inrelevantes do html ==============
    {
        int posInit = m_xml.indexOf("><", Qt::CaseInsensitive);
        int posEnd = m_xml.indexOf("<tr>", posInit, Qt::CaseInsensitive);
        m_xml.replace(posInit + 1, posEnd - (posInit + 1), "");
    }
    // ============== remove atributos inrelevantes do html ==============
    {
        int lenght = m_xml.length();
        for (int i = 0; i < lenght; ++i) {
            if (m_xml.at(i) == '<') {
                bool haveSpace = false;
                int index = -1;
                for (int j = i; j < lenght; ++j) {
                    if (m_xml.at(j) == '>') {
                        if (haveSpace)
                            m_xml.replace(index, j - index, "");
                        break;
                    } else if (m_xml.at(j) == ' ' && index == -1) {
                        haveSpace = true;
                        index = j;
                    }
                }
            }
        }
    }
    // ============== remove tags font e b do html ==============
    m_xml.replace("<font>", "", Qt::CaseInsensitive);
    m_xml.replace("</font>", "", Qt::CaseInsensitive);
    m_xml.replace("<b>", "", Qt::CaseInsensitive);
    m_xml.replace("</b>", "", Qt::CaseInsensitive);
    // ============== adiciona cabecalho xml ==============
    m_xml.insert(0, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
}
