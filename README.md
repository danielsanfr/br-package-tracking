# Br Package Tracking API

Using this small API you can get all the updates tracking of your order it from your respective tracking code. Also you can get various information regarding your code rastreamente. This information is retrieved using the web based postal service of Brazil.

## Author

This small API was developed by **Daniel San F. da Rocha**. Any questions or suggestions don't hesitate to contact me, I'll be very happy to receive posts from this project.

## License

The license of this API is the MIT License.

## Features

* Retrieve a list of all the status of your order;
* Check if the code is valid rastreamente;
* Retrieve the Captcha code of the service used to send;
* Name of the service used to send;
* Order number plus the code verifier;
* Symbol of the country of origin;
* Name of the country of origin.

## How to use

You have to execute the following steps for use this API in your project:

- You must copy the (*XML*) files that are in the **assets** folder to **the folder where the executable of your project**.
- Include the **LIBS += -L{PAHT_TO_LIB} -lpackagetracking** in your **.pro**.
- Include the **QT += network** in your **.pro**.
- Include the **QMAKE_CXXFLAGS += -std=c++11** in your **.pro**.

## Example

Below is a small example in code using the API:

```c++
#include <QDebug>
#include <QObject>
#include <QCoreApplication>

#include <Package>
#include <BrPostofficeProvider>
#include <ShippingCarrierProvider>

using namespace brpackagetracking;


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Package package("");
    if (!package.isValid())
        return -1;

    ShippingCarrierProvider *shippingCarrierProvider;
    switch (package.shippingCarrier()) {
    case Package::BrPostOffice:
    default:
        shippingCarrierProvider = new BrPostOfficeProvider(&app);
        break;
    }
    bool ok = QObject::connect(shippingCarrierProvider, &ShippingCarrierProvider::finished,
                               [&package, &app] (QList<brpackagetracking::Checkpoint> checkpoints) {
            qDebug() << __FILE__ << __PRETTY_FUNCTION__ << __LINE__ + ":";
            qDebug() << "\nPackage code:" << package.code();
            qDebug() << "Package service name:" << package.serviceName();
            qDebug() << "Package country name:" << package.countryName() << "\n";
            foreach (Checkpoint checkpoint, checkpoints)
                qDebug() << checkpoint.dateTime() << checkpoint.location() << checkpoint.situation();
            app.exit();
    });
    Q_ASSERT(ok);
    shippingCarrierProvider->getCheckpoints(package.code());

    return app.exec();
}
```