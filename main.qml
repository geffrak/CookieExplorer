import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.0
import QtWebEngine 1.5

Window {
    visible: true
    width: Screen.width / 2
    height: Screen.height / 2
    x: (Screen.width - width) / 2
    y: (Screen.height - height) / 2
    color: "#1a1c1f"

    Rectangle {
        id: urlSelector
        color: "transparent"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 100

        ComboBox {
            id: urlList
            anchors.fill: parent
            anchors.margins: 25
            model: ListModel {
                id: cbItems
            }

            editable: true

            onAccepted: {
                if (find(currentText) === -1) {
                    model.append({text: editText})
                    currentIndex = find(editText)
                }
            }

            onCurrentTextChanged: {
                webPage.url = currentText
            }

            Component.onCompleted: {
                model.append({text: link});
                currentIndex = find(link)
            }
        }
    }

    WebEngineView {

        id: webPage
        anchors.top: urlSelector.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        url: urlList.currentText
        backgroundColor: "transparent"

        onNavigationRequested: function(request) {
                    console.log("onNavigationRequested -> Navigation requested to " + request.url + "\n")
        }

        settings.errorPageEnabled: false
    }
}