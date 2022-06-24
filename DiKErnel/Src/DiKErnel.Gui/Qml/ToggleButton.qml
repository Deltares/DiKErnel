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

Button {
    id: button
    checkable: true
    Layout.fillHeight: true
    Layout.fillWidth: true
    font.pointSize: 10
    contentItem: Text {
        smooth: true
        text: button.text
        font: button.font
        color: button.checked ? "white" : "black"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
    background: Rectangle {
        color: button.checked ? "#199CD8" : "#B8B8B8"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (!button.checked)
            {
                button.checked = true;
            }
        }
    }
}
