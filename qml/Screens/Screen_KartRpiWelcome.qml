import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import "../Components"

Item {
    id: screenRoot
    width: 800
    height: 480

   // signal changeScreen(var screenUrl)

    Item{
        id: screenLabelContainer1
        width: 200
        height: 50
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 25
        Text{
            anchors.centerIn: parent
            color: "White"
            font.pixelSize: 32
            text: "Kart-Rpi Dev"
        }
    }

    Compon_Button{
        id: startButton
        anchors.centerIn: parent
        labelText: "Start"
        onBtnRelease: {
            SCREENCONTROLLER.handleChangeScreen("qrc:/Screens/Screen_KartRpiSimulator1.qml");
            SCREENCONTROLLER.startRacing();
           // changeScreen("qrc:/Screens/Screen_KartRpiSimulator1.qml")
        }
    }

}
