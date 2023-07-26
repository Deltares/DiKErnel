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

namespace DiKErnel.Integration.Data.GrassRevetmentWaveImpact
{
    internal class GrassRevetmentWaveImpactLocationDependentInput : LocationDependentInput
    {
        private double minimumWaveHeight = double.PositiveInfinity;
        private double maximumWaveHeight = double.PositiveInfinity;
        private double lowerLimitLoading = double.PositiveInfinity;
        private double upperLimitLoading = double.PositiveInfinity;
        private bool loadingRevetment = false;
        private double waveAngleImpact = double.PositiveInfinity;
        private double waveHeightImpact = double.PositiveInfinity;

        public GrassRevetmentWaveImpactLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                              GrassRevetmentWaveImpactWaveAngleImpact waveAngleImpact,
                                                              double minimumWaveHeightTemax,
                                                              double maximumWaveHeightTemin,
                                                              GrassRevetmentWaveImpactTimeLine timeLine,
                                                              double upperLimitLoadingAul,
                                                              double lowerLimitLoadingAll)
            : base(x, initialDamage, failureNumber)
        {
            WaveAngleImpact = waveAngleImpact;
            MinimumWaveHeightTemax = minimumWaveHeightTemax;
            MaximumWaveHeightTemin = maximumWaveHeightTemin;
            TimeLine = timeLine;
            UpperLimitLoadingAul = upperLimitLoadingAul;
            LowerLimitLoadingAll = lowerLimitLoadingAll;
        }

        public GrassRevetmentWaveImpactWaveAngleImpact WaveAngleImpact { get; }

        public double MinimumWaveHeightTemax { get; }

        public double MaximumWaveHeightTemin { get; }

        public GrassRevetmentWaveImpactTimeLine TimeLine { get; }

        public double UpperLimitLoadingAul { get; }

        public double LowerLimitLoadingAll { get; }

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

        private bool CalculateLoadingRevetment(double waterLevel, double waveHeightHm0)
        {
            throw new NotImplementedException();
        }

        private GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, int? timeOfFailure)
        {
            throw new NotImplementedException();
        }

        private class GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties {}
    }
}