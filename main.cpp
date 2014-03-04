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
