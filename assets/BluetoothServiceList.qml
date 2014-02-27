import bb.cascades 1.2
import blqt 1.0

Page {
    titleBar: TitleBar {
        title: "Scan Bluetooth Services via Qt API"
    }
    Container {
        layout: DockLayout {} 
        
        ListView {
            id: btServiceList
            
            dataModel: blServiceManager.devicesModel
            
            listItemComponents: [
                ListItemComponent {
                    type: "item"
                    
                    StandardListItem {
                        title: ListItemData.serviceName
                    }
                }
            ]
        }
        
        ActivityIndicator {
            id: scanServiceActivity
            preferredWidth: 200
            preferredHeight: 200
            horizontalAlignment: HorizontalAlignment.Center
            verticalAlignment: VerticalAlignment.Center
        }
        
        BluetoothServiceManager {
            id: blServiceManager
            
            onScanFinished: {
                scanServiceActivity.stop();
                
                startServiceAction.enabled = true;
                stopServiceAction.enabled = false;
                
                console.log("QML size " + devicesModel.size());
            }
        }   
    }
    
    actions: [
        ActionItem {
            id: startServiceAction
            
            title: "Scan"
            ActionBar.placement: ActionBarPlacement.OnBar
            
            onTriggered: {
                scanServiceActivity.start();
                blServiceManager.startDiscovery();
                stopServiceAction.enabled = true;
                startServiceAction.enabled = false;              
            }
        },
        ActionItem {
            id: stopServiceAction
            
            title: "Stop"
            ActionBar.placement: ActionBarPlacement.OnBar
            enabled: false
            
            onTriggered: {
                blServiceManager.stopDiscovery();
            }
        }
    ]
}