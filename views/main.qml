import QtQuick
import QtQuick.Window 2.2
import QtQuick.Controls 2.0

Window {
    property int w: 1366
    property int h: 768
    width: w; height: h;
    x:0;y:0;
    visible: true
    title: qsTr("Hello World")

    Item{
        x:0;y:0;
        width: w; height:h/10;visible: true;
            Rectangle{
                width: w; height:h/5;visible: true;
                color: "white"
                border.color: "black"
                border.width: 1
                radius: 0
                Button{
                  id:btn1
                  anchors.centerIn: parent
                  text:"Access Method From SomeClass"
                  onClicked: classA.callSlot()
                }
            }

    }

    Item{
        x:0;y:h/10;
        width: w; height:h-h/10;visible: true;
        Row{
             width: w;
            Column{
                width: (25*w)/100; height:h-h/10;visible: true;
                Rectangle{
                    width:(25*w)/100; height:h-h/10;visible: true;
                    color: "white"
                    border.color: "black"
                    border.width: 1
                    radius: 0
                }
            }
            Column{
                width: (50*w)/100; height:h-h/10;visible: true;

            }
            Column{
                width: (25*w)/100; height:h-h/10;visible: true;
                Rectangle{
                    width: (25*w)/100; height:h-h/10;visible: true;
                    color: "white"
                    border.color: "black"
                    border.width: 1
                    radius: 0

                }

            }
        }


    }

}
