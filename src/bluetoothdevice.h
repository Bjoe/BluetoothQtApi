
#ifndef BLUETOOTHDEVICE_H_
#define BLUETOOTHDEVICE_H_

#include <QObject>
#include <QString>
#include <QtConnectivity/QBluetoothAddress>
#include <QtConnectivity/QBluetoothUuid>
#include <QtConnectivity/QBluetoothDeviceInfo>

using QtMobility::QBluetoothAddress;
using QtMobility::QBluetoothUuid;

namespace blqt {

class BluetoothDevice : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString deviceName READ deviceName CONSTANT)
	Q_PROPERTY(QString remoteAddress READ remoteAddress CONSTANT)
	Q_PROPERTY(QString majorDeviceClass READ majorDeviceClass CONSTANT)
	Q_PROPERTY(QString minorDeviceClass READ minorDeviceClass CONSTANT)
	Q_PROPERTY(QString serviceClass READ serviceClass CONSTANT)
	Q_PROPERTY(QString rssi READ rssi CONSTANT)

public:
	BluetoothDevice(QObject* parent = nullptr);
	BluetoothDevice(
			const QtMobility::QBluetoothDeviceInfo& device,
			QObject* parent = nullptr);
	virtual ~BluetoothDevice();

	QString deviceName() const;
	QString remoteAddress() const;
	QString majorDeviceClass() const;
	QString minorDeviceClass() const;
	QString serviceClass() const;
	QString rssi() const;

signals:
	void connectToDevice(const QBluetoothAddress& address, const QBluetoothUuid& uuid);
	void connectToDevice(const QBluetoothAddress& address, quint16 port);

public slots:
	void onConnect();

private:
	QtMobility::QBluetoothDeviceInfo m_device;
};

} /* namespace blqt */

#endif /* BLUETOOTHDEVICE_H_ */
