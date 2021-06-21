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

#include "AsphaltRevetment.h"

#include <cmath>
#include <tuple>
#include <utility>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double AsphaltRevetment::IncrementDamage(
        const double logFailureTension,
        const double averageNumberOfWaves,
        const std::vector<std::tuple<double, double>>& widthFactors,
        const std::vector<std::tuple<double, double>>& depthFactors,
        const std::vector<std::tuple<double, double>>& impactFactors,
        const double fatigueAlpha,
        const double fatigueBeta)
    {
        double result = 0;

        for (const auto& widthFactor : widthFactors)
        {
            const auto widthFactorValue = get<0>(widthFactor);
            const auto widthFactorProbability = get<1>(widthFactor);
            const auto depthFactorAccumulation = DepthFactorAccumulation(logFailureTension, averageNumberOfWaves, widthFactorValue, depthFactors,
                                                                         impactFactors, fatigueAlpha, fatigueBeta);

            result += widthFactorProbability * depthFactorAccumulation;
        }

        return result;
    }

    double AsphaltRevetment::LogFailureTension(
        const double failureTension)
    {
        return log10(failureTension);
    }

    double AsphaltRevetment::DepthFactorAccumulation(
        const double logFailureTension,
        const double averageNumberOfWaves,
        const double widthFactorValue,
        const std::vector<std::tuple<double, double>>& depthFactors,
        const std::vector<std::tuple<double, double>>& impactFactors,
        const double fatigueAlpha,
        const double fatigueBeta)
    {
        double result = 0;

        for (const auto& depthFactor : depthFactors)
        {
            const auto depthFactorValue = get<0>(depthFactor);
            const auto depthFactorProbability = get<1>(depthFactor);
            const auto impactFactorAccumulation = ImpactFactorAccumulation(logFailureTension, averageNumberOfWaves, widthFactorValue,
                                                                           depthFactorValue, impactFactors, fatigueAlpha, fatigueBeta);

            result += depthFactorProbability * impactFactorAccumulation;
        }

        return result;
    }

    double AsphaltRevetment::ImpactFactorAccumulation(
        const double logFailureTension,
        const double averageNumberOfWaves,
        const double widthFactorValue,
        const double depthFactorValue,
        const std::vector<std::tuple<double, double>>& impactFactors,
        const double fatigueAlpha,
        const double fatigueBeta)
    {
        double result = 0;

        for (const auto& impactFactor : impactFactors)
        {
            const auto impactFactorValue = get<0>(impactFactor);
            const auto impactFactorProbability = get<1>(impactFactor);
            const auto fatigue = Fatigue(logFailureTension, widthFactorValue, depthFactorValue, impactFactorValue, fatigueAlpha, fatigueBeta);

            result += impactFactorProbability * averageNumberOfWaves * fatigue;
        }

        return result;
    }

    double AsphaltRevetment::Fatigue(
        const double logFailureTension,
        double widthFactorValue,
        double depthFactorValue,
        double impactFactorValue,
        const double fatigueAlpha,
        const double fatigueBeta)
    {
        const auto logTension = 2.2;

        return pow(10.0, -1.0 * fatigueBeta * pow(max(0.0, logFailureTension - logTension), fatigueAlpha));
    }

    double AsphaltRevetment::LogTension(
        const double tanA,
        double widthFactorValue,
        double depthFactorValue,
        const double impactFactorValue,
        const double impactNumberC)
    {
        const auto impactNumber = ImpactNumber(tanA, impactFactorValue, impactNumberC);
        const auto bendingStress = 1.1;

        return log10(impactNumber * bendingStress);
    }

    double AsphaltRevetment::ImpactNumber(
        const double tanA,
        const double impactFactorValue,
        const double impactNumberC)
    {
        return 4.0 * impactNumberC * tanA * impactFactorValue;
    }
}
