BrPackageTracking API
==================
Using this small API you can get all the updates tracking of your order it from your respective tracking code. Also you can get various information regarding your code rastreamente. This information is retrieved using the web based postal service of Brazil.

Features
--------
* Retrieve a list of all the status of your order;
* Check if the code is valid rastreamente;
* Retrieve the Captcha code of the service used to send;
* Name of the service used to send;
* Order number plus the code verifier;
* Symbol of the country of origin;
* Name of the country of origin.

How to use
----------
You have to execute the following steps for use this API in your project:

- You have to copy the BrPackageTracking API to your project root folder.

- Include the **qt += network** in your **.pro**.

- Include the **package.h** and **model/information.h** file to your *qt class* as follow:

```c++
#include "myclass.h"

#include <QDebug>
#include <QObject>
#include <QString>

#include "package.h"
#include "model/information.h"

using namespace brpackagetracking;
using namespace brpackagetracking::model;

MyClass::myMethod() :
        QObject(app) {
    Package *package = new Package("RC274812293HK");
    connect(package, SIGNAL(loadCompleted(brpackagetracking::Package*)), this, SLOT(handler(brpackagetracking::Package*)));
    connect(package, SIGNAL(loadError(QString)), this, SLOT(handlerError(QString)));
    if (package->validateCode() == Package::NoError) {
        package->load();
        qDebug() << "main:" << "Package code:" << package->code();
        qDebug() << "main:" << "Package service:" << package->serviceCode();
        qDebug() << "main:" << "Package number:" << package->number();
        qDebug() << "main:" << "Package country acronym:" << package->countryAcronym();
        qDebug() << "main:" << "Package service name:" << package->serviceName();
        qDebug() << "main:" << "Package country name:" << package->countryName();
    }
```

### Note: After using the method *validateCode()* you can now use the methods shown above to get the information from the tracking code. To get a list of checkpoints you will have to connect the signals above and expect your results in 2 slots (one for load completed and one laod error).