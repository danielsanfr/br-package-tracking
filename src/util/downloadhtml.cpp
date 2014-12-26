/****************************************************************************
 *
 * Copyright (c) 2014-2014 Daniel San Ferreira da Rocha <daniel.samrocha@gmail.com>
 *
 * This file is part of the BrPackageTracking API.
 *
 *    Contact: http://www.danielsan.com.br
 *       File: downloadhtml.cpp
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

#include "downloadhtml.h"

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace brpackagetracking {
namespace util {

DownloadHtml::DownloadHtml(QObject *parent) :
    QObject(parent), m_networkAccessManager(new QNetworkAccessManager(this))
{
    bool ok = connect(m_networkAccessManager, &QNetworkAccessManager::finished,
                      this, &DownloadHtml::onFinished);
    Q_ASSERT(ok);
}

void DownloadHtml::download(const QUrl &url)
{
    QNetworkRequest request(url);
    m_networkAccessManager->get(request);
}

void DownloadHtml::onFinished(QNetworkReply *replay)
{
    if (replay->error() == QNetworkReply::NoError)
        emit donwloadFinished(QString(replay->readAll()));
    else
        emit downloadError(replay->errorString());
}

}
}
