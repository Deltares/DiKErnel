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

#pragma once

#include <vector>

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all asphalt revetment specific calculation routines.
     */
    class AsphaltRevetment
    {
        public:
            static double IncrementDamage(
                double logFailureTension,
                double averageNumberOfWaves,
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness,
                double tanA,
                const std::vector<std::tuple<double, double>>& widthFactors,
                const std::vector<std::tuple<double, double>>& depthFactors,
                const std::vector<std::tuple<double, double>>& impactFactors,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC
            );

            static double LogFailureTension(
                double failureTension
            );

            static double MaximumPeakStress(
                double waveHeightHm0,
                double gravitationalAcceleration,
                double densityOfWater
            );

            static double StiffnessRelation(
                double computationalThickness,
                double equivalentElasticModulus,
                double soilElasticy,
                double stiffnessRelationNu
            );

            static double ComputationalThickness(
                double thicknessUpperLayer,
                double thicknessSubLayer,
                double elasticModulusUpperLayer,
                double elasticModulusSubLayer
            );

        private:
            static double DepthFactorAccumulation(
                double logFailureTension,
                double averageNumberOfWaves,
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness,
                double tanA,
                double widthFactorValue,
                const std::vector<std::tuple<double, double>>& depthFactors,
                const std::vector<std::tuple<double, double>>& impactFactors,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC
            );

            static double ImpactFactorAccumulation(
                double logFailureTension,
                double averageNumberOfWaves,
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness,
                double tanA,
                double widthFactorValue,
                double depthFactorValue,
                const std::vector<std::tuple<double, double>>& impactFactors,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC);

            static double Fatigue(
                double logFailureTension,
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness,
                double tanA,
                double widthFactorValue,
                double depthFactorValue,
                double impactFactorValue,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC
            );

            static double LogTension(
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness,
                double tanA,
                double widthFactorValue,
                double depthFactorValue,
                double impactFactorValue,
                double impactNumberC
            );

            static double ImpactNumber(
                double tanA,
                double impactFactorValue,
                double impactNumberC
            );

            static double BendingStress(
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness
            );

            static double SpatialDistributionBendingStress();

            static double RelativeWidthWaveImpact(
                double stiffnessRelation,
                double widthFactorValue,
                double waveHeightHm0
            );

            static double RelativeDistanceCenterWaveImpact(
                double stiffnessRelation,
                double depthFactorValue,
                double slopeAngle,
                double positionZ,
                double waterLevel,
                double waveHeightHm0);
    };
}
