#include "downloadhtml.h"

DownloadHtml::DownloadHtml(QObject *parent) :
    QObject(parent), m_accessManager(new QNetworkAccessManager(this)) {
    bool ok = connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDownloadFinished(QNetworkReply*)));
    Q_ASSERT(ok);
    Q_UNUSED(ok);
}

void DownloadHtml::download(QString url) {
    QUrl qUrl(url);
    QNetworkRequest request(qUrl);
    m_accessManager->get(request);
    qDebug() << "DownloadHtml::download: Downalod started!";
}

void DownloadHtml::onDownloadFinished(QNetworkReply *replay) {
    qDebug() << "DownloadHtml::onDownloadFinished: Download finished!";
    if (replay->error() == QNetworkReply::NoError) {
        QString html(replay->readAll());
        emit donwloadFinished(html);
    } else {
        emit downloadError(replay->errorString());
    }
}
