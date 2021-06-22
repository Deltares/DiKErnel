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

#include "AsphaltRevetmentWaveImpactLocationDependentInput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace std;

    AsphaltRevetmentWaveImpactLocationDependentInput::AsphaltRevetmentWaveImpactLocationDependentInput(
        string name,
        const double initialDamage,
        const double failureNumber,
        const double tanA,
        const double positionZ,
        const double failureTension,
        const double densityOfWater,
        const double soilElasticity,
        unique_ptr<AsphaltRevetmentWaveImpactLayer> upperLayer,
        unique_ptr<AsphaltRevetmentWaveImpactLayer> subLayer,
        const double averageNumberOfWavesCtm,
        unique_ptr<AsphaltRevetmentWaveImpactFatigue> fatigue,
        const double impactNumberC,
        const double stiffnessRelationNu,
        vector<tuple<double, double>> widthFactors,
        vector<tuple<double, double>> depthFactors,
        vector<tuple<double, double>> impactFactors)
        : LocationDependentInput(move(name), initialDamage, failureNumber, positionZ),
          _tanA(tanA),
          _failureTension(failureTension),
          _densityOfWater(densityOfWater),
          _soilElasticity(soilElasticity),
          _upperLayer(move(upperLayer)),
          _subLayer(move(subLayer)),
          _averageNumberOfWavesCtm(averageNumberOfWavesCtm),
          _fatigue(move(fatigue)),
          _impactNumberC(impactNumberC),
          _stiffnessRelationNu(stiffnessRelationNu),
          _widthFactors(move(widthFactors)),
          _depthFactors(move(depthFactors)),
          _impactFactors(move(impactFactors)) { }

    unique_ptr<TimeDependentOutput> AsphaltRevetmentWaveImpactLocationDependentInput::Calculate(
        double initialDamage,
        const ITimeDependentInput& timeDependentInput)
    {
        return nullptr;
    }

    double AsphaltRevetmentWaveImpactLocationDependentInput::GetTanA() const
    {
        return _tanA;
    }

    double AsphaltRevetmentWaveImpactLocationDependentInput::GetFailureTension() const
    {
        return _failureTension;
    }

    double AsphaltRevetmentWaveImpactLocationDependentInput::GetDensityOfWater() const
    {
        return _densityOfWater;
    }

    double AsphaltRevetmentWaveImpactLocationDependentInput::GetSoilElasticity() const
    {
        return _soilElasticity;
    }

    AsphaltRevetmentWaveImpactLayer& AsphaltRevetmentWaveImpactLocationDependentInput::GetUpperLayer() const
    {
        return *_upperLayer;
    }

    AsphaltRevetmentWaveImpactLayer& AsphaltRevetmentWaveImpactLocationDependentInput::GetSubLayer() const
    {
        return *_subLayer;
    }

    double AsphaltRevetmentWaveImpactLocationDependentInput::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm;
    }

    AsphaltRevetmentWaveImpactFatigue& AsphaltRevetmentWaveImpactLocationDependentInput::GetFatigue() const
    {
        return *_fatigue;
    }

    double AsphaltRevetmentWaveImpactLocationDependentInput::GetImpactNumberC() const
    {
        return _impactNumberC;
    }

    double AsphaltRevetmentWaveImpactLocationDependentInput::GetStiffnessRelationNu() const
    {
        return _stiffnessRelationNu;
    }

    const vector<tuple<double, double>>& AsphaltRevetmentWaveImpactLocationDependentInput::GetWidthFactors() const
    {
        return _widthFactors;
    }

    const vector<tuple<double, double>>& AsphaltRevetmentWaveImpactLocationDependentInput::GetDepthFactors() const
    {
        return _depthFactors;
    }

    const vector<tuple<double, double>>& AsphaltRevetmentWaveImpactLocationDependentInput::GetImpactFactors() const
    {
        return _impactFactors;
    }
}
