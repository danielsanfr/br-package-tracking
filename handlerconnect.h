#ifndef HANDLERCONNECT_H
#define HANDLERCONNECT_H

#include <QList>
#include <QDebug>
#include <QString>
#include <QObject>

#include "package.h"
#include "model/packageinfomodel.h"

class HandlerConnect : public QObject {
    Q_OBJECT
public:
    explicit HandlerConnect(QObject *parent = 0);
public slots:
    void handler(brpackagetracking::Package *package);
    void handlerError(QString message);
};

#endif // HANDLERCONNECT_H
