import bb.cascades 1.2
import blqt 1.0

Page {
    titleBar: TitleBar {
        title: "Scan Bluetooth Devices via Qt API"
    }
    Container {
        layout: DockLayout {} 
        
        ListView {
            id: btDeviceList
            
            dataModel: blDeviceManager.devicesModel
            
            listItemComponents: [
                ListItemComponent {
                    type: "item"
                    
                    StandardListItem {
                        title: ListItemData.deviceName
                        description:
                            ListItemData.remoteAddress + " " + 
                            ListItemData.majorDeviceClass + " " +
                            ListItemData.minorDeviceClass + " " +
                            ListItemData.serviceClass
                        status: ListItemData.rssi
                        
                        contextActions: [
                            ActionSet {
                                title: "Connection"
                                ActionItem {
                                    title: "Connect"
                                    
                                    onTriggered: {
                                        ListItemData.onConnect();
                                    }
                                }
                            }
                        ]
                    }
                }
            ]
        }
        
        ActivityIndicator {
            id: scanDeviceActivity
            preferredWidth: 200
            preferredHeight: 200
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
        }
        
        BluetoothDeviceManager {
            id: blDeviceManager
            
            onScanFinished: {
                scanDeviceActivity.stop();
                
                startDeviceAction.enabled = true;
                stopDeviceAction.enabled = false;
                
                console.log("QML size " + devicesModel.size());
            }
        }   
    }
    
    actions: [
        ActionItem {
            id: startDeviceAction
            
            title: "Scan"
            ActionBar.placement: ActionBarPlacement.OnBar
            
            onTriggered: {
                scanDeviceActivity.start();
                blDeviceManager.startDiscovery();
                stopDeviceAction.enabled = true;
                startDeviceAction.enabled = false;              
            }
        },
        ActionItem {
            id: stopDeviceAction
            
            title: "Stop"
            ActionBar.placement: ActionBarPlacement.OnBar
            enabled: false
            
            onTriggered: {
                blDeviceManager.stopDiscovery();
            }
        }
    ]
}
