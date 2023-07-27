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

namespace DiKErnel.Integration.Data.GrassRevetmentOvertopping
{
    internal class GrassRevetmentOvertoppingLocationDependentInput : LocationDependentInput
    {
        private IReadOnlyList<double> xValuesProfile;
        private IReadOnlyList<double> zValuesProfile;
        private IReadOnlyList<double> roughnessCoefficients;
        private double dikeHeight = double.PositiveInfinity;
        private double accelerationAlphaA = double.PositiveInfinity;

        private double verticalDistanceWaterLevelElevation = double.PositiveInfinity;
        private double representativeWaveRunup2P = double.PositiveInfinity;
        private double cumulativeOverload = double.PositiveInfinity;

        public GrassRevetmentOvertoppingLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                               double criticalCumulativeOverload,
                                                               double criticalFrontVelocity,
                                                               double increasedLoadTransitionAlphaM,
                                                               double reducedStrengthTransitionAlphaS,
                                                               double averageNumberOfWavesCtm, int fixedNumberOfWaves,
                                                               double frontVelocityCwo,
                                                               GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA
                                                                   locationDependentAccelerationAlphaA,
                                                               double? enforcedDikeHeight)
            : base(x, initialDamage, failureNumber)
        {
            CriticalCumulativeOverload = criticalCumulativeOverload;
            CriticalFrontVelocity = criticalFrontVelocity;
            IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM;
            ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS;
            AverageNumberOfWavesCtm = averageNumberOfWavesCtm;
            FixedNumberOfWaves = fixedNumberOfWaves;
            FrontVelocityCwo = frontVelocityCwo;
            LocationDependentAccelerationAlphaA = locationDependentAccelerationAlphaA;
            EnforcedDikeHeight = enforcedDikeHeight;
        }

        public double CriticalCumulativeOverload { get; }

        public double CriticalFrontVelocity { get; }

        public double IncreasedLoadTransitionAlphaM { get; }

        public double ReducedStrengthTransitionAlphaS { get; }

        public double AverageNumberOfWavesCtm { get; }

        public int FixedNumberOfWaves { get; }

        public double FrontVelocityCwo { get; }

        public GrassRevetmentOvertoppingLocationDependentAccelerationAlphaA LocationDependentAccelerationAlphaA { get; }

        public double? EnforcedDikeHeight { get; }

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

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            throw new NotImplementedException();
        }

        private void InitializeCalculationProfile((double, double) outerToe, (double, double) outerCrest,
                                                  IReadOnlyList<ProfileSegment> profileSegments)
        {
            throw new NotImplementedException();
        }

        private void InitializeDikeHeight((double, double) outerCrest, IReadOnlyList<ProfileSegment> profileSegments)
        {
            throw new NotImplementedException();
        }

        private void InitializeAccelerationAlphaA((double, double) outerCrest, (double, double) innerCrest)
        {
            throw new NotImplementedException();
        }

        private double CalculateRepresentativeWaveRunup2P(double waterLevel, double waveHeightHm0,
                                                          double wavePeriodTm10, double waveDirection)
        {
            throw new NotImplementedException();
        }

        private double CalculateCumulativeOverload(double averageNumberOfWaves)
        {
            throw new NotImplementedException();
        }

        private double CalculateDikeHeight((double, double) outerCrest, IReadOnlyList<ProfileSegment> profileSegments,
                                           double locationHeight)
        {
            throw new NotImplementedException();
        }

        private GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, int? timeOfFailure)
        {
            throw new NotImplementedException();
        }

        private class GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties {} // TODO: Remove
    }
}