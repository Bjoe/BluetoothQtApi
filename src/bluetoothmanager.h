
#ifndef BLUETOOTHMANAGER_H_
#define BLUETOOTHMANAGER_H_

#include <QObject>
#include <QString>
#include <QtConnectivity/QBluetoothLocalDevice>
#include <bb/cascades/CustomControl>

using QtMobility::QBluetoothLocalDevice;

namespace blqt {

class BluetoothManager : public bb::cascades::CustomControl
{
	Q_OBJECT

	Q_PROPERTY(QString name READ name CONSTANT)
	Q_PROPERTY(QString address READ address CONSTANT)
	Q_PROPERTY(QString hostMode READ hostMode NOTIFY hostModeChanged)

public:
	BluetoothManager();

	QString address() const;
	QString name() const;
	QString hostMode() const;

signals:
	void hostModeChanged();

public slots:
	void onEnableBluetooth();

private slots:
	void onError(QBluetoothLocalDevice::Error error);
	void onHostModeStateChanged(QBluetoothLocalDevice::HostMode state);

private:
	QString m_hostMode;
	QBluetoothLocalDevice *m_device;
};

}

#endif /* BLUETOOTHMANAGER_H_ */
