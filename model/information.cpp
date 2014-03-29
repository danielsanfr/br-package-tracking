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

#include "model/information.h"

namespace brpackagetracking {
namespace model {

Information::Information(QString date, QString location, QString situation, QObject *parent) :
    QObject(parent), m_date(""), m_location(""), m_situation("") {
    m_date = date;
    emit dateChanged();
    m_location = location;
    emit locationChanged();
    m_situation = situation;
    emit situationChanged();
}

Information::Information(const Information &other, QObject *parent) :
   QObject(parent),  m_date(""), m_location(""), m_situation("") {
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

}
}
