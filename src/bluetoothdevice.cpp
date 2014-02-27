
#include "bluetoothdevice.h"

#include <QList>

namespace blqt {

BluetoothDevice::BluetoothDevice(QObject* parent) :
		QObject(parent),
		m_device()
{}

BluetoothDevice::BluetoothDevice(
		const QtMobility::QBluetoothDeviceInfo& device,
		QObject* parent) :
		QObject(parent),
		m_device(device)
{

}

BluetoothDevice::~BluetoothDevice()
{
}

QString BluetoothDevice::deviceName() const
{
	return m_device.name();
}

QString BluetoothDevice::remoteAddress() const
{
	QtMobility::QBluetoothAddress address = m_device.address();
	return address.toString();
}

QString BluetoothDevice::majorDeviceClass() const
{
	QtMobility::QBluetoothDeviceInfo::MajorDeviceClass deviceClass = m_device.majorDeviceClass();
	QString className;
	switch(deviceClass) {
	case QtMobility::QBluetoothDeviceInfo::MiscellaneousDevice:
		className = "Miscellaneous";
		break;
	case QtMobility::QBluetoothDeviceInfo::ComputerDevice:
		className = "Computer";
		break;
	case QtMobility::QBluetoothDeviceInfo::PhoneDevice:
		className = "Phone";
		break;
	case QtMobility::QBluetoothDeviceInfo::LANAccessDevice:
		className = "LANAccess";
		break;
	case QtMobility::QBluetoothDeviceInfo::AudioVideoDevice:
		className = "AudioVideo";
		break;
	case QtMobility::QBluetoothDeviceInfo::PeripheralDevice:
		className = "Peripheral";
		break;
	case QtMobility::QBluetoothDeviceInfo::ImagingDevice:
		className = "Imaging";
		break;
	case QtMobility::QBluetoothDeviceInfo::WearableDevice:
		className = "Wearable";
		break;
	case QtMobility::QBluetoothDeviceInfo::ToyDevice:
		className = "Toy";
		break;
	case QtMobility::QBluetoothDeviceInfo::HealthDevice:
		className = "Health";
		break;
	case QtMobility::QBluetoothDeviceInfo::UncategorizedDevice:
		className = "Uncategorized";
		break;
	default:
		className = "Unknown";
		break;
	}
	return className;
}

QString BluetoothDevice::minorDeviceClass() const
{
	quint8 deviceClass = m_device.minorDeviceClass();
	return QString("%1").arg(deviceClass);
}

QString BluetoothDevice::serviceClass() const
{
	QtMobility::QBluetoothDeviceInfo::ServiceClasses serviceClasses = m_device.serviceClasses();

	QString serviceName;
	switch(serviceClasses) {
	case QtMobility::QBluetoothDeviceInfo::NoService:
		serviceName = "No service";
		break;
	case QtMobility::QBluetoothDeviceInfo::PositioningService:
		serviceName = "Positioning";
		break;
	case QtMobility::QBluetoothDeviceInfo::NetworkingService:
		serviceName = "Networking";
		break;
	case QtMobility::QBluetoothDeviceInfo::RenderingService:
		serviceName = "Rendering";
		break;
	case QtMobility::QBluetoothDeviceInfo::CapturingService:
		serviceName = "Capturing";
		break;
	case QtMobility::QBluetoothDeviceInfo::AudioService:
		serviceName = "Audio";
		break;
	case QtMobility::QBluetoothDeviceInfo::TelephonyService:
		serviceName = "Telephony";
		break;
	case QtMobility::QBluetoothDeviceInfo::InformationService:
		serviceName = "Information";
		break;
	case QtMobility::QBluetoothDeviceInfo::AllServices:
		serviceName = "All services";
		break;
	default:
		serviceName = "Unknown";
		break;
	}
	return serviceName;
}

QString BluetoothDevice::rssi() const
{
	qint16 signalStrength = m_device.rssi();
	return QString("%1").arg(signalStrength);
}

void BluetoothDevice::onConnect()
{
	QtMobility::QBluetoothAddress address = m_device.address();
	QList<QtMobility::QBluetoothUuid> uuids = m_device.serviceUuids();
	qDebug() << "Connect to " << address.toString() << " uuids " << uuids;
	if(uuids.size() > 0) {
		emit connectToDevice(address, uuids[0]);
	} else {
	    // Only for Test!
		emit connectToDevice(address, 80);
	}
}

} /* namespace blqt */
