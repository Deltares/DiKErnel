// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.DomainLibrary.Validators.GrassWaveImpact;
using DiKErnel.FunctionLibrary;
using DiKErnel.FunctionLibrary.GrassWaveImpact;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassWaveImpact
{
    internal class GrassWaveImpactLocationDependentInput : LocationDependentInput
    {
        private double minimumWaveHeight = double.NaN;
        private double maximumWaveHeight = double.NaN;

        public GrassWaveImpactLocationDependentInput(double x, double initialDamage, double failureNumber,
                                                     GrassWaveImpactWaveAngleImpact waveAngleImpact,
                                                     double minimumWaveHeightTemax, double maximumWaveHeightTemin,
                                                     GrassWaveImpactTimeLine timeLine, double upperLimitLoadingAul,
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

        public GrassWaveImpactWaveAngleImpact WaveAngleImpact { get; }

        public double MinimumWaveHeightTemax { get; }

        public double MaximumWaveHeightTemin { get; }

        public GrassWaveImpactTimeLine TimeLine { get; }

        public double UpperLimitLoadingAul { get; }

        public double LowerLimitLoadingAll { get; }

        public override bool Validate(IReadOnlyList<ITimeDependentInput> timeDependentInputItems,
                                      IProfileData profileData)
        {
            bool baseValidationSuccessful = base.Validate(timeDependentInputItems, profileData);

            var validationIssues = new List<ValidationIssue>
            {
                GrassWaveImpactValidator.TimeLineAgwi(TimeLine.TimeLineAgwi, TimeLine.TimeLineCgwi),
                GrassWaveImpactValidator.TimeLineBgwi(TimeLine.TimeLineBgwi),
                GrassWaveImpactValidator.TimeLineCgwi(TimeLine.TimeLineCgwi),
                GrassWaveImpactValidator.MinimumWaveHeightTemax(MinimumWaveHeightTemax),
                GrassWaveImpactValidator.MaximumWaveHeightTemin(MaximumWaveHeightTemin),
                GrassWaveImpactValidator.WaveAngleImpactNwa(WaveAngleImpact.WaveAngleImpactNwa),
                GrassWaveImpactValidator.WaveAngleImpactQwa(WaveAngleImpact.WaveAngleImpactQwa),
                GrassWaveImpactValidator.WaveAngleImpactRwa(WaveAngleImpact.WaveAngleImpactRwa),
                GrassWaveImpactValidator.UpperLimitLoadingAul(UpperLimitLoadingAul, LowerLimitLoadingAll)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            double timeLineAgwi = TimeLine.TimeLineAgwi;
            double timeLineBgwi = TimeLine.TimeLineBgwi;
            double timeLineCgwi = TimeLine.TimeLineCgwi;

            minimumWaveHeight = GrassWaveImpactFunctions.MinimumWaveHeight(timeLineAgwi, timeLineBgwi, timeLineCgwi,
                                                                           MinimumWaveHeightTemax);
            maximumWaveHeight = GrassWaveImpactFunctions.MaximumWaveHeight(timeLineAgwi, timeLineBgwi, timeLineCgwi,
                                                                           MaximumWaveHeightTemin);
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new GrassWaveImpactLocationDependentOutput(timeDependentOutputItems, Z, minimumWaveHeight,
                                                              maximumWaveHeight);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData,
                                                                            double damageAtStartOfCalculation = double.NaN)
        {
            double lowerLimitLoading = GrassWaveImpactFunctions.LowerLimitLoading(timeDependentInput.WaterLevel,
                                                                                  timeDependentInput.WaveHeightHm0, LowerLimitLoadingAll);

            double upperLimitLoading = GrassWaveImpactFunctions.UpperLimitLoading(timeDependentInput.WaterLevel,
                                                                                  timeDependentInput.WaveHeightHm0, UpperLimitLoadingAul);

            bool loadingRevetment = HydraulicLoadFunctions.LoadingRevetment(lowerLimitLoading, upperLimitLoading, Z);

            var incrementDamage = 0d;

            double waveAngle = double.NaN;
            double waveAngleImpact = double.NaN;
            double waveHeightImpact = double.NaN;

            if (loadingRevetment)
            {
                double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime, timeDependentInput.EndTime);

                waveAngle = HydraulicLoadFunctions.WaveAngle(timeDependentInput.WaveDirection, profileData.DikeOrientation);

                waveAngleImpact = GrassWaveImpactFunctions.WaveAngleImpact(waveAngle, WaveAngleImpact.WaveAngleImpactNwa,
                                                                           WaveAngleImpact.WaveAngleImpactQwa,
                                                                           WaveAngleImpact.WaveAngleImpactRwa);

                waveHeightImpact = GrassWaveImpactFunctions.WaveHeightImpact(minimumWaveHeight, maximumWaveHeight, waveAngleImpact,
                                                                             timeDependentInput.WaveHeightHm0);

                double timeLine = GrassWaveImpactFunctions.TimeLine(waveHeightImpact, TimeLine.TimeLineAgwi, TimeLine.TimeLineBgwi,
                                                                    TimeLine.TimeLineCgwi);

                incrementDamage = GrassWaveImpactFunctions.IncrementDamage(incrementTime, timeLine);
            }

            return new GrassWaveImpactTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, upperLimitLoading, lowerLimitLoading, loadingRevetment, waveAngle,
                                             waveAngleImpact, waveHeightImpact));
        }

        private static GrassWaveImpactTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double upperLimitLoading, double lowerLimitLoading, bool loadingRevetment, double waveAngle,
            double waveAngleImpact, double waveHeightImpact)
        {
            var constructionProperties = new GrassWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                LoadingRevetment = loadingRevetment,
                UpperLimitLoading = upperLimitLoading,
                LowerLimitLoading = lowerLimitLoading
            };

            if (loadingRevetment)
            {
                constructionProperties.WaveAngle = waveAngle;
                constructionProperties.WaveAngleImpact = waveAngleImpact;
                constructionProperties.WaveHeightImpact = waveHeightImpact;
            }

            return constructionProperties;
        }
    }
}