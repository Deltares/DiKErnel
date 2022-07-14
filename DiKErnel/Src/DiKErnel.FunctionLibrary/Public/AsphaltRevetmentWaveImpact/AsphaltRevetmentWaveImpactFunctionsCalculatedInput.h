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
     * \brief Class that holds all asphalt revetment wave impact specific calculated input.
     */
    class AsphaltRevetmentWaveImpactFunctionsCalculatedInput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param logFailureTension
             *        The logarithm of the failure tension.
             *        Unit = [MPa]
             * \param computationalThickness
             *        The computation thickness.
             *        Unit = [m]
             * \param stiffnessRelation
             *        The stiffness relation.
             *        Unit = [m^-1]
             * \param equivalentElasticModulus
             *        The equivalent elastic modulus.
             *        Unit = [MPa]
             * \param outerSlope
             *        The outer slope.
             *        Unit = [-]
             */
            explicit AsphaltRevetmentWaveImpactFunctionsCalculatedInput(
                double logFailureTension,
                double computationalThickness,
                double stiffnessRelation,
                double equivalentElasticModulus,
                double outerSlope);

            /*!
             * \brief Sets the average number of waves.
             * \param averageNumberOfWaves
             *        The average number of waves.
             *        Unit = [-]
             */
            void SetAverageNumberOfWaves(
                double averageNumberOfWaves);

            /*!
             * \brief Sets the maximum peak stress.
             * \param maximumPeakStress
             *        The maximum peak stress.
             *        Unit = [MPa]
             */
            void SetMaximumPeakStress(
                double maximumPeakStress);

            /*!
             * \brief Gets the logarithm of the failure tension.
             * \return The logarithm of the failure tension.
             *         Unit = [MPa]
             */
            [[nodiscard]]
            double GetLogFailureTension() const;

            /*!
             * \brief Gets the computation thickness.
             * \return The computation thickness.
             *         Unit = [m]
             */
            [[nodiscard]]
            double GetComputationalThickness() const;

            /*!
             * \brief Gets the stiffness relation.
             * \return The stiffness relation.
             *         Unit = [m^-1]
             */
            [[nodiscard]]
            double GetStiffnessRelation() const;

            /*!
             * \brief Gets the equivalent elastic modulus.
             * \return The equivalent elastic modulus.
             *         Unit = [MPa]
             */
            [[nodiscard]]
            double GetEquivalentElasticModulus() const;

            /*!
             * \brief Gets the outer slope.
             * \return The outer slope.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetOuterSlope() const;

            /*!
             * \brief Gets the average number of waves.
             * \return The average number of waves.
             *         Unit = [-]
             */
            [[nodiscard]]
            double GetAverageNumberOfWaves() const;

            /*!
             * \brief Gets the maximum peak stress.
             * \return The maximum peak stress.
             *         Unit = [MPa]
             */
            [[nodiscard]]
            double GetMaximumPeakStress() const;

        private:
            double _logFailureTension;
            double _computationalThickness;
            double _stiffnessRelation;
            double _equivalentElasticModulus;
            double _outerSlope;
            double _averageNumberOfWaves = std::numeric_limits<double>::infinity();
            double _maximumPeakStress = std::numeric_limits<double>::infinity();
    };
}
