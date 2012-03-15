import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    tools: commonTools

    orientationLock: PageOrientation.LockPortrait

    property string license: 'This program is free software: you can redistribute it and/or modify ' +
                             'it under the terms of the GNU General Public License as published by ' +
                             'the Free Software Foundation, either version 3 of the License, or ' +
                             '(at your option) any later version.<br /><br />' +

                             'This package is distributed in the hope that it will be useful, ' +
                             'but WITHOUT ANY WARRANTY; without even the implied warranty of ' +
                             'MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the ' +
                             'GNU General Public License for more details.<br /><br />' +

                             'You should have received a copy of the GNU General Public License ' +
                             'along with this program. If not, see ' +
                             '<a href="http://www.gnu.org/licenses">http://www.gnu.org/licenses</a><br /><br />'

    Flickable{
        id: flick
        anchors.fill: parent
        anchors.margins: 20

        contentHeight: aboutColumn.height

        Column{
            id: aboutColumn
            width: parent.width
            spacing: 20
            Image{
                source: "logo_100.png"
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Label{
                text: "<a href='https://gitorious.org/musicshaker/'>MusicShaker</a>"
                anchors.horizontalCenter: parent.horizontalCenter
                onLinkActivated: Qt.openUrlExternally(link)
            }
            Label{
                text: "Copyright © 2012 Thiago de Barros Lacerda"
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.WordWrap
                width: parent.width
            }
            Label{
                text: license
                wrapMode: Text.WordWrap
                width: parent.width
                onLinkActivated: Qt.openUrlExternally(link)
            }
        }
    }
    ScrollDecorator {
        flickableItem: flick
    }
}
