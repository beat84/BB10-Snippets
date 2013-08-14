// Default empty project template
import bb.cascades 1.0

// creates one page with a label
Page {
    property string cal_date
    property string cal_subject: "Study the BB10 Snippets Calendar example"
    
    actions: [
        ActionItem {
            title: qsTr("Add to calendar") + Retranslate.onLanguageChanged
            imageSource: "asset:///icons/calendar.png"
            onTriggered: {
                _app.addToCal(cal_date, cal_subject); //invoke your c++ method
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
}

