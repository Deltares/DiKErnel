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

#include "OvertoppingAdapter.h"

#include <memory>
#include <sstream>
#include <string>

#include "Geometry.h"
#include "Load.h"
#include "ModelFactors.h"
#include "Result.h"

using namespace DiKErnel::External::Overtopping;

extern "C" __declspec(dllimport) void ValidateInputC(
    Geometry* geometryInput,
    double* dikeHeight,
    ModelFactors* modelFactors,
    bool* success,
    const char* message,
    size_t size);

extern "C" __declspec(dllimport) void calculateQo(
    Load* loadInput,
    Geometry* geometryInput,
    double* dikeHeight,
    ModelFactors* modelFactors,
    Result* result,
    bool* success,
    const char* message,
    int* verbosity,
    const char* logFile,
    size_t messageSize,
    size_t logFileSize);

extern "C" __declspec(dllimport) void SetLanguage(
    const char* languageCode,
    size_t languageCodeLength);

namespace DiKErnel::External::Overtopping
{
    using namespace std;

    ModelFactors OvertoppingAdapter::_modelFactors
    {
        ._factorDeterminationQnFn = 1.0,
        ._factorDeterminationQbFb = 1.0,
        ._mz2 = 1.0,
        ._fshallow = 1.0,
        ._computedOvertopping = 1.0,
        ._criticalOvertopping = 1.0,
        ._relaxationfactor = 1.0,
        ._reductionFactorForeshore = 0.5
    };

    vector<unique_ptr<string>> OvertoppingAdapter::Validate(
        const vector<double>& xValues,
        const vector<double>& zValues,
        const vector<double>& roughnessCoefficients,
        double dikeHeight)
    {
        SetLanguage(_languageCode.c_str(), _languageCode.length());

        auto geometry = CreateGeometry(xValues, zValues, roughnessCoefficients);

        bool success = false;
        const auto messageBuffer = make_unique<string>();
        const int capacity = _nrOfMessages * _bufferSize;
        messageBuffer->reserve(capacity);

        ValidateInputC(&geometry, &dikeHeight, &_modelFactors, &success, messageBuffer->c_str(), messageBuffer->length());

        vector<unique_ptr<string>> validationMessages;

        if (success)
        {
            return validationMessages;
        }

        stringstream messages;
        messages << messageBuffer->c_str();
        string message;

        while (getline(messages, message, '\t'))
        {
            validationMessages.push_back(make_unique<string>(message));
        }

        return validationMessages;
    }

    double OvertoppingAdapter::CalculateZ2(
        double waterLevel,
        double waveHeightHm0,
        double wavePeriodTm10,
        double waveDirection,
        const vector<double>& xValues,
        const vector<double>& zValues,
        const vector<double>& roughnessCoefficients,
        double dikeHeight)
    {
        SetLanguage(_languageCode.c_str(), _languageCode.length());

        Load load
        {
            ._waterLevel = waterLevel,
            ._height = waveHeightHm0,
            ._period = wavePeriodTm10,
            ._direction = waveDirection
        };

        auto geometry = CreateGeometry(xValues, zValues, roughnessCoefficients);

        Result result{};

        bool success = false;
        const auto messageBuffer = make_unique<string>();
        messageBuffer->reserve(_bufferSize);

        const auto logFileName = make_unique<string>();
        logFileName->reserve(_bufferSize);

        calculateQo(&load, &geometry, &dikeHeight, &_modelFactors, &result, &success, messageBuffer->c_str(),
                    &_verbosity, logFileName->c_str(), messageBuffer->length(), logFileName->length());

        return result._z2;
    }

    Geometry OvertoppingAdapter::CreateGeometry(
        const vector<double>& xValues,
        const vector<double>& zValues,
        const vector<double>& roughnessCoefficients)
    {
        return Geometry{
            ._normal = 0.0,
            ._nPoints = static_cast<int>(xValues.size()),
            ._xCoords = xValues.data(),
            ._yCoords = zValues.data(),
            ._roughness = roughnessCoefficients.data()
        };
    }
}
