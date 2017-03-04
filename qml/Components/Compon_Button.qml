import QtQuick 2.5
import QtQuick.Controls 2.0
import QtQuick.Window 2.0

Item {
    id: btnRoot
    width: 150
    height: 50

    /*******************************
     *      Property               *
     *******************************/

    property bool   iconDisplay         : false
    property bool   isDisabled          : false
    property bool   isPressed           : false
    property bool   isSelected          : false

    property string labelText           : "Button"
    property int    labelSize           : 24

    property string labelColor_N        : "white"
    property string labelColor_P        : "black"
    property string labelColor_S        : ""
    property string labelColor_D        : "grey"

    property string backgroundImage_N   : ""
    property string backgroundImage_P   : ""
    property string backgroundImage_S   : ""
    property string backgroundImage_D   : ""

    property string backgroundColor_N   : "#3a6073"
    property string backgroundColor_P   : "white"
    property string backgroundColor_S   : ""
    property string backgroundColor_D   : ""

    /*******************************
     *      Signal                 *
     *******************************/
    signal btnPressed()
    signal btnRelease()

    /*******************************
     *      Function               *
     *******************************/


    Rectangle{
        id              : backgroundColor
        anchors.fill    : parent
        color           : {
            if(isDisabled){
                return backgroundColor_D
            }
            else if(isPressed){
                return backgroundColor_P
            }
            else if(isSelected){
                return backgroundColor_S
            }
            else{
                return backgroundColor_N
            }
            //isDisabled ? backgroundColor_D : backgroundColor_N
        }
        border.width    : 1
        border.color    : "transparent"
    }

    Text{
        id: btnLabel
        anchors.centerIn: parent
        visible         : !iconDisplay
        color           : labelColor_N
        font.pixelSize  : labelSize
        text            : labelText
    }

    MouseArea{
        id: touchOp
        anchors.fill: parent
        onPressed: {
            if(!isDisabled){
                //backgroundColor.color = backgroundColor_P
                isPressed = true
                backgroundColor.border.color = "black"
                btnLabel.color = labelColor_P

                btnPressed()
            }
        }
        onReleased: {
            if(!isDisabled){
                //backgroundColor.color = backgroundColor_N
                isPressed = false
                backgroundColor.border.color = "transparent"
                btnLabel.color = labelColor_N

                btnRelease()
            }
        }

    }

}
