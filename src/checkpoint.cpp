/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: checkpoint.cpp
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

#include "checkpoint.h"

namespace brpackagetracking {

class CheckpointData : public QSharedData
{
public:
    QDateTime dateTime;
    QString location;
    QString situation;
};

Checkpoint::Checkpoint(QDateTime dateTime, const QString &location, const QString &situation) :
    QObject(), data(new CheckpointData)
{
    data->dateTime = dateTime;
    data->location = location;
    data->situation = situation;
}

Checkpoint::Checkpoint(const Checkpoint &rhs) :
    QObject(), data(rhs.data)
{
}

Checkpoint::Checkpoint() : QObject(), data(new CheckpointData)
{
}

Checkpoint &Checkpoint::operator=(const Checkpoint &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Checkpoint::~Checkpoint()
{
}

QDateTime Checkpoint::dateTime() const
{
    return data->dateTime;
}

void Checkpoint::setDateTime(QDateTime dateTime)
{
    data->dateTime = dateTime;
    Q_EMIT dateTimeChanged(data->dateTime);
}

void Checkpoint::setDateTime(const QString &dateTime)
{
    setDateTime(QDateTime::fromString(dateTime, "dd/MM/yyyy hh:mm"));
}

const QString &Checkpoint::location() const
{
    return data->location;
}

void Checkpoint::setLocation(const QString &location)
{
    data->location = location;
    Q_EMIT locationChanged(data->location);
}

const QString &Checkpoint::situation() const
{
    return data->situation;
}

void Checkpoint::setSituation(const QString &situation)
{
    data->situation = situation;
    Q_EMIT situationChanged(data->situation);
}

}
