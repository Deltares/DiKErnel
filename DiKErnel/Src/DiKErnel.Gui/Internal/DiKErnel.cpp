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
        engine.load(QUrl("qrc:/layout/QtDiKErnel/Qml/Main.qml"));

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

    bool DiKErnel::ValidateJsonFormat() const
    {
        return _validateJsonFormat.value();
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

    QBindable<bool> DiKErnel::BindableValidateJsonFormat()
    {
        return &_validateJsonFormat;
    }

    QBindable<bool> DiKErnel::BindableWriteMetaData()
    {
        return &_writeMetaData;
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

    void DiKErnel::SetValidateJsonFormat(
        const bool validateJsonFormat)
    {
        _validateJsonFormat = validateJsonFormat;
    }

    void DiKErnel::SetWriteMetaData(
        const bool writeMetaData)
    {
        _writeMetaData = writeMetaData;
    }

    void DiKErnel::SetOutputLevelToFailure()
    {
        _outputLevel = JsonOutputType::Failure;
    }

    void DiKErnel::SetOutputLevelToDamage()
    {
        _outputLevel = JsonOutputType::Damage;
    }

    void DiKErnel::SetOutputLevelToPhysics()
    {
        _outputLevel = JsonOutputType::Physics;
    }

    void DiKErnel::SetStartEnabled()
    {
        const auto& inputFilePathValue = _inputFilePath.value();
        const auto& outputFilePathValue = _outputFilePath.value();

        _startEnabled = !inputFilePathValue.isEmpty()
                && !outputFilePathValue.isEmpty()
                && inputFilePathValue != outputFilePathValue;
    }

    void DiKErnel::StartCalculation()
    {
        try
        {
            map<string, vector<string>> warningMessageCache;
            map<string, vector<string>> errorMessageCache;

            const auto inputFilePathString = InputFilePath().toString();
            const auto outputFilePathString = OutputFilePath().toString();
            const auto outputFilePathStdString = outputFilePathString.toStdString();

            if (filesystem::exists(outputFilePathStdString))
            {
                filesystem::remove(outputFilePathStdString);
            }

            const auto calculationInputDataResult = ValidateAndReadJsonInput(inputFilePathString, warningMessageCache, errorMessageCache);
            if (calculationInputDataResult == nullptr)
            {
                return;
            }

            const auto& calculationInput = *calculationInputDataResult->GetData();

            if (!ValidateCalculationInput(calculationInput, warningMessageCache, errorMessageCache))
            {
                return;
            }

            const auto startTime = high_resolution_clock::now();

            const auto calculatorResult = Calculate(calculationInput, warningMessageCache, errorMessageCache);

            if (calculatorResult == nullptr)
            {
                return;
            }

            const duration<double> elapsed = high_resolution_clock::now() - startTime;

            WriteOutput(outputFilePathStdString, *calculatorResult->GetData(), elapsed, warningMessageCache, errorMessageCache);

            WriteFinalLogMessages(calculationInput, elapsed, warningMessageCache);
        }
        catch (const exception&)
        {
            AddMessage("<b>Berekening mislukt</b>");

            AddMessage("Er is een onverwachte fout opgetreden. Indien gewenst kunt u contact met ons opnemen via dikernel@deltares.nl.");

            AddMessage("");
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

        QString clipboardText = _stringList.join("\n");

        clipboardText.remove("<b>");
        clipboardText.remove("</b>");
        clipboardText.remove("<i>");
        clipboardText.remove("</i>");

        clipboard->setText(clipboardText);
    }

    unique_ptr<DataResult<ICalculationInput>> DiKErnel::ValidateAndReadJsonInput(
        const QString& inputFilePathString,
        map<string, vector<string>>& warningMessageCache,
        map<string, vector<string>>& errorMessageCache)
    {
        if (ValidateJsonFormat())
        {
            const auto validationResult = JsonInputComposer::ValidateJson(inputFilePathString.toStdString());

            const auto validationEvents = EventRegistry::Flush();

            CacheMessagesWhenApplicable("het valideren van het Json-formaat", GetEventReferences(validationEvents), warningMessageCache,
                                        errorMessageCache);

            if (!validationResult)
            {
                LogFailureMessage(errorMessageCache);
                return nullptr;
            }
        }

        auto inputComposerResult = JsonInputComposer::GetInputDataFromJson(inputFilePathString.toStdString());

        CacheMessagesWhenApplicable("het lezen van de invoer", inputComposerResult->GetEvents(), warningMessageCache, errorMessageCache);

        if (!inputComposerResult->GetSuccessful())
        {
            LogFailureMessage(errorMessageCache);
            return nullptr;
        }

        return inputComposerResult;
    }

    bool DiKErnel::ValidateCalculationInput(
        const ICalculationInput& calculationInput,
        map<string, vector<string>>& warningMessageCache,
        map<string, vector<string>>& errorMessageCache)
    {
        const auto validationResult = Validator::Validate(calculationInput);

        CacheMessagesWhenApplicable("het valideren van de invoer", validationResult->GetEvents(), warningMessageCache, errorMessageCache);

        if (*validationResult->GetData() == ValidationResultType::Failed || !validationResult->GetSuccessful())
        {
            LogFailureMessage(errorMessageCache);
            return false;
        }

        return true;
    }

    shared_ptr<DataResult<CalculationOutput>> DiKErnel::Calculate(
        const ICalculationInput& calculationInput,
        map<string, vector<string>>& warningMessageCache,
        map<string, vector<string>>& errorMessageCache)
    {
        Calculator calculator(calculationInput);
        calculator.WaitForCompletion();

        auto calculatorResult = calculator.GetResult();

        CacheMessagesWhenApplicable("de berekening", calculatorResult->GetEvents(), warningMessageCache, errorMessageCache);

        if (calculator.GetCalculationState() != CalculationState::FinishedSuccessfully || !calculatorResult->GetSuccessful())
        {
            LogFailureMessage(errorMessageCache);
            return nullptr;
        }

        return calculatorResult;
    }

    void DiKErnel::WriteOutput(
        const string& outputFilePathStdString,
        const CalculationOutput& calculationOutput,
        const duration<double> elapsed,
        map<string, vector<string>>& warningMessageCache,
        map<string, vector<string>>& errorMessageCache)
    {
        vector<pair<string, variant<double, string>>> metaDataItems;

        if (WriteMetaData())
        {
            metaDataItems.emplace_back(
                pair<string, variant<double, string>>("versie", ApplicationHelper::GetApplicationVersionString()));
            metaDataItems.emplace_back(
                pair<string, variant<double, string>>("besturingssysteem", ApplicationHelper::GetOperatingSystemName()));
            metaDataItems.emplace_back(
                pair<string, variant<double, string>>("tijdstipBerekening", ApplicationHelper::GetFormattedDateTimeString()));
            metaDataItems.emplace_back(
                pair<string, variant<double, string>>("tijdsduurBerekening", elapsed.count()));
        }

        const auto outputComposerResult = JsonOutputComposer::WriteCalculationOutputToJson(
            outputFilePathStdString,
            calculationOutput,
            _outputLevel,
            metaDataItems);

        CacheMessagesWhenApplicable("het schrijven van de resultaten", outputComposerResult->GetEvents(), warningMessageCache,
                                    errorMessageCache);

        if (!outputComposerResult->GetSuccessful())
        {
            LogFailureMessage(errorMessageCache);
        }
    }

    void DiKErnel::WriteFinalLogMessages(
        const ICalculationInput& calculationInput,
        const duration<double> elapsed,
        map<string, vector<string>>& warningMessageCache)
    {
        AddMessage("<b>Berekening gelukt</b>");

        LogCachedMessages(warningMessageCache, "waarschuwing", "waarschuwingen");

        const auto numberOfLocations = calculationInput.GetLocationDependentInputItems().size();
        const auto numberOfTimeSteps = calculationInput.GetTimeDependentInputItems().size() - 1;

        const QString timeStepString = QString(numberOfTimeSteps == 1 ? "is %1 tijdstap" : "zijn %1 tijdstappen")
                .arg(numberOfTimeSteps);

        AddMessage(QString("Er %1 doorgerekend voor %2 %3.")
                   .arg(timeStepString)
                   .arg(numberOfLocations)
                   .arg(numberOfLocations == 1 ? "locatie" : "locaties"));

        AddMessage(QString("De rekenduur bedroeg %1 seconden.").arg(elapsed.count()));

        AddMessage("Zie het uitvoerbestand voor verdere details.");

        AddMessage("");
    }

    void DiKErnel::AddMessage(
        const QString& message)
    {
        _stringList.append(message);
        _logMessages->setStringList(_stringList);
    }

    void DiKErnel::CacheMessagesWhenApplicable(
        const string& endOfDescription,
        const vector<reference_wrapper<Event>>& events,
        map<string, vector<string>>& warningMessageCache,
        map<string, vector<string>>& errorMessageCache)
    {
        vector<string> warningMessages;
        vector<string> errorMessages;

        for (const auto& logEventReference : events)
        {
            const auto& logEvent = logEventReference.get();

            logEvent.GetEventType() == EventType::Warning
                ? warningMessages.push_back(logEvent.GetMessage())
                : errorMessages.push_back(logEvent.GetMessage());
        }

        if (!warningMessages.empty())
        {
            warningMessageCache[endOfDescription] = warningMessages;
        }

        if (!errorMessages.empty())
        {
            errorMessageCache[endOfDescription] = errorMessages;
        }
    }

    vector<reference_wrapper<Event>> DiKErnel::GetEventReferences(
        const vector<unique_ptr<Event>>& events)
    {
        vector<reference_wrapper<Event>> eventReferences;

        for (const auto& event : events)
        {
            eventReferences.emplace_back(*event);
        }

        return eventReferences;
    }

    void DiKErnel::LogFailureMessage(
        map<string, vector<string>>& errorMessageCache)
    {
        AddMessage("<b>Berekening mislukt</b>");

        LogCachedMessages(errorMessageCache, "fout", "fouten");

        AddMessage("");
    }

    void DiKErnel::LogCachedMessages(
        map<string, vector<string>>& messageCache,
        const string& messageTypeDescriptionSingular,
        const string& messageTypeDescriptionPlural)
    {
        for (const auto& [endOfDescription, messages] : messageCache)
        {
            if (messages.size() == 1)
            {
                AddMessage(QString("De volgende %1 is opgetreden tijdens %2:")
                           .arg(messageTypeDescriptionSingular.c_str())
                           .arg(endOfDescription.c_str()));
                AddMessage(QString("<i>%1</i>").arg(messages.at(0).c_str()));
            }
            else
            {
                AddMessage(QString("De volgende %1 zijn opgetreden tijdens %2:")
                           .arg(messageTypeDescriptionPlural.c_str())
                           .arg(endOfDescription.c_str()));

                for (const auto& message : messages)
                {
                    AddMessage(QString("- <i>%1</i>").arg(message.c_str()));
                }
            }
        }
    }
}
