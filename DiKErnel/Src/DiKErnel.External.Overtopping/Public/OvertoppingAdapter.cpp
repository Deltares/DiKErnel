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

#include <cstdlib>
#include <memory>
#include <string>

#include "Geometry.h"
#include "Load.h"
#include "Result.h"
#include "Input.h"

using namespace DiKErnel::External::Overtopping;

extern "C" __declspec(dllimport) void ValidateInputC(
    Geometry* geometryInput,
    double* dikeHeight,
    Input* modelFactors,
    bool* success,
    const char* message,
    int size);

extern "C" __declspec(dllimport) void calculateQo(
    Load* loadInput,
    Geometry* geometryInput,
    double* dikeHeight,
    Input* modelFactors,
    Result* result,
    bool* success,
    const char* message,
    int* verbosity,
    const char* logFile,
    int messageSize,
    int logFileSize);

namespace DiKErnel::External::Overtopping
{
    using namespace std;

    constexpr int LOG_FILE_NAME_SIZE = 256;

    void OvertoppingAdapter::Validate(
        Geometry& geometry,
        Input& input,
        const string* messageBuffer,
        bool* success,
        double dikeHeight)
    {
        const int messageLength = messageBuffer->length();
        ValidateInputC(&geometry, &dikeHeight, &input, success, messageBuffer->c_str(), messageLength);
    }

    void OvertoppingAdapter::CalculateQo(
        Load& load,
        Geometry& geometry,
        Input& input,
        Result* result,
        const string* messageBuffer,
        bool* success,
        double dikeHeight)
    {
        int verbosity = -1;

        const auto logFileName = make_unique<string>();
        logFileName->reserve(LOG_FILE_NAME_SIZE);

        const int messageLength = messageBuffer->length();
        calculateQo(&load, &geometry, &dikeHeight, &input, result, success,
                    messageBuffer->c_str(), &verbosity, logFileName->c_str(), messageLength, LOG_FILE_NAME_SIZE);
    }
}
