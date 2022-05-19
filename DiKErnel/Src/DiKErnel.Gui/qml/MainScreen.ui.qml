

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts 1.0

Rectangle {
    id: rectangle
    width: 1250
    height: 650
    color: "#e6e6e6"
    border.width: 0
    anchors.fill: parent

    Image {
        id: image
        x: 20
        y: 20
        width: 178
        height: 178
        source: "/Resources/logo.svg"
        fillMode: Image.PreserveAspectFit
    }

    ColumnLayout {
        x: 241
        y: 49
        width: 68
        height: 121

        Label {
            id: label
            text: qsTr("Applicatie")
        }

        Label {
            id: label2
            text: qsTr("Versie")
        }

        Label {
            id: label4
            text: qsTr("Bedrijf")
        }

        Label {
            id: label6
            text: qsTr("Contact")
        }
    }

    ColumnLayout {
        x: 353
        y: 49
        width: 172
        height: 121

        Label {
            id: label1
            text: qsTr("DiKernel-gui")
        }

        Label {
            id: label3
            text: qsTr("22.1.1.0 (ALPHA)")
        }

        Label {
            id: label5
            text: qsTr("Deltares")
        }

        Label {
            id: label7
            color: "#2a47b8"
            text: qsTr("dikernel@deltares.nl")
        }
    }

    RowLayout {}

    Text {
        id: text1
        x: 20
        y: 221
        width: 490
        height: 166
        text: qsTr("Disclaimer: De ALPHA versie van DiKErnel is nog in de testfase en zal op vele onderdelen nog moeten worden verbeterd en uitgebreid. Het doel van deze ALPHA versie is om feedback te ontvangen op het huidige functioneren en om tekortkomingen te detecteren. DiKErnel dient met de grootst mogelijke voorzichtigheid te worden geïnstalleerd en gebruikt. Op geen enkele manier mag er worden vertrouwd op de beschikbare resultaten, de bijgeleverde softwaredocumentatie en al het andere materiaal dat bij deze versie beschikbaar wordt gesteld.")
        horizontalAlignment: Text.AlignJustify
        wrapMode: Text.Wrap
        font.pointSize: 11
    }

    ToolSeparator {
        id: toolSeparator
        x: 516
        width: 32
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        bottomPadding: 0
        topPadding: 0
    }

    ToolSeparator {
        id: toolSeparator1
        x: 0
        y: 393
        width: 532
        height: 32
        rightPadding: 0
        leftPadding: 0
        orientation: Qt.Horizontal
    }

    TextField {
        id: textField
        x: 20
        y: 455
        width: 442
        height: 32
        placeholderText: qsTr("Text Field")
    }

    TextField {
        id: textField1
        x: 20
        y: 532
        width: 442
        height: 32
        placeholderText: qsTr("Text Field")
    }

    Label {
        id: label8
        x: 20
        y: 431
        text: qsTr("Invoerbestand")
    }

    Label {
        id: label9
        x: 20
        y: 507
        text: qsTr("Uitvoerbestand")
    }

    Button {
        id: button
        x: 474
        y: 457
        width: 36
        height: 32
        text: qsTr("...")
    }

    Button {
        id: button1
        x: 474
        y: 532
        width: 36
        height: 32
        text: qsTr("...")
    }

    Label {
        id: label10
        x: 554
        y: 20
        text: qsTr("Berichten")
    }

    Button {
        id: button3
        x: 1137
        y: 597
        text: qsTr("Wissen")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 21
        anchors.rightMargin: 22
        rightPadding: 22
        leftPadding: 22
    }

    Button {
        id: button4
        x: 919
        y: 597
        text: qsTr("Kopieer naar klembord")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 21
        anchors.rightMargin: 136
        rightPadding: 22
        leftPadding: 22
        spacing: 8
    }

    Button {
        id: button2
        x: 436
        y: 597
        text: qsTr("Start")
        rightPadding: 22
        leftPadding: 22
    }

    ScrollView {
        id: scrollView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 69
        anchors.topMargin: 49
        anchors.leftMargin: 554
        anchors.rightMargin: 22

        TextArea {
            id: textArea
            anchors.fill: parent
            placeholderText: qsTr("Text Area")
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.2}
}
##^##*/

