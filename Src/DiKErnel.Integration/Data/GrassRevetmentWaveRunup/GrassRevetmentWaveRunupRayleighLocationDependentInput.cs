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

using System.Collections.Generic;
using DiKErnel.Core.Data;

namespace DiKErnel.Integration.Data.GrassRevetmentWaveRunup
{
    internal class GrassRevetmentWaveRunupRayleighLocationDependentInput : GrassRevetmentWaveRunupLocationDependentInput
    {
        private int _fixedNumberOfWaves;
        private double _frontVelocityCu;

        private double _verticalDistanceWaterLevelElevation = double.PositiveInfinity;
        private double _waveAngleImpact = double.PositiveInfinity;
        private double _representativeWaveRunup2P = double.PositiveInfinity;
        private double _cumulativeOverload = double.PositiveInfinity;

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
                   representative2P, waveAngleImpact) {}

        public int GetFixedNumberOfWaves();

        public double GetFrontVelocityCu();

        public bool Validate(
            IReadOnlyList<ITimeDependentInput> timeDependentInputs,
            IProfileData profileData)

        public LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)

        protected TimeDependentOutput CalculateTimeDependentOutput(
            double initialDamage,
            ITimeDependentInput timeDependentInput,
            IProfileData profileData)override;override;override;

        private double CalculateRepresentativeWaveRunup2P(
            double surfSimilarityParameter,
            double waveHeightHm0);

        private double CalculateCumulativeOverload(
            double averageNumberOfWaves);

        private GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage,
            double damage,
            int? timeOfFailure);
    }
}