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
                    LogFlexuralStrength = 0.4,
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
                    MaximumWaveHeight = 2.2,
                    MinimumWaveHeight = 2.3,
                    WaveAngle = 2.4,
                    WaveAngleImpact = 2.5,
                    WaveHeightImpact = 2.6
                });

            var grassWaveRunupRayleighTimeDependentOutput = new GrassRevetmentWaveRunupRayleighTimeDependentOutput(
                new GrassRevetmentWaveRunupRayleighTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 2.7,
                    Damage = 2.8,
                    TimeOfFailure = 29,
                    VerticalDistanceWaterLevelElevation = 3.0,
                    WaveAngle = 3.1,
                    WaveAngleImpact = 3.2,
                    RepresentativeWaveRunup2P = 3.3,
                    CumulativeOverload = 3.4,
                    AverageNumberOfWaves = 3.5
                });

            var naturalStoneTimeDependentOutput = new NaturalStoneRevetmentTimeDependentOutput(
                new NaturalStoneRevetmentTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 3.6,
                    Damage = 3.7,
                    TimeOfFailure = 38,
                    OuterSlope = 3.9,
                    SlopeUpperLevel = 4.0,
                    SlopeUpperPosition = 4.1,
                    SlopeLowerLevel = 4.2,
                    SlopeLowerPosition = 4.3,
                    LoadingRevetment = true,
                    SurfSimilarityParameter = 4.4,
                    WaveSteepnessDeepWater = 4.5,
                    UpperLimitLoading = 4.6,
                    LowerLimitLoading = 4.7,
                    DepthMaximumWaveLoad = 4.8,
                    DistanceMaximumWaveElevation = 4.9,
                    NormativeWidthOfWaveImpact = 5.0,
                    HydraulicLoad = 5.1,
                    WaveAngle = 5.2,
                    WaveAngleImpact = 5.3,
                    Resistance = 5.4,
                    ReferenceTimeDegradation = 5.5,
                    ReferenceDegradation = 5.6
                });

            return new CalculationOutput(new List<LocationDependentOutput>
            {
                new AsphaltRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    asphaltWaveImpactTimeDependentOutput
                }, 5.7, 5.8, 5.9, 6.0, 6.1, 6.2),
                new GrassRevetmentOvertoppingLocationDependentOutput(new[]
                {
                    grassOvertoppingTimeDependentOutput
                }),
                new GrassRevetmentWaveImpactLocationDependentOutput(new[]
                {
                    grassWaveImpactTimeDependentOutput
                }, 5.9),
                new GrassRevetmentWaveRunupRayleighLocationDependentOutput(new[]
                {
                    grassWaveRunupRayleighTimeDependentOutput
                }, 6.0),
                new NaturalStoneRevetmentLocationDependentOutput(new[]
                {
                    naturalStoneTimeDependentOutput
                }, 6.1)
            });
        }

        private static CalculationOutput CreateCalculationOutputWithRevetmentSpecificTimeDependentOutputWithOnlyMandatoryDataSet()
        {
            var asphaltWaveImpactTimeDependentOutput = new AsphaltRevetmentWaveImpactTimeDependentOutput(
                new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
                {
                    IncrementDamage = 0.1,
                    Damage = 0.2,
                    LogFlexuralStrength = 0.3,
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
                }, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8),
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