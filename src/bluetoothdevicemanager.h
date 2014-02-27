
#ifndef BLUETOOTHDEVICEMANAGER_H_
#define BLUETOOTHDEVICEMANAGER_H_

#include <QObject>
#include <QString>
#include <bb/cascades/CustomControl>
#include <bb/cascades/DataModel>
#include <bb/cascades/GroupDataModel>
#include <QtConnectivity/QBluetoothAddress>
#include <QtConnectivity/QBluetoothUuid>
#include <QtConnectivity/QBluetoothDeviceDiscoveryAgent>
#include <QtConnectivity/QBluetoothDeviceInfo>
#include <QtConnectivity/QBluetoothSocket>

using QtMobility::QBluetoothDeviceInfo;
using QtMobility::QBluetoothDeviceDiscoveryAgent;
using QtMobility::QBluetoothAddress;
using QtMobility::QBluetoothUuid;
using QtMobility::QBluetoothSocket;

namespace blqt {

class BluetoothDeviceManager : public bb::cascades::CustomControl
{
	Q_OBJECT

	Q_PROPERTY(bb::cascades::DataModel* devicesModel READ devicesModel CONSTANT)

public:
	BluetoothDeviceManager();

	bb::cascades::DataModel* devicesModel() const;

signals:
	void scanFinished();
	void connected();
	void disconnected();

public slots:
	void startDiscovery();
	void stopDiscovery();

private slots:
	void onDiscovered(const QBluetoothDeviceInfo& info);
	void onScanFinished();
	void onError(QBluetoothDeviceDiscoveryAgent::Error error);
	void onError(QBluetoothSocket::SocketError error);
	void onConnectToDevice(const QBluetoothAddress& address, const QBluetoothUuid& uuid);
	void onConnectToDevice(const QBluetoothAddress& address, quint16 port);
	void onStateChanged(QBluetoothSocket::SocketState state);

private:
	QBluetoothSocket* m_socket;
    QBluetoothDeviceDiscoveryAgent* m_agent;
	bb::cascades::GroupDataModel* m_devicesModel;
};

} /* namespace blqt */
#endif /* BLUETOOTHDEVICEMANAGER_H_ */
