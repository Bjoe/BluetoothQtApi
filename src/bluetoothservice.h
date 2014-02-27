
#ifndef BLUETOOTHSERVICE_H_
#define BLUETOOTHSERVICE_H_

#include <QObject>
#include <QtConnectivity/QBluetoothServiceInfo>

namespace blqt {

class BluetoothService : public QObject
{
	Q_OBJECT

	Q_PROPERTY(QString serviceName READ serviceName CONSTANT)

public:
	BluetoothService(QObject* parent = nullptr);
	BluetoothService(const QtMobility::QBluetoothServiceInfo& info, QObject* parent = nullptr);

	QString serviceName() const;

private:
	QtMobility::QBluetoothServiceInfo m_info;
};

} /* namespace blqt */
#endif /* BLUETOOTHSERVICE_H_ */
