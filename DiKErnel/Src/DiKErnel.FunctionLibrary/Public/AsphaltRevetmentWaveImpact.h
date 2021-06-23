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
     * \brief Class that holds all asphalt revetment wave impact specific calculation routines.
     */
    class AsphaltRevetmentWaveImpact
    {
        public:
            /*!
             * \brief Calculates the increment of damage.
             * \param logFailureTension
             *        The logarithm of the failure tension.
             *        Unit = [MPa]
             * \param averageNumberOfWaves
             *        The average number of waves.
             *        Unit = [-]
             * \param maximumPeakStress
             *        The maximum peak stress.
             *        Unit = [MPa]
             * \param stiffnessRelation
             *        The stiffness relation.
             *        Unit = [m^-1]
             * \param computationalThickness
             *        The computation thickness.
             *        Unit = [m]
             * \param tanA
             *        The tanA.
             *        Unit = [-]
             * \param widthFactors
             *        The width factors.
             *        Unit = [-]
             * \param depthFactors
             *        The depth factors.
             *        Unit = [-]
             * \param impactFactors
             *        The impact factors.
             *        Unit = [-]
             * \param positionZ
             *        The vertical position.
             *        Unit = [m]
             * \param waterLevel
             *        The water level.
             *        Unit = [m]
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param fatigueAlpha
             *        The fatigue alpha coefficient.
             *        Unit = [-]
             * \param fatigueBeta
             *        The fatigue beta coefficient.
             *        Unit = [-]
             * \param impactNumberC
             *        The impact number c coefficient.
             *        Unit = [-]
             * \return The increment of damage.
             *         Unit = [-]
             */
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
                double positionZ,
                double waterLevel,
                double waveHeightHm0,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC
            );

            /*!
             * \brief Calculates the logarithm of the failure tension.
             * \param failureTension
             *        The failure tension.
             *        Unit = [MPa]
             * \return The logarithm of the failure tension.
             *         Unit = [MPa]
             */
            static double LogFailureTension(
                double failureTension
            );

            /*!
             * \brief Calculates the maximum peak stress.
             * \param waveHeightHm0
             *        The wave height.
             *        Unit = [m]
             * \param gravitationalAcceleration
             *        The gravitational acceleration.
             *        Unit = [m/s^2]
             * \param densityOfWater
             *        The density of water.
             *        Unit = [kg/m^3]
             * \return The maximum peak stress.
             *         Unit = [MPa]
             */
            static double MaximumPeakStress(
                double waveHeightHm0,
                double gravitationalAcceleration,
                double densityOfWater
            );

            /*!
             * \brief Calculates the stiffness relation.
             * \param computationalThickness
             *        The computation thickness.
             *        Unit = [m]
             * \param equivalentElasticModulus
             *        The equivalent elastic modulus.
             *        Unit = [MPa]
             * \param soilElasticity
             *        The soil elasticity.
             *        Unit = [MPa/m]
             * \param stiffnessRelationNu
             *        The Nu coefficient.
             *        Unit = [-]
             * \return The stiffness relation.
             *         Unit = [m^-1]
             */
            static double StiffnessRelation(
                double computationalThickness,
                double equivalentElasticModulus,
                double soilElasticity,
                double stiffnessRelationNu
            );

            /*!
             * \brief Calculates the computational thickness.
             * \param thicknessUpperLayer
             *        The thickness of the upper layer.
             *        Unit = [m]
             * \param thicknessSubLayer
             *        The thickness of the sub layer.
             *        Unit = [m]
             * \param elasticModulusUpperLayer
             *        The elastic modulus of the upper layer.
             *        Unit = [MPa]
             * \param elasticModulusSubLayer
             *        The elastic modulus of the sub layer.
             *        Unit = [MPa]
             * \return The computational thickness.
             *         Unit = [m]
             */
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
                double sinA,
                double widthFactorValue,
                const std::vector<std::tuple<double, double>>& depthFactors,
                const std::vector<std::tuple<double, double>>& impactFactors,
                double positionZ,
                double waterLevel,
                double waveHeightHm0,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC
            );

            static double ImpactFactorAccumulation(
                double logFailureTension,
                double averageNumberOfWaves,
                double bendingStress,
                double tanA,
                const std::vector<std::tuple<double, double>>& impactFactors,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC
            );

            static double Fatigue(
                double logFailureTension,
                double bendingStress,
                double tanA,
                double impactFactorValue,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC
            );

            static double LogTension(
                double bendingStress,
                double tanA,
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
                double computationalThickness,
                double sinA,
                double widthFactorValue,
                double depthFactorValue,
                double positionZ,
                double waterLevel,
                double waveHeightHm0
            );

            static double SpatialDistributionBendingStress(
                double stiffnessRelation,
                double sinA,
                double widthFactorValue,
                double depthFactorValue,
                double positionZ,
                double waterLevel,
                double waveHeightHm0
            );

            static double RelativeWidthWaveImpact(
                double stiffnessRelation,
                double widthFactorValue,
                double waveHeightHm0
            );

            static double RelativeDistanceCenterWaveImpact(
                double stiffnessRelation,
                double depthFactorValue,
                double sinA,
                double positionZ,
                double waterLevel,
                double waveHeightHm0
            );
    };
}
