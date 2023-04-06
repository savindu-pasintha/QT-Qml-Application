import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls.Material 2.3
import QtQuick.Controls.Styles 1.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.qmlmodels 1.0

Window {
    width: 640
    height: 480
    visible: true
    id:mainWindowId
    title: qsTr("Hello World")


    TabBar {
        id: barId
        width: parent.width
        height: 30
        anchors{
            top: mainWindowId.top
            left: mainWindowId.left
            right: mainWindowId.right
        }

        TabButton {
            text: qsTr("Home")

        }
        TabButton {
            text: qsTr("Discover")
        }

    }

    StackLayout {
        width: mainWindowId.width
        height: mainWindowId.height - barId.height
        currentIndex: barId.currentIndex
        anchors{
            top: barId.bottom
            left: mainWindowId.left
            right: mainWindowId.right
            bottom: mainWindowId.bottom
        }
        Item {
            id: homeTab
            width: parent.width
            height: parent.height
            Rectangle{
                id:r1Id
                width: parent.width
                height: parent.height
//                color: "brown"
                Image {
                        source: "./img.PNG"
                        fillMode: Image.PreserveAspectFit
                        asynchronous: true
                    }
              }
        }
        Item {
            id: discoverTab;
            width: parent.width
            height: parent.height
            Rectangle{
                width: parent.width
                height: parent.height
                color: "orange";

                GridView {
                    width: parent.width
                    height: parent.height
                    model: ListModel{
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                        ListElement{name : "Jim Williams";portrait : "./img.PNG" }
                    }
                    delegate: Column {
                        Rectangle{
                            id:r2Id
                            Image {
                               id:img2Id
                               width: 100; height: 100;
                               source: portrait;
                               anchors{
                                   horizontalCenter: parent.horizontalCenter
                               }
                               asynchronous: true
                            }
                            Text {
                                text: name
                                 width: 100; height: 100;
                                 anchors{
                                     horizontalCenter: img2Id.top
                                 }
                            }
                        }


                    }
                }

             }
        }
    }
}
