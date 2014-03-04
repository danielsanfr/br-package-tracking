BrPackageTracking API
==================
Using this small API you can get all the updates tracking of your order it from your respective tracking code. Also you can get various information regarding your code rastreamente. This information is retrieved using the web based postal service of Brazil.

Features
--------
* Recuperar umas lista contendo todos os status da sua encomenda;
* Verificar se o código de rastreamente é válido;
* Recuperar o códido do serviço usado no envio;
* Nome do serviço usado no envio;
* Número da encomenda mais o código verificador;
* Sigla do país de origem;
* Nome do país de origem;

How to use
----------
You have to execute the following steps:

- You have to copy the build folder to your project root folder.

![Screenshot] (https://s3.amazonaws.com/microSamples/Screen+Shot+2013-12-19+at+16.31.16.png)

- Include the include(build/build.pri) in your .pro. The result of the addition is:

```
APP_NAME = AppInfoMicroSample

CONFIG += qt warn_on cascades10

include(build/build.pri)
include(config.pri)
```

- Include the header ApplicationInfo.hpp in you ApplicationUI.cpp file, the result should be:

```c++
include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>

#include "applicationinfo.hpp"

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
{
	ApplicationInfo::registerQmlTypes();
    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);
```