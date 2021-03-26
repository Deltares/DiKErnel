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

#include "NaturalStoneRevetmentLocationDependentInput.h"

#include "Constants.h"
#include "HydraulicLoad.h"
#include "NaturalStoneRevetment.h"
#include "Revetment.h"
#include "TimeDependentInput.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace FunctionLibrary;
    using namespace std;

    NaturalStoneRevetmentLocationDependentInput::NaturalStoneRevetmentLocationDependentInput(
        string name,
        const double initialDamage,
        const double failureNumber,
        const double slopeAngle,
        const double relativeDensity,
        const double thicknessTopLayer,
        unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads,
        unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading,
        unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading,
        unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation,
        unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact,
        unique_ptr<NaturalStoneRevetmentWaveAngleImpact> waveAngleImpact)
        : LocationDependentInput(move(name), initialDamage, failureNumber),
          _slopeAngle(slopeAngle),
          _relativeDensity(relativeDensity),
          _thicknessTopLayer(thicknessTopLayer),
          _hydraulicLoads(move(hydraulicLoads)),
          _upperLimitLoading(move(upperLimitLoading)),
          _lowerLimitLoading(move(lowerLimitLoading)),
          _distanceMaximumWaveElevation(move(distanceMaximumWaveElevation)),
          _normativeWidthOfWaveImpact(move(normativeWidthOfWaveImpact)),
          _waveAngleImpact(move(waveAngleImpact)) {}

    double NaturalStoneRevetmentLocationDependentInput::Calculate(
        const double startDamage,
        const ITimeDependentInput& timeDependentInput)
    {
        const auto tanA = GetSlopeAngle();
        const auto positionZ = 1.0;
        const auto waterLevel = timeDependentInput.GetWaterLevel();
        const auto waveHeightHm0 = timeDependentInput.GetWaveHeightHm0();
        const auto wavePeriodTm10 = timeDependentInput.GetWavePeriodTm10();

        const auto impactShallowWater = NaturalStoneRevetment::ImpactShallowWater();

        const auto waveSteepnessDeepWater = HydraulicLoad::WaveSteepnessDeepWater(
            waveHeightHm0,
            wavePeriodTm10,
            Constants::GRAVITATIONAL_ACCELERATION);

        const auto& distanceMaximumWaveElevationInput = GetDistanceMaximumWaveElevation();
        const auto distanceMaximumWaveElevation = NaturalStoneRevetment::DistanceMaximumWaveElevation(
            impactShallowWater,
            waveSteepnessDeepWater,
            waveHeightHm0,
            distanceMaximumWaveElevationInput.GetDistanceMaximumWaveElevationAsmax(),
            distanceMaximumWaveElevationInput.GetDistanceMaximumWaveElevationBsmax());

        const auto surfSimilarityParameter = HydraulicLoad::SurfSimilarityParameter(
            tanA,
            waveHeightHm0,
            wavePeriodTm10,
            Constants::GRAVITATIONAL_ACCELERATION);

        const auto& normativeWidthOfWaveImpactInput = GetNormativeWidthOfWaveImpact();
        const auto normativeWidthOfWaveImpact = NaturalStoneRevetment::NormativeWidthOfWaveImpact(
            surfSimilarityParameter,
            waveHeightHm0,
            normativeWidthOfWaveImpactInput.GetNormativeWidthOfWaveImpactAwi(),
            normativeWidthOfWaveImpactInput.GetNormativeWidthOfWaveImpactBwi());

        const auto slopeAngle = HydraulicLoad::SlopeAngle(
            tanA);

        const auto depthMaximumWaveLoad = NaturalStoneRevetment::DepthMaximumWaveLoad(
            distanceMaximumWaveElevation,
            normativeWidthOfWaveImpact,
            slopeAngle);

        const auto& lowerLimitLoadingInput = GetLowerLimitLoading();
        const auto lowerLimitLoading = NaturalStoneRevetment::LowerLimitLoading(
            depthMaximumWaveLoad,
            surfSimilarityParameter,
            waterLevel,
            waveHeightHm0,
            lowerLimitLoadingInput.GetLowerLimitAll(),
            lowerLimitLoadingInput.GetLowerLimitBll(),
            lowerLimitLoadingInput.GetLowerLimitCll());

        const auto& upperLimitLoadingInput = GetUpperLimitLoading();
        const auto upperLimitLoading = NaturalStoneRevetment::UpperLimitLoading(
            depthMaximumWaveLoad,
            surfSimilarityParameter,
            waterLevel,
            waveHeightHm0,
            upperLimitLoadingInput.GetUpperLimitAul(),
            upperLimitLoadingInput.GetUpperLimitBul(),
            upperLimitLoadingInput.GetUpperLimitCul());

        const auto loadingOfRevetment = HydraulicLoad::LoadingOfRevetment(
            lowerLimitLoading,
            upperLimitLoading,
            positionZ);

        auto incrementOfDamage = 0.0;

        if (loadingOfRevetment)
        {
            const auto hydraulicLoad = 1.0;
            const auto resistance = 1.0;
            const auto incrementDegradation = 1.0;
            const auto waveAngleImpact = 1.0;

            incrementOfDamage = NaturalStoneRevetment::IncrementDamage(
                hydraulicLoad,
                resistance,
                incrementDegradation,
                waveAngleImpact);
        }

        return Revetment::Damage(incrementOfDamage, startDamage);

        // return NaturalStoneRevetmentDeprecated::CalculateDamage(
        //     startDamage, _slopeAngle, _relativeDensity, _thicknessTopLayer,
        //     timeDependentInput.GetWaveHeightHm0(), timeDependentInput.GetWavePeriodTm10(),
        //     timeDependentInput.GetWaveAngle(), timeDependentInput.GetBeginTime(), timeDependentInput.GetEndTime(),
        //     _hydraulicLoads->GetHydraulicLoadAp(), _hydraulicLoads->GetHydraulicLoadBp(), _hydraulicLoads->GetHydraulicLoadCp(),
        //     _hydraulicLoads->GetHydraulicLoadNp(), _hydraulicLoads->GetHydraulicLoadAs(), _hydraulicLoads->GetHydraulicLoadBs(),
        //     _hydraulicLoads->GetHydraulicLoadCs(), _hydraulicLoads->GetHydraulicLoadNs(), _waveAngleImpact->GetBetamax(),
        //     _hydraulicLoads->GetHydraulicLoadXib());
    }

    double NaturalStoneRevetmentLocationDependentInput::GetSlopeAngle() const
    {
        return _slopeAngle;
    }

    double NaturalStoneRevetmentLocationDependentInput::GetRelativeDensity() const
    {
        return _relativeDensity;
    }

    double NaturalStoneRevetmentLocationDependentInput::GetThicknessTopLayer() const
    {
        return _thicknessTopLayer;
    }

    NaturalStoneRevetmentHydraulicLoads& NaturalStoneRevetmentLocationDependentInput::GetHydraulicLoads() const
    {
        return *_hydraulicLoads;
    }

    NaturalStoneRevetmentUpperLimitLoading& NaturalStoneRevetmentLocationDependentInput::GetUpperLimitLoading() const
    {
        return *_upperLimitLoading;
    }

    NaturalStoneRevetmentLowerLimitLoading& NaturalStoneRevetmentLocationDependentInput::GetLowerLimitLoading() const
    {
        return *_lowerLimitLoading;
    }

    NaturalStoneRevetmentDistanceMaximumWaveElevation& NaturalStoneRevetmentLocationDependentInput::GetDistanceMaximumWaveElevation() const
    {
        return *_distanceMaximumWaveElevation;
    }

    NaturalStoneRevetmentNormativeWidthOfWaveImpact& NaturalStoneRevetmentLocationDependentInput::GetNormativeWidthOfWaveImpact() const
    {
        return *_normativeWidthOfWaveImpact;
    }

    NaturalStoneRevetmentWaveAngleImpact& NaturalStoneRevetmentLocationDependentInput::GetWaveAngleImpact() const
    {
        return *_waveAngleImpact;
    }
}
