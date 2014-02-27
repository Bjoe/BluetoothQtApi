
#include "bluetoothmanager.h"

#include <QDebug>

#include <bb/system/SystemToast>
#include <QtConnectivity/QBluetoothAddress>

namespace blqt {

BluetoothManager::BluetoothManager() :
		m_hostMode(),
		m_device(new QtMobility::QBluetoothLocalDevice(this))
{
	connect(m_device, SIGNAL(error(QBluetoothLocalDevice::Error)), SLOT(onError(QBluetoothLocalDevice::Error)));
	connect(m_device,
			SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
			SLOT(onHostModeStateChanged(QBluetoothLocalDevice::HostMode)));

	onHostModeStateChanged(m_device->hostMode());
}

QString BluetoothManager::address() const
{
	QtMobility::QBluetoothAddress blAddress = m_device->address();
	return blAddress.toString();
}

QString BluetoothManager::name() const
{
	return m_device->name();
}

QString BluetoothManager::hostMode() const
{
	return m_hostMode;
}

void BluetoothManager::onEnableBluetooth()
{
	m_device->powerOn();
}

void BluetoothManager::onError(QBluetoothLocalDevice::Error error)
{
	qDebug() << "Bluetooth local device error: " << error;

	QString errorMessage = QString("(%1) ").arg(error);
    switch(error) {
	case QBluetoothLocalDevice::NoError:
		errorMessage += "No error";
		qDebug() << "No error";
		break;
	case QBluetoothLocalDevice::PairingError:
		errorMessage += "Pairing error";
		qDebug() << "Pairing error";
		break;
	case QBluetoothLocalDevice::UnknownError:
		errorMessage += "Unknown error";
		qDebug() << "Unknown error";
		break;
	default:
		errorMessage += "Unknown error state";
		qDebug() << errorMessage;
		break;
	}

	bb::system::SystemToast toast;
	toast.setBody(errorMessage);
	toast.setPosition(bb::system::SystemUiPosition::MiddleCenter);
    toast.show();
}

void BluetoothManager::onHostModeStateChanged(
		QBluetoothLocalDevice::HostMode state)
{
	switch(state) {
	case QBluetoothLocalDevice::HostPoweredOff:
		m_hostMode = "Power off";
		break;
	case QBluetoothLocalDevice::HostConnectable:
		m_hostMode = "Connectable";
		break;
	case QBluetoothLocalDevice::HostDiscoverable:
		m_hostMode = "Discoverable";
		break;
	case QBluetoothLocalDevice::HostDiscoverableLimitedInquiry:
		m_hostMode = "Descoverable limited inquiry";
		break;
	default:
		m_hostMode = "Unknown";
		break;
	}
	emit hostModeChanged();
}

}
