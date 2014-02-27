
#include "bluetoothservicemanager.h"

#include <QDebug>
#include <bb/system/SystemToast>

#include "bluetoothservice.h"

namespace blqt {

BluetoothServiceManager::BluetoothServiceManager() :
		m_agent(new QBluetoothServiceDiscoveryAgent(this)),
		m_devicesModel(new bb::cascades::GroupDataModel(this))
{
	connect(m_agent, SIGNAL(serviceDiscovered(const QBluetoothServiceInfo&)),
			this, SLOT(onDiscovered(const QBluetoothServiceInfo&)));
	connect(m_agent, SIGNAL(finished()), SLOT(onScanFinished()));
	connect(m_agent, SIGNAL(canceled()), SLOT(onScanFinished()));
	connect(m_agent, SIGNAL(error(QBluetoothServiceDiscoveryAgent::Error)), SLOT(onError(QBluetoothServiceDiscoveryAgent::Error)));
}

void BluetoothServiceManager::startDiscovery()
{
	m_devicesModel->clear();
	// XXX Delete all device instance on heap, really?

	m_agent->start();
	qDebug() << "Start service scan";
}

void BluetoothServiceManager::onDiscovered(
		const QtMobility::QBluetoothServiceInfo& info)
{
	qDebug() << "Device found " + info.serviceName();
	BluetoothService* device = new BluetoothService(info, m_devicesModel);
	m_devicesModel->insert(device);
}

void BluetoothServiceManager::stopDiscovery()
{
	m_agent->stop();
	qDebug() << "Stop service scan";
}

void BluetoothServiceManager::onScanFinished()
{
	qDebug() << "Finished scan. Device Found: " << m_devicesModel->size();
	emit scanFinished();
}

bb::cascades::DataModel* BluetoothServiceManager::devicesModel() const
{
	return m_devicesModel;
}

void BluetoothServiceManager::onError(QBluetoothServiceDiscoveryAgent::Error error)
{
	QString errorMessage = QString("(%1) ").arg(error);
	switch(error) {
	case QBluetoothServiceDiscoveryAgent::NoError:
		errorMessage += "No Error";
		qDebug() << errorMessage << "NoError";
		break;
	case QBluetoothServiceDiscoveryAgent::DeviceDiscoveryError:
		errorMessage += "Device discovery error";
		qDebug() << errorMessage << "DeviceDiscoveryError";
		break;
	case QBluetoothServiceDiscoveryAgent::UnknownError:
		errorMessage += "Unknown error";
		qDebug() << errorMessage << "UnknownError";
		break;
	default:
		errorMessage += "Unknown error state";
		qDebug() << errorMessage;
		break;
	}
	QString agentErrorMessage = m_agent->errorString();
	qDebug() << "Agent error message: " << agentErrorMessage;

    bb::system::SystemToast toast;
	toast.setBody(errorMessage + " " + agentErrorMessage);
	toast.setPosition(bb::system::SystemUiPosition::MiddleCenter);
    toast.show();
}

} /* namespace blqt */
