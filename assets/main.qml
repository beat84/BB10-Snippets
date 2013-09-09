// Default empty project template
import bb.cascades 1.0

// creates one page with a label
Page {
    property string cal_date: "2013-06-12" //sample date in yyyy-MM-dd string format
    property string cal_subject: "Study the BB10 Snippets Calendar example"
    
    actions: [
        ActionItem {
            title: qsTr("Add to calendar") + Retranslate.onLanguageChanged
            imageSource: "asset:///icons/calendar.png" //add yours in asset folder
            onTriggered: {
                console.log(cal_date + ", "+cal_subject);
                _app.addToCal(cal_date, cal_subject); //invoke your c++ method
                Qt.track.trackNow("calendar", "buttons", "add"); //tracking on Google Analytics
            }
        }
    ]
    Container {
        layout: DockLayout {}
        Label {
            text: qsTr("BB10 Snippets")
            textStyle.base: SystemDefaults.TextStyles.BigText
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
        }
    }
    onCreationCompleted:{
        Qt.track = tracker.createObject();
    }
    attachedObjects:[
        ComponentDefinition {
            id: tracker
            source: "Tracker.qml"
        }
    ]
}

