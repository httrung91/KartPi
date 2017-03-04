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

    Compon_Button{
        id: gotoDebug
        labelText: "Debug"
        anchors.top: screenLabelContainer1.top
        anchors.right: parent.right
        anchors.rightMargin: 20
        onBtnRelease: {
            SCREENCONTROLLER.handleChangeScreen("qrc:/Screens/Screen_KartRpiDebug1.qml");
        }
    }

    Row{
        id: statusLabel
        width: parent.width - 140
        height: 50
        anchors.top: screenLabelContainer1.bottom
        anchors.topMargin: 50
//        anchors.left: screenLabelContainer1.left
//        anchors.leftMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20

        Rectangle{
            id: laserCountContainer
            width: 150
            height: 50
            color: "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: laserCount
                anchors.centerIn: parent
                text: LASERMODEL.numberOfShots
            }
        }

        Rectangle{
            id: schieldCountContainer
            width: 150
            height: 50
            color: "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: schieldrCount
                anchors.centerIn: parent
                text: SHIELDMODEL.shieldCount
            }
        }

        Rectangle{
            id: speedCountContainer
            width: 150
            height: 50
            color: "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: speedCount
                anchors.centerIn: parent
                text: SPEEDMODEL.speedCount
            }
        }

        Rectangle{
            id: bombcountContainer
            width: 150
            height: 50
            color: "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: bomdCount
                anchors.centerIn: parent
//                color: BOMBMODEL.isUnderBombEffect ? "red" : "white"
                text: BOMBMODEL.bombCount
            }
        }
    }

    Row{
        id: buttonControl
        width: parent.width - 140
        height: 50
        anchors.top: statusLabel.bottom
        anchors.topMargin: 20
        anchors.left: statusLabel.left
        spacing: 20

        Compon_Button{
            id: btnFire
            isDisabled: !LASERMODEL.isGunEnabled
            labelText: "Fire"
            onBtnRelease: {
                SCREENCONTROLLER.handleFireBtnPress();
            }
        }

        Compon_Button{
            id: btnShield
            labelText: "Shield"
            isDisabled: !SHIELDMODEL.isShieldEnabled
            onBtnRelease: {
                SCREENCONTROLLER.handleShieldBtnPress();
            }
        }

        Compon_Button{
            id: btnSpeed
            labelText: "Speed"
            isDisabled: !SPEEDMODEL.isSpeedEnabled
            onBtnRelease: {
                SCREENCONTROLLER.handleSpeedBtnPress();
            }
        }

        Compon_Button{
            id: btnBomb
            labelText: "Bomb"
            isDisabled: !BOMBMODEL.isUnderBombEffect
            onBtnRelease: {
//                SCREENCONTROLLER.handleSpeedBtnPress();
            }
        }
    }

    Row{
        id: statusLabel2
        width: parent.width - 140
        height: 50
        anchors.top: buttonControl.bottom
        anchors.topMargin: 20
//        anchors.left: screenLabelContainer1.left
//        anchors.leftMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 20

        Rectangle{
            id: laserStatusContainer
            width: 150
            height: 50
            color: KARTSTATUS.isUsingLaserGun ? "green" : "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: laserStatus
                anchors.centerIn: parent
                text: LASERMODEL.eventTimeLimit
            }
        }

        Rectangle{
            id: schieldStatusContainer
            width: 150
            height: 50
            color: KARTSTATUS.isUnderShieldEffect ? "green" : "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: schieldStatus
                anchors.centerIn: parent
                text: SHIELDMODEL.eventTimeLimit
            }
        }

        Rectangle{
            id: speedStatusContainer
            width: 150
            height: 50
            color: KARTSTATUS.isUnderSpeedEffect ? "green" : "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: speedStatus
                anchors.centerIn: parent
                text: SPEEDMODEL.eventTimeLimit
            }
        }

        Rectangle{
            id: bombStatusContainer
            width: 150
            height: 50
            color: KARTSTATUS.isUnderBombEffect ? "yellow" : "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: bomdStatus
                anchors.centerIn: parent
                color: BOMBMODEL.isUnderBombEffect ? "red" : "white"
                text: BOMBMODEL.isUnderBombEffect ? BOMBMODEL.eventTimeLimit : "Normal"
            }
        }
    }


    Item{
        id: kartIndicator
        width: parent.width
        height: 50
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 100
        anchors.left: parent.left

        Compon_Button{
            id: kartSpeed
            anchors.left: parent.left
            anchors.leftMargin: 70
            labelText: "Speed"
            onBtnRelease: {
                //SCREENCONTROLLER.handleSpeedBtnPress();
            }
        }

        Rectangle{
            id: speedIndicatorContainer
            width: 150
            height: 50
            anchors.left: kartSpeed.right
            anchors.leftMargin: 10
            color: "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: speedIndicator
                anchors.centerIn: parent
                text: KARTSTATUS.speedLimit + " km/h"
            }
        }

        Compon_Button{
            id: kartTime
            anchors.left: kartSpeed.right
            anchors.leftMargin: 190
            labelText: "Time"
            onBtnRelease: {
                //SCREENCONTROLLER.handleSpeedBtnPress();
            }
        }

        Rectangle{
            id: timeIndicatorContainer
            width: 150
            height: 50
            anchors.left: kartTime.right
            anchors.leftMargin: 10
            color: "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: timeStatus
                anchors.centerIn: parent
                text: KARTSTATUS.racingTime
            }
        }

        Compon_Button{
            id: kartScore
            anchors.left: kartSpeed.left
            anchors.top: kartSpeed.bottom
            anchors.topMargin: 20
            labelText: "Score"
            onBtnRelease: {
                //SCREENCONTROLLER.handleSpeedBtnPress();
            }
        }

        Rectangle{
            id: scoreStatusContainer
            width: 150
            height: 50
            anchors.left: kartScore.right
            anchors.leftMargin: 10
            anchors.top: kartScore.top
            color: "transparent"
            border.width: 1
            border.color: "black"
            Text {
                id: scoreStatus
                anchors.centerIn: parent
                text: KARTSTATUS.racingScore
            }
        }
    }
}
