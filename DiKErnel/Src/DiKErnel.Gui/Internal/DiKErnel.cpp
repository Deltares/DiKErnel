// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include "DiKErnel.h"

#include <QFileInfo>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

using namespace std;

namespace DiKErnel::Gui
{
    DiKErnel::DiKErnel(
        int argc,
        char** argv)
    {
        QGuiApplication app(argc, argv);
        QGuiApplication::setApplicationName("DiKErnel");

        QQmlApplicationEngine engine;

        QQmlContext* context = engine.rootContext();
        context->setContextProperty("dikernelApplication", this);

        engine.addImportPath(":/layout");
        engine.load(QUrl("qrc:/layout/DiKErnel/Qml/Main.qml"));

        QGuiApplication::exec();
    }

    void DiKErnel::SetInputFilePath(
        const QUrl& filePath)
    {
        _inputFilePath = QUrl::fromLocalFile(QFileInfo(QUrl(filePath).toLocalFile()).absolutePath()).toString();

        qDebug() << "FILEPATH SELECTED: " << _inputFilePath;
    }
}
