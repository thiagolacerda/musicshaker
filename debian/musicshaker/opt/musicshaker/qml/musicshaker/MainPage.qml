import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: root
    tools: commonTools

    property bool shakeEnabled: enabler.checked

    Rectangle {
        id: header

        height: 50

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        Label {
            anchors.centerIn: parent

            text: "Setup your App"
            color: "white"
        }

        color: "#0cbadf"
    }

    Flickable {
        id: flick
        clip: true
        anchors {
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        contentHeight: column.height
        Column {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
            ColumnItem {
                id: enabler
                text: "Enable MusicShaker"
                onItemClicked: print("AAAAAB");
                onCheckedChanged: shaker.serviceEnabled = enabler.checked;
            }
            ColumnItem {
                text: "Select Service"
                enabled: root.shakeEnabled
                onItemClicked: serviceMenu.open();
                checkBoxVisible: false
            }
        }
    }

    ServiceMenu {
        id: serviceMenu
    }

    ScrollDecorator {
        flickableItem: flick
    }
}
