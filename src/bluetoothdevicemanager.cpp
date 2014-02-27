
#include "bluetoothdevicemanager.h"

#include <bb/system/SystemToast>
#include <QDebug>


#include "bluetoothdevice.h"

namespace blqt {

BluetoothDeviceManager::BluetoothDeviceManager() :
		m_socket(new QtMobility::QBluetoothSocket(this)),
		m_agent(new QtMobility::QBluetoothDeviceDiscoveryAgent(this)),
		m_devicesModel(new bb::cascades::GroupDataModel(this))
{
	connect(m_agent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
			this, SLOT(onDiscovered(const QBluetoothDeviceInfo&)));
	connect(m_agent, SIGNAL(finished()), SLOT(onScanFinished()));
	connect(m_agent, SIGNAL(canceled()), SLOT(onScanFinished()));
	connect(m_agent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)), SLOT(onError(QBluetoothDeviceDiscoveryAgent::Error)));

	connect(m_socket, SIGNAL(connected()), SIGNAL(connected()));
	connect(m_socket, SIGNAL(disconnected()), SIGNAL(disconnected()));
	connect(m_socket, SIGNAL(stateChanged(QBluetoothSocket::SocketState)), SLOT(onStateChanged(QBluetoothSocket::SocketState)));
}

void BluetoothDeviceManager::startDiscovery()
{
	m_devicesModel->clear();
	// XXX Delete all instance on heap, really?

	m_agent->start();
	qDebug() << "Start device scan";
}

void BluetoothDeviceManager::onDiscovered(
		const QtMobility::QBluetoothDeviceInfo& info)
{
	qDebug() << "Device found " + info.name();
	BluetoothDevice* device = new BluetoothDevice(info, m_devicesModel);
	connect(device,
			SIGNAL(connectToDevice(const QBluetoothAddress&, const QBluetoothUuid&)),
			SLOT(onConnectToDevice(const QBluetoothAddress&, const QBluetoothUuid&)));
	connect(device,
			SIGNAL(connectToDevice(const QBluetoothAddress&, quint16)),
			SLOT(onConnectToDevice(const QBluetoothAddress&, quint16)));
	m_devicesModel->insert(device);
}

void BluetoothDeviceManager::stopDiscovery()
{
	m_agent->stop();
	qDebug() << "Stop device scan";
}

void BluetoothDeviceManager::onScanFinished()
{
	qDebug() << "Finished scan. Device Found: " << m_devicesModel->size();
	emit scanFinished();
}

bb::cascades::DataModel* BluetoothDeviceManager::devicesModel() const
{
	return m_devicesModel;
}

void BluetoothDeviceManager::onError(QBluetoothDeviceDiscoveryAgent::Error error)
{
	QString errorMessage = QString("(%1) ").arg(error);
	switch(error) {
	case QBluetoothDeviceDiscoveryAgent::NoError:
		errorMessage += "No Error";
		qDebug() << "NoError";
		break;
	case QBluetoothDeviceDiscoveryAgent::IOFailure:
		errorMessage += "IO Failure";
		qDebug() << "IOFailure";
		break;
	case QBluetoothDeviceDiscoveryAgent::PoweredOff:
		errorMessage += "Powered off";
		qDebug() << "PoweredOff";
		break;
	case QBluetoothDeviceDiscoveryAgent::UnknownError:
		errorMessage += "Unknown errer";
		qDebug() << "Unknown error";
		break;
	default:
		errorMessage += "Unknown error state";
		qDebug() << "Error " << error;
		break;
	}

	QString agentErrorMessage = m_agent->errorString();
	qDebug() << "Agent error message: " << agentErrorMessage;

    bb::system::SystemToast toast;
	toast.setBody("Agent error: " + errorMessage + " " + agentErrorMessage);
	toast.setPosition(bb::system::SystemUiPosition::MiddleCenter);
    toast.show();
}

void BluetoothDeviceManager::onError(QBluetoothSocket::SocketError error)
{
    QString errorMessage = QString("(%1) ").arg(error);
	switch(error) {
	case QBluetoothSocket::ConnectionRefusedError:
		errorMessage += "Connection refused";
		qDebug() << "Connection refused";
		break;
	case QBluetoothSocket::RemoteHostClosedError:
		errorMessage += "Remote host closed socket";
		qDebug() << "Remote host closed";
		break;
	case QBluetoothSocket::HostNotFoundError:
		errorMessage += "Host not found";
		qDebug() << "Host not found";
		break;
	case QBluetoothSocket::ServiceNotFoundError:
		errorMessage += "Service not found";
		qDebug() << "Service not found";
		break;
	case QBluetoothSocket::NetworkError:
		errorMessage += "Network error";
		qDebug() << "Network error";
		break;
	case QBluetoothSocket::UnknownSocketError:
		errorMessage += "Unknown sockt error";
		qDebug() << "Unknown socket error";
		break;
	case QBluetoothSocket::NoSocketError:
		errorMessage += "No socket error";
		qDebug() << "No socket error";
		break;
	default:
		errorMessage += "Unknown error state";
		qDebug() << errorMessage;
		break;
	}

	QString agentErrorMessage = m_socket->errorString();
	qDebug() << "Socket error message: " << agentErrorMessage;

    bb::system::SystemToast toast;
	toast.setBody("Socket error: " + errorMessage + " " + agentErrorMessage);
	toast.setPosition(bb::system::SystemUiPosition::MiddleCenter);
    toast.show();
}

void BluetoothDeviceManager::onStateChanged(
		QBluetoothSocket::SocketState state)
{
	qDebug() << "Socket state changed";

	QString stateMessage = QString("(%1) ").arg(state);
	switch(state) {
	case QBluetoothSocket::UnconnectedState:
		stateMessage += "Unconnected state";
		qDebug() << "Unconnected state";
		break;
	case QBluetoothSocket::ServiceLookupState:
		stateMessage += "Service lookup state";
		qDebug() << "Service lookup state";
		break;
	case QBluetoothSocket::ConnectingState:
		stateMessage += "Connection state";
		qDebug() << "Connecting state";
		break;
	case QBluetoothSocket::ConnectedState:
		stateMessage += "Connected state";
		qDebug() << "Connected state";
		break;
	case QBluetoothSocket::BoundState:
		stateMessage += "Bound state";
		qDebug() << "Bound state";
		break;
	case QBluetoothSocket::ClosingState:
		stateMessage += "Closing state";
		qDebug() << "closing state";
		break;
	case QBluetoothSocket::ListeningState:
		stateMessage += "Listening state";
		qDebug() << "Listening state";
		break;
	default:
		stateMessage += "Unknown state";
		qDebug() << stateMessage;
		break;
	}

	bb::system::SystemToast toast;
	toast.setBody("Socket state changed " + stateMessage);
	toast.setPosition(bb::system::SystemUiPosition::MiddleCenter);
    toast.show();
}

void BluetoothDeviceManager::onConnectToDevice(
		const QBluetoothAddress& address,
		const QBluetoothUuid& uuid)
{
	m_socket->connectToService(address, uuid);
}

void BluetoothDeviceManager::onConnectToDevice(
		const QBluetoothAddress& address,
		quint16 port)
{
    // Connecting to port is not supported on QNX ??
	m_socket->connectToService(address, port);
}


} /* namespace blqt */
