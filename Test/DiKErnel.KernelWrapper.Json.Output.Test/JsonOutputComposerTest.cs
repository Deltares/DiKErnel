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
            WriteCalculationOutputToJson_JsonOutputTypeFailure_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedFailureOutput.json", JsonOutputType.Failure, false);
        }

        [Test]
        public void
            WriteCalculationOutputToJson_JsonOutputTypeDamage_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedDamageOutput.json", JsonOutputType.Damage, false);
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
            WriteCalculationOutputToJson_JsonOutputTypeFailureWithMetaData_ReturnsResultWithSuccessfulTrueAndNoEventsAndWritesExpectedValues()
        {
            PerformTest("ExpectedFailureOutputWithMetaData.json", JsonOutputType.Failure, true);
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

        private static void PerformPhysicsTest(string filename, CalculationOutput calculationOutput)
        {
            // Call
            SimpleResult result = JsonOutputComposer.WriteCalculationOutputToJson(
                actualOutputFilePath, calculationOutput, JsonOutputType.Physics);

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
                    EquivalentElasticModulus = 0.8,
                    AverageNumberOfWaves = 0.9
                });

            var grassOvertoppingTimeDependentOutput = new GrassRevetmentOvertoppingTimeDependentOutput(
                new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.0,
                    Damage = 1.1,
                    TimeOfFailure = 12,
                    VerticalDistanceWaterLevelElevation = 1.3,
                    RepresentativeWaveRunup2P = 1.4,
                    CumulativeOverload = 1.5,
                    AverageNumberOfWaves = 1.6
                });

            var grassWaveImpactTimeDependentOutput = new GrassRevetmentWaveImpactTimeDependentOutput(
                new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.7,
                    Damage = 1.8,
                    TimeOfFailure = 19,
                    LoadingRevetment = true,
                    UpperLimitLoading = 2.0,
                    LowerLimitLoading = 2.1,
                    MinimumWaveHeight = 2.2,
                    MaximumWaveHeight = 2.3,
                    WaveAngleImpact = 2.4,
                    WaveHeightImpact = 2.5
                });

            var grassWaveRunupRayleighTimeDependentOutput = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 2.6,
                    Damage = 2.7,
                    TimeOfFailure = 28,
                    VerticalDistanceWaterLevelElevation = 2.9,
                    WaveAngleImpact = 3.0,
                    RepresentativeWaveRunup2P = 3.1,
                    CumulativeOverload = 3.2,
                    AverageNumberOfWaves = 3.3
                });

            var naturalStoneTimeDependentOutput = new NaturalStoneRevetmentTimeDependentOutput(
                new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 3.4,
                    Damage = 3.5,
                    TimeOfFailure = 36,
                    OuterSlope = 3.7,
                    SlopeUpperLevel = 3.8,
                    SlopeUpperPosition = 3.9,
                    SlopeLowerLevel = 4.0,
                    SlopeLowerPosition = 4.1,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 4.2,
                    WaveSteepnessDeepWater = 4.3,
                    UpperLimitLoading = 4.4,
                    LowerLimitLoading = 4.5,
                    DepthMaximumWaveLoad = 4.6,
                    DistanceMaximumWaveElevation = 4.7,
                    NormativeWidthOfWaveImpact = 4.8,
                    HydraulicLoad = 4.9,
                    WaveAngleImpact = 5.0,
                    Resistance = 5.1,
                    ReferenceTimeDegradation = 5.2,
                    ReferenceDegradation = 5.3
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 5.3, 5.4),
                new GrassRevetmentOvertoppingLocationDependentOutput(new[]
                {
                    grassOvertoppingTimeDependentOutput
                }),
                new GrassRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 5.5),
                new GrassRevetmentWaveRunupRayleighLocationDependentOutput(new[]
                {
                    grassWaveRunupRayleighTimeDependentOutput
                }, 5.6),
                new NaturalStoneRevetmentLocationDependentOutput(new[]
                {
                    naturalStoneTimeDependentOutput
                }, 5.7)
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
                    EquivalentElasticModulus = 0.7,
                    AverageNumberOfWaves = 0.8
                });

            var grassOvertoppingTimeDependentOutput = new GrassRevetmentOvertoppingTimeDependentOutput(
                new GrassRevetmentOvertoppingTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.9,
                    Damage = 1.0,
                    VerticalDistanceWaterLevelElevation = 1.1
                });

            var grassWaveImpactTimeDependentOutput = new GrassRevetmentWaveImpactTimeDependentOutput(
                new GrassRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.2,
                    Damage = 1.3,
                    LoadingRevetment = true,
                    UpperLimitLoading = 1.4,
                    LowerLimitLoading = 1.5
                });

            var grassWaveRunupRayleighTimeDependentOutput = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.6,
                    Damage = 1.7,
                    VerticalDistanceWaterLevelElevation = 1.8
                });

            var naturalStoneTimeDependentOutput = new NaturalStoneRevetmentTimeDependentOutput(
                new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 1.9,
                    Damage = 2.0,
                    OuterSlope = 2.1,
                    SlopeUpperLevel = 2.2,
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