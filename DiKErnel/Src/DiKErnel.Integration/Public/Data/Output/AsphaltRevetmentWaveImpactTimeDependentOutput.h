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

#include "AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties.h"
#include "TimeDependentOutput.h"

namespace DiKErnel::Integration
{
    /*!
     * \brief Time dependent output of an asphalt revetment wave impact location.
     */
    class AsphaltRevetmentWaveImpactTimeDependentOutput : public Core::TimeDependentOutput
    {
        public:
            /*!
             * \brief Creates a new instance.
             * \param constructionProperties
             *        The construction properties.
             * \exception InvalidTimeDependentOutputException
             *            Thrown when mandatory properties are nullptr.
             */
            explicit AsphaltRevetmentWaveImpactTimeDependentOutput(
                AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties& constructionProperties);
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
            std::unique_ptr<double> _logFailureTension = nullptr;
            std::unique_ptr<double> _maximumPeakStress = nullptr;
            std::unique_ptr<double> _stiffnessRelation = nullptr;
            std::unique_ptr<double> _computationalThickness = nullptr;
            std::unique_ptr<double> _equivalentElasticModulus = nullptr;
    };
}
