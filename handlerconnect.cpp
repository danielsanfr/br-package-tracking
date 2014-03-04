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
