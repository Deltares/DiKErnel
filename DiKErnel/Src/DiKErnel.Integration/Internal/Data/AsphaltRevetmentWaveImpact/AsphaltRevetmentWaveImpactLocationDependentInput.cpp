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

#include "AsphaltRevetmentWaveImpactLocationDependentInput.h"

#include "AsphaltRevetmentWaveImpactFunctions.h"
#include "AsphaltRevetmentWaveImpactLocationDependentOutput.h"
#include "AsphaltRevetmentWaveImpactTimeDependentOutput.h"
#include "AsphaltRevetmentWaveImpactValidator.h"
#include "CharacteristicPointsHelper.h"
#include "Constants.h"
#include "RevetmentFunctions.h"
#include "RevetmentValidator.h"
#include "ValidationHelper.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace FunctionLibrary;
    using namespace std;
    using namespace Util;

    AsphaltRevetmentWaveImpactLocationDependentInput::AsphaltRevetmentWaveImpactLocationDependentInput(
        const double x,
        const double initialDamage,
        const double failureNumber,
        const double failureTension,
        const double densityOfWater,
        const double soilElasticity,
        unique_ptr<AsphaltRevetmentWaveImpactLayer> upperLayer,
        unique_ptr<AsphaltRevetmentWaveImpactLayer> subLayer,
        const double averageNumberOfWavesCtm,
        unique_ptr<AsphaltRevetmentWaveImpactFatigue> fatigue,
        const double impactNumberC,
        const double stiffnessRelationNu,
        vector<pair<double, double>> widthFactors,
        vector<pair<double, double>> depthFactors,
        vector<pair<double, double>> impactFactors)
        : LocationDependentInput(x, initialDamage, failureNumber),
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

    AsphaltRevetmentWaveImpactLayer* AsphaltRevetmentWaveImpactLocationDependentInput::GetSubLayer() const
    {
        return _subLayer.get();
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

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactLocationDependentInput::GetWidthFactors() const
    {
        return _widthFactors;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactLocationDependentInput::GetDepthFactors() const
    {
        return _depthFactors;
    }

    const vector<pair<double, double>>& AsphaltRevetmentWaveImpactLocationDependentInput::GetImpactFactors() const
    {
        return _impactFactors;
    }

    bool AsphaltRevetmentWaveImpactLocationDependentInput::Validate(
        const IProfileData& profileData) const
    {
        const auto baseValidationSuccessful = LocationDependentInput::Validate(profileData);

        vector<unique_ptr<ValidationIssue>> validationIssues;
        validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::FatigueAlpha(_fatigue->GetAlpha()));
        validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::FatigueBeta(_fatigue->GetBeta()));
        validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::FailureTension(_failureTension));
        validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::ImpactNumberC(_impactNumberC));
        validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::DensityOfWater(_densityOfWater));
        validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::SoilElasticity(_soilElasticity));
        validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::StiffnessRelationNu(_stiffnessRelationNu));
        validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::Thickness(_upperLayer->GetThickness()));
        validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::ElasticModulus(_upperLayer->GetElasticModulus()));

        if (_subLayer != nullptr)
        {
            validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::Thickness(_subLayer->GetThickness()));
            validationIssues.emplace_back(AsphaltRevetmentWaveImpactValidator::ElasticModulus(_subLayer->GetElasticModulus()));
        }

        validationIssues.emplace_back(RevetmentValidator::AverageNumberOfWavesCtm(_averageNumberOfWavesCtm));

        return ValidationHelper::RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
    }

    unique_ptr<LocationDependentOutput> AsphaltRevetmentWaveImpactLocationDependentInput::GetLocationDependentOutput(
        vector<unique_ptr<TimeDependentOutput>> timeDependentOutputItems)
    {
        return make_unique<AsphaltRevetmentWaveImpactLocationDependentOutput>(GetZ(), move(timeDependentOutputItems),
                                                                              _calculatedInput->GetOuterSlope());
    }

    void AsphaltRevetmentWaveImpactLocationDependentInput::InitializeDerivedLocationDependentInput(
        const IProfileData& profileData)
    {
        LocationDependentInput::InitializeDerivedLocationDependentInput(profileData);

        double subLayerThickness;
        double subLayerElasticModulus;

        if (_subLayer != nullptr)
        {
            subLayerThickness = _subLayer->GetThickness();
            subLayerElasticModulus = _subLayer->GetElasticModulus();
        }
        else
        {
            subLayerThickness = 0;
            subLayerElasticModulus = _upperLayer->GetElasticModulus();
        }

        const auto logFailureTension = AsphaltRevetmentWaveImpactFunctions::LogFailureTension(_failureTension);
        const auto computationalThickness = AsphaltRevetmentWaveImpactFunctions::ComputationalThickness(
            _upperLayer->GetThickness(), subLayerThickness,
            _upperLayer->GetElasticModulus(),
            subLayerElasticModulus);
        const auto stiffnessRelation = AsphaltRevetmentWaveImpactFunctions::StiffnessRelation(computationalThickness, subLayerElasticModulus,
                                                                                              _soilElasticity, _stiffnessRelationNu);

        const auto& characteristicPoints = profileData.GetCharacteristicPoints();
        const auto notchOuterBerm =
                CharacteristicPointsHelper::GetCoordinatesForType(characteristicPoints, CharacteristicPointType::NotchOuterBerm);
        const auto crestOuterBerm =
                CharacteristicPointsHelper::GetCoordinatesForType(characteristicPoints, CharacteristicPointType::CrestOuterBerm);

        auto horizontalPosition = GetX();
        if (notchOuterBerm != nullptr && crestOuterBerm != nullptr
            && (horizontalPosition > crestOuterBerm->first && horizontalPosition <= notchOuterBerm->first))
        {
            horizontalPosition = crestOuterBerm->first;
        }

        const auto profileSegment = profileData.GetProfileSegment(horizontalPosition);
        const auto& profileSegmentLowerPoint = profileSegment->GetLowerPoint();
        const auto& profileSegmentUpperPoint = profileSegment->GetUpperPoint();

        const auto outerSlope = AsphaltRevetmentWaveImpactFunctions::OuterSlope(profileSegmentLowerPoint.GetX(), profileSegmentLowerPoint.GetZ(),
                                                                                profileSegmentUpperPoint.GetX(), profileSegmentUpperPoint.GetZ());

        _calculatedInput = make_unique<AsphaltRevetmentWaveImpactFunctionsCalculatedInput>(
            logFailureTension, computationalThickness, stiffnessRelation,
            subLayerElasticModulus, outerSlope);

        _input = make_unique<AsphaltRevetmentWaveImpactFunctionsInput>(GetZ(), _widthFactors, _depthFactors, _impactFactors, _fatigue->GetAlpha(),
                                                                       _fatigue->GetBeta(), _impactNumberC);
    }

    unique_ptr<TimeDependentOutput> AsphaltRevetmentWaveImpactLocationDependentInput::CalculateTimeDependentOutput(
        const double initialDamage,
        const ITimeDependentInput& timeDependentInput,
        const IProfileData& profileData)
    {
        const auto beginTime = timeDependentInput.GetBeginTime();
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();

        const auto incrementTime = RevetmentFunctions::IncrementTime(beginTime, timeDependentInput.GetEndTime());
        const auto averageNumberOfWaves = RevetmentFunctions::AverageNumberOfWaves(incrementTime, timeDependentInput.GetWavePeriodTm10(),
                                                                                   _averageNumberOfWavesCtm);

        const auto maximumPeakStress = AsphaltRevetmentWaveImpactFunctions::MaximumPeakStress(waveHeightHm0,
                                                                                              Constants::GetGravitationalAcceleration(),
                                                                                              _densityOfWater);

        _calculatedInput->SetAverageNumberOfWaves(averageNumberOfWaves);
        _calculatedInput->SetMaximumPeakStress(maximumPeakStress);

        _input->SetWaterLevel(timeDependentInput.GetWaterLevel());
        _input->SetWaveHeightHm0(waveHeightHm0);

        const auto incrementDamage = AsphaltRevetmentWaveImpactFunctions::IncrementDamage(*_input, *_calculatedInput);

        const auto damage = RevetmentFunctions::Damage(incrementDamage, initialDamage);

        unique_ptr<int> timeOfFailure = nullptr;

        if (const auto failureNumber = GetFailureNumber(); RevetmentFunctions::FailureRevetment(damage, initialDamage, failureNumber))
        {
            const auto durationInTimeStepFailure = RevetmentFunctions::DurationInTimeStepFailure(incrementTime, incrementDamage, failureNumber,
                                                                                                 initialDamage);
            timeOfFailure = make_unique<int>(RevetmentFunctions::TimeOfFailure(durationInTimeStepFailure, beginTime));
        }

        return make_unique<AsphaltRevetmentWaveImpactTimeDependentOutput>(incrementDamage, damage, move(timeOfFailure),
                                                                          _calculatedInput->GetLogFailureTension(),
                                                                          _calculatedInput->GetMaximumPeakStress(),
                                                                          _calculatedInput->GetStiffnessRelation(),
                                                                          _calculatedInput->GetComputationalThickness(),
                                                                          _calculatedInput->GetEquivalentElasticModulus());
    }
}
