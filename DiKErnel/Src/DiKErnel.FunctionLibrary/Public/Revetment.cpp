// Copyright (C) Stichting Deltares 2020. All rights reserved.
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

#include "Revetment.h"

#include <cmath>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    int Revetment::IncrementTime(
        const int beginTime,
        const int endTime)
    {
        return endTime - beginTime;
    }

    double Revetment::AverageNumberOfWaves(
        const double incrementTime,
        const double wavePeriodTm10,
        const double averageNumberOfWavesCtm)
    {
        return incrementTime / (averageNumberOfWavesCtm * wavePeriodTm10);
    }

    double Revetment::InterpolationVerticalHeight(
        const double horizontalPosition,
        vector<pair<double, double>> dikeProfile)
    {
        for (auto i = 0; i < static_cast<int>(dikeProfile.size()); ++i)
        {
            const auto& [xCurrentDikeProfilePoint, zCurrentDikeProfilePoint] = dikeProfile[i];

            if (abs(xCurrentDikeProfilePoint - horizontalPosition) <= numeric_limits<double>::epsilon())
            {
                return zCurrentDikeProfilePoint;
            }

            if (xCurrentDikeProfilePoint > horizontalPosition)
            {
                if (i == 0)
                {
                    return numeric_limits<double>::infinity();
                }

                const auto& [xPreviousDikeProfilePoint, zPreviousDikeProfilePoint] = dikeProfile[i - 1];

                return zPreviousDikeProfilePoint + (zCurrentDikeProfilePoint - zPreviousDikeProfilePoint)
                        / (xCurrentDikeProfilePoint - xPreviousDikeProfilePoint)
                        * (horizontalPosition - xPreviousDikeProfilePoint);
            }
        }

        return numeric_limits<double>::infinity();
    }

    double Revetment::Damage(
        const double incrementDamage,
        const double initialDamage)
    {
        return initialDamage + incrementDamage;
    }

    bool Revetment::FailureRevetment(
        const double damage,
        const double initialDamage,
        const double failureNumber)
    {
        return initialDamage < failureNumber && damage >= failureNumber;
    }

    double Revetment::DurationInTimeStepFailure(
        const double incrementTime,
        const double incrementDamage,
        const double failureNumber,
        const double initialDamage)
    {
        return (failureNumber - initialDamage) / incrementDamage * incrementTime;
    }

    int Revetment::TimeOfFailure(
        const double durationInTimeStepFailure,
        const double beginTime)
    {
        return static_cast<int>(ceil(durationInTimeStepFailure + beginTime));
    }
}
