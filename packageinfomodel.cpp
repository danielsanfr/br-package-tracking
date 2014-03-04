#include "packageinfomodel.h"

PackageInfoModel::PackageInfoModel(QString date, QString location, QString situation, QObject *parent) :
    QObject(parent), m_date(""), m_location(""), m_situation("") {
    m_date = date;
    emit dateChanged();
    m_location = location;
    emit locationChanged();
    m_situation = situation;
    emit situationChanged();
}

PackageInfoModel::PackageInfoModel(const PackageInfoModel &other) :
   QObject(),  m_date(""), m_location(""), m_situation("") {
    m_date = other.date();
    emit dateChanged();
    m_location = other.location();
    emit locationChanged();
    m_situation = other.situation();
    emit situationChanged();
}

PackageInfoModel::PackageInfoModel(QObject *parent) :
    QObject(parent), m_date(""), m_location(""), m_situation("") {
}

QString PackageInfoModel::date() const {
    return m_date;
}

void PackageInfoModel::setDate(QString newDate) {
    m_date = newDate;
    emit dateChanged();
}

QString PackageInfoModel::location() const {
    return m_location;
}

void PackageInfoModel::setLocation(QString newLocation) {
    m_location = newLocation;
    emit locationChanged();
}

QString PackageInfoModel::situation() const {
    return m_situation;
}

void PackageInfoModel::setSituation(QString newSituation) {
    m_situation = newSituation;
    emit situationChanged();
}

PackageInfoModel &PackageInfoModel::operator=(const PackageInfoModel &other) {
    if (this != &other) {
        m_date = other.date();
        emit dateChanged();
        m_location = other.location();
        emit locationChanged();
        m_situation = other.situation();
        emit situationChanged();
    }
    return *this;
}
