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

#include "AsphaltRevetmentWaveImpactTimeDependentOutput.h"

namespace DiKErnel::Integration
{
    using namespace std;

    AsphaltRevetmentWaveImpactTimeDependentOutput::AsphaltRevetmentWaveImpactTimeDependentOutput(
        const double incrementDamage,
        const double damage,
        unique_ptr<int> timeOfFailure,
        const double logFailureTension,
        const double maximumPeakStress,
        const double stiffnessRelation,
        const double computationalThickness,
        const double equivalentElasticModulus)
        : TimeDependentOutput(incrementDamage, damage, move(timeOfFailure)),
          _logFailureTension(logFailureTension),
          _maximumPeakStress(maximumPeakStress),
          _stiffnessRelation(stiffnessRelation),
          _computationalThickness(computationalThickness),
          _equivalentElasticModulus(equivalentElasticModulus) {}

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetLogFailureTension() const
    {
        return _logFailureTension;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetMaximumPeakStress() const
    {
        return _maximumPeakStress;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetStiffnessRelation() const
    {
        return _stiffnessRelation;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetComputationalThickness() const
    {
        return _computationalThickness;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetEquivalentElasticModulus() const
    {
        return _equivalentElasticModulus;
    }
}
