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

#include "OvertoppingWrapper.h"

#include "Geometry.h"
#include "Load.h"
#include "Result.h"

namespace DiKErnel::Overtopping::KernelWrapper
{
    using namespace std;

    constexpr int SIZE = 32 * 255;
    constexpr int LOGFILESIZE = 32 * 255;
    
    extern "C" __declspec(dllimport) void ValidateInputC(
        Geometry* geometryInput,
        double* dikeHeight,
        Input* modelFactors,
        bool* success,
        const char* message,
        int size);

    extern "C" __declspec(dllimport) void calculateQo(
        Load * loadInput,
        Geometry* geometryInput,
        double* dikeHeight,
        Input * modelFactors,
        Result* result,
        bool* success,
        const char* message,
        int* verbosity,
        const char* logFile,
        int messageSize,
        int logFileSize);

    bool OvertoppingWrapper::Validate(
        Geometry& geometry,
        Input& input,
        double dikeHeight)
    {
        bool success;

        const char* message = new char[SIZE];
        ValidateInputC(&geometry, &dikeHeight, &input, &success, message, SIZE);

        delete[] message;

        return success;
    }

    double OvertoppingWrapper::Calculate2P(
        Load& load,
        Geometry& geometry,
        Input& input,
        double dikeHeight)
    {
        bool success;
        int verbosity = -1;

        Result result{};

        const char* message = new char[SIZE];
        const char* logFile = new char[LOGFILESIZE];
        calculateQo(&load, &geometry, &dikeHeight, &input, &result, &success, message, &verbosity, logFile, SIZE, LOGFILESIZE);
    
        return result._z2;
    }
}
