import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: root

    property bool shakeEnabled: enabler.checked

    Rectangle {
        id: header

        height: 90

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        Label {
            anchors.centerIn: parent

            text: "Setup your Shake"
            color: "white"
            font.pixelSize: 28
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
                onCheckedChanged: shaker.serviceEnabled = enabler.checked;
                Component.onCompleted: checked = shaker.serviceEnabled
            }
            ColumnItem {
                text: "Select Service"
                enabled: root.shakeEnabled
                onItemClicked: serviceMenu.open();
                checkBoxVisible: false
            }
        }
    }

    ChooseDialog {
        id: serviceMenu
        onAccepted: shaker.action = selectedIndex;
        Component.onCompleted: selectedIndex = shaker.action
    }

    ScrollDecorator {
        flickableItem: flick
    }
}
