
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/cascades/QListDataModel>

#include "bluetoothmanager.h"
#include "bluetoothdevicemanager.h"
#include "bluetoothservicemanager.h"
#include "bluetoothdevice.h"
#include "bluetoothservice.h"

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app),
        m_pTranslator( new QTranslator(this)),
        m_pLocaleHandler( new LocaleHandler(this))
{
	qmlRegisterType<blqt::BluetoothManager>("blqt", 1, 0, "BluetoothManager");
	qmlRegisterType<blqt::BluetoothServiceManager>("blqt", 1, 0, "BluetoothServiceManager");
	qmlRegisterType<blqt::BluetoothDeviceManager>("blqt", 1, 0, "BluetoothDeviceManager");
	qmlRegisterType<blqt::BluetoothDevice>("blqt", 1, 0, "BluetoothDevice");
	qmlRegisterType<blqt::BluetoothService>("blqt", 1, 0, "BluetoothService");

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    app->setScene(root);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("BluetoothQtApi_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}
