import QtQuick 1.1
import com.nokia.meego 1.0

SelectionDialog {
    id: dialog
    titleText: "Select Shake Action"
    model: ListModel {
        ListElement {
            name: "Play/Pause"
        }
        ListElement {
            name: "Next"
        }
        ListElement {
            name: "Previous"
        }
    }
}
