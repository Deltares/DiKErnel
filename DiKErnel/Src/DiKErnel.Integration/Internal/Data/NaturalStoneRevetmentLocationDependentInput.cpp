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
        const double tanA,
        const double relativeDensity,
        const double thicknessTopLayer,
        unique_ptr<NaturalStoneRevetmentHydraulicLoads> hydraulicLoads,
        unique_ptr<NaturalStoneRevetmentUpperLimitLoading> upperLimitLoading,
        unique_ptr<NaturalStoneRevetmentLowerLimitLoading> lowerLimitLoading,
        unique_ptr<NaturalStoneRevetmentDistanceMaximumWaveElevation> distanceMaximumWaveElevation,
        unique_ptr<NaturalStoneRevetmentNormativeWidthOfWaveImpact> normativeWidthOfWaveImpact,
        unique_ptr<NaturalStoneRevetmentWaveAngleImpact> waveAngleImpact)
        : LocationDependentInput(move(name), initialDamage, failureNumber),
          _tanA(tanA),
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
        const auto tanA = GetTanA();
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
            const auto& hydraulicLoadInput = GetHydraulicLoads();
            const auto hydraulicLoad = NaturalStoneRevetment::HydraulicLoad(
                surfSimilarityParameter,
                waveHeightHm0,
                hydraulicLoadInput.GetHydraulicLoadXib(),
                hydraulicLoadInput.GetHydraulicLoadAp(),
                hydraulicLoadInput.GetHydraulicLoadBp(),
                hydraulicLoadInput.GetHydraulicLoadCp(),
                hydraulicLoadInput.GetHydraulicLoadNp(),
                hydraulicLoadInput.GetHydraulicLoadAs(),
                hydraulicLoadInput.GetHydraulicLoadBs(),
                hydraulicLoadInput.GetHydraulicLoadCs(),
                hydraulicLoadInput.GetHydraulicLoadNs());

            const auto resistance = NaturalStoneRevetment::Resistance(
                GetRelativeDensity(),
                GetThicknessTopLayer());

            const auto& waveAngleImpactInput = GetWaveAngleImpact();
            const auto waveAngleImpact = NaturalStoneRevetment::WaveAngleImpact(
                timeDependentInput.GetWaveAngle(),
                waveAngleImpactInput.GetBetamax());

            const auto referenceDegradation = NaturalStoneRevetment::ReferenceDegradation(
                resistance,
                hydraulicLoad,
                waveAngleImpact,
                startDamage);

            const auto referenceTimeDegradation = NaturalStoneRevetment::ReferenceTimeDegradation(
                referenceDegradation,
                wavePeriodTm10);

            const auto incrementTime = Revetment::IncrementTime(
                timeDependentInput.GetBeginTime(),
                timeDependentInput.GetEndTime());

            const auto incrementDegradation = NaturalStoneRevetment::IncrementDegradation(
                referenceTimeDegradation,
                incrementTime,
                wavePeriodTm10);

            incrementOfDamage = NaturalStoneRevetment::IncrementDamage(
                hydraulicLoad,
                resistance,
                incrementDegradation,
                waveAngleImpact);
        }

        return Revetment::Damage(incrementOfDamage, startDamage);
    }

    double NaturalStoneRevetmentLocationDependentInput::GetTanA() const
    {
        return _tanA;
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
