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

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <stdexcept>

#include "Calculator.h"
#include "JsonInputComposer.h"
#include "JsonOutputComposer.h"
#include "Validator.h"

using namespace DiKErnel::Core;
using namespace DiKErnel::KernelWrapper::Json::Input;
using namespace DiKErnel::KernelWrapper::Json::Output;
using namespace std;

namespace DiKErnel::Gui
{
    DiKErnel::DiKErnel(
        int argc,
        char** argv)
        : _stringList(QStringList())
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

    DiKErnel::~DiKErnel()
    {
        delete _logMessages;
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

    void DiKErnel::StartCalculation()
    {
        AddMessage("Fetching input");

        const auto filePath = InputFilePath().toString().toStdString();

        // Read input Json file
        const auto inputComposerResult = JsonInputComposer::GetInputDataFromJson(filePath);

        for (auto& logEvent : inputComposerResult->GetEvents())
        {
            AddMessage(QString::fromUtf8(logEvent.get().GetMessage()));
        }

        if (!inputComposerResult->GetSuccessful())
        {
            AddMessage("Fetching input failed");
            return;
        }

        const auto* inputData = inputComposerResult->GetData();
        const auto& calculationInput = inputData->GetCalculationInput();

        AddMessage("Validating input");

        const auto validationResult = Validator::Validate(calculationInput);

        for (auto& logEvent : validationResult->GetEvents())
        {
            AddMessage(QString::fromUtf8(logEvent.get().GetMessage()));
        }

        if (*validationResult->GetData() == ValidationResultType::Failed)
        {
            AddMessage("Validation failed");
        }

        if (!validationResult->GetSuccessful())
        {
            AddMessage("Validating input unsuccessful");
            return;
        }

        AddMessage("Performing calculation");

        Calculator calculator(calculationInput);
        calculator.WaitForCompletion();

        const auto calculatorResult = calculator.GetResult();

        for (auto& logEvent : calculatorResult->GetEvents())
        {
            AddMessage(QString::fromUtf8(logEvent.get().GetMessage()));
        }

        if (calculator.GetCalculationState() != CalculationState::FinishedSuccessfully)
        {
            AddMessage("Calculation not finished successfully");
            return;
        }

        if (!calculatorResult->GetSuccessful())
        {
            AddMessage("Calculation failed");
            return;
        }

        AddMessage("Writing output");
        const auto outputComposerResult = JsonOutputComposer::WriteCalculationOutputToJson(OutputFilePath().toString().toStdString(),
                                                                                           *calculatorResult->GetData(),
                                                                                           ConvertProcessType(inputData->GetProcessType()));

        for (auto& logEvent : outputComposerResult->GetEvents())
        {
            AddMessage(QString::fromUtf8(logEvent.get().GetMessage()));
        }

        if (!outputComposerResult->GetSuccessful())
        {
            AddMessage("Writing output failed");
        }
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

    void DiKErnel::AddMessage(
        const QString& message)
    {
        _stringList.append(message);
        _logMessages->setStringList(_stringList);
    }

    QUrl DiKErnel::InputFilePath() const
    {
        return _inputFilePath.value();
    }

    QUrl DiKErnel::OutputFilePath() const
    {
        return _outputFilePath.value();
    }

    QStringListModel* DiKErnel::LogMessages() const
    {
        return _logMessages.value();
    }

    QBindable<QUrl> DiKErnel::BindableInputFilePath()
    {
        return &_inputFilePath;
    }

    QBindable<QUrl> DiKErnel::BindableOutputFilePath()
    {
        return &_outputFilePath;
    }

    QBindable<QStringListModel*> DiKErnel::BindableLogMessages()
    {
        return &_logMessages;
    }
}
