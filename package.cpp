#include "package.h"

using namespace brpackagetracking;
using namespace brpackagetracking::core;
using namespace brpackagetracking::model;

Package::Package(QString code, QObject *parent) :
    QObject(parent), m_htmlParser(new HtmlParser(this)), m_downloadHtml(new DownloadHtml(this)) {
    m_validCode = false;
    m_code = code;
    bool ok = connect(m_downloadHtml, SIGNAL(donwloadFinished(QString)), this, SLOT(onDownloadFinished(QString)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    bool okError = connect(m_downloadHtml, SIGNAL(downloadError(QString)), this, SIGNAL(loadError(QString)));
    Q_ASSERT(okError);
    Q_UNUSED(okError);
}

Package::Package(QObject *parent) :
    QObject(parent), m_htmlParser(new HtmlParser(this)), m_downloadHtml(new DownloadHtml(this)) {
    m_validCode = false;
    bool ok = connect(m_downloadHtml, SIGNAL(donwloadFinished(QString)), this, SLOT(onDownloadFinished(QString)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
    bool okError = connect(m_downloadHtml, SIGNAL(downloadError(QString)), this, SIGNAL(laodError(QString)));
    Q_ASSERT(okError);
    Q_UNUSED(okError);
}

void Package::load() {
    if (m_validCode) {
        qDebug() << "Package::load";
        m_downloadHtml->download(POST_OFFICE_URL + m_code);
    }
}

void Package::onDownloadFinished(QString html) {
    qDebug() << "Package::onDownloadFinished";
    if (m_html != html && !html.isEmpty()) {
        m_html = html;
        m_checkpoints = m_htmlParser->parse(m_html);
    }
    emit loadCompleted(this);
}

Package::CodeError Package::validateCode() {
    if (m_code.length() != 13)
        return Package::LengthError;
    QString serviceCode = QStringRef(new QString(m_code), 0, 2).toString();
    if (!validateServiceCode(serviceCode))
        return Package::ServiceCodeError;
    QString number = QStringRef(new QString(m_code), 2, 9).toString();
    if (QVariant(number).toInt() == 0)
        return Package::NumberIsNotIntegerError;
    m_number = QVariant(number).toInt();
    QString countryAcronym = QStringRef(new QString(m_code), 11, 2).toString();
    if (!validateCountyAcronym(countryAcronym))
        return Package::CountryError;
    m_validCode = true;
    return Package::NoError;
}

bool Package::validateServiceCode(QString serviceCode) {
    Util *util = Util::getInstance();
    m_serviceName = util->serviceNameByServiceCode(serviceCode);
    if (!m_serviceName.isEmpty()) {
        m_serviceCode = serviceCode;
        return true;
    }
    return false;
}

bool Package::validateCountyAcronym(QString countryAcronym) {
    Util *util = Util::getInstance();
    m_countryName = util->countryInfosByCountryAcronym(countryAcronym).take("country_name");
    if (!m_countryName.isEmpty()) {
        m_countryAcronym = countryAcronym;
        return true;
    }
    return false;
}

void Package::clearAttributes() {
    m_validCode = false;
    m_number = -1;
    m_html.clear();
    m_serviceName.clear();
    m_serviceCode.clear();
    m_countryName.clear();
    m_countryAcronym.clear();
    m_checkpoints.clear();
}

void Package::setCode(QString code) {
    m_code = code;
    clearAttributes();
}

bool Package::isValidCode() const {
    return m_validCode;
}

int Package::number() const {
    return m_number;
}

QString Package::code() const {
    return m_code;
}

QString Package::serviceName() const {
    return m_serviceName;
}

QString Package::serviceCode() const {
    return m_serviceCode;
}

QString Package::countryName() const {
    return m_countryName;
}

QString Package::countryAcronym() const {
    return m_countryAcronym;
}

QList< PackageInfoModel > Package::checkpoints() const {
    return m_checkpoints;
}
