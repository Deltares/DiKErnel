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
using DiKErnel.FunctionLibrary.GrassRevetmentWaveImpact;
using DiKErnel.Integration.Helpers;
using DiKErnel.Util.Validation;

namespace DiKErnel.Integration.Data.GrassWaveImpact
{
    internal class GrassWaveImpactLocationDependentInput : LocationDependentInput
    {
        private double minimumWaveHeight = double.NaN;
        private double maximumWaveHeight = double.NaN;
        private double lowerLimitLoading = double.NaN;
        private double upperLimitLoading = double.NaN;
        private bool loadingRevetment;
        private double waveAngle = double.NaN;
        private double waveAngleImpact = double.NaN;
        private double waveHeightImpact = double.NaN;

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
                GrassRevetmentWaveImpactValidator.TimeLineAgwi(TimeLine.TimeLineAgwi, TimeLine.TimeLineCgwi),
                GrassRevetmentWaveImpactValidator.TimeLineBgwi(TimeLine.TimeLineBgwi),
                GrassRevetmentWaveImpactValidator.TimeLineCgwi(TimeLine.TimeLineCgwi),
                GrassRevetmentWaveImpactValidator.MinimumWaveHeightTemax(MinimumWaveHeightTemax),
                GrassRevetmentWaveImpactValidator.MaximumWaveHeightTemin(MaximumWaveHeightTemin),
                GrassRevetmentWaveImpactValidator.WaveAngleImpactNwa(WaveAngleImpact.WaveAngleImpactNwa),
                GrassRevetmentWaveImpactValidator.WaveAngleImpactQwa(WaveAngleImpact.WaveAngleImpactQwa),
                GrassRevetmentWaveImpactValidator.WaveAngleImpactRwa(WaveAngleImpact.WaveAngleImpactRwa),
                GrassRevetmentWaveImpactValidator.UpperLimitLoadingAul(UpperLimitLoadingAul, LowerLimitLoadingAll)
            };

            return ValidationHelper.RegisterValidationIssues(validationIssues) && baseValidationSuccessful;
        }

        public override LocationDependentOutput GetLocationDependentOutput(
            IReadOnlyList<TimeDependentOutput> timeDependentOutputItems)
        {
            return new GrassWaveImpactLocationDependentOutput(timeDependentOutputItems, Z, minimumWaveHeight,
                                                              maximumWaveHeight);
        }

        protected override void InitializeDerivedLocationDependentInput(IProfileData profileData)
        {
            base.InitializeDerivedLocationDependentInput(profileData);

            double timeLineAgwi = TimeLine.TimeLineAgwi;
            double timeLineBgwi = TimeLine.TimeLineBgwi;
            double timeLineCgwi = TimeLine.TimeLineCgwi;

            minimumWaveHeight = GrassRevetmentWaveImpactFunctions.MinimumWaveHeight(timeLineAgwi, timeLineBgwi,
                                                                                    timeLineCgwi,
                                                                                    MinimumWaveHeightTemax);
            maximumWaveHeight = GrassRevetmentWaveImpactFunctions.MaximumWaveHeight(timeLineAgwi, timeLineBgwi,
                                                                                    timeLineCgwi,
                                                                                    MaximumWaveHeightTemin);
        }

        protected override TimeDependentOutput CalculateTimeDependentOutput(double initialDamage,
                                                                            ITimeDependentInput timeDependentInput,
                                                                            IProfileData profileData)
        {
            loadingRevetment = CalculateLoadingRevetment(timeDependentInput.WaterLevel,
                                                         timeDependentInput.WaveHeightHm0);

            var incrementDamage = 0.0;
            double damage = initialDamage;
            double? timeOfFailure = null;

            if (loadingRevetment)
            {
                double incrementTime = RevetmentFunctions.IncrementTime(timeDependentInput.BeginTime,
                                                                        timeDependentInput.EndTime);

                waveAngle = HydraulicLoadFunctions.WaveAngle(timeDependentInput.WaveDirection, profileData.DikeOrientation);

                waveAngleImpact = GrassRevetmentWaveImpactFunctions.WaveAngleImpact(waveAngle,
                                                                                    WaveAngleImpact.WaveAngleImpactNwa,
                                                                                    WaveAngleImpact.WaveAngleImpactQwa,
                                                                                    WaveAngleImpact.WaveAngleImpactRwa);

                waveHeightImpact = GrassRevetmentWaveImpactFunctions.WaveHeightImpact(minimumWaveHeight,
                                                                                      maximumWaveHeight,
                                                                                      waveAngleImpact,
                                                                                      timeDependentInput.WaveHeightHm0);

                double timeLine = GrassRevetmentWaveImpactFunctions.TimeLine(waveHeightImpact, TimeLine.TimeLineAgwi,
                                                                             TimeLine.TimeLineBgwi,
                                                                             TimeLine.TimeLineCgwi);

                incrementDamage = GrassRevetmentWaveImpactFunctions.IncrementDamage(incrementTime, timeLine);

                damage = RevetmentFunctions.Damage(incrementDamage, initialDamage);

                if (RevetmentFunctions.FailureRevetment(damage, initialDamage, FailureNumber))
                {
                    double durationInTimeStepFailure = RevetmentFunctions.DurationInTimeStepFailure(
                        incrementTime, incrementDamage, FailureNumber, initialDamage);

                    timeOfFailure = RevetmentFunctions.TimeOfFailure(durationInTimeStepFailure,
                                                                     timeDependentInput.BeginTime);
                }
            }

            return new GrassWaveImpactTimeDependentOutput(
                CreateConstructionProperties(incrementDamage, damage, timeOfFailure));
        }

        private bool CalculateLoadingRevetment(double waterLevel, double waveHeightHm0)
        {
            lowerLimitLoading = GrassRevetmentWaveImpactFunctions.LowerLimitLoading(waterLevel, waveHeightHm0,
                                                                                    LowerLimitLoadingAll);
            upperLimitLoading = GrassRevetmentWaveImpactFunctions.UpperLimitLoading(waterLevel, waveHeightHm0,
                                                                                    UpperLimitLoadingAul);

            return HydraulicLoadFunctions.LoadingRevetment(lowerLimitLoading, upperLimitLoading, Z);
        }

        private GrassWaveImpactTimeDependentOutputConstructionProperties CreateConstructionProperties(
            double incrementDamage, double damage, double? timeOfFailure)
        {
            var constructionProperties = new GrassWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = incrementDamage,
                Damage = damage,
                TimeOfFailure = timeOfFailure,
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