// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System;
using System.Collections.Generic;
using DiKErnel.Core.Data;

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    internal class GrassRevetmentWaveRunupRayleighLocationDependentInput : GrassRevetmentWaveRunupLocationDependentInput
    {
        private double verticalDistanceWaterLevelElevation = double.PositiveInfinity;
        private double waveAngleImpact = double.PositiveInfinity;
        private double representativeWaveRunup2P = double.PositiveInfinity;
        private double cumulativeOverload = double.PositiveInfinity;

        public GrassRevetmentWaveRunupRayleighLocationDependentInput(double x, double initialDamage,
                                                                     double failureNumber, double outerSlope,
                                                                     double criticalCumulativeOverload,
                                                                     double criticalFrontVelocity,
                                                                     double increasedLoadTransitionAlphaM,
                                                                     double reducedStrengthTransitionAlphaS,
                                                                     double averageNumberOfWavesCtm,
                                                                     GrassRevetmentWaveRunupRepresentative2P representative2P,
                                                                     GrassRevetmentWaveRunupWaveAngleImpact waveAngleImpact,
                                                                     int fixedNumberOfWaves, double frontVelocityCu)
            : base(x, initialDamage, failureNumber, outerSlope, criticalCumulativeOverload, criticalFrontVelocity,
                   increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, averageNumberOfWavesCtm,
                   representative2P, waveAngleImpact)
        {
            FixedNumberOfWaves = fixedNumberOfWaves;
            FrontVelocityCu = frontVelocityCu;
        }

        public int FixedNumberOfWaves { get; }

        public double FrontVelocityCu { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            return base.Validate(timeDependentInputItems, profileData);
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return base.GetLocationDependentOutput(timeDependentOutputItems);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            throw new NotImplementedException();
        }

        private double CalculateRepresentativeWaveRunup2P(double surfSimilarityParameter, double waveHeightHm0)
        {
            throw new NotImplementedException();
        }

        private double CalculateCumulativeOverload(double averageNumberOfWaves)
        {
            throw new NotImplementedException();
        }

        private GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, int? timeOfFailure)
        {
            throw new NotImplementedException();
        }

        private class GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties {}
    }
}