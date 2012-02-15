import QtQuick 1.1
import com.nokia.meego 1.0

Item {
    id: root

    property alias text: label.text
    property alias showDivider: divider.visible
    property alias checkBoxVisible: check.visible
    property alias checked: check.checked
    anchors.left: parent.left
    anchors.right: parent.right
    height: 100

    signal itemClicked()
    signal checkClicked()

    Component.onCompleted: print("enabled: " + root.enabled)
    onEnabledChanged: print("changed: " + root.enabled)

    MouseArea {
        id: itemArea
        anchors.fill: parent
        onClicked: root.itemClicked();
        enabled: !check.visible && root.enabled
    }

    Rectangle {
        color: "#3c3c3c"
        visible: itemArea.pressed
        anchors.fill: parent
    }

    CheckBox {
        id: check
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 10
        }

        onClicked: root.checkClicked()
    }

    Label {
        id: label
        anchors {
            left: parent.left
            leftMargin: 20
            right: check.left
            verticalCenter: parent.verticalCenter
        }
        font.pixelSize: 28
        opacity: root.enabled ? 1.0 : 0.5
    }

    Rectangle {
        id: divider
        color: "#c2c2c2"
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            topMargin: 10
            leftMargin: 10
            rightMargin: 10
        }
        height: 1
    }
}
