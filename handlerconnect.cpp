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

#include "handlerconnect.h"

using namespace brpackagetracking;
using namespace brpackagetracking::model;

HandlerConnect::HandlerConnect(QObject *parent) :
    QObject(parent) {
}

void HandlerConnect::handler(Package *package) {
    QList< Information > checkpoints = package->checkpoints();
    int length = checkpoints.length();
    qDebug() << "HandlerConnect::handler:" << "=============================================";
    for (int i = 0; i < length; ++i) {
        qDebug() << "HandlerConnect::handler:" << "Date:" << checkpoints.at(i).date();
        qDebug() << "HandlerConnect::handler:" << "Location:" << checkpoints.at(i).location();
        qDebug() << "HandlerConnect::handler:" << "Situation:" << checkpoints.at(i).situation();
        qDebug() << "HandlerConnect::handler:" << "=============================================";
    }
}

void HandlerConnect::handlerError(QString message) {
    qDebug() << "HandlerConnect::handlerError:" << message;
}
