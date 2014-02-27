
#include "bluetoothservice.h"

namespace blqt {

BluetoothService::BluetoothService(QObject* parent) : QObject(parent)
{}

BluetoothService::BluetoothService(
		const QtMobility::QBluetoothServiceInfo& info, QObject* parent) :
				QObject(parent),
				m_info(info)
{}

QString BluetoothService::serviceName() const
{
	return m_info.serviceName();
}

} /* namespace blqt */
