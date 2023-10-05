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
using FileAssert = DiKErnel.TestUtil.FileAssert;

namespace DiKErnel.KernelWrapper.Json.Output.Test
{
    [TestFixture]
    public class JsonOutputComposerTest
    {
        private static readonly string actualOutputFilePath = Path.Combine(Path.GetTempPath(), "actualOutput.json");

        [OneTimeTearDown]
        public void TearDown()
        {
            File.Delete(actualOutputFilePath);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypeFailureWithoutMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedFailureOutputWithoutMetaData.json", JsonOutputType.Failure, false);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypeFailureWithMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedFailureOutputWithMetaData.json", JsonOutputType.Failure, true);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypeDamageWithoutMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedDamageOutputWithoutMetaData.json", JsonOutputType.Damage, false);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypeDamageWithMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedDamageOutputWithMetaData.json", JsonOutputType.Damage, true);
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
                            "stack trace for more information:\nInvalid revetment type.", result.Events[0].Message);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithAllDataAndMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest(
                "ExpectedPhysicsOutputWithAllDataAndMetaData.json",
                CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet(), true);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithAllDataAndWithoutMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest(
                "ExpectedPhysicsOutputWithAllDataAndWithoutMetaData.json",
                CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet(), false);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithOnlyMandatoryDataAndMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest(
                "ExpectedPhysicsOutputWithOnlyMandatoryDataAndMetaData.json",
                CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet(), true);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithOnlyMandatoryDataAndWithoutMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest(
                "ExpectedPhysicsOutputWithOnlyMandatoryDataAndWithoutMetaData.json",
                CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet(), false);
        }

        private static void PerformTest(string filename, JsonOutputType outputType, bool withMetaData)
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
                actualOutputFilePath, calculationOutput, outputType, metaDataItems: metaDataItems);

            // Assert
            string expectedOutputFilePath =
                Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Output.Test"),
                             "JsonOutputComposerTest", filename);

            FileAssert.AssertFileContents(expectedOutputFilePath, actualOutputFilePath);

            Assert.IsTrue(result.Successful);
            CollectionAssert.IsEmpty(result.Events);
        }

        private static void PerformPhysicsTest(string filename, CalculationOutput calculationOutput, bool withMetaData)
        {
            // Setup
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
                actualOutputFilePath, calculationOutput, JsonOutputType.Physics, metaDataItems: metaDataItems);

            // Assert
            string expectedOutputFilePath =
                Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Output.Test"),
                             "JsonOutputComposerTest", filename);

            FileAssert.AssertFileContents(expectedOutputFilePath, actualOutputFilePath);

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
                    LogFailureTension = 0.4,
                    MaximumPeakStress = 0.5,
                    StiffnessRelation = 0.6,
                    ComputationalThickness = 0.7,
                    EquivalentElasticModulus = 0.8
                });

            var grassOvertoppingTimeDependentOutput = new GrassRevetmentOvertoppingTimeDependentOutput(
                new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.9,
                    Damage = 1.0,
                    TimeOfFailure = 11,
                    VerticalDistanceWaterLevelElevation = 1.2,
                    RepresentativeWaveRunup2P = 1.3,
                    CumulativeOverload = 1.4,
                    AverageNumberOfWaves = 1.5
                });

            var grassWaveImpactTimeDependentOutput = new GrassRevetmentWaveImpactTimeDependentOutput(
                new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.5,
                    Damage = 1.6,
                    TimeOfFailure = 17,
                    LoadingRevetment = true,
                    UpperLimitLoading = 1.8,
                    LowerLimitLoading = 1.9,
                    MinimumWaveHeight = 2.0,
                    MaximumWaveHeight = 2.1,
                    WaveAngleImpact = 2.2,
                    WaveHeightImpact = 2.3
                });

            var grassWaveRunupRayleighTimeDependentOutput = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 2.4,
                    Damage = 2.5,
                    TimeOfFailure = 26,
                    VerticalDistanceWaterLevelElevation = 2.7,
                    WaveAngleImpact = 2.8,
                    RepresentativeWaveRunup2P = 2.9,
                    CumulativeOverload = 3.0,
                    AverageNumberOfWaves = 3.1
                });

            var naturalStoneTimeDependentOutput = new NaturalStoneRevetmentTimeDependentOutput(
                new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 3.2,
                    Damage = 3.3,
                    TimeOfFailure = 34,
                    OuterSlope = 3.5,
                    SlopeUpperLevel = 3.6,
                    SlopeUpperPosition = 3.7,
                    SlopeLowerLevel = 3.8,
                    SlopeLowerPosition = 3.9,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 4.0,
                    WaveSteepnessDeepWater = 4.1,
                    UpperLimitLoading = 4.2,
                    LowerLimitLoading = 4.3,
                    DepthMaximumWaveLoad = 4.4,
                    DistanceMaximumWaveElevation = 4.5,
                    NormativeWidthOfWaveImpact = 4.6,
                    HydraulicLoad = 4.7,
                    WaveAngleImpact = 4.8,
                    Resistance = 4.9,
                    ReferenceTimeDegradation = 5.0,
                    ReferenceDegradation = 5.1
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 5.2, 5.3),
                new GrassRevetmentOvertoppingLocationDependentOutput(new[]
                {
                    grassOvertoppingTimeDependentOutput
                }),
                new GrassRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 5.4),
                new GrassRevetmentWaveRunupRayleighLocationDependentOutput(new[]
                {
                    grassWaveRunupRayleighTimeDependentOutput
                }, 5.5),
                new NaturalStoneRevetmentLocationDependentOutput(new[]
                {
                    naturalStoneTimeDependentOutput
                }, 5.6)
            });
        }

        private static CalculationOutput CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet()
        {
            var asphaltWaveImpactTimeDependentOutput = new AsphaltRevetmentWaveImpactTimeDependentOutput(
                new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.1,
                    Damage = 0.2,
                    LogFailureTension = 0.3,
                    MaximumPeakStress = 0.4,
                    StiffnessRelation = 0.5,
                    ComputationalThickness = 0.6,
                    EquivalentElasticModulus = 0.7
                });

            var grassOvertoppingTimeDependentOutput = new GrassRevetmentOvertoppingTimeDependentOutput(
                new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.8,
                    Damage = 0.9,
                    VerticalDistanceWaterLevelElevation = 1.0
                });

            var grassWaveImpactTimeDependentOutput = new GrassRevetmentWaveImpactTimeDependentOutput(
                new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.1,
                    Damage = 1.2,
                    LoadingRevetment = true,
                    UpperLimitLoading = 1.3,
                    LowerLimitLoading = 1.4
                });

            var grassWaveRunupRayleighTimeDependentOutput = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.5,
                    Damage = 1.6,
                    VerticalDistanceWaterLevelElevation = 1.7
                });

            var naturalStoneTimeDependentOutput = new NaturalStoneRevetmentTimeDependentOutput(
                new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.8,
                    Damage = 1.9,
                    OuterSlope = 2.0,
                    SlopeUpperLevel = 2.1,
                    SlopeUpperPosition = 2.2,
                    SlopeLowerLevel = 2.3,
                    SlopeLowerPosition = 2.4,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 2.5,
                    WaveSteepnessDeepWater = 2.6,
                    UpperLimitLoading = 2.7,
                    LowerLimitLoading = 2.8,
                    DepthMaximumWaveLoad = 2.9,
                    DistanceMaximumWaveElevation = 3.0,
                    NormativeWidthOfWaveImpact = 3.1
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 3.2, 3.3),
                new GrassRevetmentOvertoppingLocationDependentOutput(new[]
                {
                    grassOvertoppingTimeDependentOutput
                }),
                new GrassRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 3.4),
                new GrassRevetmentWaveRunupRayleighLocationDependentOutput(new[]
                {
                    grassWaveRunupRayleighTimeDependentOutput
                }, 3.5),
                new NaturalStoneRevetmentLocationDependentOutput(new[]
                {
                    naturalStoneTimeDependentOutput
                }, 3.6)
            });
        }
    }
}