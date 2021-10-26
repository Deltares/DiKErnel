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

#include <memory>

#include "ValidationIssue.h"

namespace DiKErnel::DomainLibrary
{
    /*!
     * \brief Class that holds all asphalt revetment wave impact specific validation routines.
     */
    class AsphaltRevetmentWaveImpactValidator
    {
        public:
            /*!
             * \brief Validates the fatigue alpha coefficient.
             * \param fatigueAlpha
             *        The fatigue alpha coefficient.
             * \return A validation issue when the fatigue alpha coefficient is not valid;
             *         nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> FatigueAlpha(
                double fatigueAlpha);

            /*!
             * \brief Validates the fatigue beta coefficient.
             * \param fatigueBeta
             *        The fatigue beta coefficient.
             * \return A validation issue when the fatigue beta coefficient is not valid;
             *         nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> FatigueBeta(
                double fatigueBeta);

            /*!
             * \brief Validates the failure tension.
             * \param failureTension
             *        The failure tension.
             * \return A validation issue when the failure tension is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> FailureTension(
                double failureTension);

            /*!
             * \brief Validates the impact number C coefficient.
             * \param impactNumberC
             *        The impact number C coefficient.
             * \return A validation issue when the impact number C coefficient is not valid;
             *         nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> ImpactNumberC(
                double impactNumberC);

            /*!
             * \brief Validates the density of water.
             * \param densityOfWater
             *        The density of water.
             * \return A validation issue when the density of water is not valid;
             *         nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> DensityOfWater(
                double densityOfWater);

            /*!
             * \brief Validates the soil elasticity.
             * \param soilElasticity
             *        The soil elasticity.
             * \return A validation issue when the soil elasticity is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> SoilElasticity(
                double soilElasticity);

            /*!
             * \brief Validates the Nu coefficient.
             * \param stiffnessRelationNu
             *        The Nu coefficient.
             * \return A validation issue when the Nu coefficient is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> StiffnessRelationNu(
                double stiffnessRelationNu);

            /*!
             * \brief Validates the thickness.
             * \param thickness
             *        The thickness.
             * \return A validation issue when the thickness is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> Thickness(
                double thickness);

            /*!
             * \brief Validates the elastic modulus.
             * \param elasticModulus
             *        The elastic modulus.
             * \return A validation issue when the elastic modulus is not valid; nullptr otherwise.
             */
            static std::unique_ptr<ValidationIssue> ElasticModulus(
                double elasticModulus);

        private:
            static std::unique_ptr<ValidationIssue> ValidateLargerThanZero(
                double propertyToValidate,
                const std::string& propertyName);
    };
}
