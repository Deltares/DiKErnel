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

#include "AsphaltRevetmentWaveImpactFunctionsCalculatedInput.h"

namespace DiKErnel::FunctionLibrary
{
    using namespace std;

    AsphaltRevetmentWaveImpactFunctionsCalculatedInput::AsphaltRevetmentWaveImpactFunctionsCalculatedInput(
        const double logFailureTension,
        const double computationalThickness,
        const double stiffnessRelation,
        const double equivalentElasticModulus,
        const double outerSlope)
        : _logFailureTension(logFailureTension),
        _computationalThickness(computationalThickness),
        _stiffnessRelation(stiffnessRelation),
        _equivalentElasticModulus(equivalentElasticModulus),
        _outerSlope(outerSlope) { }

    void AsphaltRevetmentWaveImpactFunctionsCalculatedInput::SetAverageNumberOfWaves(
        const double averageNumberOfWaves)
    {
        _averageNumberOfWaves = averageNumberOfWaves;
    }

    void AsphaltRevetmentWaveImpactFunctionsCalculatedInput::SetMaximumPeakStress(
        const double maximumPeakStress)
    {
        _maximumPeakStress = maximumPeakStress;
    }

    double AsphaltRevetmentWaveImpactFunctionsCalculatedInput::GetLogFailureTension() const
    {
        return _logFailureTension;
    }

    double AsphaltRevetmentWaveImpactFunctionsCalculatedInput::GetComputationalThickness() const
    {
        return _computationalThickness;
    }

    double AsphaltRevetmentWaveImpactFunctionsCalculatedInput::GetStiffnessRelation() const
    {
        return _stiffnessRelation;
    }

    double AsphaltRevetmentWaveImpactFunctionsCalculatedInput::GetEquivalentElasticModulus() const
    {
        return _equivalentElasticModulus;
    }

    double AsphaltRevetmentWaveImpactFunctionsCalculatedInput::GetOuterSlope() const
    {
        return _outerSlope;
    }

    double AsphaltRevetmentWaveImpactFunctionsCalculatedInput::GetAverageNumberOfWaves() const
    {
        return _averageNumberOfWaves;
    }

    double AsphaltRevetmentWaveImpactFunctionsCalculatedInput::GetMaximumPeakStress() const
    {
        return _maximumPeakStress;
    }
}
