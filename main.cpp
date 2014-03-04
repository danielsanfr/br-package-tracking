#include <QCoreApplication>

#include "util.h"
#include "package.h"
#include "packageinfomodel.h"
#include "handlerconnect.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Util::getInstance();
    HandlerConnect *handler = new HandlerConnect();
    Package *package = new Package("RC274812293HK");
    package->connect(package, SIGNAL(loadCompleted(Package*)), handler, SLOT(handler(Package*)));
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
