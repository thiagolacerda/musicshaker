import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    id: root

    property bool shakeEnabled: enabler.checked

    tools: commonTools

    Item {
        id: header

        height: 90

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        Item {
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                bottom: parent.bottom
            }
            width: childrenRect.width

            Label {
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    left: icon.right
                    leftMargin: 6
                }
                verticalAlignment: Text.AlignVCenter

                text: "Setup your Shake"
                color: "white"
                font.pixelSize: 28
            }

            Image {
                id: icon
                fillMode: Image.PreserveAspectFit
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                    topMargin: 8
                    bottomMargin: 8
                }
                source: "qrc:/musicshaker100.png"
            }
        }
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
                text: "Select Action"
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
