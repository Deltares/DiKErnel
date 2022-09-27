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
#include <string>

#include "Geometry.h"
#include "Load.h"
#include "Result.h"
#include "ModelFactors.h"

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

    void OvertoppingAdapter::Validate(
        Geometry& geometry,
        double dikeHeight,
        ModelFactors& modelFactors,
        const string* messageBuffer,
        bool* success)
    {
        SetLanguage(_languageCode.c_str(), _languageCode.length());
        ValidateInputC(&geometry, &dikeHeight, &modelFactors, success, messageBuffer->c_str(), messageBuffer->length());
    }

    void OvertoppingAdapter::CalculateQo(
        Load& load,
        Geometry& geometry,
        double dikeHeight,
        ModelFactors& modelFactors,
        Result* result,
        const string* messageBuffer,
        bool* success)
    {
        SetLanguage(_languageCode.c_str(), _languageCode.length());

        const auto logFileName = make_unique<string>();
        logFileName->reserve(_logFileNameSize);

        calculateQo(&load, &geometry, &dikeHeight, &modelFactors, result, success,
                    messageBuffer->c_str(), &_verbosity, logFileName->c_str(), messageBuffer->length(), _logFileNameSize);
    }
}
