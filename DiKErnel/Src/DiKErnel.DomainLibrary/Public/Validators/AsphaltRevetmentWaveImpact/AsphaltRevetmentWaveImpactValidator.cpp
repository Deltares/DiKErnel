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

#include "AsphaltRevetmentWaveImpactValidator.h"

namespace DiKErnel::DomainLibrary
{
    using namespace std;
    using namespace Util;

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::FatigueAlpha(
        const double fatigueAlpha)
    {
        return ValidateLargerThanZero(fatigueAlpha, "FatigueAlpha");
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::FatigueBeta(
        const double fatigueBeta)
    {
        return ValidateLargerThanZero(fatigueBeta, "FatigueBeta");
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::FailureTension(
        const double failureTension)
    {
        return ValidateLargerThanZero(failureTension, "FailureTension");
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::ImpactNumberC(
        const double impactNumberC)
    {
        return ValidateLargerThanZero(impactNumberC, "ImpactNumberC");
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::DensityOfWater(
        const double densityOfWater)
    {
        if (densityOfWater < 950 || densityOfWater > 1050)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, "DensityOfWater must be in range [950, 1050].");
        }

        return nullptr;
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::SoilElasticity(
        const double soilElasticity)
    {
        return ValidateLargerThanZero(soilElasticity, "SoilElasticity");
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::StiffnessRelationNu(
        const double stiffnessRelationNu)
    {
        return ValidateLargerThanZero(stiffnessRelationNu, "StiffnessRelationNu");
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::Thickness(
        const double thickness)
    {
        return ValidateLargerThanZero(thickness, "Thickness");
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::ElasticModulus(
        const double elasticModulus)
    {
        return ValidateLargerThanZero(elasticModulus, "ElasticModulus");
    }

    unique_ptr<ValidationIssue> AsphaltRevetmentWaveImpactValidator::ValidateLargerThanZero(
        const double propertyToValidate,
        const string& propertyName)
    {
        if (propertyToValidate <= 0)
        {
            return make_unique<ValidationIssue>(ValidationIssueType::Error, propertyName + " must be larger than 0.");
        }

        return nullptr;
    }
}