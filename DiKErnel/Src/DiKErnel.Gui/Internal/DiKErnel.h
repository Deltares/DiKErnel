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

#pragma once

#include <QObject>
#include <QProperty>
#include <QStringListModel>
#include <QUrl>

#include "Event.h"

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

            Q_PROPERTY(QStringListModel* LogMessages
                READ LogMessages
                CONSTANT)

            Q_PROPERTY(bool StartEnabled
                READ StartEnabled
                BINDABLE BindableStartEnabled)

            Q_PROPERTY(QString VersionNumber
                READ VersionNumber
                CONSTANT)

        public:
            explicit DiKErnel(
                int argc,
                char** argv);

            QUrl InputFilePath() const;

            QUrl OutputFilePath() const;

            bool StartEnabled() const;

            QStringListModel* LogMessages() const;

            static QString VersionNumber();

            QBindable<QUrl> BindableInputFilePath();

            QBindable<QUrl> BindableOutputFilePath();

            QBindable<bool> BindableStartEnabled();

        public slots:
            void SetInputFilePath(
                const QUrl& inputFilePath);

            void SetOutputFilePath(
                const QUrl& outputFilePath);

            void SetStartEnabled();

            void StartCalculation(
                bool validateJsonFormat,
                bool writeMetaData);

            void ClearLogMessages();

            void CopyToClipboard() const;

        signals:
            void InputFilePathChanged();

            void OutputFilePathChanged();

            void StartEnabledChanged();

            void LogMessagesChanged();

        private:
            void AddMessage(
                const QString& message);

            void LogEventsWhenApplicable(
                const QString& message,
                const std::vector<std::reference_wrapper<Util::Event>>& events);

            static std::vector<std::reference_wrapper<Util::Event>> GetEventReferences(
                const std::vector<std::unique_ptr<Util::Event>>& events);

            static std::string GetEventTypeString(
                Util::EventType eventType);

            void LogClosingMessage(
                const QString& message);

            QStringList _stringList;

            Q_OBJECT_BINDABLE_PROPERTY(
                DiKErnel, QUrl, _inputFilePath, &DiKErnel::InputFilePathChanged)

            Q_OBJECT_BINDABLE_PROPERTY(
                DiKErnel, QUrl, _outputFilePath, &DiKErnel::OutputFilePathChanged)

            Q_OBJECT_BINDABLE_PROPERTY(
                DiKErnel, bool, _startEnabled, &DiKErnel::StartEnabledChanged)

            Q_OBJECT_BINDABLE_PROPERTY_WITH_ARGS(
                DiKErnel, std::unique_ptr<QStringListModel>, _logMessages,
                std::make_unique<QStringListModel>(this), &DiKErnel::LogMessagesChanged)
    };
}
