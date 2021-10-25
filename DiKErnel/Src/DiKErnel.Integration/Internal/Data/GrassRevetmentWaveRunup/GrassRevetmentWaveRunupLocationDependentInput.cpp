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

#include "GrassRevetmentWaveRunupLocationDependentInput.h"

#include "GrassRevetmentWaveRunupValidator.h"
#include "ValidationHelper.h"

namespace DiKErnel::Integration
{
    using namespace Core;
    using namespace DomainLibrary;
    using namespace std;

    GrassRevetmentWaveRunupLocationDependentInput::GrassRevetmentWaveRunupLocationDependentInput(
        const double x,
        const double initialDamage,
        const double failureNumber,
        const double outerSlope,
        const double criticalCumulativeOverload,
        const double criticalFrontVelocity,
        const double increasedLoadTransitionAlphaM,
        const double reducedStrengthTransitionAlphaS,
        const double averageNumberOfWavesCtm,
        unique_ptr<GrassRevetmentWaveRunupRepresentative2P> representative2P,
        unique_ptr<GrassRevetmentWaveRunupWaveAngleImpact> waveAngleImpact)
        : LocationDependentInput(x, initialDamage, failureNumber),
          _outerSlope(outerSlope),
          _criticalCumulativeOverload(criticalCumulativeOverload),
          _criticalFrontVelocity(criticalFrontVelocity),
          _increasedLoadTransitionAlphaM(increasedLoadTransitionAlphaM),
          _reducedStrengthTransitionAlphaS(reducedStrengthTransitionAlphaS),
          _averageNumberOfWavesCtm(averageNumberOfWavesCtm),
          _representative2P(move(representative2P)),
          _waveAngleImpact(move(waveAngleImpact)) {}

    double GrassRevetmentWaveRunupLocationDependentInput::GetOuterSlope() const
    {
        return _outerSlope;
    }

    double GrassRevetmentWaveRunupLocationDependentInput::GetCriticalCumulativeOverload() const
    {
        return _criticalCumulativeOverload;
    }

    double GrassRevetmentWaveRunupLocationDependentInput::GetCriticalFrontVelocity() const
    {
        return _criticalFrontVelocity;
    }

    double GrassRevetmentWaveRunupLocationDependentInput::GetIncreasedLoadTransitionAlphaM() const
    {
        return _increasedLoadTransitionAlphaM;
    }

    double GrassRevetmentWaveRunupLocationDependentInput::GetReducedStrengthTransitionAlphaS() const
    {
        return _reducedStrengthTransitionAlphaS;
    }

    double GrassRevetmentWaveRunupLocationDependentInput::GetAverageNumberOfWavesCtm() const
    {
        return _averageNumberOfWavesCtm;
    }

    GrassRevetmentWaveRunupRepresentative2P& GrassRevetmentWaveRunupLocationDependentInput::GetRepresentative2P() const
    {
        return *_representative2P;
    }

    GrassRevetmentWaveRunupWaveAngleImpact& GrassRevetmentWaveRunupLocationDependentInput::GetWaveAngleImpact() const
    {
        return *_waveAngleImpact;
    }

    bool GrassRevetmentWaveRunupLocationDependentInput::Validate()
    {
        const auto baseValidationSucceeded = LocationDependentInput::Validate();

        const auto representativeWaveRunup2PGammab = GrassRevetmentWaveRunupValidator::RepresentativeWaveRunup2PGammab(
            _representative2P->GetGammab());
        const auto representativeWaveRunup2PGammaf = GrassRevetmentWaveRunupValidator::RepresentativeWaveRunup2PGammaf(
            _representative2P->GetGammaf());
        const auto outerSlope = GrassRevetmentWaveRunupValidator::OuterSlope(_outerSlope);
        const auto criticalFrontVelocity = GrassRevetmentWaveRunupValidator::CriticalFrontVelocity(_criticalFrontVelocity);
        const auto increasedLoadTransitionAlphaM = GrassRevetmentWaveRunupValidator::IncreasedLoadTransitionAlphaM(_increasedLoadTransitionAlphaM);
        const auto reducedStrengthTransitionAlphaS = GrassRevetmentWaveRunupValidator::ReducedStrengthTransitionAlphaS(
            _reducedStrengthTransitionAlphaS);

        return ValidationHelper::RegisterValidationIssue(representativeWaveRunup2PGammab.get())
                && ValidationHelper::RegisterValidationIssue(representativeWaveRunup2PGammaf.get())
                && ValidationHelper::RegisterValidationIssue(outerSlope.get())
                && ValidationHelper::RegisterValidationIssue(criticalFrontVelocity.get())
                && ValidationHelper::RegisterValidationIssue(increasedLoadTransitionAlphaM.get())
                && ValidationHelper::RegisterValidationIssue(reducedStrengthTransitionAlphaS.get())
                && baseValidationSucceeded;
    }
}
