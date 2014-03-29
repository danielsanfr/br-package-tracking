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

#ifndef PACKAGEINFOMODEL_H
#define PACKAGEINFOMODEL_H

#include <QObject>
#include <QString>

namespace brpackagetracking {
namespace model {
class Information : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged FINAL)
    Q_PROPERTY(QString situation READ situation WRITE setSituation NOTIFY situationChanged FINAL)
public:
    explicit Information(QString date, QString location, QString situation, QObject *parent = 0);
    Information(const Information &other, QObject *parent = 0);
    explicit Information(QObject *parent = 0);
    Q_INVOKABLE QString date() const;
    Q_INVOKABLE void setDate(QString newDate);
    Q_INVOKABLE QString location() const;
    Q_INVOKABLE void setLocation(QString newLocation);
    Q_INVOKABLE QString situation() const;
    Q_INVOKABLE void setSituation(QString newSituation);
    Information &operator=(const Information &other);
signals:
    void dateChanged();
    void locationChanged();
    void situationChanged();
public slots:
private:
    QString m_date;
    QString m_location;
    QString m_situation;
};
}
}

#endif // PACKAGEINFOMODEL_H
