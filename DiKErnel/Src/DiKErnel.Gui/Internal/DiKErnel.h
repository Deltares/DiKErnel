﻿// Copyright (C) Stichting Deltares 2022. All rights reserved.
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

#pragma once
#include <QObject>
#include <QProperty>
#include <QUrl>

namespace DiKErnel::Gui
{
    class DiKErnel : public QObject
    {
            Q_OBJECT

            Q_PROPERTY(QUrl InputFilePath
                READ InputFilePath
                WRITE SetInputFilePath
                BINDABLE BindableInputFilePath)

            Q_PROPERTY(QUrl OutputFilePath
                READ OutputFilePath
                WRITE SetOutputFilePath
                BINDABLE BindableOutputFilePath)

        public:
            explicit DiKErnel(
                int argc,
                char** argv);

            QUrl InputFilePath() const;

            QUrl OutputFilePath() const;

            QBindable<QUrl> BindableInputFilePath();

            QBindable<QUrl> BindableOutputFilePath();

        public slots:
            void SetInputFilePath(
                const QUrl& inputFilePath);

            void SetOutputFilePath(
                const QUrl& outputFilePath);

        signals:
            void InputFilePathChanged();

            void OutputFilePathChanged();

        private:
            Q_OBJECT_BINDABLE_PROPERTY(
                DiKErnel, QUrl, _inputFilePath, &DiKErnel::InputFilePathChanged)

            Q_OBJECT_BINDABLE_PROPERTY(
                DiKErnel, QUrl, _outputFilePath, &DiKErnel::OutputFilePathChanged)
    };
}
