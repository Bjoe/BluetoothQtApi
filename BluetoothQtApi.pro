APP_NAME = BluetoothQtApi

QMAKE_CXXFLAGS += -Wc,-std=c++0x

CONFIG += qt warn_on cascades10 mobility
LIBS += -lbbsystem

MOBILITY += connectivity

include(config.pri)
