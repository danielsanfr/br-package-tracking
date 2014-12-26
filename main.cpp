/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: main,cpp
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

#include <QDebug>
#include <QObject>
#include <QCoreApplication>

#include "src/package.h"
#include "src/brpostofficeprovider.h"
#include "src/shippingcarrierprovider.h"

using namespace brpackagetracking;

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Package package("");
    if (!package.isValid())
        return -1;

    ShippingCarrierProvider *shippingCarrierProvider;
    switch (package.shippingCarrier()) {
    case Package::BrPostOffice:
    default:
        shippingCarrierProvider = new BrPostOfficeProvider(&app);
        break;
    }
    bool ok = QObject::connect(shippingCarrierProvider, &ShippingCarrierProvider::finished,
                               [&package, &app] (QList<brpackagetracking::Checkpoint> checkpoints) {
            qDebug() << "\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
                        "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%";
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << __LINE__ + ":";
            qDebug() << "\nPackage code:" << package.code();
            qDebug() << "Package service name:" << package.serviceName();
            qDebug() << "Package country name:" << package.countryName() << "\n";
            foreach (Checkpoint checkpoint, checkpoints)
                qDebug() << checkpoint.dateTime() << checkpoint.location() << checkpoint.situation();
            qDebug() << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
                        "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
            app.exit();
    });
    Q_ASSERT(ok);
    shippingCarrierProvider->getCheckpoints(package.code());

    return app.exec();
}
