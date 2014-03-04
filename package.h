#ifndef PACKAGE_H
#define PACKAGE_H

#include <QList>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QStringRef>
#include <QVariant>

#include "util.h"
#include "htmlparser.h"
#include "downloadhtml.h"
#include "packageinfomodel.h"

#define POST_OFFICE_URL QString("http://websro.correios.com.br/sro_bin/txect01$.QueryList?P_ITEMCODE=&P_LINGUA=001&P_TESTE=&P_TIPO=001&P_COD_UNI=")
#define POST_OFFICE_URL_M QString("http://websro.correios.com.br/sro_bin/txect01$.QueryList?P_LINGUA=001&P_TIPO=001&P_COD_UNI=")

class Package : public QObject
{
    Q_OBJECT
public:
    enum CodeError {
        NoError = 0,
        LengthError,
        ServiceCodeError,
        NumberIsNotIntegerError,
        CountryError
    };
    explicit Package(QString code, QObject *parent = 0);
    explicit Package(QObject *parent = 0);
    void load();
    Package::CodeError validateCode();
    void setCode(QString code);
    bool isValidCode() const;
    int number() const;
    QString code() const;
    QString serviceName() const;
    QString serviceCode() const;
    QString countryName() const;
    QString countryAcronym() const;
    QList< PackageInfoModel > checkpoints() const;
signals:
    void loadCompleted(Package *package);
    void loadError(QString message);
public slots:
private slots:
    void onDownloadFinished(QString html);
private:
    void clearAttributes();
    bool validateServiceCode(QString serviceCode);
    bool validateCountyAcronym(QString countryAcronym);
    bool m_validCode;
    int m_number;
    QString m_code;
    QString m_html;
    QString m_serviceName;
    QString m_serviceCode;
    QString m_countryName;
    QString m_countryAcronym;
    HtmlParser *m_htmlParser;
    DownloadHtml *m_downloadHtml;
    QList< PackageInfoModel > m_checkpoints;
};

#endif // PACKAGE_H
