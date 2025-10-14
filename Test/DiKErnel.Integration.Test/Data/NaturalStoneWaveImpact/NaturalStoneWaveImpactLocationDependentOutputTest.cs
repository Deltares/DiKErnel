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

using System;
using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using NSubstitute;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Integration.Test.Data.NaturalStoneWaveImpact
{
    [TestFixture]
    internal sealed class NaturalStoneWaveImpactLocationDependentOutputTest
    {
        [Test]
        public void Constructor_ExpectedValues()
        {
            // Setup
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            ITimeDependentInput[] timeDependentInputItems = Array.Empty<ITimeDependentInput>();
            double z = Random.NextDouble();
            double resistance = Random.NextDouble();
            TimeDependentOutput[] timeDependentOutputItems = Array.Empty<TimeDependentOutput>();

            // Call
            var output = new NaturalStoneWaveImpactLocationDependentOutput(initialDamage, failureNumber, timeDependentInputItems,
                                                                           timeDependentOutputItems, z, resistance);

            // Assert
            Assert.That(output, Is.InstanceOf<LocationDependentOutput>());
            Assert.That(output.TimeDependentOutputItems, Is.SameAs(timeDependentOutputItems));
            Assert.That(output.Z, Is.EqualTo(z));
            Assert.That(output.Resistance, Is.EqualTo(resistance));
        }

        [Test]
        public void GivenNaturalStoneWaveImpactLocationDependentOutput_WhenGetTimeOfFailure_ThenExpectedValue()
        {
            // Given
            const double initialDamage = 0.2;
            const double incrementDamage1 = 0.3;
            const double incrementDamage2 = 0.5;
            const double failureNumber = 0.6;

            LocationDependentOutput locationDependentOutput = CreateLocationDependentOutput(initialDamage, failureNumber, incrementDamage1,
                                                                                            incrementDamage2);

            List<ITimeDependentInput> timeDependentInputItems = CreateTimeDependentInputItems();

            // When
            double? timeOfFailure = locationDependentOutput.GetTimeOfFailure(initialDamage, failureNumber, timeDependentInputItems);

            // Then
            Assert.That(timeOfFailure, Is.EqualTo(280).Within(1.0e-1));
        }

        private static NaturalStoneWaveImpactLocationDependentOutput CreateLocationDependentOutput(
            double initialDamage, double failureNumber, double incrementDamage1, double incrementDamage2)
        {
            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties timeDependentOutputConstructionProperties1 =
                CreateTimeDependentOutputConstructionProperties(incrementDamage1, Random.NextDouble(), Random.NextDouble(),
                                                                Random.NextDouble());

            NaturalStoneWaveImpactTimeDependentOutputConstructionProperties timeDependentOutputConstructionProperties2 =
                CreateTimeDependentOutputConstructionProperties(incrementDamage2, 0.7, 0.8, 1.5);

            var timeDependentOutputItems = new List<TimeDependentOutput>
            {
                new NaturalStoneWaveImpactTimeDependentOutput(timeDependentOutputConstructionProperties1),
                new NaturalStoneWaveImpactTimeDependentOutput(timeDependentOutputConstructionProperties2)
            };

            return new NaturalStoneWaveImpactLocationDependentOutput(initialDamage, failureNumber, timeDependentOutputItems,
                                                                     Random.NextDouble(), 0.59);
        }

        private static NaturalStoneWaveImpactTimeDependentOutputConstructionProperties CreateTimeDependentOutputConstructionProperties(
            double incrementDamage, double hydraulicLoad, double waveAngleImpact, double referenceTimeDegradation)
        {
            return new NaturalStoneWaveImpactTimeDependentOutputConstructionProperties
            {
                OuterSlope = Random.NextDouble(),
                SlopeUpperLevel = Random.NextDouble(),
                SlopeUpperPosition = Random.NextDouble(),
                SlopeLowerLevel = Random.NextDouble(),
                SlopeLowerPosition = Random.NextDouble(),
                LoadingRevetment = true,
                SurfSimilarityParameter = Random.NextDouble(),
                WaveSteepnessDeepWater = Random.NextDouble(),
                UpperLimitLoading = Random.NextDouble(),
                LowerLimitLoading = Random.NextDouble(),
                DepthMaximumWaveLoad = Random.NextDouble(),
                DistanceMaximumWaveElevation = Random.NextDouble(),
                NormativeWidthOfWaveImpact = Random.NextDouble(),
                IncrementDamage = incrementDamage,
                HydraulicLoad = hydraulicLoad,
                WaveAngleImpact = waveAngleImpact,
                ReferenceTimeDegradation = referenceTimeDegradation
            };
        }

        private static List<ITimeDependentInput> CreateTimeDependentInputItems()
        {
            var timeDependentInput1 = Substitute.For<ITimeDependentInput>();
            timeDependentInput1.BeginTime.Returns(0);
            timeDependentInput1.EndTime.Returns(200);

            var timeDependentInput2 = Substitute.For<ITimeDependentInput>();
            timeDependentInput2.BeginTime.Returns(200);
            timeDependentInput2.EndTime.Returns(600);
            timeDependentInput2.WavePeriodTm10.Returns(8);

            return new List<ITimeDependentInput>
            {
                timeDependentInput1,
                timeDependentInput2
            };
        }
    }
}