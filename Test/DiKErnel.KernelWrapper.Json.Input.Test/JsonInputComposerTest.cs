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
using System.Linq;
using DiKErnel.Core.Data;
using DiKErnel.Integration.Data;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.Integration.TestUtil;
using DiKErnel.TestUtil;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.KernelWrapper.Json.Input.Test
{
    [TestFixture]
    public class JsonInputComposerTest
    {
        [Test]
        public void GivenJsonFileWithAllData_WhenGetInputDataFromJson_ThenReturnsResultWithCalculationInputWithExpectedValues()
        {
            // Given
            string filePath = Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test"),
                                           "JsonInputComposerTest", "InputWithAllData.json");

            // When
            ComposedInputData result = JsonInputComposer.GetInputDataFromJson(filePath);

            // Then
            Assert.That(result, Is.Not.Null);

            Assert.That(result.CalculationInputDataResult, Is.Not.Null);

            ICalculationInput calculationInput = result.CalculationInputDataResult.Data;

            Assert.That(calculationInput, Is.InstanceOf<CalculationInput>());

            IProfileData profileData = calculationInput.ProfileData;

            Assert.That(calculationInput.ProfileData.DikeOrientation, Is.EqualTo(14.45));
            IReadOnlyList<ProfileSegment> profileSegments = profileData.ProfileSegments;
            Assert.That(profileSegments, Has.Count.EqualTo(23));
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
            ProfileDataAssertHelper.AssertProfileSegment(60, 14.25, 65, 15.7, 1, profileSegments[15]);
            ProfileDataAssertHelper.AssertProfileSegment(65, 15.7, 70, 15.8, 1.5, profileSegments[16]);
            ProfileDataAssertHelper.AssertProfileSegment(70, 15.8, 75, 14.3, 1.5, profileSegments[17]);
            ProfileDataAssertHelper.AssertProfileSegment(75, 14.3, 80, 12.7, 1.5, profileSegments[18]);
            ProfileDataAssertHelper.AssertProfileSegment(80, 12.7, 85, 11.4, 1.5, profileSegments[19]);
            ProfileDataAssertHelper.AssertProfileSegment(85, 11.4, 90, 10, 1.5, profileSegments[20]);
            ProfileDataAssertHelper.AssertProfileSegment(90, 10, 95, 8.5, 1.5, profileSegments[21]);
            ProfileDataAssertHelper.AssertProfileSegment(95, 8.5, 100, 7.1, 1.5, profileSegments[22]);

            IReadOnlyList<CharacteristicPoint> characteristicPoints = profileData.CharacteristicPoints;
            Assert.That(characteristicPoints, Has.Count.EqualTo(6));
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
            Assert.That(timeDependentInputItems, Has.Count.EqualTo(5));
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                0, 100, 0.1, 0.5, 2, 0, timeDependentInputItems[0]);
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                100, 500, 0.5, 0.8, 6, 7, timeDependentInputItems[1]);
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                500, 800.5, 1.15, 1.2, 6, 8, timeDependentInputItems[2]);
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                800.5, 1200, 1.77, 1.5, 7, 350, timeDependentInputItems[3]);
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                1200, 2000, 2, 0.5, 4, 355, timeDependentInputItems[4]);

            IReadOnlyList<ILocationDependentInput> locationDependentInputItems =
                calculationInput.LocationDependentInputItems;
            Assert.That(locationDependentInputItems, Has.Count.EqualTo(5));

            var naturalStoneWaveImpactLocationDependentInputItem =
                locationDependentInputItems[0] as NaturalStoneWaveImpactLocationDependentInput;
            Assert.That(naturalStoneWaveImpactLocationDependentInputItem, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                11, naturalStoneWaveImpactLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0.1, 1.06, naturalStoneWaveImpactLocationDependentInputItem);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                1.65, 0.3, naturalStoneWaveImpactLocationDependentInputItem);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertHydraulicLoads(
                5, 1.3, 1.7, 0.9, -0.8, 10, -8, 6, 4.9, naturalStoneWaveImpactLocationDependentInputItem.HydraulicLoads);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertSlope(
                0.95, 1.8, naturalStoneWaveImpactLocationDependentInputItem.Slope);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                6.1, 3.6, 4.5, naturalStoneWaveImpactLocationDependentInputItem.UpperLimitLoading);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                4.1, 8, 0.5, naturalStoneWaveImpactLocationDependentInputItem.LowerLimitLoading);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertDistanceMaximumWaveElevation(
                0.7, 0.319, naturalStoneWaveImpactLocationDependentInputItem.DistanceMaximumWaveElevation);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertNormativeWidthOfWaveImpact(
                1, 0.01, naturalStoneWaveImpactLocationDependentInputItem.NormativeWidthOfWaveImpact);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                30, naturalStoneWaveImpactLocationDependentInputItem.WaveAngleImpact);

            var grassWaveImpactLocationDependentInputItem =
                locationDependentInputItems[1] as GrassWaveImpactLocationDependentInput;
            Assert.That(grassWaveImpactLocationDependentInputItem, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                1, grassWaveImpactLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0.04, 1.07, grassWaveImpactLocationDependentInputItem);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                2500000, grassWaveImpactLocationDependentInputItem);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                3.1, grassWaveImpactLocationDependentInputItem);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                0.9, 0.1, 8, grassWaveImpactLocationDependentInputItem.WaveAngleImpact);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                0.3, -0.1, 0.96, grassWaveImpactLocationDependentInputItem.TimeLine);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                1, grassWaveImpactLocationDependentInputItem);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                3.5, grassWaveImpactLocationDependentInputItem);

            var grassWaveRunupRayleighDiscreteLocationDependentInputItem =
                locationDependentInputItems[2] as GrassWaveRunupRayleighDiscreteLocationDependentInput;
            Assert.That(grassWaveRunupRayleighDiscreteLocationDependentInputItem, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                64.9, grassWaveRunupRayleighDiscreteLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0.0006, 0.45, grassWaveRunupRayleighDiscreteLocationDependentInputItem);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1.5, 0.8, grassWaveRunupRayleighDiscreteLocationDependentInputItem);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.99, grassWaveRunupRayleighDiscreteLocationDependentInputItem);
            GrassWaveRunupRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7213, 5000, grassWaveRunupRayleighDiscreteLocationDependentInputItem);
            GrassWaveRunupLocationDependentInputAssertHelper.AssertFrontVelocity(
                8.3, 3.5, grassWaveRunupRayleighDiscreteLocationDependentInputItem);

            var asphaltWaveImpactLocationDependentInputItem =
                locationDependentInputItems[3] as AsphaltWaveImpactLocationDependentInput;
            Assert.That(asphaltWaveImpactLocationDependentInputItem, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                25, asphaltWaveImpactLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                1, 0.0098, asphaltWaveImpactLocationDependentInputItem);
            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                5.6, 0.25, 53, 1.1, 4, 0.58, asphaltWaveImpactLocationDependentInputItem);
            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                0.16, 18214, asphaltWaveImpactLocationDependentInputItem.UpperLayer);
            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                0.2, 15000, asphaltWaveImpactLocationDependentInputItem.SubLayer);
            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertFatigue(
                0.723, 7.2, asphaltWaveImpactLocationDependentInputItem.Fatigue);
            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertFactors(
                new List<(double, double)>
                {
                    (1.6, 1.0392),
                    (1.7, 1.0738)
                }, new List<(double, double)>
                {
                    (-2, 1.0244),
                    (-1.875, 1.0544)
                }, new List<(double, double)>
                {
                    (6, 2.039),
                    (6.4, 2.1)
                },
                asphaltWaveImpactLocationDependentInputItem);

            var grassWaveOvertoppingRayleighDiscreteLocationDependentInput =
                locationDependentInputItems[4] as GrassWaveOvertoppingRayleighDiscreteLocationDependentInput;
            Assert.That(grassWaveOvertoppingRayleighDiscreteLocationDependentInput, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                65, grassWaveOvertoppingRayleighDiscreteLocationDependentInput);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0.023, 0.3, grassWaveOvertoppingRayleighDiscreteLocationDependentInput);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertGeneralProperties(
                15.75, grassWaveOvertoppingRayleighDiscreteLocationDependentInput);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                0.5, 1.8, grassWaveOvertoppingRayleighDiscreteLocationDependentInput);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.29, grassWaveOvertoppingRayleighDiscreteLocationDependentInput);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7001, 100000, grassWaveOvertoppingRayleighDiscreteLocationDependentInput);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertFrontVelocity(
                3.6, 45.1, grassWaveOvertoppingRayleighDiscreteLocationDependentInput);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1.8, 4.4, grassWaveOvertoppingRayleighDiscreteLocationDependentInput.AccelerationAlphaA);

            Assert.That(result.LocationIds, Is.EqualTo(new[]
            {
                1,
                2,
                3,
                5,
                9
            }));
        }

        [Test]
        public void GivenJsonFileWithAllMandatoryData_WhenGetInputDataFromJson_ThenReturnsResultWithCalculationInputWithExpectedValues()
        {
            // Given
            string filePath = Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test"),
                                           "JsonInputComposerTest", "InputWithAllMandatoryData.json");

            // When
            ComposedInputData result = JsonInputComposer.GetInputDataFromJson(filePath);

            // Then
            Assert.That(result, Is.Not.Null);

            Assert.That(result.CalculationInputDataResult, Is.Not.Null);

            ICalculationInput calculationInput = result.CalculationInputDataResult.Data;

            Assert.That(calculationInput, Is.InstanceOf<CalculationInput>());

            IProfileData profileData = calculationInput.ProfileData;

            Assert.That(profileData.DikeOrientation, Is.EqualTo(14.45));
            IReadOnlyList<ProfileSegment> profileSegments = profileData.ProfileSegments;
            Assert.That(profileSegments, Has.Count.EqualTo(3));
            ProfileDataAssertHelper.AssertProfileSegment(30, 5.55, 65, 15.7, 1, profileSegments[0]);
            ProfileDataAssertHelper.AssertProfileSegment(65, 15.7, 75, 15.7, 1, profileSegments[1]);
            ProfileDataAssertHelper.AssertProfileSegment(75, 15.7, 85, 10, 1, profileSegments[2]);

            IReadOnlyList<CharacteristicPoint> characteristicPoints = profileData.CharacteristicPoints;
            Assert.That(characteristicPoints, Has.Count.EqualTo(4));
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[0].StartPoint, CharacteristicPointType.OuterToe, characteristicPoints[0]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[0].EndPoint, CharacteristicPointType.OuterCrest, characteristicPoints[1]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[2].StartPoint, CharacteristicPointType.InnerCrest, characteristicPoints[2]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(
                profileSegments[2].EndPoint, CharacteristicPointType.InnerToe, characteristicPoints[3]);

            IReadOnlyList<ITimeDependentInput> timeDependentInputItems = calculationInput.TimeDependentInputItems;
            Assert.That(timeDependentInputItems, Has.Count.EqualTo(1));
            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(
                0.5, 100, 0.1, 0.5, 2, 350, timeDependentInputItems[0]);

            IReadOnlyList<ILocationDependentInput> locationDependentInputItems =
                calculationInput.LocationDependentInputItems;
            Assert.That(locationDependentInputItems, Has.Count.EqualTo(8));

            var naturalStoneWaveImpactLocationDependentInputItem =
                locationDependentInputItems[0] as NaturalStoneWaveImpactLocationDependentInput;
            Assert.That(naturalStoneWaveImpactLocationDependentInputItem, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                32.79, naturalStoneWaveImpactLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0, 1, naturalStoneWaveImpactLocationDependentInputItem);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                1.65, 0.7, naturalStoneWaveImpactLocationDependentInputItem);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertHydraulicLoads(
                4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, naturalStoneWaveImpactLocationDependentInputItem.HydraulicLoads);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertSlope(
                0.05, 1.5, naturalStoneWaveImpactLocationDependentInputItem.Slope);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                0.1, 0.6, 4, naturalStoneWaveImpactLocationDependentInputItem.UpperLimitLoading);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                0.1, 0.2, 4, naturalStoneWaveImpactLocationDependentInputItem.LowerLimitLoading);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertDistanceMaximumWaveElevation(
                0.42, 0.9, naturalStoneWaveImpactLocationDependentInputItem.DistanceMaximumWaveElevation);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertNormativeWidthOfWaveImpact(
                0.96, 0.11, naturalStoneWaveImpactLocationDependentInputItem.NormativeWidthOfWaveImpact);
            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                78, naturalStoneWaveImpactLocationDependentInputItem.WaveAngleImpact);

            var grassWaveImpactLocationDependentInputItem1 =
                locationDependentInputItems[1] as GrassWaveImpactLocationDependentInput;
            Assert.That(grassWaveImpactLocationDependentInputItem1, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                38.4, grassWaveImpactLocationDependentInputItem1);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0, 1, grassWaveImpactLocationDependentInputItem1);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                3600000, grassWaveImpactLocationDependentInputItem1);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                3.6, grassWaveImpactLocationDependentInputItem1);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                2d / 3, 0.35, 10, grassWaveImpactLocationDependentInputItem1.WaveAngleImpact);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                1, -0.000009722, 0.25, grassWaveImpactLocationDependentInputItem1.TimeLine);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                0, grassWaveImpactLocationDependentInputItem1);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                0.5, grassWaveImpactLocationDependentInputItem1);

            var grassWaveImpactLocationDependentInputItem2 =
                locationDependentInputItems[2] as GrassWaveImpactLocationDependentInput;
            Assert.That(grassWaveImpactLocationDependentInputItem2, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                40, grassWaveImpactLocationDependentInputItem2);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0, 1, grassWaveImpactLocationDependentInputItem2);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                3600000, grassWaveImpactLocationDependentInputItem2);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                3.6, grassWaveImpactLocationDependentInputItem2);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                2d / 3, 0.35, 10, grassWaveImpactLocationDependentInputItem2.WaveAngleImpact);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                0.8, -0.00001944, 0.25, grassWaveImpactLocationDependentInputItem2.TimeLine);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                0, grassWaveImpactLocationDependentInputItem2);
            GrassWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                0.5, grassWaveImpactLocationDependentInputItem2);

            var grassWaveRunupRayleighDiscreteLocationDependentInputItem1 =
                locationDependentInputItems[3] as GrassWaveRunupRayleighDiscreteLocationDependentInput;
            Assert.That(grassWaveRunupRayleighDiscreteLocationDependentInputItem1, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                50.98, grassWaveRunupRayleighDiscreteLocationDependentInputItem1);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0, 1, grassWaveRunupRayleighDiscreteLocationDependentInputItem1);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, grassWaveRunupRayleighDiscreteLocationDependentInputItem1);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, grassWaveRunupRayleighDiscreteLocationDependentInputItem1);
            GrassWaveRunupRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, grassWaveRunupRayleighDiscreteLocationDependentInputItem1);
            GrassWaveRunupLocationDependentInputAssertHelper.AssertFrontVelocity(
                6.6, 1.1, grassWaveRunupRayleighDiscreteLocationDependentInputItem1);

            var grassWaveRunupRayleighDiscreteLocationDependentInputItem2 =
                locationDependentInputItems[4] as GrassWaveRunupRayleighDiscreteLocationDependentInput;
            Assert.That(grassWaveRunupRayleighDiscreteLocationDependentInputItem2, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                57.698, grassWaveRunupRayleighDiscreteLocationDependentInputItem2);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0, 1, grassWaveRunupRayleighDiscreteLocationDependentInputItem2);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, grassWaveRunupRayleighDiscreteLocationDependentInputItem2);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, grassWaveRunupRayleighDiscreteLocationDependentInputItem2);
            GrassWaveRunupRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, grassWaveRunupRayleighDiscreteLocationDependentInputItem2);
            GrassWaveRunupLocationDependentInputAssertHelper.AssertFrontVelocity(
                4.3, 1.1, grassWaveRunupRayleighDiscreteLocationDependentInputItem2);

            var asphaltWaveImpactLocationDependentInputItem =
                locationDependentInputItems[5] as AsphaltWaveImpactLocationDependentInput;
            Assert.That(asphaltWaveImpactLocationDependentInputItem, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                39, asphaltWaveImpactLocationDependentInputItem);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0, 1, asphaltWaveImpactLocationDependentInputItem);
            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                1.56, 1025, 56, 1, 1, 0.35, asphaltWaveImpactLocationDependentInputItem);
            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                0.16, 18214, asphaltWaveImpactLocationDependentInputItem.UpperLayer);
            Assert.That(asphaltWaveImpactLocationDependentInputItem.SubLayer, Is.Null);
            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertFatigue(
                0.42, 4.76, asphaltWaveImpactLocationDependentInputItem.Fatigue);
            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertFactors(
                new List<(double, double)>
                {
                    (0.1, 0.0392),
                    (0.2, 0.0738),
                    (0.3, 0.1002),
                    (0.4, 0.1162),
                    (0.5, 0.1213),
                    (0.6, 0.1168),
                    (0.7, 0.1051),
                    (0.8, 0.089),
                    (0.9, 0.0712),
                    (1, 0.0541),
                    (1.1, 0.0391),
                    (1.2, 0.0269),
                    (1.3, 0.0216),
                    (1.4, 0.015),
                    (1.5, 0.0105)
                }, new List<(double, double)>
                {
                    (-1, 0.005040816326530646),
                    (-0.9744897959183674, 0.00596482278562177),
                    (-0.9489795918367347, 0.007049651822326582),
                    (-0.923469387755102, 0.008280657034496978),
                    (-0.8979591836734694, 0.009643192019984783),
                    (-0.8724489795918368, 0.011122610376641823),
                    (-0.846938775510204, 0.012704265702320014),
                    (-0.8214285714285714, 0.014373511594871225),
                    (-0.7959183673469388, 0.016115701652147284),
                    (-0.7704081632653061, 0.017916189471999994),
                    (-0.7448979591836735, 0.019760328652281334),
                    (-0.7193877551020409, 0.02163347279084307),
                    (-0.6938775510204082, 0.02352097548553716),
                    (-0.6683673469387754, 0.025408190334215378),
                    (-0.6428571428571429, 0.027280470934729583),
                    (-0.6173469387755102, 0.029123170884931715),
                    (-0.5918367346938775, 0.030921643782673508),
                    (-0.5663265306122449, 0.03266124322580695),
                    (-0.5408163265306123, 0.034327322812183814),
                    (-0.5153061224489797, 0.03590523613965599),
                    (-0.4897959183673469, 0.036419783440920166),
                    (-0.4642857142857143, 0.03634372210983519),
                    (-0.4387755102040817, 0.03603984556448696),
                    (-0.41326530612244894, 0.0355249692161967),
                    (-0.3877551020408163, 0.03481590847628564),
                    (-0.3622448979591837, 0.033929478756075014),
                    (-0.33673469387755095, 0.032882495466886014),
                    (-0.31122448979591844, 0.03169177402003989),
                    (-0.2857142857142858, 0.03037412982685786),
                    (-0.2602040816326531, 0.028946378298661132),
                    (-0.23469387755102034, 0.02742533484677094),
                    (-0.2091836734693877, 0.02582781488250851),
                    (-0.1836734693877552, 0.024170633817195083),
                    (-0.15816326530612246, 0.022470607062151843),
                    (-0.13265306122448983, 0.02074455002870004),
                    (-0.1071428571428571, 0.019009278128160882),
                    (-0.08163265306122447, 0.01728160677185561),
                    (-0.056122448979591955, 0.015578351371105446),
                    (-0.030612244897959218, 0.01391632733723159),
                    (-0.005102040816326481, 0.012312350081555283),
                    (0.020408163265306145, 0.010783235015397755),
                    (0.04591836734693877, 0.00934579755008022),
                    (0.0714285714285714, 0.008016853096923902),
                    (0.09693877551020402, 0.006813217067250026),
                    (0.12244897959183665, 0.005751704872379814),
                    (0.1479591836734695, 0.004849131923634483),
                    (0.17346938775510212, 0.004122313632335269),
                    (0.19897959183673475, 0.0035880654098033892),
                    (0.22448979591836737, 0.003263202667360069),
                    (0.25, 0.0031645408163265307)
                }, new List<(double, double)>
                {
                    (2, 0.039),
                    (2.4, 0.1),
                    (2.8, 0.18),
                    (3.2, 0.235),
                    (3.6, 0.2),
                    (4, 0.13),
                    (4.4, 0.08),
                    (4.8, 0.02),
                    (5.2, 0.01),
                    (5.6, 0.005),
                    (6, 0.001)
                },
                asphaltWaveImpactLocationDependentInputItem);

            var grassWaveOvertoppingRayleighDiscreteLocationDependentInput1 =
                locationDependentInputItems[6] as GrassWaveOvertoppingRayleighDiscreteLocationDependentInput;
            Assert.That(grassWaveOvertoppingRayleighDiscreteLocationDependentInput1, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                65, grassWaveOvertoppingRayleighDiscreteLocationDependentInput1);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0, 1, grassWaveOvertoppingRayleighDiscreteLocationDependentInput1);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertGeneralProperties(
                null, grassWaveOvertoppingRayleighDiscreteLocationDependentInput1);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, grassWaveOvertoppingRayleighDiscreteLocationDependentInput1);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, grassWaveOvertoppingRayleighDiscreteLocationDependentInput1);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, grassWaveOvertoppingRayleighDiscreteLocationDependentInput1);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertFrontVelocity(
                6.6, 1.45, grassWaveOvertoppingRayleighDiscreteLocationDependentInput1);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1, 1.4, grassWaveOvertoppingRayleighDiscreteLocationDependentInput1.AccelerationAlphaA);

            var grassWaveOvertoppingRayleighDiscreteLocationDependentInput2 =
                locationDependentInputItems[7] as GrassWaveOvertoppingRayleighDiscreteLocationDependentInput;
            Assert.That(grassWaveOvertoppingRayleighDiscreteLocationDependentInput2, Is.Not.Null);
            LocationDependentInputAssertHelper.AssertLocationProperties(
                85, grassWaveOvertoppingRayleighDiscreteLocationDependentInput2);
            LocationDependentInputAssertHelper.AssertDamageProperties(
                0, 1, grassWaveOvertoppingRayleighDiscreteLocationDependentInput2);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertGeneralProperties(
                null, grassWaveOvertoppingRayleighDiscreteLocationDependentInput2);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, grassWaveOvertoppingRayleighDiscreteLocationDependentInput2);
            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, grassWaveOvertoppingRayleighDiscreteLocationDependentInput2);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, grassWaveOvertoppingRayleighDiscreteLocationDependentInput2);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertFrontVelocity(
                4.3, 1.45, grassWaveOvertoppingRayleighDiscreteLocationDependentInput2);
            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1, 1.4, grassWaveOvertoppingRayleighDiscreteLocationDependentInput2.AccelerationAlphaA);

            Assert.That(result.LocationIds, Is.Not.Null);
            Assert.That(result.LocationIds.All(lid => !lid.HasValue), Is.True);
        }

        [Test]
        public void
            GivenJsonInputWithGrassWaveRunupNoCalculationMethod_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            GivenInvalidJsonInputFile_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent(
                "GrassWaveRunupNoCalculationMethod.json",
                "An unhandled error occurred while composing calculation data from the Json input. See stack trace " +
                $"for more information:{Environment.NewLine}Cannot convert protocol type.");
        }

        [Test]
        public void GivenNotExistingJsonInputFile_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            GivenInvalidJsonInputFile_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent(
                "NotExisting.json", "The provided input file does not exist");
        }

        [Test]
        public void GivenCompleteAndValidJsonInputFile_WhenValidatingJson_ThenReturnsTrueAndNoEventsRegistered()
        {
            // Given
            string filePath = Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test"),
                                           "JsonInputComposerTest", "InputWithAllData.json");

            // When
            bool result = JsonInputComposer.ValidateJson(filePath);

            // Then
            Assert.That(result, Is.True);

            Assert.That(EventRegistry.Flush(), Is.Empty);
        }

        [Test]
        public void GivenInvalidlyFormattedJsonInputFile_WhenValidatingJson_ThenReturnsFalseAndExpectedEventsRegistered()
        {
            // Given
            string filePath = Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test"),
                                           "JsonInputComposerTest", "InvalidFormat.json");

            // When
            bool result = JsonInputComposer.ValidateJson(filePath);

            // Then
            Assert.That(result, Is.False);

            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();
            Assert.That(registeredEvents, Has.Count.EqualTo(1));
            Assert.That(registeredEvents[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(registeredEvents[0].Message, Is.EqualTo("The provided input file is invalid (error found on line 4, position 8)"));
        }

        [Test]
        public void GivenIncompleteJsonInputFile_WhenValidatingJson_ThenReturnsFalseAndExpectedEventsRegistered()
        {
            // Given
            string filePath = Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test"),
                                           "JsonInputComposerTest", "Incomplete.json");

            // When
            bool result = JsonInputComposer.ValidateJson(filePath);

            // Then
            Assert.That(result, Is.False);

            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();
            Assert.That(registeredEvents, Has.Count.EqualTo(1));
            Assert.That(registeredEvents[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(registeredEvents[0].Message, Is.EqualTo("Required properties are missing from object: tijdstippen, " +
                                                                "hydraulischeBelastingen, dijkprofiel, locaties."));
        }

        [Test]
        public void GivenNotExistingJsonInputFile_WhenValidatingJson_ThenReturnsFalseAndExpectedEventsRegistered()
        {
            // Given
            const string filePath = "NotExisting.json";

            // When
            bool result = JsonInputComposer.ValidateJson(filePath);

            // Then
            Assert.That(result, Is.False);

            IReadOnlyList<Event> registeredEvents = EventRegistry.Flush();
            Assert.That(registeredEvents, Has.Count.EqualTo(1));
            Assert.That(registeredEvents[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(registeredEvents[0].Message, Is.EqualTo("The provided input file does not exist"));
        }

        private static void GivenInvalidJsonInputFile_WhenGetInputDataFromJson_ThenReturnsResultWithSuccessfulFalseAndEvent(
            string fileName, string expectedMessage)
        {
            // Given
            string filePath = Path.Combine(TestDataPathHelper.GetTestDataPath("DiKErnel.KernelWrapper.Json.Input.Test"),
                                           "JsonInputComposerTest", fileName);

            // When
            ComposedInputData result = JsonInputComposer.GetInputDataFromJson(filePath);

            // Then
            DataResult<ICalculationInput> calculationInputDataResult = result.CalculationInputDataResult;

            Assert.That(calculationInputDataResult.Successful, Is.False);

            Assert.That(calculationInputDataResult.Events, Has.Count.EqualTo(1));
            Assert.That(calculationInputDataResult.Events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(calculationInputDataResult.Events[0].Message, Is.EqualTo(expectedMessage));

            Assert.That(result.LocationIds, Is.Empty);
        }
    }
}