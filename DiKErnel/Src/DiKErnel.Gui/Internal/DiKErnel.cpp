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

#include "DiKErnel.h"

#include <filesystem>
#include <QClipboard>
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <stdexcept>

#include "ApplicationHelper.h"
#include "Calculator.h"
#include "EventRegistry.h"
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "Validator.h"

namespace DiKErnel::Gui
{
    using namespace Application;
    using namespace Core;
    using namespace KernelWrapper::Json::Input;
    using namespace KernelWrapper::Json::Output;
    using namespace std;
    using namespace std::chrono;
    using namespace Util;

    DiKErnel::DiKErnel(
        int argc,
        char** argv)
        : _stringList(QStringList())
    {
        QGuiApplication app(argc, argv);
        QGuiApplication::setApplicationName("DiKErnel");
        QGuiApplication::setWindowIcon(QIcon(":/Resources/logo.svg"));

        QQmlApplicationEngine engine;

        QQmlContext* context = engine.rootContext();
        context->setContextProperty("dikernelApplication", this);

        engine.addImportPath(":/layout");
        engine.load(QUrl("qrc:/layout/DiKErnel/Qml/Main.qml"));

        connect(this, &DiKErnel::InputFilePathChanged, this, &DiKErnel::SetStartEnabled);
        connect(this, &DiKErnel::OutputFilePathChanged, this, &DiKErnel::SetStartEnabled);

        QGuiApplication::exec();
    }

    QUrl DiKErnel::InputFilePath() const
    {
        return _inputFilePath.value();
    }

    QUrl DiKErnel::OutputFilePath() const
    {
        return _outputFilePath.value();
    }

    bool DiKErnel::WriteMetaData() const
    {
        return _writeMetaData.value();
    }

    bool DiKErnel::StartEnabled() const
    {
        return _startEnabled.value();
    }

    QStringListModel* DiKErnel::LogMessages() const
    {
        return _logMessages.value().get();
    }

    QString DiKErnel::VersionNumber()
    {
        return QString::fromStdString(ApplicationHelper::GetApplicationVersionString());
    }

    QBindable<QUrl> DiKErnel::BindableInputFilePath()
    {
        return &_inputFilePath;
    }

    QBindable<QUrl> DiKErnel::BindableOutputFilePath()
    {
        return &_outputFilePath;
    }

    QBindable<bool> DiKErnel::BindableStartEnabled()
    {
        return &_startEnabled;
    }

    QBindable<bool> DiKErnel::BindableWriteMetaData()
    {
        return &_writeMetaData;
    }

    void DiKErnel::SetInputFilePath(
        const QUrl& inputFilePath)
    {
        _inputFilePath = inputFilePath.toLocalFile();
    }

    void DiKErnel::SetOutputFilePath(
        const QUrl& outputFilePath)
    {
        _outputFilePath = outputFilePath.toLocalFile();
    }

    void DiKErnel::SetWriteMetaData(
        const bool writeMetaData)
    {
        _writeMetaData = writeMetaData;
    }

    void DiKErnel::SetStartEnabled()
    {
        _startEnabled = !_inputFilePath.value().isEmpty() && !_outputFilePath.value().isEmpty();
    }

    void DiKErnel::StartCalculation(
        const bool validateJsonFormat,
        const int outputTypeId)
    {
        try
        {
            const auto outputFilePathString = OutputFilePath().toString();
            const auto outputFilePathStdString = outputFilePathString.toStdString();
            if (filesystem::exists(outputFilePathStdString))
            {
                filesystem::remove(outputFilePathStdString);
            }

            const auto inputFilePathString = InputFilePath().toString();
            AddMessage(QString("De invoer uit bestand \"%1\" wordt gelezen...").arg(inputFilePathString));

            if (validateJsonFormat)
            {
                const auto validationResult = JsonInputComposer::ValidateJson(inputFilePathString.toStdString());

                const auto validationEvents = EventRegistry::Flush();

                LogEventsWhenApplicable("De volgende meldingen zijn opgetreden tijdens het valideren van het Json-formaat:",
                                        GetEventReferences(validationEvents));

                if (!validationResult)
                {
                    LogClosingMessage("Het lezen van de invoer is mislukt.");

                    return;
                }
            }

            const auto inputComposerResult = JsonInputComposer::GetInputDataFromJson(
                inputFilePathString.toStdString());

            LogEventsWhenApplicable("De volgende meldingen zijn opgetreden tijdens het lezen van de invoer:", inputComposerResult->GetEvents());

            if (!inputComposerResult->GetSuccessful())
            {
                LogClosingMessage("Het lezen van de invoer is mislukt.");
                return;
            }

            AddMessage("Het lezen van de invoer is voltooid.");

            const auto& calculationInput = *inputComposerResult->GetData();

            AddMessage("De invoer wordt gevalideerd...");

            const auto validationResult = Validator::Validate(calculationInput);

            LogEventsWhenApplicable("De volgende meldingen zijn opgetreden tijdens het valideren van de invoer:", validationResult->GetEvents());

            if (*validationResult->GetData() == ValidationResultType::Failed)
            {
                LogClosingMessage("De invoer is ongeldig.");
                return;
            }

            if (!validationResult->GetSuccessful())
            {
                LogClosingMessage("Het valideren van de invoer is mislukt.");
                return;
            }

            AddMessage("Het valideren van de invoer is voltooid.");

            AddMessage("De berekening wordt uitgevoerd...");

            const auto startTime = high_resolution_clock::now();

            Calculator calculator(calculationInput);
            calculator.WaitForCompletion();

            const auto calculatorResult = calculator.GetResult();

            LogEventsWhenApplicable("De volgende meldingen zijn opgetreden tijdens de berekening:", calculatorResult->GetEvents());

            if (calculator.GetCalculationState() != CalculationState::FinishedSuccessfully || !calculatorResult->GetSuccessful())
            {
                LogClosingMessage("De berekening is mislukt.");
                return;
            }

            AddMessage("De berekening is voltooid.");

            const duration<double> elapsed = high_resolution_clock::now() - startTime;

            const auto numberOfLocations = calculationInput.GetLocationDependentInputItems().size();
            const auto numberOfTimeSteps = calculationInput.GetTimeDependentInputItems().size() - 1;

            const QString locationString = QString(numberOfLocations == 1 ? "is %1 locatie" : "zijn %1 locaties")
                    .arg(numberOfLocations);

            AddMessage(QString("Er %1 voor %2 %3 berekend in %4 seconden.").arg(locationString)
                                                                           .arg(numberOfTimeSteps)
                                                                           .arg(numberOfTimeSteps == 1 ? "tijdstap" : "tijdstappen")
                                                                           .arg(elapsed.count()));

            AddMessage(QString("De resultaten van de berekening worden naar bestand \"%1\" geschreven...").arg(outputFilePathString));

            vector<pair<string, variant<double, string>>> metaDataItems;

            if (WriteMetaData())
            {
                metaDataItems.emplace_back(pair<string, variant<double, string>>("Versie", ApplicationHelper::GetApplicationVersionString()));
                metaDataItems.emplace_back(pair<string, variant<double, string>>("Besturingssysteem", ApplicationHelper::GetOperatingSystemName()));
                metaDataItems.emplace_back(pair<string, variant<double, string>>("DatumTijd", ApplicationHelper::GetFormattedDateTimeString()));
                metaDataItems.emplace_back(pair<string, variant<double, string>>("Rekentijd", elapsed.count()));
            }

            const auto outputComposerResult = JsonOutputComposer::WriteCalculationOutputToJson(
                outputFilePathStdString,
                *calculatorResult->GetData(),
                GetOutputType(outputTypeId),
                metaDataItems
            );

            LogEventsWhenApplicable("De volgende meldingen zijn opgetreden tijdens het schrijven van de resultaten:",
                                    outputComposerResult->GetEvents());

            if (!outputComposerResult->GetSuccessful())
            {
                LogClosingMessage("Het schrijven van de resultaten is mislukt.");
                return;
            }

            LogClosingMessage("Het schrijven van de resultaten is voltooid.");
        }
        catch (const exception&)
        {
            LogClosingMessage("Er is een onverwachte fout opgetreden. Indien gewenst kunt u contact met ons opnemen via dikernel@deltares.nl.");
        }
    }

    void DiKErnel::ClearLogMessages()
    {
        _stringList.clear();
        _logMessages->setStringList(_stringList);
    }

    void DiKErnel::CopyToClipboard() const
    {
        QClipboard* clipboard = QGuiApplication::clipboard();
        clipboard->setText(_stringList.join("\n"));
    }

    JsonOutputType DiKErnel::GetOutputType(
        const int outputTypeId)
    {
        if (outputTypeId == 0)
        {
            return JsonOutputType::Failure;
        }

        if (outputTypeId == 1)
        {
            return JsonOutputType::Damage;
        }

        return JsonOutputType::Physics;
    }

    void DiKErnel::AddMessage(
        const QString& message)
    {
        _stringList.append(message);
        _logMessages->setStringList(_stringList);
    }

    void DiKErnel::LogEventsWhenApplicable(
        const QString& message,
        const vector<reference_wrapper<Event>>& events)
    {
        if (!events.empty())
        {
            AddMessage(message);

            for (const auto& logEventReference : events)
            {
                const auto& logEvent = logEventReference.get();
                AddMessage(QString("- [%1] %2")
                           .arg(QString::fromUtf8(GetEventTypeString(logEvent.GetEventType())))
                           .arg(QString::fromUtf8(logEvent.GetMessage())));
            }
        }
    }

    vector<reference_wrapper<Event>> DiKErnel::GetEventReferences(
        const std::vector<std::unique_ptr<Event>>& events)
    {
        vector<reference_wrapper<Event>> eventReferences;

        for (const auto& event : events)
        {
            eventReferences.emplace_back(*event);
        }

        return eventReferences;
    }

    string DiKErnel::GetEventTypeString(
        const EventType eventType)
    {
        switch (eventType)
        {
            case EventType::Warning:
                return "Waarschuwing";
            case EventType::Error:
                return "Fout";
            default:
                throw runtime_error("Unsupported EventType");
        }
    }

    void DiKErnel::LogClosingMessage(
        const QString& message)
    {
        AddMessage(message);
        AddMessage("-----------------------------------------------------------------");
    }
}
