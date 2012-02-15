// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
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
