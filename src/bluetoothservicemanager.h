
#ifndef BLUETOOTHSERVICEMANAGER_H_
#define BLUETOOTHSERVICEMANAGER_H_

#include <QObject>
#include <QString>
#include <bb/cascades/DataModel>
#include <bb/cascades/GroupDataModel>
#include <QtConnectivity/QBluetoothServiceDiscoveryAgent>
#include <QtConnectivity/QBluetoothServiceInfo>
#include <bb/cascades/CustomControl>

using QtMobility::QBluetoothServiceInfo;
using QtMobility::QBluetoothServiceDiscoveryAgent;

namespace blqt {

class BluetoothServiceManager : public bb::cascades::CustomControl
{
	Q_OBJECT

	Q_PROPERTY(bb::cascades::DataModel* devicesModel READ devicesModel CONSTANT)

public:
	BluetoothServiceManager();

	bb::cascades::DataModel* devicesModel() const;

signals:
	void scanFinished();

public slots:
	void startDiscovery();
	void stopDiscovery();

private slots:
	void onDiscovered(const QBluetoothServiceInfo& info);
	void onScanFinished();
	void onError(QBluetoothServiceDiscoveryAgent::Error error);

private:
    QBluetoothServiceDiscoveryAgent* m_agent;
	bb::cascades::GroupDataModel* m_devicesModel;
};

} /* namespace blqt */
#endif /* BLUETOOTHSERVICEMANAGER_H_ */
