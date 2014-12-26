/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: downloadhtml.h
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

#ifndef DOWNLOADHTML_H
#define DOWNLOADHTML_H

#include <QUrl>
#include <QObject>
#include <QString>

QT_BEGIN_NAMESPACE
class QNetworkReply;
class QNetworkAccessManager;
QT_END_NAMESPACE

namespace brpackagetracking {
namespace util {

class DownloadHtml : public QObject {
    Q_OBJECT
public:
    DownloadHtml(QObject *parent = 0);
    void download(const QUrl &url);
signals:
    void downloadError(QString error);
    void donwloadFinished(QString html);
private slots:
    void onFinished(QNetworkReply *replay);
private:
    QNetworkAccessManager *m_networkAccessManager;
};

}
}

#endif // DOWNLOADHTML_H
