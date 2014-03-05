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

#include <QCoreApplication>

#include "package.h"
#include "handlerconnect.h"

using namespace brpackagetracking;

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    HandlerConnect *handler = new HandlerConnect();
    Package *package = new Package("RC274812293HK");
    package->connect(package, SIGNAL(loadCompleted(brpackagetracking::Package*)), handler, SLOT(handler(brpackagetracking::Package*)));
    package->connect(package, SIGNAL(loadError(QString)), handler, SLOT(handlerError(QString)));
    if (package->validateCode() == Package::NoError) {
        package->load();
        qDebug() << "main:" << "Package code:" << package->code();
        qDebug() << "main:" << "Package service:" << package->serviceCode();
        qDebug() << "main:" << "Package number:" << package->number();
        qDebug() << "main:" << "Package country acronym:" << package->countryAcronym();
        qDebug() << "main:" << "Package service name:" << package->serviceName();
        qDebug() << "main:" << "Package country name:" << package->countryName();
    }
    return a.exec();
}
