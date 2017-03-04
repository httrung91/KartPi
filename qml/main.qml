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

//    Screen_KartRpiDebug1{
//        id: screenKartRpiDebug1
//        anchors.centerIn: parent
//    }

    Item{
        id: contentScreen
        anchors.fill: parent
        Loader{
            id: screenLoader
            anchors.fill: parent
            source: SCREENCONTROLLER.screenUrl //"qrc:/Screens/Screen_KartRpiWelcome.qml"
        }
    }

//    Connections{
//        target: screenLoader.item

//    }

//    Loader{
//        id: screenLoader
//        anchors.fill: parent
//        source: "./Screens/Screen_KartRpiWelcome.qml"
//    }

}
