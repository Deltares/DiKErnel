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
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness,
        const double tanA,
        const std::vector<std::tuple<double, double>>& widthFactors,
        const std::vector<std::tuple<double, double>>& depthFactors,
        const std::vector<std::tuple<double, double>>& impactFactors,
        const double fatigueAlpha,
        const double fatigueBeta,
        const double impactNumberC)
    {
        double result = 0;

        for (const auto& widthFactor : widthFactors)
        {
            const auto widthFactorValue = get<0>(widthFactor);
            const auto widthFactorProbability = get<1>(widthFactor);
            const auto depthFactorAccumulation = DepthFactorAccumulation(logFailureTension, averageNumberOfWaves, maximumPeakStress,
                                                                         stiffnessRelation, computationalThickness, tanA, widthFactorValue,
                                                                         depthFactors, impactFactors, fatigueAlpha, fatigueBeta, impactNumberC);

            result += widthFactorProbability * depthFactorAccumulation;
        }

        return result;
    }

    double AsphaltRevetment::LogFailureTension(
        const double failureTension)
    {
        return log10(failureTension);
    }

    double AsphaltRevetment::MaximumPeakStress(
        const double waveHeightHm0,
        const double gravitationalAcceleration,
        const double densityOfWater)
    {
        return gravitationalAcceleration * densityOfWater * waveHeightHm0 / pow(10.0, 6.0);
    }

    double AsphaltRevetment::StiffnessRelation(
        const double computationalThickness,
        const double equivalentElasticModulus,
        const double soilElasticy,
        const double stiffnessRelationNu)
    {
        return pow(3.0 * soilElasticy * (1.0 - pow(stiffnessRelationNu, 2.0)) / (equivalentElasticModulus * computationalThickness), 0.25);
    }

    double AsphaltRevetment::DepthFactorAccumulation(
        const double logFailureTension,
        const double averageNumberOfWaves,
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness,
        const double tanA,
        const double widthFactorValue,
        const std::vector<std::tuple<double, double>>& depthFactors,
        const std::vector<std::tuple<double, double>>& impactFactors,
        const double fatigueAlpha,
        const double fatigueBeta,
        const double impactNumberC)
    {
        double result = 0;

        for (const auto& depthFactor : depthFactors)
        {
            const auto depthFactorValue = get<0>(depthFactor);
            const auto depthFactorProbability = get<1>(depthFactor);
            const auto impactFactorAccumulation = ImpactFactorAccumulation(logFailureTension, averageNumberOfWaves, maximumPeakStress,
                                                                           stiffnessRelation, computationalThickness, tanA, widthFactorValue,
                                                                           depthFactorValue, impactFactors, fatigueAlpha, fatigueBeta,
                                                                           impactNumberC);

            result += depthFactorProbability * impactFactorAccumulation;
        }

        return result;
    }

    double AsphaltRevetment::ImpactFactorAccumulation(
        const double logFailureTension,
        const double averageNumberOfWaves,
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness,
        const double tanA,
        const double widthFactorValue,
        const double depthFactorValue,
        const std::vector<std::tuple<double, double>>& impactFactors,
        const double fatigueAlpha,
        const double fatigueBeta,
        const double impactNumberC)
    {
        double result = 0;

        for (const auto& impactFactor : impactFactors)
        {
            const auto impactFactorValue = get<0>(impactFactor);
            const auto impactFactorProbability = get<1>(impactFactor);
            const auto fatigue = Fatigue(logFailureTension, maximumPeakStress, stiffnessRelation, computationalThickness, tanA, widthFactorValue,
                                         depthFactorValue, impactFactorValue, fatigueAlpha, fatigueBeta, impactNumberC);

            result += impactFactorProbability * averageNumberOfWaves * fatigue;
        }

        return result;
    }

    double AsphaltRevetment::Fatigue(
        const double logFailureTension,
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness,
        const double tanA,
        const double widthFactorValue,
        const double depthFactorValue,
        const double impactFactorValue,
        const double fatigueAlpha,
        const double fatigueBeta,
        const double impactNumberC)
    {
        const auto logTension = LogTension(maximumPeakStress, stiffnessRelation, computationalThickness, tanA, widthFactorValue, depthFactorValue,
                                           impactFactorValue, impactNumberC);

        return pow(10.0, -1.0 * fatigueBeta * pow(max(0.0, logFailureTension - logTension), fatigueAlpha));
    }

    double AsphaltRevetment::LogTension(
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness,
        const double tanA,
        double widthFactorValue,
        double depthFactorValue,
        const double impactFactorValue,
        const double impactNumberC)
    {
        const auto impactNumber = ImpactNumber(tanA, impactFactorValue, impactNumberC);
        const auto bendingStress = BendingStress(maximumPeakStress, stiffnessRelation, computationalThickness);

        return log10(impactNumber * bendingStress);
    }

    double AsphaltRevetment::ImpactNumber(
        const double tanA,
        const double impactFactorValue,
        const double impactNumberC)
    {
        return 4.0 * impactNumberC * tanA * impactFactorValue;
    }

    double AsphaltRevetment::BendingStress(
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness)
    {
        const auto spatialDistributionBendingStress = 4.4;

        return max(pow(10.0, -99.0),
                   -1.0 * (3 * maximumPeakStress / (4.0 * pow(stiffnessRelation, 2.0) * pow(computationalThickness, 2.0))) *
                   spatialDistributionBendingStress);
    }
}
