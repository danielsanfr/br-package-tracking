#ifndef DOWNLOADHTML_H
#define DOWNLOADHTML_H

#include <QUrl>
#include <QDebug>
#include <QObject>
#include <QString>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace brpackagetracking {
namespace core {
class DownloadHtml : public QObject {
    Q_OBJECT
public:
    explicit DownloadHtml(QObject *parent = 0);
    void download(QString url);
signals:
    void downloadError(QString error);
    void donwloadFinished(QString html);
private slots:
    void onDownloadFinished(QNetworkReply *replay);
private:
    QNetworkAccessManager *m_accessManager;
};
}
}

#endif // DOWNLOADHTML_H
