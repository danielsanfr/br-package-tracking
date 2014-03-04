#include "model/information.h"

using namespace brpackagetracking::model;

Information::Information(QString date, QString location, QString situation, QObject *parent) :
    QObject(parent), m_date(""), m_location(""), m_situation("") {
    m_date = date;
    emit dateChanged();
    m_location = location;
    emit locationChanged();
    m_situation = situation;
    emit situationChanged();
}

Information::Information(const Information &other) :
   QObject(),  m_date(""), m_location(""), m_situation("") {
    m_date = other.date();
    emit dateChanged();
    m_location = other.location();
    emit locationChanged();
    m_situation = other.situation();
    emit situationChanged();
}

Information::Information(QObject *parent) :
    QObject(parent), m_date(""), m_location(""), m_situation("") {
}

QString Information::date() const {
    return m_date;
}

void Information::setDate(QString newDate) {
    m_date = newDate;
    emit dateChanged();
}

QString Information::location() const {
    return m_location;
}

void Information::setLocation(QString newLocation) {
    m_location = newLocation;
    emit locationChanged();
}

QString Information::situation() const {
    return m_situation;
}

void Information::setSituation(QString newSituation) {
    m_situation = newSituation;
    emit situationChanged();
}

Information &Information::operator=(const Information &other) {
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
