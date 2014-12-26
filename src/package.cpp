/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: package,cpp
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

#include "package.h"

#include <QStringRef>

#include "util/util.h"

namespace brpackagetracking {

using namespace util;

class PackageData : public QSharedData
{
public:
    PackageData() {
        error = Package::UnknowError;
        shippingCarriers = Package::UnknowShippingCarriers;
    }
    QString code;
    QString serviceName;
    QString countryName;
    Package::CodeError error;
    Package::ShippingCarriers shippingCarriers;
    QList<brpackagetracking::Checkpoint> checkpoints;
};

Package::Package(const QString &code) : data(new PackageData)
{
    data->code = code;
    validateCode();
}

Package::Package(const Package &rhs) : data(rhs.data)
{
}

Package &Package::operator=(const Package &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

Package::~Package()
{
}

bool Package::isValid()
{
    return (data->error == NoError);
}

void Package::setCode(const QString &code)
{
    if (code != data->code) {
        data = new PackageData;
        data->code = code;
        validateCode();
    }
}

const QString &Package::code()
{
    return data->code;
}

QString Package::serviceName()
{
    if (isValid())
        return data->serviceName;
    return QString();
}

QString Package::countryName()
{
    if (isValid())
        return data->countryName;
    return QString();
}

QString Package::serviceCode()
{
    if (isValid())
        return QStringRef(&(data->code), 0, 2).toString();
    return QString();
}

QString Package::countryAcronym()
{
    if (isValid())
        return QStringRef(&(data->code), 11, 2).toString();
    return QString();
}

QString Package::errorString()
{
    switch (data->error) {
    case NoError:
        return QString("No error");
    case LengthError:
        return QString("Length error");
    case NumberIsNotIntegerError:
        return QString("Number is not an integer error");
    case CountryAcronymError:
        return QString("Country acrony error");
    case UnknowError:
    default:
        return QString("Unknow error");
    }
}

Package::CodeError Package::error()
{
    return data->error;
}

Package::ShippingCarriers Package::shippingCarrier()
{
    return data->shippingCarriers;
}

void Package::addCheckpoint(QDateTime dateTime, const QString &location, const QString &situation)
{
    addCheckpoint(Checkpoint(dateTime, location, situation));
}

void Package::addCheckpoint(Checkpoint checkpoint)
{
    if (!isValid())
        return;
    data->checkpoints.append(checkpoint);
}

const Checkpoint &Package::checkpointsAt(int i) const
{
    return data->checkpoints.at(i);
}

const QList<Checkpoint> &Package::checkpoints() const
{
    return data->checkpoints;
}

void Package::validateCode()
{
    data->error = UnknowError;
    Util *util = Util::instance();
    if (data->code.length() != 13) {
        data->error = LengthError;
        return;
    }

    bool ok;
    QStringRef(&(data->code), 2, 9).toInt(&ok);
    if (!ok) {
        data->error = NumberIsNotIntegerError;
        return;
    }

    QString tempServiceName =
            util->serviceNameByCode(QStringRef(&(data->code), 0, 2).toString());
    if (tempServiceName.isEmpty()) {
        data->error = ServiceCodeError;
        return;
    }

    QString tempCountryName =
            util->countryInfosByAcronym(QStringRef(&(data->code), 11, 2).toString())
            .take("country_name");
    if (tempCountryName.isEmpty()) {
        data->error = CountryAcronymError;
        return;
    }

    data->error = NoError;
    data->serviceName = tempServiceName;
    data->countryName = tempCountryName;
}

}
