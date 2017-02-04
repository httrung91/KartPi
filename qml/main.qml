import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import "./Screens"

ApplicationWindow {
    visible: true
    width: 800
    height: 480

    Rectangle{
        id: background
        anchors.fill: parent
        color: "#666600"
    }

    Screen_KartRpiDebug1{
        id: screenKartRpiDebug1
        anchors.centerIn: parent
    }

}
