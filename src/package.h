/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: package.h
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

#ifndef PACKAGE_H
#define PACKAGE_H

#include <QList>
#include <QString>
#include <QDateTime>
#include <QSharedDataPointer>

#include "checkpoint.h"

namespace brpackagetracking {

class PackageData;

class Package
{
public:
    enum CodeError {
        UnknowError = -1,
        NoError,
        LengthError,
        ServiceCodeError,
        NumberIsNotIntegerError,
        CountryAcronymError
    };
    enum ShippingCarriers {
        UnknowShippingCarriers = -1,
        BrPostOffice
    };
    Package(const QString &code);
    Package(const Package &);
    Package &operator=(const Package &);
    ~Package();
    void setCode(const QString &code);
    const QString &code();
    QString serviceName();
    QString countryName();
    QString serviceCode();
    QString countryAcronym();
    bool isValid();
    QString errorString();
    brpackagetracking::Package::CodeError error();
    brpackagetracking::Package::ShippingCarriers shippingCarrier();
    void addCheckpoint(QDateTime dateTime, const QString &location, const QString &situation);
    void addCheckpoint(brpackagetracking::Checkpoint checkpoint);
    const brpackagetracking::Checkpoint &checkpointsAt(int i) const;
    const QList<brpackagetracking::Checkpoint> &checkpoints() const;
private:
    QSharedDataPointer<brpackagetracking::PackageData> data;
    void validateCode();
};

} // brpackagetracking

#endif // PACKAGE_H
