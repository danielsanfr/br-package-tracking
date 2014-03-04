#include "util.h"

Util::Util(QObject *parent) :
    QObject(parent) {
    qDebug() << "Util::Util: Constructor";
    loadData();
}

QString Util::serviceNameByServiceCode(QString serviceCode) {
    return m_services.take(serviceCode);
}

QMap<QString, QString> Util::countryInfosByCountryAcronym(QString countryAcronym) {
    return m_countries.take(countryAcronym);
}

void Util::loadData() {
    QFile fileServies("post-office-sevices.xml");
    QFile fileCountries("countries-infos.xml");
    QString servicesXml;
    QString countriesXml;
    if (fileServies.open(QFile::ReadOnly | QIODevice::Text)) {
        while (!fileServies.atEnd())
            servicesXml.append(fileServies.readLine());
    }
    if (fileCountries.open(QFile::ReadOnly | QIODevice::Text)) {
        while (!fileCountries.atEnd())
            countriesXml.append(fileCountries.readLine());
    }
    // ============== parse xml's ==============
    if (!servicesXml.isEmpty()) {
        QXmlStreamReader xmlStreamReader(servicesXml);
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
                    int i = 0;
                    xmlStreamReader.readNext();
                    QString key, value;
                    while(!(xmlStreamReader.tokenType() == QXmlStreamReader::EndElement &&
                            xmlStreamReader.name() == "tr") && i < 2) {
                        if(xmlStreamReader.tokenType() == QXmlStreamReader::StartElement) {
                            xmlStreamReader.readNext();
                            switch(i) {
                            case 0:
                                key = xmlStreamReader.text().toString();
                                break;
                            case 1:
                                value = xmlStreamReader.text().toString();
                                break;
                            }
                            ++i;
                        }
                        xmlStreamReader.readNext();
                    }
                    m_services.insert(key, value);
                }
            }
        }
    }
    qDebug() << "Util::loadData:" << m_services.size();
    if (!countriesXml.isEmpty()) {
        QXmlStreamReader xmlStreamReader(countriesXml);
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
                if(xmlStreamReader.name() == "TABLE") {
                    continue;
                }
                /* If it's named person, we'll dig the information from there.*/
                if(xmlStreamReader.name() == "TR") {
                    int i = 0;
                    xmlStreamReader.readNext();
                    QString ord, country, key, key3, code;
                    while(!(xmlStreamReader.tokenType() == QXmlStreamReader::EndElement &&
                            xmlStreamReader.name() == "TR") && i < 5) {
                        if(xmlStreamReader.tokenType() == QXmlStreamReader::StartElement) {
                            xmlStreamReader.readNext();
                            switch(i) {
                            case 0:
                                ord = xmlStreamReader.text().toString();
                                break;
                            case 1:
                                country = xmlStreamReader.text().toString();
                                break;
                            case 2:
                                key = xmlStreamReader.text().toString();
                                break;
                            case 3:
                                key3 = xmlStreamReader.text().toString();
                                break;
                            case 4:
                                code = xmlStreamReader.text().toString();
                                break;
                            }
                            ++i;
                        }
                        xmlStreamReader.readNext();
                    }
                    QMap<QString, QString> countryMap;
                    countryMap.insert("ord", ord);
                    countryMap.insert("country_name", country);
                    countryMap.insert("triple_acronym", key3);
                    countryMap.insert("code", code);
                    m_countries.insert(key, countryMap);
                }
            }
        }
    }
    qDebug() << "Util::loadData:" << m_countries.size();
}
