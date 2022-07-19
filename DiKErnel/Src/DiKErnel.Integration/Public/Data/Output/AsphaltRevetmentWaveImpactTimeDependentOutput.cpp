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

#include "AsphaltRevetmentWaveImpactTimeDependentOutput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;

    AsphaltRevetmentWaveImpactTimeDependentOutput::AsphaltRevetmentWaveImpactTimeDependentOutput(
        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties& constructionProperties)
        : TimeDependentOutput(constructionProperties),
          _logFailureTension(move(constructionProperties._logFailureTension)),
          _maximumPeakStress(move(constructionProperties._maximumPeakStress)),
          _stiffnessRelation(move(constructionProperties._stiffnessRelation)),
          _computationalThickness(move(constructionProperties._computationalThickness)),
          _equivalentElasticModulus(move(constructionProperties._equivalentElasticModulus))
    {
        ThrowExceptionWhenPropertyIsNullPtr(_logFailureTension.get(), "logFailureTension");
        ThrowExceptionWhenPropertyIsNullPtr(_maximumPeakStress.get(), "maximumPeakStress");
        ThrowExceptionWhenPropertyIsNullPtr(_stiffnessRelation.get(), "stiffnessRelation");
        ThrowExceptionWhenPropertyIsNullPtr(_computationalThickness.get(), "computationalThickness");
        ThrowExceptionWhenPropertyIsNullPtr(_equivalentElasticModulus.get(), "equivalentElasticModulus");
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetLogFailureTension() const
    {
        return *_logFailureTension;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetMaximumPeakStress() const
    {
        return *_maximumPeakStress;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetStiffnessRelation() const
    {
        return *_stiffnessRelation;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetComputationalThickness() const
    {
        return *_computationalThickness;
    }

    double AsphaltRevetmentWaveImpactTimeDependentOutput::GetEquivalentElasticModulus() const
    {
        return *_equivalentElasticModulus;
    }
}
