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

#include "AsphaltRevetmentWaveImpactFunctionsInput.h"

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
             * \param input
             *        The input to use for the calculation.
             * \return The increment of damage.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double IncrementDamage(
                const AsphaltRevetmentWaveImpactFunctionsInput& input);

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
             * \param slopeLowerPosition
             *        The lower position of the slope.
             *        Unit = [m]
             * \param slopeLowerLevel
             *        The lower level of the slope.
             *        Unit = [m]
             * \param slopeUpperPosition
             *        The upper position of the slope.
             *        Unit = [m]
             * \param slopeUpperLevel
             *        The upper level of the slope.
             *        Unit = [m]
             * \return The outer slope.
             *         Unit = [-]
             */
            [[nodiscard]]
            static double OuterSlope(
                double slopeLowerPosition,
                double slopeLowerLevel,
                double slopeUpperPosition,
                double slopeUpperLevel);

        private:
            [[nodiscard]]
            static double DepthFactorAccumulation(
                const AsphaltRevetmentWaveImpactFunctionsInput& input,
                double relativeWidthWaveImpact,
                double sinA);

            [[nodiscard]]
            static double ImpactFactorAccumulation(
                const AsphaltRevetmentWaveImpactFunctionsInput& input,
                double bendingStress);

            [[nodiscard]]
            static double Fatigue(
                const AsphaltRevetmentWaveImpactFunctionsInput& input,
                double bendingStress,
                double impactFactorValue);

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
                const AsphaltRevetmentWaveImpactFunctionsInput& input,
                double relativeWidthWaveImpact,
                double sinA,
                double depthFactorValue);

            [[nodiscard]]
            static double SpatialDistributionBendingStress(
                const AsphaltRevetmentWaveImpactFunctionsInput& input,
                double relativeWidthWaveImpact,
                double sinA,
                double depthFactorValue);

            [[nodiscard]]
            static double RelativeWidthWaveImpact(
                double stiffnessRelation,
                double widthFactorValue,
                double waveHeightHm0);

            [[nodiscard]]
            static double RelativeDistanceCenterWaveImpact(
                const AsphaltRevetmentWaveImpactFunctionsInput& input,
                double depthFactorValue,
                double sinA);
    };
}
