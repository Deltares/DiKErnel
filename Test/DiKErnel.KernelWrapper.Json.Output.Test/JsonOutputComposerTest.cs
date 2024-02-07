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
using System.IO;
using DiKErnel.Core.Data;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.TestUtil;
using DiKErnel.Util;
using NSubstitute;
using NUnit.Framework;

namespace DiKErnel.KernelWrapper.Json.Output.Test
{
    [TestFixture]
    public class JsonOutputComposerTest
    {
        private static readonly string actualOutputFilePath = Path.Combine(Path.GetTempPath(), "actualOutput.json");

        [TearDown]
        public void TearDown()
        {
            File.Delete(actualOutputFilePath);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypeFailure_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedFailureOutput.json", JsonOutputType.Failure);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypeDamage_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedDamageOutput.json", JsonOutputType.Damage);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsAndTimeDependentOutputNotSupported_ReturnsResultWithSuccessfulFalseAndWithExpectedEvent()
        {
            // Setup
            var calculationOutput = new CalculationOutput(new List<LocationDependentOutput>
            {
                Substitute.For<LocationDependentOutput>(new List<TimeDependentOutput>
                {
                    Substitute.For<TimeDependentOutput>(new TimeDependentOutputConstructionProperties
                    {
                        IncrementDamage = 0,
                        Damage = 0.15,
                        TimeOfFailure = null
                    })
                })
            });

            // Call
            SimpleResult result = JsonOutputComposer.WriteCalculationOutputToJson(
                "", calculationOutput, JsonOutputType.Physics);

            // Assert
            Assert.That(result.Successful, Is.False);

            Assert.That(result.Events, Has.Count.EqualTo(1));
            Assert.That(result.Events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(result.Events[0].Message, Is.EqualTo("An unhandled error occurred while composing Json output " +
                                                             "from the calculation data. See stack trace for more " +
                                                             $"information:{Environment.NewLine}Invalid revetment type."));
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithAllDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest(
                "ExpectedPhysicsOutputWithAllData.json",
                CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet());
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithOnlyMandatoryDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest(
                "ExpectedPhysicsOutputWithOnlyMandatoryData.json",
                CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet());
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypeFailureWithLocationIds_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedFailureOutputWithLocationIds.json", JsonOutputType.Failure, withLocationIds: true);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypeFailureWithMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedFailureOutputWithMetaData.json", JsonOutputType.Failure, withMetaData: true);
        }

        private static void PerformTest(string filename, JsonOutputType outputType, bool withLocationIds = false, bool withMetaData = false)
        {
            // Setup
            var calculationOutput = new CalculationOutput(new List<LocationDependentOutput>
            {
                Substitute.For<LocationDependentOutput>(new List<TimeDependentOutput>
                {
                    Substitute.For<TimeDependentOutput>(new TimeDependentOutputConstructionProperties
                    {
                        IncrementDamage = 0,
                        Damage = 0.15,
                        TimeOfFailure = null
                    }),
                    Substitute.For<TimeDependentOutput>(new TimeDependentOutputConstructionProperties
                    {
                        IncrementDamage = 0,
                        Damage = 0.253,
                        TimeOfFailure = 60.1
                    })
                }),
                Substitute.For<LocationDependentOutput>(new List<TimeDependentOutput>
                {
                    Substitute.For<TimeDependentOutput>(new TimeDependentOutputConstructionProperties
                    {
                        IncrementDamage = 0,
                        Damage = 0.28,
                        TimeOfFailure = null
                    }),
                    Substitute.For<TimeDependentOutput>(new TimeDependentOutputConstructionProperties
                    {
                        IncrementDamage = 0,
                        Damage = 0.512,
                        TimeOfFailure = null
                    })
                })
            });

            IReadOnlyList<int?> locationIds = null;

            if (withLocationIds)
            {
                locationIds = new int?[]
                {
                    2,
                    6
                };
            }

            Dictionary<string, object> metaDataItems = null;

            if (withMetaData)
            {
                metaDataItems = new Dictionary<string, object>
                {
                    {
                        "Test 1", 1.23
                    },
                    {
                        "Test 2", "4.56"
                    }
                };
            }

            // Call
            SimpleResult result = JsonOutputComposer.WriteCalculationOutputToJson(
                actualOutputFilePath, calculationOutput, outputType, locationIds, metaDataItems);

            // Assert
            string expectedOutputFilePath =
                Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Output.Test"),
                             "JsonOutputComposerTest", filename);

            AssertHelper.AssertFileContents(expectedOutputFilePath, actualOutputFilePath);

            Assert.That(result.Successful, Is.True);
            Assert.That(result.Events, Is.Empty);
        }

        private static void PerformPhysicsTest(string filename, CalculationOutput calculationOutput)
        {
            // Call
            SimpleResult result = JsonOutputComposer.WriteCalculationOutputToJson(
                actualOutputFilePath, calculationOutput, JsonOutputType.Physics);

            // Assert
            string expectedOutputFilePath =
                Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Output.Test"),
                             "JsonOutputComposerTest", filename);

            AssertHelper.AssertFileContents(expectedOutputFilePath, actualOutputFilePath);

            Assert.That(result.Successful, Is.True);
            Assert.That(result.Events, Is.Empty);
        }

        private static CalculationOutput CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet()
        {
            var asphaltWaveImpactTimeDependentOutput = new AsphaltWaveImpactTimeDependentOutput(
                new AsphaltWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.1,
                    Damage = 0.2,
                    TimeOfFailure = 0.3,
                    MaximumPeakStress = 0.4,
                    AverageNumberOfWaves = 0.5
                });

            var grassCumulativeOverloadTimeDependentOutput =
                new GrassCumulativeOverloadTimeDependentOutput(
                    new GrassCumulativeOverloadTimeDependentOutputConstructionProperties
                    {
                        IncrementDamage = 0.6,
                        Damage = 0.7,
                        TimeOfFailure = 0.8,
                        VerticalDistanceWaterLevelElevation = 0.9,
                        RepresentativeWaveRunup2P = 1,
                        CumulativeOverload = 1.1,
                        AverageNumberOfWaves = 1.2
                    });

            var grassWaveImpactTimeDependentOutput = new GrassWaveImpactTimeDependentOutput(
                new GrassWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.3,
                    Damage = 1.4,
                    TimeOfFailure = 1.5,
                    LoadingRevetment = true,
                    UpperLimitLoading = 1.6,
                    LowerLimitLoading = 1.7,
                    WaveAngle = 1.8,
                    WaveAngleImpact = 1.9,
                    WaveHeightImpact = 2
                });

            var naturalStoneWaveImpactTimeDependentOutput = new NaturalStoneWaveImpactTimeDependentOutput(
                new NaturalStoneWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 2.1,
                    Damage = 2.2,
                    TimeOfFailure = 2.3,
                    OuterSlope = 2.4,
                    SlopeUpperLevel = 2.5,
                    SlopeUpperPosition = 2.6,
                    SlopeLowerLevel = 2.7,
                    SlopeLowerPosition = 2.8,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 2.9,
                    WaveSteepnessDeepWater = 3,
                    UpperLimitLoading = 3.1,
                    LowerLimitLoading = 3.2,
                    DepthMaximumWaveLoad = 3.3,
                    DistanceMaximumWaveElevation = 3.4,
                    NormativeWidthOfWaveImpact = 3.5,
                    HydraulicLoad = 3.6,
                    WaveAngle = 3.7,
                    WaveAngleImpact = 3.8,
                    ReferenceTimeDegradation = 3.9,
                    ReferenceDegradation = 4
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6),
                new GrassCumulativeOverloadLocationDependentOutput(new[]
                {
                    grassCumulativeOverloadTimeDependentOutput
                }, 4.7),
                new GrassWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 4.8, 4.9, 5),
                new NaturalStoneWaveImpactLocationDependentOutput(new[]
                {
                    naturalStoneWaveImpactTimeDependentOutput
                }, 5.1, 5.2)
            });
        }

        private static CalculationOutput CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet()
        {
            var asphaltWaveImpactTimeDependentOutput = new AsphaltWaveImpactTimeDependentOutput(
                new AsphaltWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.1,
                    Damage = 0.2,
                    MaximumPeakStress = 0.3,
                    AverageNumberOfWaves = 0.4
                });

            var grassCumulativeOverloadTimeDependentOutput =
                new GrassCumulativeOverloadTimeDependentOutput(
                    new GrassCumulativeOverloadTimeDependentOutputConstructionProperties
                    {
                        IncrementDamage = 0.5,
                        Damage = 0.6,
                        VerticalDistanceWaterLevelElevation = 0.7
                    });

            var grassWaveImpactTimeDependentOutput = new GrassWaveImpactTimeDependentOutput(
                new GrassWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.8,
                    Damage = 0.9,
                    LoadingRevetment = true,
                    UpperLimitLoading = 1,
                    LowerLimitLoading = 1.1
                });

            var naturalStoneWaveImpactTimeDependentOutput = new NaturalStoneWaveImpactTimeDependentOutput(
                new NaturalStoneWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.2,
                    Damage = 1.3,
                    OuterSlope = 1.4,
                    SlopeUpperLevel = 1.5,
                    SlopeUpperPosition = 1.6,
                    SlopeLowerLevel = 1.7,
                    SlopeLowerPosition = 1.8,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 1.9,
                    WaveSteepnessDeepWater = 2,
                    UpperLimitLoading = 2.1,
                    LowerLimitLoading = 2.2,
                    DepthMaximumWaveLoad = 2.3,
                    DistanceMaximumWaveElevation = 2.4,
                    NormativeWidthOfWaveImpact = 2.5
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 2.6, 2.7, 2.8, 2.9, 3, 3.1),
                new GrassCumulativeOverloadLocationDependentOutput(new[]
                {
                    grassCumulativeOverloadTimeDependentOutput
                }, 3.2),
                new GrassWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 3.3, 3.4, 3.5),
                new NaturalStoneWaveImpactLocationDependentOutput(new[]
                {
                    naturalStoneWaveImpactTimeDependentOutput
                }, 3.6, 3.7)
            });
        }
    }
}