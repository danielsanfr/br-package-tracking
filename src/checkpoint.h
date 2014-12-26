/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: checkpoint.h
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

#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QSharedDataPointer>

namespace brpackagetracking {

class CheckpointData;

class Checkpoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY dateTimeChanged FINAL)
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged FINAL)
    Q_PROPERTY(QString situation READ situation WRITE setSituation NOTIFY situationChanged FINAL)
public:
    Checkpoint(QDateTime dateTime, const QString &location, const QString &situation);
    Checkpoint(const Checkpoint &);
    Checkpoint();
    Checkpoint &operator=(const Checkpoint &);
    ~Checkpoint();
    Q_INVOKABLE QDateTime dateTime() const;
    Q_INVOKABLE void setDateTime(QDateTime dateTime);
    Q_INVOKABLE void setDateTime(const QString &dateTime);
    Q_INVOKABLE const QString &location() const;
    Q_INVOKABLE void setLocation(const QString &location);
    Q_INVOKABLE const QString &situation() const;
    Q_INVOKABLE void setSituation(const QString &situation);
Q_SIGNALS:
    void dateTimeChanged(QDateTime dateTime);
    void locationChanged(const QString &location);
    void situationChanged(const QString &situation);
private:
    QSharedDataPointer<CheckpointData> data;
};

}

#endif // CHECKPOINT_H
