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

#include "TimeDependentOutput.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Time dependent output of a asphalt revetment wave impact location.
     */
    class AsphaltRevetmentWaveImpactTimeDependentOutput : public Core::TimeDependentOutput
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
             * \param logFailureTension
             *        The log failure tension.
             * \param maximumPeakStress
             *        The maximum peak stress.
             * \param stiffnessRelation
             *        The stiffness relation.
             * \param computationalThickness
             *        The computational thickness.
             * \param equivalentElasticModulus
             *        The equivalent elastic modulus.
             */
            explicit AsphaltRevetmentWaveImpactTimeDependentOutput(
                double incrementDamage,
                double damage,
                std::unique_ptr<int> timeOfFailure,
                double logFailureTension,
                double maximumPeakStress,
                double stiffnessRelation,
                double computationalThickness,
                double equivalentElasticModulus);

            /*!
             * \brief Gets the log failure tension.
             * \return The log failure tension.
             */
            double GetLogFailureTension() const;

            /*!
             * \brief Gets the maximum peak stress.
             * \return The maximum peak stress.
             */
            double GetMaximumPeakStress() const;

            /*!
             * \brief Gets the stiffness relation.
             * \return The stiffness relation.
             */
            double GetStiffnessRelation() const;

            /*!
             * \brief Gets the computational thickness.
             * \return The computational thickness.
             */
            double GetComputationalThickness() const;

            /*!
             * \brief Gets the equivalent elastic modulus.
             * \return The equivalent elastic modulus.
             */
            double GetEquivalentElasticModulus() const;

        private:
            const double _logFailureTension;
            const double _maximumPeakStress;
            const double _stiffnessRelation;
            const double _computationalThickness;
            const double _equivalentElasticModulus;
    };
}
