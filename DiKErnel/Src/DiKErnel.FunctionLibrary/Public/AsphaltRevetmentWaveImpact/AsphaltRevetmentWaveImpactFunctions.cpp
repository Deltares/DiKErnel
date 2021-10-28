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

#include "AsphaltRevetmentWaveImpactFunctions.h"

#include <cmath>
#include <utility>

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    double AsphaltRevetmentWaveImpactFunctions::IncrementDamage(
        const double logFailureTension,
        const double averageNumberOfWaves,
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness,
        const double outerSlope,
        const vector<pair<double, double>>& widthFactors,
        const vector<pair<double, double>>& depthFactors,
        const vector<pair<double, double>>& impactFactors,
        const double z,
        const double waterLevel,
        const double waveHeightHm0,
        const double fatigueAlpha,
        const double fatigueBeta,
        const double impactNumberC)
    {
        auto result = 0.0;

        const auto sinA = sin(atan(outerSlope));

        for (const auto& [widthFactorValue, widthFactorProbability] : widthFactors)
        {
            const auto relativeWidthWaveImpact = RelativeWidthWaveImpact(stiffnessRelation, widthFactorValue, waveHeightHm0);
            const auto depthFactorAccumulation = DepthFactorAccumulation(logFailureTension, averageNumberOfWaves, maximumPeakStress,
                                                                         stiffnessRelation, computationalThickness, relativeWidthWaveImpact,
                                                                         outerSlope, sinA, depthFactors, impactFactors, z, waterLevel,
                                                                         waveHeightHm0, fatigueAlpha, fatigueBeta, impactNumberC);

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

    double AsphaltRevetmentWaveImpactFunctions::DepthFactorAccumulation(
        const double logFailureTension,
        const double averageNumberOfWaves,
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness,
        const double relativeWidthWaveImpact,
        const double outerSlope,
        const double sinA,
        const vector<pair<double, double>>& depthFactors,
        const vector<pair<double, double>>& impactFactors,
        const double z,
        const double waterLevel,
        const double waveHeightHm0,
        const double fatigueAlpha,
        const double fatigueBeta,
        const double impactNumberC)
    {
        auto result = 0.0;

        for (const auto& [depthFactorValue, depthFactorProbability] : depthFactors)
        {
            const auto bendingStress = BendingStress(maximumPeakStress, stiffnessRelation, computationalThickness, relativeWidthWaveImpact, sinA,
                                                     depthFactorValue, z, waterLevel, waveHeightHm0);
            const auto impactFactorAccumulation = ImpactFactorAccumulation(logFailureTension, averageNumberOfWaves, bendingStress, outerSlope,
                                                                           impactFactors, fatigueAlpha, fatigueBeta, impactNumberC);

            result += depthFactorProbability * impactFactorAccumulation;
        }

        return result;
    }

    double AsphaltRevetmentWaveImpactFunctions::ImpactFactorAccumulation(
        const double logFailureTension,
        const double averageNumberOfWaves,
        const double bendingStress,
        const double outerSlope,
        const vector<pair<double, double>>& impactFactors,
        const double fatigueAlpha,
        const double fatigueBeta,
        const double impactNumberC)
    {
        auto result = 0.0;

        for (const auto& [impactFactorValue, impactFactorProbability] : impactFactors)
        {
            const auto fatigue = Fatigue(logFailureTension, bendingStress, outerSlope, impactFactorValue, fatigueAlpha, fatigueBeta, impactNumberC);

            result += impactFactorProbability * averageNumberOfWaves * fatigue;
        }

        return result;
    }

    double AsphaltRevetmentWaveImpactFunctions::Fatigue(
        const double logFailureTension,
        const double bendingStress,
        const double outerSlope,
        const double impactFactorValue,
        const double fatigueAlpha,
        const double fatigueBeta,
        const double impactNumberC)
    {
        const auto logTension = LogTension(bendingStress, outerSlope, impactFactorValue, impactNumberC);

        return pow(10.0, -fatigueBeta * pow(max(0.0, logFailureTension - logTension), fatigueAlpha));
    }

    double AsphaltRevetmentWaveImpactFunctions::LogTension(
        const double bendingStress,
        const double outerSlope,
        const double impactFactorValue,
        const double impactNumberC)
    {
        const auto impactNumber = ImpactNumber(outerSlope, impactFactorValue, impactNumberC);

        return log10(impactNumber * bendingStress);
    }

    double AsphaltRevetmentWaveImpactFunctions::ImpactNumber(
        const double outerSlope,
        const double impactFactorValue,
        const double impactNumberC)
    {
        return 4.0 * impactNumberC * outerSlope * impactFactorValue;
    }

    double AsphaltRevetmentWaveImpactFunctions::BendingStress(
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness,
        const double relativeWidthWaveImpact,
        const double sinA,
        const double depthFactorValue,
        const double z,
        const double waterLevel,
        const double waveHeightHm0)
    {
        const auto spatialDistributionBendingStress = SpatialDistributionBendingStress(stiffnessRelation, relativeWidthWaveImpact, sinA,
                                                                                       depthFactorValue, z, waterLevel, waveHeightHm0);

        return max(pow(10.0, -99.0), -3.0 * maximumPeakStress / (4.0 * pow(stiffnessRelation, 2.0) * pow(computationalThickness, 2.0))
                   * spatialDistributionBendingStress);
    }

    double AsphaltRevetmentWaveImpactFunctions::SpatialDistributionBendingStress(
        const double stiffnessRelation,
        const double relativeWidthWaveImpact,
        const double sinA,
        const double depthFactorValue,
        const double z,
        const double waterLevel,
        const double waveHeightHm0)
    {
        const auto relativeDistanceCenterWaveImpact = RelativeDistanceCenterWaveImpact(stiffnessRelation, depthFactorValue, sinA, z, waterLevel,
                                                                                       waveHeightHm0);

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
        const double stiffnessRelation,
        const double widthFactorValue,
        const double waveHeightHm0)
    {
        return min(85.0, stiffnessRelation * widthFactorValue * waveHeightHm0 / 2.0);
    }

    double AsphaltRevetmentWaveImpactFunctions::RelativeDistanceCenterWaveImpact(
        const double stiffnessRelation,
        const double depthFactorValue,
        const double sinA,
        const double z,
        const double waterLevel,
        const double waveHeightHm0)
    {
        return min(85.0, stiffnessRelation * abs(z - waterLevel - depthFactorValue * waveHeightHm0) / sinA);
    }
}
