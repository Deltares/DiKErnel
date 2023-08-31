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
using DiKErnel.Integration.Data;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneRevetment;
using DiKErnel.Integration.TestUtil;
using DiKErnel.TestUtil;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.KernelWrapper.Json.Input.Test
{
    [TestFixture]
    public class JsonInputComposerTest
    {
        private static void PerformInvalidJsonTest(string fileName, string expectedStackTrace)
        {
            // Given
            string filePath = Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test"),
                                           "JsonInputComposerTest", fileName);

            // When
            DataResult<ICalculationInput> result = JsonInputComposer.GetInputDataFromJson(filePath);

            // Then
            Assert.IsFalse(result.Successful);

            Assert.AreEqual(1, result.Events.Count);
            Assert.AreEqual(EventType.Error, result.Events[0].Type);
            Assert.AreEqual("An unhandled error occurred while composing calculation data from the Json input. See " +
                            "stack trace for more information:\n" + expectedStackTrace, result.Events[0].Message);
        }

        [Test]
        public void GivenJsonFileWithAllData_WhenGetInputDataFromJson_ThenReturnsResultWithCalculationInputWithExpectedValues()
        {
            // Given
            string filePath = Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test"),
                                           "JsonInputComposerTest", "InputWithAllData.json");

            // When
            DataResult<ICalculationInput> result = JsonInputComposer.GetInputDataFromJson(filePath);
            ICalculationInput calculationInput = result.Data;

            // Then
            Assert.IsInstanceOf<CalculationInput>(calculationInput);

            IProfileData profileData = calculationInput.ProfileData;

            IReadOnlyList<ProfileSegment> profileSegments = profileData.ProfileSegments;
            Assert.AreEqual(23, profileSegments.Count);
            ProfileDataAssertHelper.AssertProfileSegment(-30, -11.85, -20, -8.95, 0, profileSegments[0]);
            ProfileDataAssertHelper.AssertProfileSegment(-20, -8.95, -10, -6.05, 0, profileSegments[1]);
            ProfileDataAssertHelper.AssertProfileSegment(-10, -6.05, 0, -3.15, 0, profileSegments[2]);
            ProfileDataAssertHelper.AssertProfileSegment(0, -3.15, 5, -1.7, 0.5, profileSegments[3]);
            ProfileDataAssertHelper.AssertProfileSegment(5, -1.7, 10, -0.25, 0.55, profileSegments[4]);
            ProfileDataAssertHelper.AssertProfileSegment(10, -0.25, 15, 1.2, 0.6, profileSegments[5]);
            ProfileDataAssertHelper.AssertProfileSegment(15, 1.2, 20, 2.65, 0.65, profileSegments[6]);
            ProfileDataAssertHelper.AssertProfileSegment(20, 2.65, 25, 4.1, 0.7, profileSegments[7]);
            ProfileDataAssertHelper.AssertProfileSegment(25, 4.1, 30, 5.55, 0.75, profileSegments[8]);
            ProfileDataAssertHelper.AssertProfileSegment(30, 5.55, 35, 7, 0.8, profileSegments[9]);
            ProfileDataAssertHelper.AssertProfileSegment(35, 7, 40, 8.45, 0.85, profileSegments[10]);
            ProfileDataAssertHelper.AssertProfileSegment(40, 8.45, 45, 9.9, 0.9, profileSegments[11]);
            ProfileDataAssertHelper.AssertProfileSegment(45, 9.9, 50, 11.35, 0.92, profileSegments[12]);
            ProfileDataAssertHelper.AssertProfileSegment(50, 11.35, 55, 12.8, 0.97, profileSegments[13]);
            ProfileDataAssertHelper.AssertProfileSegment(55, 12.8, 60, 14.25, 0.99, profileSegments[14]);
            ProfileDataAssertHelper.AssertProfileSegment(60, 14.25, 65, 15.7, 1.0, profileSegments[15]);
            ProfileDataAssertHelper.AssertProfileSegment(65, 15.7, 70, 15.8, 1.5, profileSegments[16]);
            ProfileDataAssertHelper.AssertProfileSegment(70, 15.8, 75, 14.3, 1.5, profileSegments[17]);
            ProfileDataAssertHelper.AssertProfileSegment(75, 14.3, 80, 12.7, 1.5, profileSegments[18]);
            ProfileDataAssertHelper.AssertProfileSegment(80, 12.7, 85, 11.4, 1.5, profileSegments[19]);
            ProfileDataAssertHelper.AssertProfileSegment(85, 11.4, 90, 10, 1.5, profileSegments[20]);
            ProfileDataAssertHelper.AssertProfileSegment(90, 10, 95, 8.5, 1.5, profileSegments[21]);
            ProfileDataAssertHelper.AssertProfileSegment(95, 8.5, 100, 7.1, 1.5, profileSegments[22]);

            IReadOnlyList<CharacteristicPoint> characteristicPoints = profileData.CharacteristicPoints;
            Assert.AreEqual(6, characteristicPoints.Count);
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[2].EndPoint, CharacteristicPointType.OuterToe, characteristicPoints[0]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[10].EndPoint, CharacteristicPointType.CrestOuterBerm, characteristicPoints[1]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[12].EndPoint, CharacteristicPointType.NotchOuterBerm, characteristicPoints[2]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[15].EndPoint, CharacteristicPointType.OuterCrest, characteristicPoints[3]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[16].EndPoint, CharacteristicPointType.InnerCrest, characteristicPoints[4]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[22].EndPoint, CharacteristicPointType.InnerToe, characteristicPoints[5]);

            IReadOnlyList<ITimeDependentInput> timeDependentInputItems = calculationInput.TimeDependentInputItems;
            Assert.AreEqual(5, timeDependentInputItems.Count);
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                0, 100, 0.1, 0.5, 2, -10, timeDependentInputItems[0]);
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                100, 500, 0.5, 0.8, 6, -5, timeDependentInputItems[1]);
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                500, 800, 1.15, 1.2, 6, 0, timeDependentInputItems[2]);
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                800, 1200, 1.77, 1.5, 7, 7, timeDependentInputItems[3]);
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                1200, 2000, 2, 0.5, 4, 8, timeDependentInputItems[4]);

            IReadOnlyList<ILocationDependentInput> locationDependentInputItems =
                calculationInput.LocationDependentInputItems;
            Assert.AreEqual(5, locationDependentInputItems.Count);

            var naturalStoneRevetmentLocationDependentInputItem =
                locationDependentInputItems[0] as NaturalStoneRevetmentLocationDependentInput;
            Assert.IsNotNull(naturalStoneRevetmentLocationDependentInputItem);

            LocationDependentInputAssertHelper.AssertLocationProperties(
                11, naturalStoneRevetmentLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0.1, 1.06, naturalStoneRevetmentLocationDependentInputItem);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertGeneralProperties(
                1.65, 0.3, naturalStoneRevetmentLocationDependentInputItem);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertHydraulicLoads(
                5, 1.3, 1.7, 0.9, -0.8, 10, -8, 6, 4.9, naturalStoneRevetmentLocationDependentInputItem.HydraulicLoads);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertSlope(
                0.95, 1.8, naturalStoneRevetmentLocationDependentInputItem.Slope);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                6.1, 3.6, 4.5, naturalStoneRevetmentLocationDependentInputItem.UpperLimitLoading);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                4.1, 8, 0.5, naturalStoneRevetmentLocationDependentInputItem.LowerLimitLoading);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertDistanceMaximumWaveElevation(
                0.7, 0.319, naturalStoneRevetmentLocationDependentInputItem.DistanceMaximumWaveElevation);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertNormativeWidthOfWaveImpact(
                1, 0.01, naturalStoneRevetmentLocationDependentInputItem.NormativeWidthOfWaveImpact);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                30, naturalStoneRevetmentLocationDependentInputItem.WaveAngleImpact);

            var grassRevetmentWaveImpactLocationDependentInputItem =
                locationDependentInputItems[1] as GrassRevetmentWaveImpactLocationDependentInput;
            Assert.IsNotNull(grassRevetmentWaveImpactLocationDependentInputItem);

            LocationDependentInputAssertHelper.AssertLocationProperties(
                1, grassRevetmentWaveImpactLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0.04, 1.07, grassRevetmentWaveImpactLocationDependentInputItem);
            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                2500000, grassRevetmentWaveImpactLocationDependentInputItem);
            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                3.1, grassRevetmentWaveImpactLocationDependentInputItem);
            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                0.9, 0.1, 8, grassRevetmentWaveImpactLocationDependentInputItem.WaveAngleImpact);
            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                0.3, -0.1, 0.96, grassRevetmentWaveImpactLocationDependentInputItem.TimeLine);
            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                1, grassRevetmentWaveImpactLocationDependentInputItem);
            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                3.5, grassRevetmentWaveImpactLocationDependentInputItem);

            var grassRevetmentWaveRunupRayleighLocationDependentInputItem =
                locationDependentInputItems[2] as GrassRevetmentWaveRunupRayleighLocationDependentInput;
            Assert.IsNotNull(grassRevetmentWaveRunupRayleighLocationDependentInputItem);

            LocationDependentInputAssertHelper.AssertLocationProperties(
                64.9, grassRevetmentWaveRunupRayleighLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0.0006, 0.45, grassRevetmentWaveRunupRayleighLocationDependentInputItem);
            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertGeneralProperties(
                0.7, grassRevetmentWaveRunupRayleighLocationDependentInputItem);
            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertRepresentative2P(
                1.56, 4.6, 3.5, 3.2, 4.1, grassRevetmentWaveRunupRayleighLocationDependentInputItem.Representative2P);
            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                0.0011, 89, grassRevetmentWaveRunupRayleighLocationDependentInputItem.WaveAngleImpact);
            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1.5, 0.8, grassRevetmentWaveRunupRayleighLocationDependentInputItem);
            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.99, grassRevetmentWaveRunupRayleighLocationDependentInputItem);
            GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7213, 5000, grassRevetmentWaveRunupRayleighLocationDependentInputItem);
            GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                8.3, 3.5, grassRevetmentWaveRunupRayleighLocationDependentInputItem);

            var asphaltRevetmentWaveImpactLocationDependentInputItem =
                locationDependentInputItems[3] as AsphaltRevetmentWaveImpactLocationDependentInput;
            Assert.IsNotNull(asphaltRevetmentWaveImpactLocationDependentInputItem);

            LocationDependentInputAssertHelper.AssertLocationProperties(
                25, asphaltRevetmentWaveImpactLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                1, 0.0098, asphaltRevetmentWaveImpactLocationDependentInputItem);
            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                5.6, 0.25, 53, 1.1, 4, 0.58, asphaltRevetmentWaveImpactLocationDependentInputItem);
            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                0.16, 18214, asphaltRevetmentWaveImpactLocationDependentInputItem.UpperLayer);
            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                0.2, 15000, asphaltRevetmentWaveImpactLocationDependentInputItem.SubLayer);
            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertFatigue(
                0.723, 7.2, asphaltRevetmentWaveImpactLocationDependentInputItem.Fatigue);

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertFactors(
                new List<(double, double)>
                {
                    (1.6, 1.0392),
                    (1.7, 1.0738)
                }, new List<(double, double)>
                {
                    (-2.0, 1.0244),
                    (-1.875, 1.0544)
                }, new List<(double, double)>
                {
                    (6.0, 2.039),
                    (6.4, 2.1)
                },
                asphaltRevetmentWaveImpactLocationDependentInputItem);

            var grassRevetmentOvertoppingLocationDependentInputItem =
                locationDependentInputItems[4] as GrassRevetmentOvertoppingLocationDependentInput;
            Assert.IsNotNull(grassRevetmentOvertoppingLocationDependentInputItem);

            LocationDependentInputAssertHelper.AssertLocationProperties(
                65, grassRevetmentOvertoppingLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0.023, 0.3, grassRevetmentOvertoppingLocationDependentInputItem);
            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertGeneralProperties(
                15.75, grassRevetmentOvertoppingLocationDependentInputItem);
            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertTransitionAlpha(
                0.5, 1.8, grassRevetmentOvertoppingLocationDependentInputItem);
            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.29, grassRevetmentOvertoppingLocationDependentInputItem);
            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7001, 100000, grassRevetmentOvertoppingLocationDependentInputItem);
            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertFrontVelocity(
                3.6, 45.1, grassRevetmentOvertoppingLocationDependentInputItem);
            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1.8, 4.4, grassRevetmentOvertoppingLocationDependentInputItem.LocationDependentAccelerationAlphaA);
        }

        // [Test]
        // public void GivenJsonFileWithAllMandatoryData_WhenGetInputDataFromJson_ThenReturnsResultWithCalculationInputWithExpectedValues()
        // {
        //     // Given
        //     var filePath = (TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
        //                            / "InputWithAllMandatoryData.json").string();
        //
        //     // When
        //     var result = JsonInputComposer.GetInputDataFromJson(filePath);
        //     var calculationInput = result.Data();
        //
        //     // Then
        //     AssertHelper.AssertIsInstanceOf<CalculationInput>(calculationInput);
        //
        //     var profileData = calculationInput.ProfileData();
        //
        //     var profileSegments = profileData.ProfileSegments();
        //     ASSERT_EQ(3, profileSegments.Count);
        //     auto profileSegment1 = profileSegments[0];
        //     auto profileSegment2 = profileSegments[1];
        //     auto profileSegment3 = profileSegments[2];
        //     ProfileDataAssertHelper.AssertProfileSegment(30, 5.55, 65, 15.7, 1, profileSegment1);
        //     ProfileDataAssertHelper.AssertProfileSegment(65, 15.7, 75, 15.7, 1, profileSegment2);
        //     ProfileDataAssertHelper.AssertProfileSegment(75, 15.7, 85, 10, 1, profileSegment3);
        //
        //     var characteristicPoints = profileData.CharacteristicPoints();
        //     ASSERT_EQ(4, characteristicPoints.Count);
        //
        //     ProfileDataAssertHelper.AssertCharacteristicPoint(profileSegment1.StartPoint(), CharacteristicPointType.OuterToe,
        //                                                        characteristicPoints[0));
        //     ProfileDataAssertHelper.AssertCharacteristicPoint(profileSegment1.EndPoint(), CharacteristicPointType.OuterCrest,
        //                                                        characteristicPoints[1));
        //     ProfileDataAssertHelper.AssertCharacteristicPoint(profileSegment3.StartPoint(), CharacteristicPointType.InnerCrest,
        //                                                        characteristicPoints[2));
        //     ProfileDataAssertHelper.AssertCharacteristicPoint(profileSegment3.EndPoint(), CharacteristicPointType.InnerToe,
        //                                                        characteristicPoints[3));
        //
        //     var timeDependentInputItems = calculationInput.TimeDependentInputItems();
        //     ASSERT_EQ(1, timeDependentInputItems.Count);
        //     TimeDependentInputAssertHelper.AssertTimeDependentInputItem(0, 100, 0.1, 0.5, 2, -10, timeDependentInputItems[0));
        //
        //     var locationDependentInputItems = calculationInput.LocationDependentInputItems();
        //     ASSERT_EQ(8, locationDependentInputItems.Count);
        //
        //     var naturalStoneRevetmentLocationDependentInputItem = NaturalStoneRevetmentLocationDependentInput*>(
        //         &locationDependentInputItems[0]);
        //     Assert.IsNotNull(naturalStoneRevetmentLocationDependentInputItem);
        //
        //     LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, naturalStoneRevetmentLocationDependentInputItem);
        //     NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertGeneralProperties(
        //         32.79, 1.65, 0.7, naturalStoneRevetmentLocationDependentInputItem);
        //     NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertHydraulicLoads(
        //         4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, naturalStoneRevetmentLocationDependentInputItem.HydraulicLoads());
        //     NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertSlope(
        //         0.05, 1.5, naturalStoneRevetmentLocationDependentInputItem.Slope());
        //     NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertUpperLimitLoading(
        //         0.1, 0.6, 4, naturalStoneRevetmentLocationDependentInputItem.UpperLimitLoading());
        //     NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertLowerLimitLoading(
        //         0.1, 0.2, 4, naturalStoneRevetmentLocationDependentInputItem.LowerLimitLoading());
        //     NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertDistanceMaximumWaveElevation(
        //         0.42, 0.9, naturalStoneRevetmentLocationDependentInputItem.DistanceMaximumWaveElevation());
        //     NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertNormativeWidthOfWaveImpact(
        //         0.96, 0.11, naturalStoneRevetmentLocationDependentInputItem.NormativeWidthOfWaveImpact());
        //     NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertWaveAngleImpact(
        //         78, naturalStoneRevetmentLocationDependentInputItem.WaveAngleImpact());
        //
        //     var grassRevetmentWaveImpactLocationDependentInputItem1 = GrassRevetmentWaveImpactLocationDependentInput*>(
        //         &locationDependentInputItems[1]);
        //     Assert.IsNotNull(grassRevetmentWaveImpactLocationDependentInputItem1);
        //
        //     LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, grassRevetmentWaveImpactLocationDependentInputItem1);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
        //         38.4, grassRevetmentWaveImpactLocationDependentInputItem1);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
        //         3600000, grassRevetmentWaveImpactLocationDependentInputItem1);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
        //         3.6, grassRevetmentWaveImpactLocationDependentInputItem1);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
        //         2.0 / 3.0, 0.35, 10, grassRevetmentWaveImpactLocationDependentInputItem1.WaveAngleImpact());
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
        //         1, -0.000009722, 0.25, grassRevetmentWaveImpactLocationDependentInputItem1.TimeLine());
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
        //         0, grassRevetmentWaveImpactLocationDependentInputItem1);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
        //         0.5, grassRevetmentWaveImpactLocationDependentInputItem1);
        //
        //     var grassRevetmentWaveImpactLocationDependentInputItem2 = GrassRevetmentWaveImpactLocationDependentInput*>(
        //         &locationDependentInputItems[2]);
        //     Assert.IsNotNull(grassRevetmentWaveImpactLocationDependentInputItem2);
        //
        //     LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, grassRevetmentWaveImpactLocationDependentInputItem2);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
        //         40, grassRevetmentWaveImpactLocationDependentInputItem2);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
        //         3600000, grassRevetmentWaveImpactLocationDependentInputItem2);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
        //         3.6, grassRevetmentWaveImpactLocationDependentInputItem2);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
        //         2.0 / 3.0, 0.35, 10, grassRevetmentWaveImpactLocationDependentInputItem2.WaveAngleImpact());
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
        //         0.8, -0.00001944, 0.25, grassRevetmentWaveImpactLocationDependentInputItem2.TimeLine());
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
        //         0, grassRevetmentWaveImpactLocationDependentInputItem2);
        //     GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
        //         0.5, grassRevetmentWaveImpactLocationDependentInputItem2);
        //
        //     var grassRevetmentWaveRunupRayleighLocationDependentInputItem1 = dynamic_cast
        //         <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems[3]);
        //     Assert.IsNotNull(grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        //
        //     LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertGeneralProperties(
        //         50.98, 0.8, grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertRepresentative2P(
        //         1.65, 4, 1.5, 1, 1, grassRevetmentWaveRunupRayleighLocationDependentInputItem1.Representative2P());
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertWaveAngleImpact(
        //         0.0022, 80, grassRevetmentWaveRunupRayleighLocationDependentInputItem1.WaveAngleImpact());
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertTransitionAlpha(
        //         1, 1, grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
        //         0.92, grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        //     GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertCumulativeOverload(
        //         7000, 10000, grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        //     GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
        //         6.6, 1.1, grassRevetmentWaveRunupRayleighLocationDependentInputItem1);
        //
        //     var grassRevetmentWaveRunupRayleighLocationDependentInputItem2 = dynamic_cast
        //         <GrassRevetmentWaveRunupRayleighLocationDependentInput*>(&locationDependentInputItems[4]);
        //     Assert.IsNotNull(grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        //
        //     LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertGeneralProperties(
        //         57.698, 0.9, grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertRepresentative2P(
        //         1.65, 4, 1.5, 1, 1, grassRevetmentWaveRunupRayleighLocationDependentInputItem2.Representative2P());
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertWaveAngleImpact(
        //         0.0022, 80, grassRevetmentWaveRunupRayleighLocationDependentInputItem2.WaveAngleImpact());
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertTransitionAlpha(
        //         1, 1, grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        //     GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
        //         0.92, grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        //     GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertCumulativeOverload(
        //         7000, 10000, grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        //     GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
        //         4.3, 1.1, grassRevetmentWaveRunupRayleighLocationDependentInputItem2);
        //
        //     var asphaltRevetmentWaveImpactLocationDependentInputItem = dynamic_cast
        //         <AsphaltRevetmentWaveImpactLocationDependentInput*>(&locationDependentInputItems[5]);
        //     Assert.IsNotNull(asphaltRevetmentWaveImpactLocationDependentInputItem);
        //
        //     LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, asphaltRevetmentWaveImpactLocationDependentInputItem);
        //     AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
        //         39, 1.56, 1025, 56, 1, 1, 0.35, asphaltRevetmentWaveImpactLocationDependentInputItem);
        //     AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLayer(
        //         0.16, 18214, asphaltRevetmentWaveImpactLocationDependentInputItem.UpperLayer());
        //     ASSERT_EQ(nullptr, asphaltRevetmentWaveImpactLocationDependentInputItem.SubLayer());
        //     AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertFatigue(
        //         0.42, 4.76, asphaltRevetmentWaveImpactLocationDependentInputItem.Fatigue());
        //
        //     var expectedWidthFactors = vector
        //     {
        //         pair(0.1, 0.0392),
        //         pair(0.2, 0.0738),
        //         pair(0.3, 0.1002),
        //         pair(0.4, 0.1162),
        //         pair(0.5, 0.1213),
        //         pair(0.6, 0.1168),
        //         pair(0.7, 0.1051),
        //         pair(0.8, 0.0890),
        //         pair(0.9, 0.0712),
        //         pair(1.0, 0.0541),
        //         pair(1.1, 0.0391),
        //         pair(1.2, 0.0269),
        //         pair(1.3, 0.0216),
        //         pair(1.4, 0.0150),
        //         pair(1.5, 0.0105)
        //     }
        //     ;
        //
        //     var expectedDepthFactors = vector
        //     {
        //         pair(-1.0, 0.0244),
        //         pair(-0.875, 0.0544),
        //         pair(-0.750, 0.0938),
        //         pair(-0.625, 0.1407),
        //         pair(-0.500, 0.1801),
        //         pair(-0.375, 0.1632),
        //         pair(-0.250, 0.1426),
        //         pair(-0.125, 0.0994),
        //         pair(0.0, 0.06),
        //         pair(0.125, 0.0244),
        //         pair(0.250, 0.0169)
        //     }
        //     ;
        //
        //     var expectedImpactFactors = vector
        //     {
        //         pair(2.0, 0.039),
        //         pair(2.4, 0.1),
        //         pair(2.8, 0.18),
        //         pair(3.2, 0.235),
        //         pair(3.6, 0.2),
        //         pair(4.0, 0.13),
        //         pair(4.4, 0.08),
        //         pair(4.8, 0.02),
        //         pair(5.2, 0.01),
        //         pair(5.6, 0.005),
        //         pair(6.0, 0.001)
        //     }
        //     ;
        //
        //     AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertFactors(
        //         expectedWidthFactors, expectedDepthFactors, expectedImpactFactors, asphaltRevetmentWaveImpactLocationDependentInputItem);
        //
        //     var grassRevetmentOvertoppingLocationDependentInputItem1 =
        //         GrassRevetmentOvertoppingLocationDependentInput*>(
        //             &locationDependentInputItems[6]);
        //     Assert.IsNotNull(grassRevetmentOvertoppingLocationDependentInputItem1);
        //     LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, grassRevetmentOvertoppingLocationDependentInputItem1);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertGeneralProperties(
        //         65, nullptr, grassRevetmentOvertoppingLocationDependentInputItem1);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertTransitionAlpha(
        //         1, 1, grassRevetmentOvertoppingLocationDependentInputItem1);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
        //         0.92, grassRevetmentOvertoppingLocationDependentInputItem1);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertCumulativeOverload(
        //         7000, 10000, grassRevetmentOvertoppingLocationDependentInputItem1);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertFrontVelocity(
        //         6.6, 1.45, grassRevetmentOvertoppingLocationDependentInputItem1);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
        //         1, 1.4, grassRevetmentOvertoppingLocationDependentInputItem1.LocationDependentAccelerationAlphaA());
        //
        //     var grassRevetmentOvertoppingLocationDependentInputItem2 =
        //         GrassRevetmentOvertoppingLocationDependentInput*>(
        //             &locationDependentInputItems[7]);
        //     Assert.IsNotNull(grassRevetmentOvertoppingLocationDependentInputItem2);
        //     LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, grassRevetmentOvertoppingLocationDependentInputItem2);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertGeneralProperties(
        //         85, nullptr, grassRevetmentOvertoppingLocationDependentInputItem2);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertTransitionAlpha(
        //         1, 1, grassRevetmentOvertoppingLocationDependentInputItem2);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
        //         0.92, grassRevetmentOvertoppingLocationDependentInputItem2);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertCumulativeOverload(
        //         7000, 10000, grassRevetmentOvertoppingLocationDependentInputItem2);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertFrontVelocity(
        //         4.3, 1.45, grassRevetmentOvertoppingLocationDependentInputItem2);
        //
        //     GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
        //         1, 1.4, grassRevetmentOvertoppingLocationDependentInputItem2.LocationDependentAccelerationAlphaA());
        // }
        //
        // [Test]
        // public void GivenJsonInputWithInvalidAsphaltRevetmentWaveImpactTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        // {
        //     PerformInvalidJsonTest("InvalidAsphaltRevetmentWaveImpactTopLayerType.json", "Cannot convert top layer type.");
        // }
        //
        // [Test]
        // public void GivenJsonInputWithInvalidGrassRevetmentOvertoppingTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        // {
        //     PerformInvalidJsonTest("InvalidGrassRevetmentOvertoppingTopLayerType.json", "Cannot convert top layer type.");
        // }
        //
        // [Test]
        // public void GivenJsonInputWithInvalidGrassRevetmentWaveImpactTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        // {
        //     PerformInvalidJsonTest("InvalidGrassRevetmentWaveImpactTopLayerType.json", "Cannot convert top layer type.");
        // }
        //
        // [Test]
        // public void GivenJsonInputWithInvalidGrassRevetmentWaveRunupRayleighTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        // {
        //     PerformInvalidJsonTest("InvalidGrassRevetmentWaveRunupRayleighTopLayerType.json", "Cannot convert top layer type.");
        // }
        //
        // [Test]
        // public void GivenJsonInputWithInvalidGrassRevetmentWaveRunupCalculationProtocolType_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        // {
        //     PerformInvalidJsonTest("InvalidGrassRevetmentWaveRunupCalculationProtocolType.json",
        //                            "Cannot convert calculation protocol type.");
        // }
        //
        // [Test]
        // public void GivenJsonInputWithGrassRevetmentWaveRunupNoCalculationMethod_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        // {
        //     PerformInvalidJsonTest("GrassRevetmentWaveRunupNoCalculationMethod.json", "Cannot convert calculation protocol type.");
        // }
        //
        // [Test]
        // public void GivenJsonInputWithInvalidNaturalStoneRevetmentTypeTopLayer_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        // {
        //     PerformInvalidJsonTest("InvalidNaturalStoneRevetmentTopLayerType.json", "Cannot convert top layer type.");
        // }
        //
        // [Test]
        // public void GivenNotExistingJsonInputFile_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        // {
        //     // Given
        //     var filePath = "NotExisting";
        //
        //     // When
        //     var result = JsonInputComposer.GetInputDataFromJson(filePath);
        //
        //     // Then
        //     ASSERT_FALSE(result.Successful());
        //
        //     var events = result.Events();
        //     ASSERT_EQ(1, events.Count);
        //     EventAssertHelper.AssertEvent(EventType.Error, "The provided input file does not exist", events[0));
        // }
        //
        // [Test]
        // public void GivenCompleteAndValidJsonInputFile_WhenValidatingJson_ThenReturnsTrueAndNoEventsRegistered()
        // {
        //     // Given
        //     var filePath = (TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
        //                            / "InputWithAllData.json").string();
        //
        //     // When
        //     var result = JsonInputComposer.ValidateJson(filePath);
        //
        //     // Then
        //     ASSERT_TRUE(result);
        //     ASSERT_EQ(0, EventRegistry.Flush().Count);
        // }
        //
        // [Test]
        // public void GivenInvalidJsonInputFile_WhenValidatingJson_ThenReturnsFalseAndExpectedEventsRegistered()
        // {
        //     // Given
        //     var filePath = (TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test") / "JsonInputComposerTest"
        //                            / "InvalidFormat.json").string();
        //
        //     // When
        //     var result = JsonInputComposer.ValidateJson(filePath);
        //
        //     // Then
        //     ASSERT_FALSE(result);
        //
        //     var registeredEvents = EventRegistry.Flush();
        //     ASSERT_EQ(1, registeredEvents.Count);
        //     EventAssertHelper.AssertEvent(EventType.Error, "At  of {} - required property 'tijdstippen' not found in object",
        //                                    registeredEvents[0));
        // }
        //
        // [Test]
        // public void GivenNotExistingJsonInputFile_WhenValidatingJson_ThenReturnsFalseAndExpectedEventsRegistered()
        // {
        //     // Given
        //     var filePath = "NotExisting.json";
        //
        //     // When
        //     var result = JsonInputComposer.ValidateJson(filePath);
        //
        //     // Then
        //     ASSERT_FALSE(result);
        //
        //     var registeredEvents = EventRegistry.Flush();
        //     ASSERT_EQ(1, registeredEvents.Count);
        //     EventAssertHelper.AssertEvent(EventType.Error, "The provided input file does not exist", registeredEvents[0));
        // }
    }
}