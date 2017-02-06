import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import "../Components"

Item {
    id: screenRoot
    width: 800
    height: 480

    Item{
        id: screenLabelContainer1
        width: 200
        height: 50
        x: 10
        y: 10
        Text{
            anchors.centerIn: parent
            color: "White"
            font.pixelSize: 32
            text: "Kart-Rpi Dev"
        }
    }

    Column{
        id: leftBtnColumn
        width: 180
        height: 400
        anchors.top: screenLabelContainer1.bottom
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: 20

        Compon_Button{
            id: btnFire
            labelText: "Fire"
            onBtnRelease: {
                SCREENCONTROLLER.handleFireBtnPress();
                consoleDisplay.clear();
                consoleDisplay.append(VIEWCONSOLEMODEL.consoleData);
                consoleDisplay.append("");
            }
        }

        Compon_Button{
            id: btnShield
            labelText: "Shield"
            onBtnRelease: {
                SCREENCONTROLLER.handleShieldBtnPress();
                consoleDisplay.clear();
                consoleDisplay.append(VIEWCONSOLEMODEL.consoleData);
                consoleDisplay.append("");
            }
        }

        Compon_Button{
            id: btnSpeed
            labelText: "Speed"
            onBtnRelease: {
                SCREENCONTROLLER.handleSpeedBtnPress();
                consoleDisplay.clear();
                consoleDisplay.append(VIEWCONSOLEMODEL.consoleData);
                consoleDisplay.append("");
            }
        }

        Compon_Button{
            id: btnReadTest
            labelText: "Read Test"
            onBtnRelease: {
                SCREENCONTROLLER.handleReadInputTest();
                consoleDisplay.clear();
                consoleDisplay.append(VIEWCONSOLEMODEL.consoleData);
                consoleDisplay.append("");
            }
        }
    }

    Column{
        id: rightBtnColumn
        width: 200
        height: 400
        anchors.top: screenLabelContainer1.bottom
        anchors.topMargin: 40
        anchors.left: leftBtnColumn.right
        spacing: 20

        Compon_Button{
            id: btnD
            labelText: "-"
        }

        Compon_Button{
            id: btnD3
            labelText: "-"
        }

        Compon_Button{
            id: btnD4
            labelText: "-"
        }

        Compon_Button{
            id: btnD5
            labelText: "-"
        }
    }

    Rectangle{
        id: sepLine
        width: 2
        height: 480
        anchors.centerIn: parent
        color: "black"
    }

    Item{
        width: 380
        height: 440
        x: 410
        y: 20


        Flickable {
            id: flickable
            anchors.fill: parent
            TextArea.flickable: TextArea {
                id: consoleDisplay
                readOnly: true
                text: VIEWCONSOLEMODEL.consoleData
                wrapMode: TextArea.Wrap

                background: Rectangle{
                    implicitWidth: 380
                    implicitHeight: 440
                    border.width: 1
                    border.color: "black"
                    color: "lightsteelblue"
                }
            }

            ScrollBar.vertical: ScrollBar {
                id: control
                size: 0.3
                position: 0.2
                active: true

                contentItem: Rectangle {
                    implicitWidth: 6
                    implicitHeight: 100
                    radius: width / 2
                    color: control.pressed ? "#81e889" : "#c2f4c6"
                }
            }
        }
    }
}
