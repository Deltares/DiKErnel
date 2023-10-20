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
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneRevetment;
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
            Assert.IsFalse(result.Successful);

            Assert.AreEqual(1, result.Events.Count);
            Assert.AreEqual(EventType.Error, result.Events[0].Type);
            Assert.AreEqual("An unhandled error occurred while composing Json output from the calculation data. See " +
                            $"stack trace for more information:{Environment.NewLine}Invalid revetment type.",
                            result.Events[0].Message);
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
                        TimeOfFailure = 60
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

            Assert.IsTrue(result.Successful);
            CollectionAssert.IsEmpty(result.Events);
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

            Assert.IsTrue(result.Successful);
            CollectionAssert.IsEmpty(result.Events);
        }

        private static CalculationOutput CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet()
        {
            var asphaltWaveImpactTimeDependentOutput = new AsphaltRevetmentWaveImpactTimeDependentOutput(
                new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.1,
                    Damage = 0.2,
                    TimeOfFailure = 3,
                    MaximumPeakStress = 0.4,
                    AverageNumberOfWaves = 0.5
                });

            var grassOvertoppingTimeDependentOutput = new GrassRevetmentOvertoppingTimeDependentOutput(
                new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.6,
                    Damage = 0.7,
                    TimeOfFailure = 8,
                    VerticalDistanceWaterLevelElevation = 0.9,
                    RepresentativeWaveRunup2P = 1.0,
                    CumulativeOverload = 1.1,
                    AverageNumberOfWaves = 1.2
                });

            var grassWaveImpactTimeDependentOutput = new GrassRevetmentWaveImpactTimeDependentOutput(
                new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.3,
                    Damage = 1.4,
                    TimeOfFailure = 15,
                    LoadingRevetment = true,
                    UpperLimitLoading = 1.6,
                    LowerLimitLoading = 1.7,
                    WaveAngle = 1.8,
                    WaveAngleImpact = 1.9,
                    WaveHeightImpact = 2.0
                });

            var grassWaveRunupRayleighTimeDependentOutput = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 2.1,
                    Damage = 2.2,
                    TimeOfFailure = 23,
                    VerticalDistanceWaterLevelElevation = 2.4,
                    WaveAngle = 2.5,
                    WaveAngleImpact = 2.6,
                    RepresentativeWaveRunup2P = 2.7,
                    CumulativeOverload = 2.8,
                    AverageNumberOfWaves = 2.9
                });

            var naturalStoneTimeDependentOutput = new NaturalStoneRevetmentTimeDependentOutput(
                new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 3.0,
                    Damage = 3.1,
                    TimeOfFailure = 32,
                    OuterSlope = 3.3,
                    SlopeUpperLevel = 3.4,
                    SlopeUpperPosition = 3.5,
                    SlopeLowerLevel = 3.6,
                    SlopeLowerPosition = 3.7,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 3.8,
                    WaveSteepnessDeepWater = 3.9,
                    UpperLimitLoading = 4.0,
                    LowerLimitLoading = 4.1,
                    DepthMaximumWaveLoad = 4.2,
                    DistanceMaximumWaveElevation = 4.3,
                    NormativeWidthOfWaveImpact = 4.4,
                    HydraulicLoad = 4.5,
                    WaveAngle = 4.6,
                    WaveAngleImpact = 4.7,
                    ReferenceTimeDegradation = 4.8,
                    ReferenceDegradation = 4.9
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 5.0, 5.1, 5.2, 5.3, 5.4, 5.5),
                new GrassRevetmentOvertoppingLocationDependentOutput(new[]
                {
                    grassOvertoppingTimeDependentOutput
                }),
                new GrassRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 5.6, 5.7, 5.8),
                new GrassRevetmentWaveRunupRayleighLocationDependentOutput(new[]
                {
                    grassWaveRunupRayleighTimeDependentOutput
                }, 5.9),
                new NaturalStoneRevetmentLocationDependentOutput(new[]
                {
                    naturalStoneTimeDependentOutput
                }, 6.0, 6.1)
            });
        }

        private static CalculationOutput CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet()
        {
            var asphaltWaveImpactTimeDependentOutput = new AsphaltRevetmentWaveImpactTimeDependentOutput(
                new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.1,
                    Damage = 0.2,
                    MaximumPeakStress = 0.3,
                    AverageNumberOfWaves = 0.4
                });

            var grassOvertoppingTimeDependentOutput = new GrassRevetmentOvertoppingTimeDependentOutput(
                new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.5,
                    Damage = 0.6,
                    VerticalDistanceWaterLevelElevation = 0.7
                });

            var grassWaveImpactTimeDependentOutput = new GrassRevetmentWaveImpactTimeDependentOutput(
                new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.8,
                    Damage = 0.9,
                    LoadingRevetment = true,
                    UpperLimitLoading = 1.0,
                    LowerLimitLoading = 1.1
                });

            var grassWaveRunupRayleighTimeDependentOutput = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.2,
                    Damage = 1.3,
                    VerticalDistanceWaterLevelElevation = 1.4
                });

            var naturalStoneTimeDependentOutput = new NaturalStoneRevetmentTimeDependentOutput(
                new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.5,
                    Damage = 1.6,
                    OuterSlope = 1.7,
                    SlopeUpperLevel = 1.8,
                    SlopeUpperPosition = 1.9,
                    SlopeLowerLevel = 2.0,
                    SlopeLowerPosition = 2.1,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 2.2,
                    WaveSteepnessDeepWater = 2.3,
                    UpperLimitLoading = 2.4,
                    LowerLimitLoading = 2.5,
                    DepthMaximumWaveLoad = 2.6,
                    DistanceMaximumWaveElevation = 2.7,
                    NormativeWidthOfWaveImpact = 2.8
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4),
                new GrassRevetmentOvertoppingLocationDependentOutput(new[]
                {
                    grassOvertoppingTimeDependentOutput
                }),
                new GrassRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 3.5, 3.6, 3.7),
                new GrassRevetmentWaveRunupRayleighLocationDependentOutput(new[]
                {
                    grassWaveRunupRayleighTimeDependentOutput
                }, 3.8),
                new NaturalStoneRevetmentLocationDependentOutput(new[]
                {
                    naturalStoneTimeDependentOutput
                }, 3.9, 4.0)
            });
        }
    }
}