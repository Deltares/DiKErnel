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
        fillMode: Image.PreserveAspectFit
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
            text: qsTr("22.1.1.0 (ALPHA)")
            font.pointSize: 10
        }

        Label {
            text: qsTr("Deltares")
            font.pointSize: 10
        }

        Label {
            color: "#2a47b8"
            text: qsTr("dikernel@deltares.nl")
            font.pointSize: 10
        }
    }

    ToolSeparator {
        x: 0
        y: 160
        width: 1024
        rightPadding: 20
        leftPadding: 20
        bottomPadding: 0
        topPadding: 0
        orientation: Qt.Horizontal
    }

    ToolSeparator {
        x: 380
        y: 0
        width: 32
        height: 160
        bottomPadding: 20
        topPadding: 20
    }

    Text {
        x: 420
        y: 25
        width: 580
        height: 110
        text: qsTr("Disclaimer: De ALPHA versie van DiKErnel is nog in de testfase en zal op vele onderdelen nog moeten worden verbeterd en uitgebreid. Het doel van deze ALPHA versie is om feedback te ontvangen op het huidige functioneren en om tekortkomingen te detecteren. DiKErnel dient met de grootst mogelijke voorzichtigheid te worden geïnstalleerd en gebruikt. Op geen enkele manier mag er worden vertrouwd op de beschikbare resultaten, de bijgeleverde softwaredocumentatie en al het andere materiaal dat bij deze versie beschikbaar wordt gesteld.")
        horizontalAlignment: Text.AlignJustify
        wrapMode: Text.Wrap
        font.pointSize: 10
    }

    TextField {
        x: 25
        y: 209
        width: 375
        height: 32
        placeholderText: qsTr("Invoerbestand")
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
        placeholderText: qsTr("Uitvoerbestand")
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

    FileDialog {
        id: inputFileDialog
        nameFilters : ["Json Files (*.json)"]
        title: "Please choose a file"
        onAccepted: {
            dikernelApplication.SetInputFilePath(inputFileDialog.selectedFile)
        }
    }

    Button {
        x: 849
        y: 209
        width: 32
        height: 32
        text: qsTr("...")
    }

    Button {
        x: 930
        y: 209
        text: qsTr("Start")
        rightPadding: 20
        leftPadding: 20
    }

    Button {
        x: 914
        y: 711
        text: qsTr("Wissen")
        leftPadding: 20
        rightPadding: 20
    }

    Button {
        x: 716
        y: 711
        text: qsTr("Kopieer naar klembord")
        leftPadding: 20
        rightPadding: 20
    }

    Rectangle {
        x: 25
        y: 247
        width: 975
        height: 458
        color: "#ffffff"

        ScrollView {
            anchors.fill: parent
            Text {
                anchors.fill: parent
                leftPadding: 8
                topPadding: 8
                font.pointSize: 10
                textFormat: Text.RichText
            }
        }
    }
}