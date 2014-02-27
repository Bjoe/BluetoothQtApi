import bb.cascades 1.2
import blqt 1.0

TabbedPane {
    id: mainPane    
    showTabsOnActionBar: false
    
    Tab {
        title: "Manager"
        
        Page {
            titleBar: TitleBar {
                title: "Local Bluetooth Device via Qt API"
            }
            Container {
                Label {
                    text: "Name"
                }
                Label {
                    text: blManager.name
                }
                Label {
                	text: "Address"
                }
                Label {
                    text: blManager.address
                }
                Label {
                    text: "Host mode"
                }
                Label {
                    text: blManager.hostMode
                }
                
                BluetoothManager {
                    id: blManager
                }
            }
            
            actions: [
                ActionItem {
                    title: "Power on"
                    ActionBar.placement: ActionBarPlacement.OnBar

                    onTriggered: {
                        blManager.onEnableBluetooth();
                    }
                }
            ]
        }
    
    }
    
    Tab {
        title: "Device"
        
        content : BluetoothDeviceList {
        
        }
    }
    
    Tab {
        title: "Service"
        
        content: BluetoothServiceList {
        
        } 
    }
}