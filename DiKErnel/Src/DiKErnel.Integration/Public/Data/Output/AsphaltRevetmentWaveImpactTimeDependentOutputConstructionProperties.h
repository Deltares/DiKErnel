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

#include <limits>

#include "TimeDependentOutputConstructionProperties.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Construction properties to construct asphalt revetment wave impact time dependent
     *        output.
     */
    class AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties : public TimeDependentOutputConstructionProperties
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param incrementDamage
             *        The increment damage.
             * \param damage
             *        The damage.
             * \param timeOfFailure
             *        The time of failure.
             */
            explicit AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure);

            /*!
             * \brief Sets the log failure tension.
             * \param logFailureTension
             *        The log failure tension.
             */
            void SetLogFailureTension(
                double logFailureTension);

            /*!
             * \brief Sets the maximum peak stress.
             * \param maximumPeakStress
             *        The maximum peak stress.
             */
            void SetMaximumPeakStress(
                double maximumPeakStress);

            /*!
             * \brief Sets the stiffness relation.
             * \param stiffnessRelation
             *        The stiffness relation.
             */
            void SetStiffnessRelation(
                double stiffnessRelation);

            /*!
             * \brief Sets the computational thickness.
             * \param computationalThickness
             *        The computational thickness.
             */
            void SetComputationalThickness(
                double computationalThickness);

            /*!
             * \brief Sets the equivalent elastic modulus.
             * \param equivalentElasticModulus
             *        The equivalent elastic modulus.
             */
            void SetEquivalentElasticModulus(
                double equivalentElasticModulus);

            /*!
             * \brief Gets the log failure tension.
             * \return The log failure tension.
             */
            [[nodiscard]]
            double GetLogFailureTension() const;

            /*!
             * \brief Gets the maximum peak stress.
             * \return The maximum peak stress.
             */
            [[nodiscard]]
            double GetMaximumPeakStress() const;

            /*!
             * \brief Gets the stiffness relation.
             * \return The stiffness relation.
             */
            [[nodiscard]]
            double GetStiffnessRelation() const;

            /*!
             * \brief Gets the computational thickness.
             * \return The computational thickness.
             */
            [[nodiscard]]
            double GetComputationalThickness() const;

            /*!
             * \brief Gets the equivalent elastic modulus.
             * \return The equivalent elastic modulus.
             */
            [[nodiscard]]
            double GetEquivalentElasticModulus() const;

        private:
            double _logFailureTension = std::numeric_limits<double>::infinity();
            double _maximumPeakStress = std::numeric_limits<double>::infinity();
            double _stiffnessRelation = std::numeric_limits<double>::infinity();
            double _computationalThickness = std::numeric_limits<double>::infinity();
            double _equivalentElasticModulus = std::numeric_limits<double>::infinity();
    };
}
