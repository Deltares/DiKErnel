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

#pragma once

#include <vector>

namespace DiKErnel::FunctionLibrary
{
    /*!
     * \brief Class that holds all asphalt revetment wave impact specific calculation routines.
     */
    class AsphaltRevetmentWaveImpactFunctions
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
             * \param outerSlope
             *        The outer slope.
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
             * \param z
             *        The z coordinate.
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
            [[nodiscard]]
            static double IncrementDamage(
                double logFailureTension,
                double averageNumberOfWaves,
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness,
                double outerSlope,
                const std::vector<std::pair<double, double>>& widthFactors,
                const std::vector<std::pair<double, double>>& depthFactors,
                const std::vector<std::pair<double, double>>& impactFactors,
                double z,
                double waterLevel,
                double waveHeightHm0,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC);

            /*!
             * \brief Calculates the logarithm of the failure tension.
             * \param failureTension
             *        The failure tension.
             *        Unit = [MPa]
             * \return The logarithm of the failure tension.
             *         Unit = [MPa]
             */
            [[nodiscard]]
            static double LogFailureTension(
                double failureTension);

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
            [[nodiscard]]
            static double MaximumPeakStress(
                double waveHeightHm0,
                double gravitationalAcceleration,
                double densityOfWater);

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
            [[nodiscard]]
            static double StiffnessRelation(
                double computationalThickness,
                double equivalentElasticModulus,
                double soilElasticity,
                double stiffnessRelationNu);

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
            [[nodiscard]]
            static double ComputationalThickness(
                double thicknessUpperLayer,
                double thicknessSubLayer,
                double elasticModulusUpperLayer,
                double elasticModulusSubLayer);

            /*!
             * \brief Calculates the outer slope.
             * \param slopeUpperPosition
             *        The upper position of the slope.
             *        Unit = [m]
             * \param slopeUpperLevel
             *        The upper level of the slope.
             *        Unit = [m]
             * \param slopeLowerPosition
             *        The lower position of the slope.
             *        Unit = [m]
             * \param slopeLowerLevel
             *        The lower level of the slope.
             *        Unit = [m]
             * \return The outer slope.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double OuterSlope(
                double slopeUpperPosition,
                double slopeUpperLevel,
                double slopeLowerPosition,
                double slopeLowerLevel);

        private:
            [[nodiscard]]
            static double DepthFactorAccumulation(
                double logFailureTension,
                double averageNumberOfWaves,
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness,
                double relativeWidthWaveImpact,
                double outerSlope,
                double sinA,
                const std::vector<std::pair<double, double>>& depthFactors,
                const std::vector<std::pair<double, double>>& impactFactors,
                double z,
                double waterLevel,
                double waveHeightHm0,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC);

            [[nodiscard]]
            static double ImpactFactorAccumulation(
                double logFailureTension,
                double averageNumberOfWaves,
                double bendingStress,
                double outerSlope,
                const std::vector<std::pair<double, double>>& impactFactors,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC);

            [[nodiscard]]
            static double Fatigue(
                double logFailureTension,
                double bendingStress,
                double outerSlope,
                double impactFactorValue,
                double fatigueAlpha,
                double fatigueBeta,
                double impactNumberC);

            [[nodiscard]]
            static double LogTension(
                double bendingStress,
                double outerSlope,
                double impactFactorValue,
                double impactNumberC);

            [[nodiscard]]
            static double ImpactNumber(
                double outerSlope,
                double impactFactorValue,
                double impactNumberC);

            [[nodiscard]]
            static double BendingStress(
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness,
                double relativeWidthWaveImpact,
                double sinA,
                double depthFactorValue,
                double z,
                double waterLevel,
                double waveHeightHm0);

            [[nodiscard]]
            static double SpatialDistributionBendingStress(
                double stiffnessRelation,
                double relativeWidthWaveImpact,
                double sinA,
                double depthFactorValue,
                double z,
                double waterLevel,
                double waveHeightHm0);

            [[nodiscard]]
            static double RelativeWidthWaveImpact(
                double stiffnessRelation,
                double widthFactorValue,
                double waveHeightHm0);

            [[nodiscard]]
            static double RelativeDistanceCenterWaveImpact(
                double stiffnessRelation,
                double depthFactorValue,
                double sinA,
                double z,
                double waterLevel,
                double waveHeightHm0);
    };
}
