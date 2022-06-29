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
import QtQuick.Layouts 1.0
import "."

Switch {
    id: control
    font.pointSize: Style.pointSize
    padding: 0
    Layout.fillHeight: true
    Layout.fillWidth: true
    indicator: Rectangle {
        implicitWidth: 44
        implicitHeight: 20
        x: control.leftPadding
        y: parent.height / 2 - height / 2
        radius: 10
        color: control.checked ? "#199CD8" : "#B8B8B8"
        border.color: control.checked ? "#199CD8" : "#B8B8B8"
        Rectangle {
            x: control.checked ? parent.width - width - 4 : 4
            y: parent.height / 2 - height / 2
            width: 12
            height: 12
            radius: 6
            color: "#FFFFFF"
            border.color: control.checked ? "#199CD8" : "#B8B8B8"
        }
    }
    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: "#000000"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
