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

#include "Calculator.h"
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "Validator.h"
#include "Version.h"

namespace DiKErnel::Gui
{
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
        return QString::fromStdString(VERSION_STRING);
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

    void DiKErnel::SetStartEnabled()
    {
        _startEnabled = !_inputFilePath.value().isEmpty() && !_outputFilePath.value().isEmpty();
    }

    void DiKErnel::StartCalculation()
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

            const auto inputComposerResult = JsonInputComposer::GetInputDataFromJson(
                inputFilePathString.toStdString());

            LogEventsWhenApplicable("De volgende meldingen zijn opgetreden tijdens het lezen van de invoer:", inputComposerResult->GetEvents());

            if (!inputComposerResult->GetSuccessful())
            {
                LogClosingMessage("Het lezen van de invoer is mislukt.");
                return;
            }

            AddMessage("Het lezen van de invoer is voltooid.");

            const auto* inputData = inputComposerResult->GetData();
            const auto& calculationInput = inputData->GetCalculationInput();

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

            const auto endTime = high_resolution_clock::now();
            const duration<double> elapsed = endTime - startTime;

            const auto numberOfLocations = calculationInput.GetLocationDependentInputItems().size();
            const auto numberOfTimeSteps = calculationInput.GetTimeDependentInputItems().size() - 1;

            const QString locationString = QString(numberOfLocations == 1 ? "is %1 locatie" : "zijn %1 locaties")
                    .arg(numberOfLocations);

            AddMessage(QString("Er %1 voor %2 %3 berekend in %4 seconden.").arg(locationString)
                                                                           .arg(numberOfTimeSteps)
                                                                           .arg(numberOfTimeSteps == 1 ? "tijdstap" : "tijdstappen")
                                                                           .arg(elapsed.count()));

            AddMessage(QString("De resultaten van de berekening worden naar bestand \"%1\" geschreven...").arg(outputFilePathString));

            const auto outputComposerResult = JsonOutputComposer::WriteCalculationOutputToJson(
                outputFilePathStdString,
                *calculatorResult->GetData(),
                ConvertProcessType(inputData->GetProcessType()),
                vector
                {
                    pair<string, variant<double, string>>("Versie", VERSION_STRING),
                    pair<string, variant<double, string>>("Besturingssysteem", GetOperatingSystemName()),
                    pair<string, variant<double, string>>("DatumTijd", GetFormattedDateTimeString()),
                    pair<string, variant<double, string>>("Rekentijd", elapsed.count())
                }
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
                AddMessage(QString("- %1: %2")
                           .arg(QString::fromUtf8(GetEventTypeString(logEvent.GetEventType())))
                           .arg(QString::fromUtf8(logEvent.GetMessage())));
            }
        }
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

    JsonOutputType DiKErnel::ConvertProcessType(
        const JsonInputProcessType processType)
    {
        switch (processType)
        {
            case JsonInputProcessType::Failure:
                return JsonOutputType::Failure;
            case JsonInputProcessType::Damage:
                return JsonOutputType::Damage;
            case JsonInputProcessType::Physics:
                return JsonOutputType::Physics;
            default:
                throw runtime_error("Unsupported processType");
        }
    }

    string DiKErnel::GetOperatingSystemName()
    {
        #ifdef _WIN64
        return "Windows 64-bit";
        #elif _WIN32
        return "Windows 32-bit";
        #elif __APPLE__ || __MACH__
        return "Mac OSX";
        #elif __linux__
        return "Linux";
        #elif __FreeBSD__
        return "FreeBSD";
        #elif __unix || __unix__
        return "Unix";
        #else
        return "Other";
        #endif
    }

    string DiKErnel::GetFormattedDateTimeString()
    {
        tm tm{};

        const auto nowAsTime = system_clock::to_time_t(system_clock::now());

        localtime_s(&tm, &nowAsTime);

        char formattedTime[20];

        strftime(formattedTime, sizeof formattedTime, "%FT%TZ", &tm);

        return formattedTime;
    }
}
