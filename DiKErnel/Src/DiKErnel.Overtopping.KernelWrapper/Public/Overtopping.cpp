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

#include "Overtopping.h"

#include <sstream>

#include "Result.h"

namespace DiKErnel::Overtopping::KernelWrapper
{
    using namespace std;

    extern "C" void ValidateInputC(
        Geometry* geometry,
        double* dikeHeight,
        Input* input,
        bool* success,
        stringstream* message,
        int* stringLength);

    extern "C" void calculateQo(
        Load* load,
        Geometry* geometry,
        double* dikeHeight,
        Input* input,
        Result* result,
        bool* success,
        stringstream* message,
        int* verbosity,
        stringstream* logFile,
        int* stringLength1,
        int* stringLength2);

    bool Overtopping::Validate(
        Geometry& geometry,
        Input& input,
        double dikeHeight)
    {
        bool success;
        stringstream message;
        int stringLength;

        ValidateInputC(&geometry, &dikeHeight, &input, &success, &message, &stringLength);

        return success;
    }

    double Overtopping::Calculate2P(
        Load& load,
        Geometry& geometry,
        Input& input,
        double dikeHeight)
    {
        bool success;
        int verbosity;
        stringstream message;
        stringstream logFile;
        int stringLength1;
        int stringLength2;

        Result result{};

        calculateQo(&load, &geometry, &dikeHeight, &input, &result, &success, &message, &verbosity, &logFile, &stringLength1, &stringLength2);

        return result._z2;
    }
}
