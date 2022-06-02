// Copyright (C) Stichting Deltares 2022. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, version 3.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/lgpl-3.0.html>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts 1.0

Rectangle {
    width: 1024
    height: 768
    color: "#e6e6e6"
    border.width: 0
    anchors.fill: parent

    Image {
        x: 25
        y: 25
        width: 110
        height: 110
        source: "/Resources/logo.svg"
        sourceSize: Qt.size(110, 110)
    }

    ColumnLayout {
        x: 165
        y: 25
        width: 70
        height: 110

        Label {
            text: qsTr("Applicatie")
            font.pointSize: 10
        }

        Label {
            text: qsTr("Versie")
            font.pointSize: 10
        }

        Label {
            text: qsTr("Bedrijf")
            font.pointSize: 10
        }

        Label {
            text: qsTr("Contact")
            font.pointSize: 10
        }
    }

    ColumnLayout {
        x: 254
        y: 25
        width: 125
        height: 110

        Label {
            text: qsTr("DiKernel-gui")
            font.pointSize: 10
        }

        Label {
            text: dikernelApplication.VersionNumber
            font.pointSize: 10
        }

        Label {
            text: qsTr("Deltares")
            font.pointSize: 10
        }

        Label {
            color: "#2a47b8"
            text: qsTr("<a href='mailto:dikernel@deltares.nl'>dikernel@deltares.nl</a>")
            font.pointSize: 10
            onLinkActivated: Qt.openUrlExternally(link)
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.NoButton
                cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
            }
        }
    }

    ToolSeparator {
        y: 160
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 25
        anchors.rightMargin: 25
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0
        topPadding: 0
        orientation: Qt.Horizontal
    }

    Rectangle {
        x: 400
        y: 25
        width: 600
        height: 110
        color: "#00ffffff"
        border.width: 1
        border.color: "#d3d3d3"

        Text {
            text: qsTr("Disclaimer: De ALPHA versie van DiKErnel is nog in de testfase en zal op vele onderdelen nog moeten worden verbeterd en uitgebreid. Het doel van deze ALPHA versie is om feedback te ontvangen op het huidige functioneren en om tekortkomingen te detecteren. DiKErnel dient met de grootst mogelijke voorzichtigheid te worden geïnstalleerd en gebruikt. Op geen enkele manier mag er worden vertrouwd op de beschikbare resultaten, de bijgeleverde softwaredocumentatie en al het andere materiaal dat bij deze versie beschikbaar wordt gesteld.")
            anchors.fill: parent
            horizontalAlignment: Text.AlignJustify
            wrapMode: Text.Wrap
            anchors.rightMargin: 10
            anchors.bottomMargin: 6
            anchors.leftMargin: 10
            anchors.topMargin: 6
            font.pointSize: 9
        }
    }

    TextField {
        x: 25
        y: 209
        width: 375
        height: 32
        readOnly: true
        placeholderText: qsTr("Invoerbestand.json")
        text: dikernelApplication.InputFilePath
    }

    Label {
        x: 25
        y: 185
        text: qsTr("Invoerbestand")
        font.pointSize: 10
    }

    TextField {
        x: 468
        y: 209
        width: 375
        height: 32
        readOnly: true
        placeholderText: qsTr("Uitvoerbestand.json")
        text: dikernelApplication.OutputFilePath
    }

    Label {
        x: 468
        y: 185
        text: qsTr("Uitvoerbestand")
        font.pointSize: 10
    }

    Button {
        x: 406
        y: 209
        width: 32
        height: 32
        text: qsTr("...")
        onClicked: inputFileDialog.open()
    }

    Button {
        x: 849
        y: 209
        width: 32
        height: 32
        text: qsTr("...")
        onClicked: outputFileDialog.open()
    }

    Button {
        y: 209
        text: qsTr("Start")
        anchors.right: parent.right
        anchors.rightMargin: 25
        rightPadding: 20
        leftPadding: 20
        enabled: dikernelApplication.StartEnabled
        onClicked: dikernelApplication.StartCalculation()
    }

    Button {
        text: qsTr("Wissen")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 25
        anchors.bottomMargin: 25
        leftPadding: 20
        rightPadding: 20
        onClicked: dikernelApplication.ClearLogMessages()
    }

    Button {
        text: qsTr("Kopieer naar klembord")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25
        anchors.rightMargin: 117
        leftPadding: 20
        rightPadding: 20
        onClicked: dikernelApplication.CopyToClipboard()
    }

    Rectangle {
        color: "#ffffff"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 25
        anchors.topMargin: 247
        anchors.rightMargin: 25
        anchors.bottomMargin: 63

        ListView {
            anchors {
                fill: parent
                margins: 8
            }
            clip: true
            ScrollBar.vertical: ScrollBar { }
            ScrollBar.horizontal: ScrollBar { }
            flickableDirection: Flickable.HorizontalAndVerticalFlick
            contentWidth: 1500
            model: dikernelApplication.LogMessages
            delegate: Rectangle {
                height: messageText.implicitHeight + 4

                Text {
                    id: messageText
                    font.pointSize: 10
                    text: display
                }
            }
            onCountChanged: {
                positionViewAtEnd()
            }
        }
    }

    FileDialog {
        id: inputFileDialog
        nameFilters : ["Json-bestanden (*.json)"]
        title: "Selecteer een bestand"
        fileMode: FileDialog.OpenFile
        onAccepted: {
            dikernelApplication.SetInputFilePath(inputFileDialog.selectedFile)
        }
    }

    FileDialog {
        id: outputFileDialog
        nameFilters : ["Json-bestanden (*.json)"]
        title: "Selecteer een bestand"
        fileMode: FileDialog.SaveFile
        onAccepted: {
            dikernelApplication.SetOutputFilePath(outputFileDialog.selectedFile)
        }
    }
}