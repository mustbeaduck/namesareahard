import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Shapes 1.4
import QtQuick.Layouts 1.15
import QtQuick.Controls 1.0


Window {

   id: mainWindow

   title: ":)"
   visible: true

   width: 400
   height: 400

   color: "#f2f2f2"

   Item {

      id: wrapper
      property int triangleOffset: width/4

      width: parent.height < parent.width ? parent.height : parent.width
      height: width/2

      anchors.bottom: parent.bottom
      anchors.horizontalCenter: parent.horizontalCenter

      Rectangle {

         width: (parent.height + 40)* 2
         height: width

         anchors.verticalCenter: parent.bottom
         anchors.horizontalCenter: parent.horizontalCenter

         radius: width/2

         color: "#fff"
      }

      Shape{

         width: parent.width
         height: parent.height

         ShapePath {

            startX: wrapper.triangleOffset
            startY: wrapper.height

            fillColor: "red"

            PathLine { x: wrapper.width/2; y: -40 }
            PathLine { x: wrapper.width - wrapper.triangleOffset; y: wrapper.height }

         }
      }

      Text {
         id: frequency
         text: tuner.frequency + "Hz"

         anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: offset.top
            bottomMargin: 10
         }

         font.pixelSize: 15
         font.bold: true

         color: "#f2f2f2"
      }

      Text {
         id: offset
         text: tuner.offset > 0 ? "+" + tuner.offset : tuner.offset

         anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 20
         }

         font.pixelSize: 15
         font.bold: true

         color: "#f2f2f2"
      }

      ColumnLayout {

         id: mainColumn

         width: parent.width
         height: parent.height

         transformOrigin: Item.Bottom

         //NumberAnimation on rotation { from: -180; to: 180; duration: 10000; loops: Animation.Infinite }
         rotation: tuner.offset * -5

         Behavior on rotation { NumberAnimation { duration: tuner.notechanged ? 0 : 300 } }

         Text {
            id: middleNote

            Layout.alignment: Qt.AlignCenter
            color: Math.abs(parent.rotation) > 3 ? "black" : "white"

            font.pixelSize: 35
            //font.bold: true

            text: tuner.midnote
         }

         RowLayout {

            Layout.bottomMargin: parent.height/2
            Layout.alignment: Qt.AlignBottom
            Layout.preferredWidth: parent.width

            Text {

               id: leftNote

               rotation: -45

               Layout.alignment: Qt.AlignLeft
               Layout.leftMargin: wrapper.triangleOffset - width

               font.pixelSize: 35
               text: tuner.leftnote
            }

            Text {

               id: rightNote

               rotation: 45

               Layout.alignment: Qt.AlignRight
               Layout.rightMargin: wrapper.triangleOffset - width

               font.pixelSize: 35
               text: tuner.rightnote
            }
         }
      }
   }
}
