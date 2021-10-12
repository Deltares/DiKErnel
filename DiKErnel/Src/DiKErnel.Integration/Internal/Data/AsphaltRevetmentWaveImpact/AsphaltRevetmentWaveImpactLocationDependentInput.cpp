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

#include "AsphaltRevetmentWaveImpact.h"
#include "AsphaltRevetmentWaveImpactTimeDependentOutput.h"
#include "Constants.h"
#include "Revetment.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace FunctionLibrary;
    using namespace std;

    AsphaltRevetmentWaveImpactLocationDependentInput::AsphaltRevetmentWaveImpactLocationDependentInput(
        string name,
        const double x,
        const double initialDamage,
        const double failureNumber,
        const double outerSlope,
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
        : LocationDependentInput(move(name), x, initialDamage, failureNumber),
          _outerSlope(outerSlope),
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

    double AsphaltRevetmentWaveImpactLocationDependentInput::GetOuterSlope() const
    {
        return _outerSlope;
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

    void AsphaltRevetmentWaveImpactLocationDependentInput::InitializeDerivedLocationDependentInput(
        const IProfileData& profileData)
    {
        LocationDependentInput::InitializeDerivedLocationDependentInput(profileData);

        _logFailureTension = AsphaltRevetmentWaveImpact::LogFailureTension(_failureTension);
        _computationalThickness = AsphaltRevetmentWaveImpact::ComputationalThickness(_upperLayer->GetThickness(), _subLayer->GetThickness(),
                                                                                     _upperLayer->GetElasticModulus(),
                                                                                     _subLayer->GetElasticModulus());
        _stiffnessRelation = AsphaltRevetmentWaveImpact::StiffnessRelation(_computationalThickness, _subLayer->GetElasticModulus(),
                                                                           _soilElasticity, _stiffnessRelationNu);
    }

    unique_ptr<TimeDependentOutput> AsphaltRevetmentWaveImpactLocationDependentInput::CalculateTimeDependentOutput(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput,
        const IProfileData& profileData)
    {
        const auto beginTime = timeDependentInput.GetBeginTime();
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();

        const auto incrementTime = Revetment::IncrementTime(beginTime, timeDependentInput.GetEndTime());
        const auto averageNumberOfWaves = Revetment::AverageNumberOfWaves(incrementTime, timeDependentInput.GetWavePeriodTm10(),
                                                                          _averageNumberOfWavesCtm);
        const auto maximumPeakStress = AsphaltRevetmentWaveImpact::MaximumPeakStress(waveHeightHm0, Constants::GRAVITATIONAL_ACCELERATION,
                                                                                     _densityOfWater);
        const auto incrementDamage = AsphaltRevetmentWaveImpact::IncrementDamage(_logFailureTension, averageNumberOfWaves, maximumPeakStress,
                                                                                 _stiffnessRelation, _computationalThickness, _outerSlope,
                                                                                 _widthFactors, _depthFactors, _impactFactors, GetPositionZ(),
                                                                                 timeDependentInput.GetWaterLevel(), waveHeightHm0,
                                                                                 _fatigue->GetAlpha(), _fatigue->GetBeta(), _impactNumberC);
        const auto damage = Revetment::Damage(incrementDamage, initialDamage);

        const auto failureNumber = GetFailureNumber();
        unique_ptr<int> timeOfFailure = nullptr;

        if (Revetment::FailureRevetment(damage, initialDamage, failureNumber))
        {
            const auto durationInTimeStepFailure = Revetment::DurationInTimeStepFailure(incrementTime, incrementDamage, failureNumber,
                                                                                        initialDamage);
            timeOfFailure = make_unique<int>(Revetment::TimeOfFailure(durationInTimeStepFailure, beginTime));
        }

        return make_unique<AsphaltRevetmentWaveImpactTimeDependentOutput>(incrementDamage, damage, move(timeOfFailure), _logFailureTension,
                                                                          maximumPeakStress, _stiffnessRelation, _computationalThickness,
                                                                          _subLayer->GetElasticModulus());
    }
}
