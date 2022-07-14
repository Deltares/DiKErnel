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

#include "AsphaltRevetmentWaveImpactFunctions.h"

#include <cmath>
#include <utility>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double AsphaltRevetmentWaveImpactFunctions::IncrementDamage(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput)
    {
        auto result = 0.0;

        const auto sinA = sin(atan(calculatedInput.GetOuterSlope()));

        for (const auto& [widthFactorValue, widthFactorProbability] : input.GetWidthFactors())
        {
            const auto relativeWidthWaveImpact = RelativeWidthWaveImpact(input, calculatedInput, widthFactorValue);
            const auto depthFactorAccumulation = DepthFactorAccumulation(input, calculatedInput, relativeWidthWaveImpact, sinA);

            result += widthFactorProbability * depthFactorAccumulation;
        }

        return result;
    }

    double AsphaltRevetmentWaveImpactFunctions::LogFailureTension(
        const double failureTension)
    {
        return log10(failureTension);
    }

    double AsphaltRevetmentWaveImpactFunctions::MaximumPeakStress(
        const double waveHeightHm0,
        const double gravitationalAcceleration,
        const double densityOfWater)
    {
        return gravitationalAcceleration * densityOfWater * waveHeightHm0 / pow(10.0, 6.0);
    }

    double AsphaltRevetmentWaveImpactFunctions::StiffnessRelation(
        const double computationalThickness,
        const double equivalentElasticModulus,
        const double soilElasticity,
        const double stiffnessRelationNu)
    {
        return pow(3.0 * soilElasticity * (1.0 - pow(stiffnessRelationNu, 2.0)) / (equivalentElasticModulus * pow(computationalThickness, 3.0)),
                   1.0 / 4.0);
    }

    double AsphaltRevetmentWaveImpactFunctions::ComputationalThickness(
        const double thicknessUpperLayer,
        const double thicknessSubLayer,
        const double elasticModulusUpperLayer,
        const double elasticModulusSubLayer)
    {
        return thicknessUpperLayer * pow(elasticModulusUpperLayer / elasticModulusSubLayer, 1.0 / 3.0) + thicknessSubLayer;
    }

    double AsphaltRevetmentWaveImpactFunctions::OuterSlope(
        const double slopeLowerPosition,
        const double slopeLowerLevel,
        const double slopeUpperPosition,
        const double slopeUpperLevel)
    {
        return (slopeUpperLevel - slopeLowerLevel) / (slopeUpperPosition - slopeLowerPosition);
    }

    double AsphaltRevetmentWaveImpactFunctions::DepthFactorAccumulation(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput,
        const double relativeWidthWaveImpact,
        const double sinA)
    {
        auto result = 0.0;

        for (const auto& [depthFactorValue, depthFactorProbability] : input.GetDepthFactors())
        {
            const auto bendingStress = BendingStress(input, calculatedInput, relativeWidthWaveImpact, sinA, depthFactorValue);
            const auto impactFactorAccumulation = ImpactFactorAccumulation(input, calculatedInput, bendingStress);

            result += depthFactorProbability * impactFactorAccumulation;
        }

        return result;
    }

    double AsphaltRevetmentWaveImpactFunctions::ImpactFactorAccumulation(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput,
        const double bendingStress)
    {
        auto result = 0.0;

        for (const auto& [impactFactorValue, impactFactorProbability] : input.GetImpactFactors())
        {
            const auto fatigue = Fatigue(input, calculatedInput, bendingStress, impactFactorValue);

            result += impactFactorProbability * calculatedInput.GetAverageNumberOfWaves() * fatigue;
        }

        return result;
    }

    double AsphaltRevetmentWaveImpactFunctions::Fatigue(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput,
        const double bendingStress,
        const double impactFactorValue)
    {
        const auto logTension = LogTension(input, calculatedInput, bendingStress, impactFactorValue);

        return pow(10.0, -input.GetFatigueBeta() * pow(max(0.0, calculatedInput.GetLogFailureTension() - logTension), input.GetFatigueAlpha()));
    }

    double AsphaltRevetmentWaveImpactFunctions::LogTension(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput,
        const double bendingStress,
        const double impactFactorValue)
    {
        const auto impactNumber = ImpactNumber(input, calculatedInput, impactFactorValue);

        return log10(impactNumber * bendingStress);
    }

    double AsphaltRevetmentWaveImpactFunctions::ImpactNumber(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput,
        const double impactFactorValue)
    {
        return 4.0 * input.GetImpactNumberC() * calculatedInput.GetOuterSlope() * impactFactorValue;
    }

    double AsphaltRevetmentWaveImpactFunctions::BendingStress(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput,
        const double relativeWidthWaveImpact,
        const double sinA,
        const double depthFactorValue)
    {
        const auto spatialDistributionBendingStress = SpatialDistributionBendingStress(input, calculatedInput, relativeWidthWaveImpact, sinA,
                                                                                       depthFactorValue);

        return max(pow(10.0, -99.0),
                   -3.0 * calculatedInput.GetMaximumPeakStress() / (4.0 * pow(calculatedInput.GetStiffnessRelation(), 2.0) * pow(
                       calculatedInput.GetComputationalThickness(), 2.0))
                   * spatialDistributionBendingStress);
    }

    double AsphaltRevetmentWaveImpactFunctions::SpatialDistributionBendingStress(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput,
        const double relativeWidthWaveImpact,
        const double sinA,
        const double depthFactorValue)
    {
        const auto relativeDistanceCenterWaveImpact = RelativeDistanceCenterWaveImpact(input, calculatedInput, depthFactorValue, sinA);

        const auto sinRelativeDistanceCenterWaveImpact = sin(relativeDistanceCenterWaveImpact);
        const auto sinRelativeWidthWaveImpact = sin(relativeWidthWaveImpact);
        const auto cosRelativeDistanceCenterWaveImpact = cos(relativeDistanceCenterWaveImpact);
        const auto cosRelativeWidthWaveImpact = cos(relativeWidthWaveImpact);
        const auto expNegativeRelativeDistanceCenterWaveImpact = exp(-relativeDistanceCenterWaveImpact);
        const auto expNegativeRelativeWidthWaveImpact = exp(-relativeWidthWaveImpact);

        if (relativeWidthWaveImpact >= relativeDistanceCenterWaveImpact)
        {
            const auto expRelativeDistanceCenterWaveImpact = exp(relativeDistanceCenterWaveImpact);

            return (-sinRelativeDistanceCenterWaveImpact * (expRelativeDistanceCenterWaveImpact - expNegativeRelativeDistanceCenterWaveImpact)
                        * (cosRelativeWidthWaveImpact - sinRelativeWidthWaveImpact) * expNegativeRelativeWidthWaveImpact
                        + cosRelativeDistanceCenterWaveImpact * (expRelativeDistanceCenterWaveImpact + expNegativeRelativeDistanceCenterWaveImpact)
                        * (cosRelativeWidthWaveImpact + sinRelativeWidthWaveImpact) * expNegativeRelativeWidthWaveImpact
                        - 2.0 * expNegativeRelativeDistanceCenterWaveImpact
                        * (cosRelativeDistanceCenterWaveImpact + sinRelativeDistanceCenterWaveImpact))
                    / relativeWidthWaveImpact;
        }

        const auto expRelativeWidthWaveImpact = exp(relativeWidthWaveImpact);

        return (cosRelativeDistanceCenterWaveImpact * (expRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact - sinRelativeWidthWaveImpact)
                        + expNegativeRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact + sinRelativeWidthWaveImpact))
                    + sinRelativeDistanceCenterWaveImpact * (expRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact + sinRelativeWidthWaveImpact)
                        + expNegativeRelativeWidthWaveImpact * (cosRelativeWidthWaveImpact - sinRelativeWidthWaveImpact))
                    - 2.0 * (cosRelativeDistanceCenterWaveImpact + sinRelativeDistanceCenterWaveImpact))
                * expNegativeRelativeDistanceCenterWaveImpact / relativeWidthWaveImpact;
    }

    double AsphaltRevetmentWaveImpactFunctions::RelativeWidthWaveImpact(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput,
        const double widthFactorValue)
    {
        return min(85.0, calculatedInput.GetStiffnessRelation() * widthFactorValue * input.GetWaveHeightHm0() / 2.0);
    }

    double AsphaltRevetmentWaveImpactFunctions::RelativeDistanceCenterWaveImpact(
        const AsphaltRevetmentWaveImpactFunctionsInput& input,
        const AsphaltRevetmentWaveImpactFunctionsCalculatedInput& calculatedInput,
        const double depthFactorValue,
        const double sinA)
    {
        return min(85.0, calculatedInput.GetStiffnessRelation() * abs(
                       input.GetZ() - input.GetWaterLevel() - depthFactorValue * input.GetWaveHeightHm0()) / sinA);
    }
}
