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

using System;
using System.Collections.Generic;
using DiKErnel.Core.Data;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneRevetment;
using DiKErnel.Integration.TestUtil;
using DiKErnel.Util;
using DiKErnel.Util.Helpers;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Integration.Test
{
    [TestFixture]
    public class CalculationInputBuilderTest
    {
        private static void AssertResultWithSuccessfulFalseAndEvent(SimpleResult result, string expectedMessage)
        {
            Assert.IsFalse(result.Successful);

            IReadOnlyList<Event> events = result.Events;
            Assert.AreEqual(1, events.Count);
            Assert.AreEqual(EventType.Error, events[0].Type);
            Assert.AreEqual(expectedMessage, events[0].Message);
        }

        private static void AddDefaultProfileAndTimeStep(CalculationInputBuilder builder)
        {
            const double startPointX = 0;
            const double endPointX = 10;

            builder.AddDikeProfileSegment(startPointX, 10, endPointX, 20);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
        }

        private static void GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
            Action<CalculationInputBuilder> addLocationAction, double locationX)
        {
            GivenLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                addLocationAction, "The location with position " + NumericsHelper.ToString(locationX) + " must be " +
                                   "between the outer toe and outer crest.");
        }

        private static void GivenLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
            Action<CalculationInputBuilder> addLocationAction, string expectedMessage)
        {
            // Given
            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            addLocationAction(builder);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, expectedMessage);
        }

        private static void GivenGrassOvertoppingLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
            double locationX)
        {
            GivenLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddDikeProfileSegment(10, 20, 30, 40);
                    builder.AddDikeProfileSegment(30, 40, 50, 60);
                    builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
                    builder.AddDikeProfilePoint(50, CharacteristicPointType.InnerToe);
                    builder.AddGrassOvertoppingLocation(new GrassRevetmentOvertoppingLocationConstructionProperties(
                                                            locationX,
                                                            Random.NextEnumValue<GrassRevetmentTopLayerType>()));
                },
                "The location with position " + NumericsHelper.ToString(locationX) + " must be on or between the " +
                "outer crest and inner toe.");
        }

        #region Profile segments

        [Test]
        public void GivenBuilderWithoutDikeProfileSegments_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "At least 1 profile segment is required.");
        }

        [Test]
        public void
            GivenBuilderWithDikeProfileSegmentsAdded_WhenProfileSegmentXCoordinateUnchained_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(10, 20, 20, 30);
            builder.AddDikeProfileSegment(20.01, 30, 30, 40);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The start point of the profile segment (20.01, 30) must be equal to the end point of the " +
                        "previous profile segment (20, 30).");
        }

        [Test]
        public void
            GivenBuilderWithDikeProfileSegmentsAdded_WhenProfileSegmentZCoordinateUnchained_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(10, 20, 20, 30);
            builder.AddDikeProfileSegment(20, 30.01, 30, 40);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The start point of the profile segment (20, 30.01) must be equal to the end point of the " +
                        "previous profile segment (20, 30).");
        }

        [Test]
        public void GivenBuilderWithDikeProfileSegmentAddedWithoutRoughness_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const double startPointX = 10;
            const double startPointZ = 20;
            const double endPointX = 20;
            const double endPointZ = 30;

            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassRevetmentWaveImpactLocationConstructionProperties(
                                                   10.1, GrassRevetmentTopLayerType.ClosedSod));
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ProfileSegment> actualProfileSegments = result.Data.ProfileData.ProfileSegments;
            Assert.AreEqual(1, actualProfileSegments.Count);

            ProfileDataAssertHelper.AssertProfileSegment(startPointX, startPointZ, endPointX, endPointZ, 1.0,
                                                         actualProfileSegments[0]);
        }

        [Test]
        public void GivenBuilderWithDikeProfileSegmentAddedWithRoughness_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const double startPointX = 10;
            const double startPointZ = 20;
            const double endPointX = 20;
            const double endPointZ = 30;
            double roughnessCoefficient = Random.NextDouble();

            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, roughnessCoefficient);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassRevetmentWaveImpactLocationConstructionProperties(
                                                   10.1, GrassRevetmentTopLayerType.ClosedSod));
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ProfileSegment> actualProfileSegments = result.Data.ProfileData.ProfileSegments;
            Assert.AreEqual(1, actualProfileSegments.Count);

            ProfileDataAssertHelper.AssertProfileSegment(startPointX, startPointZ, endPointX, endPointZ,
                                                         roughnessCoefficient, actualProfileSegments[0]);
        }

        [Test]
        public void GivenBuilderWithDikeProfileSegmentsAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const double startPointXSegment1 = 10;
            const double startPointZSegment1 = 20;
            const double endPointXSegment1 = 20;
            const double endPointZSegment1 = 30;
            const double endPointXSegment2 = 30;
            const double endPointZSegment2 = 40;
            double roughnessCoefficient = Random.NextDouble();

            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(startPointXSegment1, startPointZSegment1, endPointXSegment1,
                                          endPointZSegment1, roughnessCoefficient);
            builder.AddDikeProfileSegment(endPointXSegment1, endPointZSegment1, endPointXSegment2, endPointZSegment2,
                                          roughnessCoefficient);
            builder.AddDikeProfilePoint(startPointXSegment1, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointXSegment1, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassRevetmentWaveImpactLocationConstructionProperties(
                                                   10.1, GrassRevetmentTopLayerType.ClosedSod));
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ProfileSegment> actualProfileSegments = result.Data.ProfileData.ProfileSegments;
            Assert.AreEqual(2, actualProfileSegments.Count);

            ProfileDataAssertHelper.AssertProfileSegment(startPointXSegment1, startPointZSegment1, endPointXSegment1,
                                                         endPointZSegment1, roughnessCoefficient,
                                                         actualProfileSegments[0]);

            ProfileDataAssertHelper.AssertProfileSegment(endPointXSegment1, endPointZSegment1, endPointXSegment2,
                                                         endPointZSegment2, roughnessCoefficient,
                                                         actualProfileSegments[1]);

            Assert.AreSame(actualProfileSegments[0].EndPoint, actualProfileSegments[1].StartPoint);
        }

        #endregion

        #region Profile points

        [Test]
        public void
            GivenBuilderWithDikeProfilePointDataOuterToeNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 20, 30);
            builder.AddDikeProfilePoint(10.01, CharacteristicPointType.OuterToe);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The outer toe must be on a start or end point of a profile segment.");
        }

        [Test]
        public void
            GivenBuilderWithDikeProfilePointDataCrestOuterBermNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 20, 30);
            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(10.01, CharacteristicPointType.CrestOuterBerm);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The crest outer berm must be on a start or end point of a profile segment.");
        }

        [Test]
        public void
            GivenBuilderWithDikeProfilePointDataNotchOuterBermNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 20, 30);
            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(10.01, CharacteristicPointType.NotchOuterBerm);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The notch outer berm must be on a start or end point of a profile segment.");
        }

        [Test]
        public void
            GivenBuilderWithDikeProfilePointDataOuterCrestNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 20, 30);
            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(10.01, CharacteristicPointType.OuterCrest);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The outer crest must be on a start or end point of a profile segment.");
        }

        [Test]
        public void
            GivenBuilderWithDikeProfilePointDataInnerCrestNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 20, 30);
            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(20.01, CharacteristicPointType.InnerCrest);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The inner crest must be on a start or end point of a profile segment.");
        }

        [Test]
        public void
            GivenBuilderWithDikeProfilePointDataInnerToeNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 20, 30);
            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(20.01, CharacteristicPointType.InnerToe);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The inner toe must be on a start or end point of a profile segment.");
        }

        [Test]
        public void GivenBuilderWithoutDikeProfilePointDataOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 10, 30);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterCrest);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "The outer toe is required.");
        }

        [Test]
        public void GivenBuilderWithoutDikeProfilePointDataOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 10, 30);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "The outer crest is required.");
        }

        [Test]
        public void
            GivenBuilderWithGrassOvertoppingLocationAndWithoutDikeProfilePointDataInnerToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const int startPointX = 10;

            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, startPointX, 30);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.InnerCrest);
            builder.AddGrassOvertoppingLocation(new GrassRevetmentOvertoppingLocationConstructionProperties(
                                                    0.1, GrassRevetmentTopLayerType.ClosedSod));

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "The inner toe is required.");
        }

        [Test]
        public void
            GivenBuilderWithGrassOvertoppingLocationAndWithoutDikeProfilePointDataInnerCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const int startPointX = 10;

            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, startPointX, 30);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(new GrassRevetmentOvertoppingLocationConstructionProperties(
                                                    0.1, GrassRevetmentTopLayerType.ClosedSod));

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "The inner crest is required.");
        }

        [Test]
        public void GivenBuilderWithDikeProfilePointDataOnSegmentPoints_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const CharacteristicPointType outerToe = CharacteristicPointType.OuterToe;
            const CharacteristicPointType outerCrest = CharacteristicPointType.OuterCrest;

            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(10, 20, 20, 30);
            builder.AddDikeProfilePoint(10, outerToe);
            builder.AddDikeProfilePoint(20, outerCrest);
            builder.AddGrassWaveImpactLocation(new GrassRevetmentWaveImpactLocationConstructionProperties(
                                                   10.1, GrassRevetmentTopLayerType.ClosedSod));
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IProfileData actualProfileData = result.Data.ProfileData;
            IReadOnlyList<ProfileSegment> actualProfileSegments = actualProfileData.ProfileSegments;
            IReadOnlyList<CharacteristicPoint> actualCharacteristicPoints = actualProfileData.CharacteristicPoints;
            Assert.AreEqual(1, actualProfileSegments.Count);
            Assert.AreEqual(2, actualCharacteristicPoints.Count);

            ProfileSegment actualSegment = actualProfileSegments[0];
            ProfileDataAssertHelper.AssertCharacteristicPoint(actualSegment.StartPoint, outerToe,
                                                              actualCharacteristicPoints[0]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(actualSegment.EndPoint, outerCrest,
                                                              actualCharacteristicPoints[1]);
        }

        #endregion

        #region Time steps

        [Test]
        public void GivenBuilderWithoutTimeStepAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 10, 20);
            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassRevetmentWaveImpactLocationConstructionProperties(
                                                   0.1, GrassRevetmentTopLayerType.ClosedSod));

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "At least 1 time step is required.");
        }

        [Test]
        public void GivenBuilderWithNonSuccessiveTimeStepsAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 10, 20);
            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassRevetmentWaveImpactLocationConstructionProperties(
                                                   0.1, GrassRevetmentTopLayerType.ClosedSod));
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);
            builder.AddTimeStep(3, 4, 0.3, 0.4, 0.5, 0.6);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The begin time of the time step (3) must be equal to the end time of the previous time " +
                        "step (2).");
        }

        [Test]
        public void GivenBuilderWithTimeStepWithInvalidBeginAndEndTimeAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(0, 10, 10, 20);
            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassRevetmentWaveImpactLocationConstructionProperties(
                                                   0.1, GrassRevetmentTopLayerType.ClosedSod));
            builder.AddTimeStep(2, 1, 0.3, 0.4, 0.5, 0.6);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The begin time of the time step (2) must be smaller than the end time of the time step (1).");
        }

        [Test]
        public void GivenBuilderWithTimeStepAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const int beginTime = 1;
            const int endTime = 2;
            const double waterLevel = 0.3;
            const double waveHeightHm0 = 0.4;
            const double wavePeriodTm10 = 0.5;
            const double waveAngle = 0.6;

            const double startPointX = 0;
            const double endPointX = 10;

            var builder = new CalculationInputBuilder();
            builder.AddDikeProfileSegment(startPointX, 10, endPointX, 20);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassRevetmentWaveImpactLocationConstructionProperties(
                                                   0.1, GrassRevetmentTopLayerType.ClosedSod));
            builder.AddTimeStep(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveAngle);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ITimeDependentInput> actualTimeDependentInputItems = result.Data.TimeDependentInputItems;
            Assert.AreEqual(1, actualTimeDependentInputItems.Count);

            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(beginTime, endTime, waterLevel, waveHeightHm0,
                                                                        wavePeriodTm10, waveAngle,
                                                                        actualTimeDependentInputItems[0]);
        }

        #endregion

        #region Locations

        [Test]
        public void GivenBuilderWithoutLocationAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "At least 1 location is required.");
        }

        #region Asphalt wave impact

        [Test]
        public void GivenBuilderWithAsphaltWaveImpactLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 0;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddAsphaltWaveImpactLocation(
                        new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                            locationX, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 0.2, 0.3, 0.4, 0.5));
                }, locationX);
        }

        [Test]
        public void GivenBuilderWithAsphaltWaveImpactLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 10;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddAsphaltWaveImpactLocation(
                        new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                            locationX, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 0.2, 0.3, 0.4, 0.5));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithAsphaltWaveImpactLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const AsphaltRevetmentTopLayerType topLayerType = (AsphaltRevetmentTopLayerType) 99;
            var constructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                0.1, topLayerType, 0.2, 0.3, 0.4, 0.5);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddAsphaltWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The location with position 0.1 has an invalid top layer type.");
        }

        [Test]
        public void GivenBuilderWithFullyConfiguredAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            var topLayerType = Random.NextEnumValue<AsphaltRevetmentTopLayerType>();
            const double x = 5;
            double failureTension = Random.NextDouble();
            double soilElasticity = Random.NextDouble();
            double thicknessUpperLayer = Random.NextDouble();
            double elasticModulusUpperLayer = Random.NextDouble();
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double densityOfWater = Random.NextDouble();
            double thicknessSubLayer = Random.NextDouble();
            double elasticModulusSubLayer = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            double fatigueAlpha = Random.NextDouble();
            double fatigueBeta = Random.NextDouble();
            double impactNumberC = Random.NextDouble();
            double stiffnessRelationNu = Random.NextDouble();
            var widthFactors = new List<(double, double)>
            {
                (Random.NextDouble(), Random.NextDouble())
            };
            var depthFactors = new List<(double, double)>
            {
                (Random.NextDouble(), Random.NextDouble())
            };
            var impactFactors = new List<(double, double)>
            {
                (Random.NextDouble(), Random.NextDouble())
            };

            var constructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                x, topLayerType, failureTension, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer)
            {
                InitialDamage = initialDamage,
                FailureNumber = failureNumber,
                DensityOfWater = densityOfWater,
                ThicknessSubLayer = thicknessSubLayer,
                ElasticModulusSubLayer = elasticModulusSubLayer,
                AverageNumberOfWavesCtm = averageNumberOfWavesCtm,
                FatigueAlpha = fatigueAlpha,
                FatigueBeta = fatigueBeta,
                ImpactNumberC = impactNumberC,
                StiffnessRelationNu = stiffnessRelationNu,
                WidthFactors = widthFactors,
                DepthFactors = depthFactors,
                ImpactFactors = impactFactors
            };

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddAsphaltWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as AsphaltRevetmentWaveImpactLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, failureTension, densityOfWater, soilElasticity, averageNumberOfWavesCtm,
                impactNumberC, stiffnessRelationNu, locationDependentInput);

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                thicknessUpperLayer, elasticModulusUpperLayer, locationDependentInput.UpperLayer);

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                thicknessSubLayer, elasticModulusSubLayer, locationDependentInput.SubLayer);

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertFatigue(
                fatigueAlpha, fatigueBeta, locationDependentInput.Fatigue);

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertFactors(
                widthFactors, depthFactors, impactFactors, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredHydraulicAsphaltConcreteAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            const AsphaltRevetmentTopLayerType topLayerType = AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete;
            const double x = 5;
            double failureTension = Random.NextDouble();
            double soilElasticity = Random.NextDouble();
            double thicknessUpperLayer = Random.NextDouble();
            double elasticModulusUpperLayer = Random.NextDouble();

            var constructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                x, topLayerType, failureTension, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddAsphaltWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as AsphaltRevetmentWaveImpactLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, failureTension, 1025, soilElasticity, 1, 1, 0.35, locationDependentInput);

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                thicknessUpperLayer, elasticModulusUpperLayer, locationDependentInput.UpperLayer);

            Assert.IsNull(locationDependentInput.SubLayer);

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertFatigue(
                0.42, 4.76, locationDependentInput.Fatigue);

            var expectedWidthFactors = new List<(double, double)>
            {
                (0.1, 0.0392),
                (0.2, 0.0738),
                (0.3, 0.1002),
                (0.4, 0.1162),
                (0.5, 0.1213),
                (0.6, 0.1168),
                (0.7, 0.1051),
                (0.8, 0.0890),
                (0.9, 0.0712),
                (1.0, 0.0541),
                (1.1, 0.0391),
                (1.2, 0.0269),
                (1.3, 0.0216),
                (1.4, 0.0150),
                (1.5, 0.0105)
            };

            var expectedDepthFactors = new List<(double, double)>
            {
                (-1.0, 0.0244),
                (-0.875, 0.0544),
                (-0.750, 0.0938),
                (-0.625, 0.1407),
                (-0.500, 0.1801),
                (-0.375, 0.1632),
                (-0.250, 0.1426),
                (-0.125, 0.0994),
                (0.0, 0.06),
                (0.125, 0.0244),
                (0.250, 0.0169)
            };

            var expectedImpactFactors = new List<(double, double)>
            {
                (2.0, 0.039),
                (2.4, 0.1),
                (2.8, 0.18),
                (3.2, 0.235),
                (3.6, 0.2),
                (4.0, 0.13),
                (4.4, 0.08),
                (4.8, 0.02),
                (5.2, 0.01),
                (5.6, 0.005),
                (6.0, 0.001)
            };

            AsphaltRevetmentWaveImpactLocationDependentInputAssertHelper.AssertFactors(
                expectedWidthFactors, expectedDepthFactors, expectedImpactFactors, locationDependentInput);
        }

        #endregion

        #region Grass overtopping

        [Test]
        public void GivenBuilderWithGrassOvertoppingLocationWithXLeftFromOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            GivenGrassOvertoppingLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(9.9);
        }

        [Test]
        public void
            GivenBuilderWithGrassOvertoppingLocationWithXRightFromOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            GivenGrassOvertoppingLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(50.1);
        }

        [Test]
        public void GivenBuilderWithGrassOvertoppingLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const GrassRevetmentTopLayerType topLayerType = (GrassRevetmentTopLayerType) 99;
            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(45, topLayerType);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, 30, 40);
            builder.AddDikeProfileSegment(30, 40, 50, 60);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(50, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The location with position 45 has an invalid top layer type.");
        }

        [Test]
        public void GivenBuilderWithGrassOvertoppingLocationWithInvalidGeometry_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(45, topLayerType);

            const double outerToeX = 0;
            const double outerCrestX = 30;

            var builder = new CalculationInputBuilder();
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20);
            builder.AddDikeProfileSegment(10, 20, 20, 20);
            builder.AddDikeProfileSegment(20, 20, outerCrestX, 10);
            builder.AddDikeProfileSegment(30, 10, 40, 40);
            builder.AddDikeProfileSegment(40, 40, 50, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(outerCrestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(50, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsFalse(result.Successful);

            IReadOnlyList<Event> events = result.Events;
            Assert.AreEqual(1, events.Count);
            Assert.AreEqual(EventType.Error, events[0].Type);
            Assert.IsNotEmpty(events[0].Message);
        }

        [Test]
        public void
            GivenBuilderWithGrassOvertoppingLocationWithInvalidRoughnessCoefficients_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(45, topLayerType);

            const double outerToeX = 0;
            const double outerCrestX = 30;

            var builder = new CalculationInputBuilder();
            builder.AddTimeStep(1, 2, 0.3, 0.4, 0.5, 0.6);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20, 0.4);
            builder.AddDikeProfileSegment(10, 20, outerCrestX, 25, 1.1);
            builder.AddDikeProfileSegment(30, 25, 40, 40);
            builder.AddDikeProfileSegment(40, 40, 50, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(outerCrestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(50, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsFalse(result.Successful);

            IReadOnlyList<Event> events = result.Events;
            Assert.AreEqual(2, events.Count);
            Assert.AreEqual(EventType.Error, events[0].Type);
            Assert.IsNotEmpty(events[0].Message);
            Assert.AreEqual(EventType.Error, events[1].Type);
            Assert.IsNotEmpty(events[1].Message);
        }

        [Test]
        public void GivenBuilderWithFullyConfiguredGrassOvertoppingLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            const double x = 45;
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double criticalCumulativeOverload = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            int fixedNumberOfWaves = Random.Next();
            double frontVelocityCwo = Random.NextDouble();
            double accelerationAlphaAForCrest = Random.NextDouble();
            double accelerationAlphaAForInnerSlope = Random.NextDouble();
            double dikeHeight = Random.NextDouble();

            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(x, topLayerType)
            {
                InitialDamage = initialDamage,
                FailureNumber = failureNumber,
                CriticalCumulativeOverload = criticalCumulativeOverload,
                CriticalFrontVelocity = criticalFrontVelocity,
                IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS,
                AverageNumberOfWavesCtm = averageNumberOfWavesCtm,
                FixedNumberOfWaves = fixedNumberOfWaves,
                FrontVelocityCwo = frontVelocityCwo,
                AccelerationAlphaAForCrest = accelerationAlphaAForCrest,
                AccelerationAlphaAForInnerSlope = accelerationAlphaAForInnerSlope,
                DikeHeight = dikeHeight
            };

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, 30, 40);
            builder.AddDikeProfileSegment(30, 40, 50, 60);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(50, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassRevetmentOvertoppingLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, dikeHeight, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertTransitionAlpha(
                increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                averageNumberOfWavesCtm, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertCumulativeOverload(
                criticalCumulativeOverload, fixedNumberOfWaves, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertFrontVelocity(
                criticalFrontVelocity, frontVelocityCwo, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                accelerationAlphaAForCrest, accelerationAlphaAForInnerSlope,
                locationDependentInput.LocationDependentAccelerationAlphaA);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredClosedSodGrassOvertoppingLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassRevetmentTopLayerType topLayerType = GrassRevetmentTopLayerType.ClosedSod;
            const double x = 45;

            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(x, topLayerType);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, 30, 40);
            builder.AddDikeProfileSegment(30, 40, 50, 60);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(50, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassRevetmentOvertoppingLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, null, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertFrontVelocity(
                6.6, 1.45, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1.0, 1.4, locationDependentInput.LocationDependentAccelerationAlphaA);
        }

        [Test]
        public void GivenBuilderWithNotFullyConfiguredOpenSodGrassOvertoppingLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassRevetmentTopLayerType topLayerType = GrassRevetmentTopLayerType.OpenSod;
            const double x = 45;

            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(x, topLayerType);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, 30, 40);
            builder.AddDikeProfileSegment(30, 40, 50, 60);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(50, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassRevetmentOvertoppingLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, null, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertFrontVelocity(
                4.3, 1.45, locationDependentInput);

            GrassRevetmentOvertoppingLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1.0, 1.4, locationDependentInput.LocationDependentAccelerationAlphaA);
        }

        #endregion

        #region Grass wave impact

        [Test]
        public void GivenBuilderWithGrassWaveImpactLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 0;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveImpactLocation(
                        new GrassRevetmentWaveImpactLocationConstructionProperties(
                            locationX, GrassRevetmentTopLayerType.ClosedSod));
                }, locationX);
        }

        [Test]
        public void GivenBuilderWithGrassWaveImpactLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 10;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveImpactLocation(
                        new GrassRevetmentWaveImpactLocationConstructionProperties(
                            locationX, GrassRevetmentTopLayerType.ClosedSod));
                }, locationX);
        }

        [Test]
        public void GivenBuilderWithGrassWaveImpactLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const GrassRevetmentTopLayerType topLayerType = (GrassRevetmentTopLayerType) 99;
            var constructionProperties = new GrassRevetmentWaveImpactLocationConstructionProperties(0.1, topLayerType);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The location with position 0.1 has an invalid top layer type.");
        }

        [Test]
        public void GivenBuilderWithFullyConfiguredGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            const int x = 5;
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double timeLineAgwi = Random.NextDouble();
            double timeLineBgwi = Random.NextDouble();
            double timeLineCgwi = Random.NextDouble();
            double minimumWaveHeightTemax = Random.NextDouble();
            double maximumWaveHeightTemin = Random.NextDouble();
            double waveAngleImpactNwa = Random.NextDouble();
            double waveAngleImpactQwa = Random.NextDouble();
            double waveAngleImpactRwa = Random.NextDouble();
            double upperLimitLoadingAul = Random.NextDouble();
            double lowerLimitLoadingAll = Random.NextDouble();

            var constructionProperties = new GrassRevetmentWaveImpactLocationConstructionProperties(x, topLayerType)
            {
                InitialDamage = initialDamage,
                FailureNumber = failureNumber,
                TimeLineAgwi = timeLineAgwi,
                TimeLineBgwi = timeLineBgwi,
                TimeLineCgwi = timeLineCgwi,
                MinimumWaveHeightTemax = minimumWaveHeightTemax,
                MaximumWaveHeightTemin = maximumWaveHeightTemin,
                WaveAngleImpactNwa = waveAngleImpactNwa,
                WaveAngleImpactQwa = waveAngleImpactQwa,
                WaveAngleImpactRwa = waveAngleImpactRwa,
                UpperLimitLoadingAul = upperLimitLoadingAul,
                LowerLimitLoadingAll = lowerLimitLoadingAll
            };

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassRevetmentWaveImpactLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                minimumWaveHeightTemax, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                maximumWaveHeightTemin, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                waveAngleImpactNwa, waveAngleImpactQwa, waveAngleImpactRwa, locationDependentInput.WaveAngleImpact);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                timeLineAgwi, timeLineBgwi, timeLineCgwi, locationDependentInput.TimeLine);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                upperLimitLoadingAul, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                lowerLimitLoadingAll, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassRevetmentTopLayerType topLayerType = GrassRevetmentTopLayerType.ClosedSod;
            const int x = 5;

            var constructionProperties = new GrassRevetmentWaveImpactLocationConstructionProperties(x, topLayerType);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassRevetmentWaveImpactLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                3600000, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                3.6, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                2.0 / 3.0, 0.35, 10, locationDependentInput.WaveAngleImpact);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                1, -0.000009722, 0.25, locationDependentInput.TimeLine);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                0, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                0.5, locationDependentInput);
        }

        [Test]
        public void GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassRevetmentTopLayerType topLayerType = GrassRevetmentTopLayerType.OpenSod;
            const int x = 5;

            var constructionProperties = new GrassRevetmentWaveImpactLocationConstructionProperties(x, topLayerType);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassRevetmentWaveImpactLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                3600000, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                3.6, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                2.0 / 3.0, 0.35, 10, locationDependentInput.WaveAngleImpact);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                0.8, -0.00001944, 0.25, locationDependentInput.TimeLine);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                0, locationDependentInput);

            GrassRevetmentWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                0.5, locationDependentInput);
        }

        #endregion

        #region Grass wave run-up Rayleigh

        [Test]
        public void GivenBuilderWithGrassWaveRunupRayleighLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 0;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveRunupRayleighLocation(
                        new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                            locationX, 0.1, GrassRevetmentTopLayerType.ClosedSod));
                }, locationX);
        }

        [Test]
        public void GivenBuilderWithGrassWaveRunupRayleighLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 10;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveRunupRayleighLocation(
                        new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                            locationX, 0.1, GrassRevetmentTopLayerType.ClosedSod));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupRayleighLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const GrassRevetmentTopLayerType topLayerType = (GrassRevetmentTopLayerType) 99;
            var constructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                0.1, 0.2, topLayerType);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The location with position 0.1 has an invalid top layer type.");
        }

        [Test]
        public void GivenBuilderWithFullyConfiguredGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassRevetmentTopLayerType>();
            const int x = 5;
            double outerSlope = Random.NextDouble();
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double criticalCumulativeOverload = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            double representativeWaveRunup2PAru = Random.NextDouble();
            double representativeWaveRunup2PBru = Random.NextDouble();
            double representativeWaveRunup2PCru = Random.NextDouble();
            double representativeWaveRunup2PGammab = Random.NextDouble();
            double representativeWaveRunup2PGammaf = Random.NextDouble();
            double waveAngleImpactAbeta = Random.NextDouble();
            double waveAngleImpactBetamax = Random.NextDouble();
            int fixedNumberOfWaves = Random.Next();
            double frontVelocityCu = Random.NextDouble();

            var constructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                x, outerSlope, topLayerType)
            {
                InitialDamage = initialDamage,
                FailureNumber = failureNumber,
                CriticalCumulativeOverload = criticalCumulativeOverload,
                CriticalFrontVelocity = criticalFrontVelocity,
                IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS,
                AverageNumberOfWavesCtm = averageNumberOfWavesCtm,
                RepresentativeWaveRunup2PAru = representativeWaveRunup2PAru,
                RepresentativeWaveRunup2PBru = representativeWaveRunup2PBru,
                RepresentativeWaveRunup2PCru = representativeWaveRunup2PCru,
                RepresentativeWaveRunup2PGammab = representativeWaveRunup2PGammab,
                RepresentativeWaveRunup2PGammaf = representativeWaveRunup2PGammaf,
                WaveAngleImpactAbeta = waveAngleImpactAbeta,
                WaveAngleImpactBetamax = waveAngleImpactBetamax,
                FixedNumberOfWaves = fixedNumberOfWaves,
                FrontVelocityCu = frontVelocityCu
            };

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassRevetmentWaveRunupRayleighLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, outerSlope, locationDependentInput);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertRepresentative2P(
                representativeWaveRunup2PAru, representativeWaveRunup2PBru, representativeWaveRunup2PCru,
                representativeWaveRunup2PGammab, representativeWaveRunup2PGammaf,
                locationDependentInput.Representative2P);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                waveAngleImpactAbeta, waveAngleImpactBetamax, locationDependentInput.WaveAngleImpact);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertTransitionAlpha(
                increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, locationDependentInput);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                averageNumberOfWavesCtm, locationDependentInput);

            GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertCumulativeOverload(
                criticalCumulativeOverload, fixedNumberOfWaves, locationDependentInput);

            GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                criticalFrontVelocity, frontVelocityCu, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInpu()
        {
            // Given
            const GrassRevetmentTopLayerType topLayerType = GrassRevetmentTopLayerType.ClosedSod;
            const int x = 5;
            double outerSlope = Random.NextDouble();

            var constructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                x, outerSlope, topLayerType);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassRevetmentWaveRunupRayleighLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, outerSlope, locationDependentInput);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertRepresentative2P(
                1.65, 4, 1.5, 1, 1, locationDependentInput.Representative2P);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                0.0022, 80, locationDependentInput.WaveAngleImpact);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, locationDependentInput);

            GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                6.6, 1.1, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveRunupRayleighLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassRevetmentTopLayerType topLayerType = GrassRevetmentTopLayerType.OpenSod;
            const int x = 5;
            double outerSlope = Random.NextDouble();

            var constructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                x, outerSlope, topLayerType);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassRevetmentWaveRunupRayleighLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, outerSlope, locationDependentInput);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertRepresentative2P(
                1.65, 4, 1.5, 1, 1, locationDependentInput.Representative2P);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                0.0022, 80, locationDependentInput.WaveAngleImpact);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassRevetmentWaveRunupLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, locationDependentInput);

            GrassRevetmentWaveRunupRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                4.3, 1.1, locationDependentInput);
        }

        #endregion

        #region Natural stone

        [Test]
        public void GivenBuilderWithNaturalStoneLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 0;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddNaturalStoneLocation(
                        new NaturalStoneRevetmentLocationConstructionProperties(
                            locationX, NaturalStoneRevetmentTopLayerType.NordicStone, 0.1, 0.2));
                }, locationX);
        }

        [Test]
        public void GivenBuilderWithNaturalStoneLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 10;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddNaturalStoneLocation(
                        new NaturalStoneRevetmentLocationConstructionProperties(
                            locationX, NaturalStoneRevetmentTopLayerType.NordicStone, 0.1, 0.2));
                }, locationX);
        }

        [Test]
        public void GivenBuilderWithNaturalStoneLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const NaturalStoneRevetmentTopLayerType topLayerType = (NaturalStoneRevetmentTopLayerType) 99;
            var constructionProperties = new NaturalStoneRevetmentLocationConstructionProperties(
                0.1, topLayerType, 0.2, 0.3);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddNaturalStoneLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The location with position 0.1 has an invalid top layer type.");
        }

        [Test]
        public void GivenBuilderWithFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<NaturalStoneRevetmentTopLayerType>();
            const int x = 5;
            double thicknessTopLayer = Random.NextDouble();
            double relativeDensity = Random.NextDouble();
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double hydraulicLoadXib = Random.NextDouble();
            double hydraulicLoadAp = Random.NextDouble();
            double hydraulicLoadBp = Random.NextDouble();
            double hydraulicLoadCp = Random.NextDouble();
            double hydraulicLoadNp = Random.NextDouble();
            double hydraulicLoadAs = Random.NextDouble();
            double hydraulicLoadBs = Random.NextDouble();
            double hydraulicLoadCs = Random.NextDouble();
            double hydraulicLoadNs = Random.NextDouble();
            double slopeUpperLevelAus = Random.NextDouble();
            double slopeLowerLevelAls = Random.NextDouble();
            double upperLimitLoadingAul = Random.NextDouble();
            double upperLimitLoadingBul = Random.NextDouble();
            double upperLimitLoadingCul = Random.NextDouble();
            double lowerLimitLoadingAll = Random.NextDouble();
            double lowerLimitLoadingBll = Random.NextDouble();
            double lowerLimitLoadingCll = Random.NextDouble();
            double distanceMaximumWaveElevationAsmax = Random.NextDouble();
            double distanceMaximumWaveElevationBsmax = Random.NextDouble();
            double normativeWidthOfWaveImpactAwi = Random.NextDouble();
            double normativeWidthOfWaveImpactBwi = Random.NextDouble();
            double waveAngleImpactBetamax = Random.NextDouble();

            var constructionProperties = new NaturalStoneRevetmentLocationConstructionProperties(
                x, topLayerType, thicknessTopLayer, relativeDensity);
            constructionProperties.InitialDamage = initialDamage;
            constructionProperties.FailureNumber = failureNumber;
            constructionProperties.HydraulicLoadXib = hydraulicLoadXib;
            constructionProperties.HydraulicLoadAp = hydraulicLoadAp;
            constructionProperties.HydraulicLoadBp = hydraulicLoadBp;
            constructionProperties.HydraulicLoadCp = hydraulicLoadCp;
            constructionProperties.HydraulicLoadNp = hydraulicLoadNp;
            constructionProperties.HydraulicLoadAs = hydraulicLoadAs;
            constructionProperties.HydraulicLoadBs = hydraulicLoadBs;
            constructionProperties.HydraulicLoadCs = hydraulicLoadCs;
            constructionProperties.HydraulicLoadNs = hydraulicLoadNs;
            constructionProperties.SlopeUpperLevelAus = slopeUpperLevelAus;
            constructionProperties.SlopeLowerLevelAls = slopeLowerLevelAls;
            constructionProperties.UpperLimitLoadingAul = upperLimitLoadingAul;
            constructionProperties.UpperLimitLoadingBul = upperLimitLoadingBul;
            constructionProperties.UpperLimitLoadingCul = upperLimitLoadingCul;
            constructionProperties.LowerLimitLoadingAll = lowerLimitLoadingAll;
            constructionProperties.LowerLimitLoadingBll = lowerLimitLoadingBll;
            constructionProperties.LowerLimitLoadingCll = lowerLimitLoadingCll;
            constructionProperties.DistanceMaximumWaveElevationAsmax = distanceMaximumWaveElevationAsmax;
            constructionProperties.DistanceMaximumWaveElevationBsmax = distanceMaximumWaveElevationBsmax;
            constructionProperties.NormativeWidthOfWaveImpactAwi = normativeWidthOfWaveImpactAwi;
            constructionProperties.NormativeWidthOfWaveImpactBwi = normativeWidthOfWaveImpactBwi;
            constructionProperties.WaveAngleImpactBetamax = waveAngleImpactBetamax;

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddNaturalStoneLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as NaturalStoneRevetmentLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, relativeDensity, thicknessTopLayer, locationDependentInput);

            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertHydraulicLoads(
                hydraulicLoadAp, hydraulicLoadBp, hydraulicLoadCp, hydraulicLoadNp, hydraulicLoadAs, hydraulicLoadBs,
                hydraulicLoadCs, hydraulicLoadNs, hydraulicLoadXib, locationDependentInput.HydraulicLoads);

            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertSlope(
                slopeUpperLevelAus, slopeLowerLevelAls, locationDependentInput.Slope);

            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                upperLimitLoadingAul, upperLimitLoadingBul, upperLimitLoadingCul,
                locationDependentInput.UpperLimitLoading);

            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                lowerLimitLoadingAll, lowerLimitLoadingBll, lowerLimitLoadingCll,
                locationDependentInput.LowerLimitLoading);

            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertDistanceMaximumWaveElevation(
                distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevationBsmax,
                locationDependentInput.DistanceMaximumWaveElevation);

            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertNormativeWidthOfWaveImpact(
                normativeWidthOfWaveImpactAwi, normativeWidthOfWaveImpactBwi,
                locationDependentInput.NormativeWidthOfWaveImpact);

            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                waveAngleImpactBetamax, locationDependentInput.WaveAngleImpact);
        }

        [Test]
        public void GivenBuilderWithNotFullyConfiguredNaturalStoneLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const NaturalStoneRevetmentTopLayerType topLayerType = NaturalStoneRevetmentTopLayerType.NordicStone;
            const int x = 5;
            double thicknessTopLayer = Random.NextDouble();
            double relativeDensity = Random.NextDouble();

            var constructionProperties = new NaturalStoneRevetmentLocationConstructionProperties(
                x, topLayerType, thicknessTopLayer, relativeDensity);

            var builder = new CalculationInputBuilder();
            AddDefaultProfileAndTimeStep(builder);
            builder.AddNaturalStoneLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.IsTrue(result.Successful);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.AreEqual(1, actualLocationDependentInputItems.Count);

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as NaturalStoneRevetmentLocationDependentInput;
            Assert.IsNotNull(locationDependentInput);

            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertGeneralProperties(
                x, relativeDensity, thicknessTopLayer, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertHydraulicLoads(
                4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, locationDependentInput.HydraulicLoads);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertSlope(
                0.05, 1.5, locationDependentInput.Slope);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                0.1, 0.6, 4, locationDependentInput.UpperLimitLoading);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                0.1, 0.2, 4, locationDependentInput.LowerLimitLoading);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertDistanceMaximumWaveElevation(
                0.42, 0.9, locationDependentInput.DistanceMaximumWaveElevation);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertNormativeWidthOfWaveImpact(
                0.96, 0.11, locationDependentInput.NormativeWidthOfWaveImpact);
            NaturalStoneRevetmentLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                78, locationDependentInput.WaveAngleImpact);
        }

        #endregion

        #endregion
    }
}