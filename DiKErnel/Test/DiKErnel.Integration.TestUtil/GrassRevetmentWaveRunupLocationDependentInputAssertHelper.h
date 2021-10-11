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

#pragma once

#include "GrassRevetmentWaveRunupLocationDependentInput.h"

namespace DiKErnel::Integration::TestUtil
{
    class GrassRevetmentWaveRunupLocationDependentInputAssertHelper
    {
        public:
            static void AssertGeneralProperties(
                const std::string& name,
                double x,
                double outerSlope,
                double positionZ,
                const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput);

            static void AssertRepresentative2P(
                double representative2PAru,
                double representative2PBru,
                double representative2PCru,
                double gammaB,
                double gammaF,
                const GrassRevetmentWaveRunupRepresentative2P& representative2P);

            static void AssertWaveAngleImpact(
                double abeta,
                double betamax,
                const GrassRevetmentWaveRunupWaveAngleImpact& waveAngleImpact);

            static void AssertCumulativeOverload(
                double criticalCumulativeOverload,
                const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput);

            static void AssertFrontVelocity(
                double criticalFrontVelocity,
                const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput);

            static void AssertTransitionAlpha(
                double increasedLoadTransitionAlphaM,
                double reducedStrengthTransitionAlphaS,
                const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput);

            static void AssertAverageNumberOfWaves(
                double averageNumberOfWavesCtm,
                const GrassRevetmentWaveRunupLocationDependentInput& locationDependentInput);
    };
}
