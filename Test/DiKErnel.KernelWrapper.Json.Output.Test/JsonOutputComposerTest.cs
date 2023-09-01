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

        [Test]
        public void WriteCalculationOutputToJson_InvalidJsonOutputType_ReturnsResultWithSuccessfulFalseAndWithExpectedEvent()
        {
            // Setup
            var calculationOutput = new CalculationOutput(new List<LocationDependentOutput>());

            // Call
            SimpleResult result = JsonOutputComposer.WriteCalculationOutputToJson(
                "", calculationOutput, (JsonOutputType) 99);

            // Assert
            Assert.IsFalse(result.Successful);

            Assert.AreEqual(1, result.Events.Count);
            Assert.AreEqual(EventType.Error, result.Events[0].Type);
            Assert.AreEqual("An unhandled error occurred while composing Json output from the calculation data. See " +
                            "stack trace for more information:\n Invalid JsonOutputType.", result.Events[0].Message);
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
            SimpleResult result = JsonOutputComposer.WriteCalculationOutputToJson("", calculationOutput, JsonOutputType.Physics);

            // Assert
            Assert.IsFalse(result.Successful);

            Assert.AreEqual(1, result.Events.Count);
            Assert.AreEqual(EventType.Error, result.Events[0].Type);
            Assert.AreEqual("An unhandled error occurred while composing Json output from the calculation data. See " +
                            "stack trace for more information:\n Invalid revetment type.", result.Events[0].Message);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithAllDataAndMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest("ExpectedPhysicsOutputWithAllDataAndMetaData.json",
                               CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet(), true);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithAllDataAndWithoutMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest("ExpectedPhysicsOutputWithAllDataAndWithoutMetaData.json",
                               CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithAllDataSet(), false);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithOnlyMandatoryDataAndMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest("ExpectedPhysicsOutputWithOnlyMandatoryDataAndMetaData.json",
                               CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet(), true);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypePhysicsWithOnlyMandatoryDataAndWithoutMetaDataAndTimeDependentOutputSupported_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformPhysicsTest("ExpectedPhysicsOutputWithOnlyMandatoryDataAndWithoutMetaData.json",
                               CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet(), false);
        }

        [OneTimeTearDown]
        public void OneTimeTearDown()
        {
            File.Delete(actualOutputFilePath);
        }

        private static void PerformTest(string filename, JsonOutputType outputType, bool withMetaData)
        {
            // Setup
            var timeDependentOutputConstructionProperties1 = new TimeDependentOutputConstructionProperties
            {
                IncrementDamage = 0,
                Damage = 0.15,
                TimeOfFailure = null
            };

            var timeDependentOutputConstructionProperties2 = new TimeDependentOutputConstructionProperties
            {
                IncrementDamage = 0,
                Damage = 0.253,
                TimeOfFailure = 60
            };

            var location1TimeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties1),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties2)
            };

            var timeDependentOutputConstructionProperties3 = new TimeDependentOutputConstructionProperties
            {
                IncrementDamage = 0,
                Damage = 0.28,
                TimeOfFailure = null
            };

            var timeDependentOutputConstructionProperties4 = new TimeDependentOutputConstructionProperties
            {
                IncrementDamage = 0,
                Damage = 0.512,
                TimeOfFailure = null
            };

            var location2TimeDependentOutputItems = new List<TimeDependentOutput>
            {
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties3),
                Substitute.For<TimeDependentOutput>(timeDependentOutputConstructionProperties4)
            };

            var locations = new List<LocationDependentOutput>
            {
                Substitute.For<LocationDependentOutput>(location1TimeDependentOutputItems),
                Substitute.For<LocationDependentOutput>(location2TimeDependentOutputItems)
            };

            var calculationOutput = new CalculationOutput(locations);

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
                actualOutputFilePath, calculationOutput, outputType, metaDataItems);

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
                actualOutputFilePath, calculationOutput, JsonOutputType.Physics, metaDataItems);

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
                    CumulativeOverload = 1.4
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
                    CumulativeOverload = 3.0
                });

            var naturalStoneTimeDependentOutput = new NaturalStoneRevetmentTimeDependentOutput(
                new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 3.1,
                    Damage = 3.2,
                    TimeOfFailure = 33,
                    OuterSlope = 3.4,
                    SlopeUpperLevel = 3.5,
                    SlopeUpperPosition = 3.6,
                    SlopeLowerLevel = 3.7,
                    SlopeLowerPosition = 3.8,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 3.9,
                    WaveSteepnessDeepWater = 4.0,
                    UpperLimitLoading = 4.1,
                    LowerLimitLoading = 4.2,
                    DepthMaximumWaveLoad = 4.3,
                    DistanceMaximumWaveElevation = 4.4,
                    NormativeWidthOfWaveImpact = 4.5,
                    HydraulicLoad = 4.6,
                    WaveAngleImpact = 4.7,
                    Resistance = 4.8,
                    ReferenceTimeDegradation = 4.9,
                    ReferenceDegradation = 5.0
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 5.1, 5.2),
                new GrassRevetmentOvertoppingLocationDependentOutput(new[]
                {
                    grassOvertoppingTimeDependentOutput
                }),
                new GrassRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 5.3),
                new GrassRevetmentWaveRunupRayleighLocationDependentOutput(new[]
                {
                    grassWaveRunupRayleighTimeDependentOutput
                }, 5.4),
                new NaturalStoneRevetmentLocationDependentOutput(new[]
                {
                    naturalStoneTimeDependentOutput
                }, 5.5)
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
                    SlopeUpperPosition = 2.3,
                    SlopeLowerLevel = 2.4,
                    SlopeLowerPosition = 2.5,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 2.6,
                    WaveSteepnessDeepWater = 2.7,
                    UpperLimitLoading = 2.8,
                    LowerLimitLoading = 2.9,
                    DepthMaximumWaveLoad = 3.0,
                    DistanceMaximumWaveElevation = 3.1,
                    NormativeWidthOfWaveImpact = 3.2
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 3.3, 3.4),
                new GrassRevetmentOvertoppingLocationDependentOutput(new[]
                {
                    grassOvertoppingTimeDependentOutput
                }),
                new GrassRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 3.5),
                new GrassRevetmentWaveRunupRayleighLocationDependentOutput(new[]
                {
                    grassWaveRunupRayleighTimeDependentOutput
                }, 3.6),
                new NaturalStoneRevetmentLocationDependentOutput(new[]
                {
                    naturalStoneTimeDependentOutput
                }, 3.7)
            });
        }
    }
}