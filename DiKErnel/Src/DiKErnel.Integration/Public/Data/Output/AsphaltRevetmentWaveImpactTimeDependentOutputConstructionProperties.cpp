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

#include "AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties.h"

namespace DiKErnel::Integration
{
    using namespace std;

    AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties(
        const double incrementDamage,
        const double damage,
        unique_ptr<int> timeOfFailure)
        : TimeDependentOutputConstructionProperties(incrementDamage, damage, move(timeOfFailure)) {}

    void AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetLogFailureTension(
        const double logFailureTension)
    {
        _logFailureTension = logFailureTension;
    }

    void AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetMaximumPeakStress(
        const double maximumPeakStress)
    {
        _maximumPeakStress = maximumPeakStress;
    }

    void AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetStiffnessRelation(
        const double stiffnessRelation)
    {
        _stiffnessRelation = stiffnessRelation;
    }

    void AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetComputationalThickness(
        const double computationalThickness)
    {
        _computationalThickness = computationalThickness;
    }

    void AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::SetEquivalentElasticModulus(
        const double equivalentElasticModulus)
    {
        _equivalentElasticModulus = equivalentElasticModulus;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetLogFailureTension() const
    {
        return _logFailureTension;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetMaximumPeakStress() const
    {
        return _maximumPeakStress;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetStiffnessRelation() const
    {
        return _stiffnessRelation;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetComputationalThickness() const
    {
        return _computationalThickness;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties::GetEquivalentElasticModulus() const
    {
        return _equivalentElasticModulus;
    }
}
