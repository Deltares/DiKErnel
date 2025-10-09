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
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.Integration.TestUtil;
using DiKErnel.Util;
using DiKErnel.Util.Helpers;
using NUnit.Framework;
using Random = DiKErnel.TestUtil.Random;

namespace DiKErnel.Integration.Test
{
    [TestFixture]
    internal sealed class CalculationInputBuilderTest
    {
        [Test]
        public void GivenBuilderWithValidData_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            double dikeOrientation = Random.NextDouble();

            var builder = new CalculationInputBuilder(dikeOrientation);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   Random.NextDouble(), GrassTopLayerType.ClosedSod));
            AddDefaultProfileAndTimeStep(builder);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            Assert.That(result.Data.ProfileData.DikeOrientation, Is.EqualTo(dikeOrientation));
        }

        private static void AssertResultWithSuccessfulFalseAndEvent(SimpleResult result, string expectedMessage)
        {
            Assert.That(result.Successful, Is.False);

            IReadOnlyList<Event> events = result.Events;
            Assert.That(events, Has.Count.EqualTo(1));
            Assert.That(events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[0].Message, Is.EqualTo(expectedMessage));
        }

        private static void AddDefaultProfileAndTimeStep(CalculationInputBuilder builder)
        {
            const double startPointX = 0;
            const double endPointX = 10;

            builder.AddDikeProfileSegment(startPointX, 10, endPointX, 20);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            AddDefaultTimeStep(builder);
        }

        private static void AddDefaultTimeStep(CalculationInputBuilder builder)
        {
            builder.AddTimeStep(1.1, 2.2, Random.NextDouble(), Random.NextDouble(), Random.NextDouble(), Random.NextDouble());
        }

        private static void AddDefaultForeshore(CalculationInputBuilder builder)
        {
            builder.AddForeshore(Random.NextDouble(), Random.NextDouble());
        }

        private static void GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
            Action<CalculationInputBuilder> addLocationAction, double locationX)
        {
            GivenLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                addLocationAction, "The location with position " + NumericsHelper.ToString(locationX) + " must be " +
                                   "between the outer toe and outer crest.");
        }

        private static void GivenInnerSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
            Action<CalculationInputBuilder> addLocationAction, double locationX)
        {
            GivenLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddDikeProfileSegment(10, 20, 30, 40);
                    builder.AddDikeProfileSegment(30, 40, 50, 60);
                    builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
                    builder.AddDikeProfilePoint(50, CharacteristicPointType.InnerToe);
                    addLocationAction(builder);
                },
                "The location with position " + NumericsHelper.ToString(locationX) + " must be on or between the " +
                "outer crest and inner toe.");
        }

        private static void GivenLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
            Action<CalculationInputBuilder> addLocationAction, string expectedMessage)
        {
            // Given
            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            addLocationAction(builder);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, expectedMessage);
        }

        #region Profile segments

        [Test]
        public void GivenBuilderWithoutDikeProfileSegments_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder(Random.NextDouble());

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
            var builder = new CalculationInputBuilder(Random.NextDouble());
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
            var builder = new CalculationInputBuilder(Random.NextDouble());
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

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   startPointX + Random.NextDouble(), GrassTopLayerType.ClosedSod));
            AddDefaultTimeStep(builder);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ProfileSegment> actualProfileSegments = result.Data.ProfileData.ProfileSegments;
            Assert.That(actualProfileSegments, Has.Count.EqualTo(1));

            ProfileDataAssertHelper.AssertProfileSegment(startPointX, startPointZ, endPointX, endPointZ, 1,
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

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ, roughnessCoefficient);
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   startPointX + Random.NextDouble(), GrassTopLayerType.ClosedSod));
            AddDefaultTimeStep(builder);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ProfileSegment> actualProfileSegments = result.Data.ProfileData.ProfileSegments;
            Assert.That(actualProfileSegments, Has.Count.EqualTo(1));

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

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointXSegment1, startPointZSegment1, endPointXSegment1,
                                          endPointZSegment1, roughnessCoefficient);
            builder.AddDikeProfileSegment(endPointXSegment1, endPointZSegment1, endPointXSegment2, endPointZSegment2,
                                          roughnessCoefficient);
            builder.AddDikeProfilePoint(startPointXSegment1, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointXSegment1, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   startPointXSegment1 + Random.NextDouble(),
                                                   GrassTopLayerType.ClosedSod));
            AddDefaultTimeStep(builder);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ProfileSegment> actualProfileSegments = result.Data.ProfileData.ProfileSegments;
            Assert.That(actualProfileSegments, Has.Count.EqualTo(2));

            ProfileDataAssertHelper.AssertProfileSegment(startPointXSegment1, startPointZSegment1, endPointXSegment1,
                                                         endPointZSegment1, roughnessCoefficient,
                                                         actualProfileSegments[0]);

            ProfileDataAssertHelper.AssertProfileSegment(endPointXSegment1, endPointZSegment1, endPointXSegment2,
                                                         endPointZSegment2, roughnessCoefficient,
                                                         actualProfileSegments[1]);

            Assert.That(actualProfileSegments[1].StartPoint, Is.SameAs(actualProfileSegments[0].EndPoint));
        }

        #endregion

        #region Profile points

        [Test]
        public void
            GivenBuilderWithDikeProfilePointDataOuterToeNotOnProfileSegmentPoints_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const double startPointX = 0;
            const double endPointX = 20;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(endPointX + Random.NextDouble(), CharacteristicPointType.OuterToe);

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
            const double startPointX = 0;
            const double endPointX = 20;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX + Random.NextDouble(), CharacteristicPointType.CrestOuterBerm);

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
            const double startPointX = 0;
            const double endPointX = 20;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX + Random.NextDouble(), CharacteristicPointType.NotchOuterBerm);

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
            const double startPointX = 0;
            const double endPointX = 20;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX + Random.NextDouble(), CharacteristicPointType.OuterCrest);

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
            const double startPointX = 0;
            const double endPointX = 20;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(endPointX + Random.NextDouble(), CharacteristicPointType.InnerCrest);

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
            const double startPointX = 0;
            const double endPointX = 20;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(endPointX + Random.NextDouble(), CharacteristicPointType.InnerToe);

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
            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(0, Random.NextDouble(), 10, Random.NextDouble());
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
            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(0, Random.NextDouble(), 10, Random.NextDouble());
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "The outer crest is required.");
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighDiscreteLocationAndWithoutDikeProfilePointDataInnerToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const double endPointX = 10;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(Random.NextDouble(), Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.InnerCrest);
            builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(
                new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                    endPointX - Random.NextDouble(), GrassTopLayerType.ClosedSod));

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "The inner toe is required.");
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighDiscreteLocationAndWithoutDikeProfilePointDataInnerCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const double endPointX = 10;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(Random.NextDouble(), Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(
                new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                    endPointX - Random.NextDouble(), GrassTopLayerType.ClosedSod));

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "The inner crest is required.");
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighAnalyticalLocationAndWithoutDikeProfilePointDataInnerToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const double endPointX = 10;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(Random.NextDouble(), Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.InnerCrest);
            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(
                new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                    endPointX - Random.NextDouble(), GrassTopLayerType.ClosedSod));

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "The inner toe is required.");
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighAnalyticalLocationAndWithoutDikeProfilePointDataInnerCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const double endPointX = 10;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(Random.NextDouble(), Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(
                new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                    endPointX - Random.NextDouble(), GrassTopLayerType.ClosedSod));

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "The inner crest is required.");
        }

        [Test]
        public void GivenBuilderWithDikeProfilePointDataOnSegmentPoints_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const double startPointX = 10;
            const double endPointX = 20;

            const CharacteristicPointType outerToe = CharacteristicPointType.OuterToe;
            const CharacteristicPointType outerCrest = CharacteristicPointType.OuterCrest;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, outerToe);
            builder.AddDikeProfilePoint(endPointX, outerCrest);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   startPointX + Random.NextDouble(), GrassTopLayerType.ClosedSod));
            AddDefaultTimeStep(builder);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IProfileData actualProfileData = result.Data.ProfileData;
            IReadOnlyList<ProfileSegment> actualProfileSegments = actualProfileData.ProfileSegments;
            IReadOnlyList<CharacteristicPoint> actualCharacteristicPoints = actualProfileData.CharacteristicPoints;
            Assert.That(actualProfileSegments, Has.Count.EqualTo(1));
            Assert.That(actualCharacteristicPoints, Has.Count.EqualTo(2));

            ProfileSegment actualSegment = actualProfileSegments[0];
            ProfileDataAssertHelper.AssertCharacteristicPoint(actualSegment.StartPoint, outerToe,
                                                              actualCharacteristicPoints[0]);
            ProfileDataAssertHelper.AssertCharacteristicPoint(actualSegment.EndPoint, outerCrest,
                                                              actualCharacteristicPoints[1]);
        }

        #endregion

        #region Foreshore

        [Test]
        public void GivenBuilderWithForeshoreAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            double slope = Random.NextDouble();
            double bottomZ = Random.NextDouble();

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   Random.NextDouble(), GrassTopLayerType.ClosedSod));
            builder.AddForeshore(slope, bottomZ);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            ProfileDataAssertHelper.AssertForeshore(slope, bottomZ, result.Data.ProfileData.Foreshore);
        }

        [Test]
        public void GivenBuilderWithoutForeshoreAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   Random.NextDouble(), GrassTopLayerType.ClosedSod));

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            ProfileDataAssertHelper.AssertForeshore(double.NaN, double.NaN, result.Data.ProfileData.Foreshore);
        }

        #endregion

        #region Time steps

        [Test]
        public void GivenBuilderWithoutTimeStepAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const double startPointX = 0;
            const double endPointX = 10;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   startPointX + Random.NextDouble(), GrassTopLayerType.ClosedSod));

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(result, "At least 1 time step is required.");
        }

        [Test]
        public void GivenBuilderWithNonSuccessiveTimeStepsAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const double startPointX = 0;
            const double endPointX = 10;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   startPointX + Random.NextDouble(), GrassTopLayerType.ClosedSod));

            double startTimeStep1 = Random.NextDouble();
            double endTimeStep1 = 1 + startTimeStep1;
            double startTimeStep2 = 1 + endTimeStep1;
            builder.AddTimeStep(startTimeStep1, endTimeStep1, Random.NextDouble(), Random.NextDouble(), Random.NextDouble(),
                                Random.NextDouble());
            builder.AddTimeStep(startTimeStep2, 4.4, Random.NextDouble(), Random.NextDouble(), Random.NextDouble(), Random.NextDouble());

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result,
                $"The begin time of the time step ({NumericsHelper.ToString(startTimeStep2)}) must be equal to" +
                $" the end time of the previous time step ({NumericsHelper.ToString(endTimeStep1)}).");
        }

        [Test]
        public void GivenBuilderWithTimeStepWithInvalidBeginAndEndTimeAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const double startPointX = 0;
            const double endPointX = 10;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   startPointX + Random.NextDouble(), GrassTopLayerType.ClosedSod));
            double beginTime = Random.NextDouble();
            double endTime = beginTime - Random.NextDouble();
            builder.AddTimeStep(beginTime, endTime, Random.NextDouble(), Random.NextDouble(), Random.NextDouble(), Random.NextDouble());

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result,
                $"The begin time of the time step ({NumericsHelper.ToString(beginTime)}) must be smaller than " +
                $"the end time of the time step ({NumericsHelper.ToString(endTime)}).");
        }

        [Test]
        public void GivenBuilderWithTimeStepAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const double beginTime = 1.1;
            const double endTime = 2.2;
            double waterLevel = Random.NextDouble();
            double waveHeightHm0 = Random.NextDouble();
            double wavePeriodTm10 = Random.NextDouble();
            double waveDirection = Random.NextDouble();

            const double startPointX = 0;
            const double endPointX = 10;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            builder.AddDikeProfileSegment(startPointX, Random.NextDouble(), endPointX, Random.NextDouble());
            builder.AddDikeProfilePoint(startPointX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(endPointX, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(new GrassWaveImpactLocationConstructionProperties(
                                                   startPointX + Random.NextDouble(), GrassTopLayerType.ClosedSod));
            builder.AddTimeStep(beginTime, endTime, waterLevel, waveHeightHm0, wavePeriodTm10, waveDirection);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ITimeDependentInput> actualTimeDependentInputItems = result.Data.TimeDependentInputItems;
            Assert.That(actualTimeDependentInputItems, Has.Count.EqualTo(1));

            TimeDependentInputAssertHelper.AssertTimeDependentInputItem(beginTime, endTime, waterLevel, waveHeightHm0,
                                                                        wavePeriodTm10, waveDirection,
                                                                        actualTimeDependentInputItems[0]);
        }

        #endregion

        #region Locations

        [Test]
        public void GivenBuilderWithoutLocationAdded_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var builder = new CalculationInputBuilder(Random.NextDouble());
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
                        new AsphaltWaveImpactLocationConstructionProperties(
                            locationX, AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete, Random.NextDouble(),
                            Random.NextDouble(), Random.NextDouble(), Random.NextDouble()));
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
                        new AsphaltWaveImpactLocationConstructionProperties(
                            locationX, AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete, Random.NextDouble(),
                            Random.NextDouble(), Random.NextDouble(), Random.NextDouble()));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithAsphaltWaveImpactLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const AsphaltWaveImpactTopLayerType topLayerType = (AsphaltWaveImpactTopLayerType) 99;

            double x = Random.NextDouble();
            var constructionProperties = new AsphaltWaveImpactLocationConstructionProperties(
                x, topLayerType, Random.NextDouble(), Random.NextDouble(), Random.NextDouble(), Random.NextDouble());

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddAsphaltWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, $"The location with position {NumericsHelper.ToString(x)} has an invalid top layer type.");
        }

        [Test]
        public void GivenBuilderWithFullyConfiguredAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            var topLayerType = Random.NextEnumValue<AsphaltWaveImpactTopLayerType>();
            const double x = 5;
            double flexuralStrength = Random.NextDouble();
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

            var constructionProperties = new AsphaltWaveImpactLocationConstructionProperties(
                x, topLayerType, flexuralStrength, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer)
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

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddAsphaltWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as AsphaltWaveImpactLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                flexuralStrength, densityOfWater, soilElasticity, averageNumberOfWavesCtm, impactNumberC,
                stiffnessRelationNu, locationDependentInput);

            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                thicknessUpperLayer, elasticModulusUpperLayer, locationDependentInput.UpperLayer);

            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                thicknessSubLayer, elasticModulusSubLayer, locationDependentInput.SubLayer);

            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertFatigue(
                fatigueAlpha, fatigueBeta, locationDependentInput.Fatigue);

            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertFactors(
                widthFactors, depthFactors, impactFactors, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredHydraulicAsphaltConcreteAsphaltWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            const AsphaltWaveImpactTopLayerType topLayerType = AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete;
            const double x = 5;
            double flexuralStrength = Random.NextDouble();
            double soilElasticity = Random.NextDouble();
            double thicknessUpperLayer = Random.NextDouble();
            double elasticModulusUpperLayer = Random.NextDouble();

            var constructionProperties = new AsphaltWaveImpactLocationConstructionProperties(
                x, topLayerType, flexuralStrength, soilElasticity, thicknessUpperLayer, elasticModulusUpperLayer);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddAsphaltWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as AsphaltWaveImpactLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                flexuralStrength, 1025, soilElasticity, 1, 1, 0.35, locationDependentInput);

            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertLayer(
                thicknessUpperLayer, elasticModulusUpperLayer, locationDependentInput.UpperLayer);

            Assert.That(locationDependentInput.SubLayer, Is.Null);

            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertFatigue(
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
                (0.8, 0.089),
                (0.9, 0.0712),
                (1, 0.0541),
                (1.1, 0.0391),
                (1.2, 0.0269),
                (1.3, 0.0216),
                (1.4, 0.015),
                (1.5, 0.0105)
            };

            var expectedDepthFactors = new List<(double, double)>
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
            };

            var expectedImpactFactors = new List<(double, double)>
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
            };

            AsphaltWaveImpactLocationDependentInputAssertHelper.AssertFactors(
                expectedWidthFactors, expectedDepthFactors, expectedImpactFactors, locationDependentInput);
        }

        #endregion

        #region Grass wave overtopping Rayleigh discrete

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighDiscreteLocationWithXLeftFromOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 9.9;

            GivenInnerSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(
                        new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                            locationX, Random.NextEnumValue<GrassTopLayerType>()));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighDiscreteLocationWithXRightFromOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 50.1;

            GivenInnerSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(
                        new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                            locationX, Random.NextEnumValue<GrassTopLayerType>()));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighDiscreteLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const GrassTopLayerType topLayerType = (GrassTopLayerType) 99;
            var constructionProperties = new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                45, topLayerType);

            const double innerCrestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, innerCrestX, 40);
            builder.AddDikeProfileSegment(innerCrestX, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(innerCrestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The location with position 45 has an invalid top layer type.");
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighDiscreteLocationWithInvalidGeometry_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            var constructionProperties = new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                45, topLayerType);

            const double outerToeX = 0;
            const double crestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultTimeStep(builder);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20);
            builder.AddDikeProfileSegment(10, 20, 20, 20);
            builder.AddDikeProfileSegment(20, 20, crestX, 10);
            builder.AddDikeProfileSegment(crestX, 10, 40, 40);
            builder.AddDikeProfileSegment(40, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.False);

            IReadOnlyList<Event> events = result.Events;
            Assert.That(events, Has.Count.EqualTo(1));
            Assert.That(events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[0].Message, Is.Not.Empty);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighDiscreteLocationWithInvalidRoughnessCoefficients_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            var constructionProperties = new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                45, topLayerType);

            const double outerToeX = 0;
            const double crestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultTimeStep(builder);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20, 0.4);
            builder.AddDikeProfileSegment(10, 20, crestX, 25, 1.1);
            builder.AddDikeProfileSegment(crestX, 25, 40, 40);
            builder.AddDikeProfileSegment(40, 40, 50, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.False);

            IReadOnlyList<Event> events = result.Events;
            Assert.That(events, Has.Count.EqualTo(2));
            Assert.That(events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[0].Message, Is.Not.Empty);
            Assert.That(events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[1].Message, Is.Not.Empty);
        }

        [Test]
        public void
            GivenBuilderWithFullyConfiguredGrassWaveOvertoppingRayleighDiscreteLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            const double x = 45;
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double criticalCumulativeOverload = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            double frontVelocityCwo = Random.NextDouble();
            double accelerationAlphaAForCrest = Random.NextDouble();
            double accelerationAlphaAForInnerSlope = Random.NextDouble();
            double dikeHeight = Random.NextDouble();
            int fixedNumberOfWaves = Random.Next();

            var constructionProperties = new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                x, topLayerType)
            {
                InitialDamage = initialDamage,
                FailureNumber = failureNumber,
                CriticalCumulativeOverload = criticalCumulativeOverload,
                CriticalFrontVelocity = criticalFrontVelocity,
                IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS,
                AverageNumberOfWavesCtm = averageNumberOfWavesCtm,
                FrontVelocityCwo = frontVelocityCwo,
                AccelerationAlphaAForCrest = accelerationAlphaAForCrest,
                AccelerationAlphaAForInnerSlope = accelerationAlphaAForInnerSlope,
                DikeHeight = dikeHeight,
                FixedNumberOfWaves = fixedNumberOfWaves
            };

            const double innerCrestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, innerCrestX, 40);
            builder.AddDikeProfileSegment(innerCrestX, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(innerCrestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveOvertoppingRayleighDiscreteLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertGeneralProperties(
                dikeHeight, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                averageNumberOfWavesCtm, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                criticalFrontVelocity, frontVelocityCwo, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                accelerationAlphaAForCrest, accelerationAlphaAForInnerSlope, locationDependentInput.AccelerationAlphaA);

            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                criticalCumulativeOverload, fixedNumberOfWaves, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveOvertoppingRayleighDiscreteLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.ClosedSod;
            const double x = 45;

            var constructionProperties = new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                x, topLayerType);

            const double innerCrestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, innerCrestX, 40);
            builder.AddDikeProfileSegment(innerCrestX, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(innerCrestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveOvertoppingRayleighDiscreteLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertGeneralProperties(
                null, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                6.6, 1.45, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1, 1.4, locationDependentInput.AccelerationAlphaA);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveOvertoppingRayleighDiscreteLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.OpenSod;
            const double x = 45;

            var constructionProperties = new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(
                x, topLayerType);

            const double innerCrestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, innerCrestX, 40);
            builder.AddDikeProfileSegment(innerCrestX, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(innerCrestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveOvertoppingRayleighDiscreteLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertGeneralProperties(
                null, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassWaveOvertoppingRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                4.3, 1.45, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1, 1.4, locationDependentInput.AccelerationAlphaA);
        }

        #endregion

        #region Grass wave overtopping Rayleigh analytical

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighAnalyticalLocationWithXLeftFromOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 9.9;

            GivenInnerSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(
                        new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                            locationX, Random.NextEnumValue<GrassTopLayerType>()));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighAnalyticalLocationWithXRightFromOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 50.1;

            GivenInnerSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(
                        new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                            locationX, Random.NextEnumValue<GrassTopLayerType>()));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighAnalyticalLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const GrassTopLayerType topLayerType = (GrassTopLayerType) 99;
            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                45, topLayerType);

            const double innerCrestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, innerCrestX, 40);
            builder.AddDikeProfileSegment(innerCrestX, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(innerCrestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "The location with position 45 has an invalid top layer type.");
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighAnalyticalLocationWithInvalidGeometry_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                45, topLayerType);

            const double outerToeX = 0;
            const double crestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultTimeStep(builder);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20);
            builder.AddDikeProfileSegment(10, 20, 20, 20);
            builder.AddDikeProfileSegment(20, 20, crestX, 10);
            builder.AddDikeProfileSegment(crestX, 10, 40, 40);
            builder.AddDikeProfileSegment(40, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.False);

            IReadOnlyList<Event> events = result.Events;
            Assert.That(events, Has.Count.EqualTo(1));
            Assert.That(events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[0].Message, Is.Not.Empty);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveOvertoppingRayleighAnalyticalLocationWithInvalidRoughnessCoefficients_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                45, topLayerType);

            const double outerToeX = 0;
            const double crestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultTimeStep(builder);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20, 0.4);
            builder.AddDikeProfileSegment(10, 20, crestX, 25, 1.1);
            builder.AddDikeProfileSegment(crestX, 25, 40, 40);
            builder.AddDikeProfileSegment(40, 40, 50, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.False);

            IReadOnlyList<Event> events = result.Events;
            Assert.That(events, Has.Count.EqualTo(2));
            Assert.That(events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[0].Message, Is.Not.Empty);
            Assert.That(events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[1].Message, Is.Not.Empty);
        }

        [Test]
        public void
            GivenBuilderWithFullyConfiguredGrassWaveOvertoppingRayleighAnalyticalLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            const double x = 45;
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double criticalCumulativeOverload = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            double frontVelocityCwo = Random.NextDouble();
            double accelerationAlphaAForCrest = Random.NextDouble();
            double accelerationAlphaAForInnerSlope = Random.NextDouble();
            double dikeHeight = Random.NextDouble();

            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                x, topLayerType)
            {
                InitialDamage = initialDamage,
                FailureNumber = failureNumber,
                CriticalCumulativeOverload = criticalCumulativeOverload,
                CriticalFrontVelocity = criticalFrontVelocity,
                IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS,
                AverageNumberOfWavesCtm = averageNumberOfWavesCtm,
                FrontVelocityCwo = frontVelocityCwo,
                AccelerationAlphaAForCrest = accelerationAlphaAForCrest,
                AccelerationAlphaAForInnerSlope = accelerationAlphaAForInnerSlope,
                DikeHeight = dikeHeight
            };

            const double innerCrestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, innerCrestX, 40);
            builder.AddDikeProfileSegment(innerCrestX, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(innerCrestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveOvertoppingRayleighAnalyticalLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertGeneralProperties(
                dikeHeight, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                averageNumberOfWavesCtm, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertCumulativeOverload(
                criticalCumulativeOverload, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                criticalFrontVelocity, frontVelocityCwo, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                accelerationAlphaAForCrest, accelerationAlphaAForInnerSlope, locationDependentInput.AccelerationAlphaA);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveOvertoppingRayleighAnalyticalLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.ClosedSod;
            const double x = 45;

            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                x, topLayerType);

            const double innerCrestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, innerCrestX, 40);
            builder.AddDikeProfileSegment(innerCrestX, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(innerCrestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveOvertoppingRayleighAnalyticalLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertGeneralProperties(
                null, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                6.6, 1.45, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1, 1.4, locationDependentInput.AccelerationAlphaA);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveOvertoppingRayleighAnalyticalLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.OpenSod;
            const double x = 45;

            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                x, topLayerType);

            const double innerCrestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddDikeProfileSegment(10, 20, innerCrestX, 40);
            builder.AddDikeProfileSegment(innerCrestX, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(innerCrestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveOvertoppingRayleighAnalyticalLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertGeneralProperties(
                null, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertFrontVelocity(
                4.3, 1.45, locationDependentInput);

            GrassWaveOvertoppingRayleighLocationDependentInputAssertHelper.AssertAccelerationAlphaA(
                1, 1.4, locationDependentInput.AccelerationAlphaA);
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
                        new GrassWaveImpactLocationConstructionProperties(locationX, GrassTopLayerType.ClosedSod));
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
                        new GrassWaveImpactLocationConstructionProperties(locationX, GrassTopLayerType.ClosedSod));
                }, locationX);
        }

        [Test]
        public void GivenBuilderWithGrassWaveImpactLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const GrassTopLayerType topLayerType = (GrassTopLayerType) 99;

            double x = Random.NextDouble();
            var constructionProperties = new GrassWaveImpactLocationConstructionProperties(x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, $"The location with position {NumericsHelper.ToString(x)} has an invalid top layer type.");
        }

        [Test]
        public void GivenBuilderWithFullyConfiguredGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            const double x = 5;
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

            var constructionProperties = new GrassWaveImpactLocationConstructionProperties(x, topLayerType)
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

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0] as GrassWaveImpactLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                minimumWaveHeightTemax, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                maximumWaveHeightTemin, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                waveAngleImpactNwa, waveAngleImpactQwa, waveAngleImpactRwa, locationDependentInput.WaveAngleImpact);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                timeLineAgwi, timeLineBgwi, timeLineCgwi, locationDependentInput.TimeLine);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                upperLimitLoadingAul, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                lowerLimitLoadingAll, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.ClosedSod;
            const double x = 5;

            var constructionProperties = new GrassWaveImpactLocationConstructionProperties(x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0] as GrassWaveImpactLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                3600000, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                3.6, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                2d / 3, 0.35, 10, locationDependentInput.WaveAngleImpact);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                1, -0.000009722, 0.25, locationDependentInput.TimeLine);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                0, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                0.5, locationDependentInput);
        }

        [Test]
        public void GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.OpenSod;
            const double x = 5;

            var constructionProperties = new GrassWaveImpactLocationConstructionProperties(x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0] as GrassWaveImpactLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertMinimumWaveHeight(
                3600000, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertMaximumWaveHeight(
                3.6, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                2d / 3, 0.35, 10, locationDependentInput.WaveAngleImpact);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertTimeLine(
                0.8, -0.00001944, 0.25, locationDependentInput.TimeLine);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                0, locationDependentInput);

            GrassWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                0.5, locationDependentInput);
        }

        #endregion

        #region Grass wave run-up Rayleigh discrete

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupRayleighDiscreteLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 0;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveRunupRayleighDiscreteLocation(
                        new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                            locationX, GrassTopLayerType.ClosedSod));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupRayleighDiscreteLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 10;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddGrassWaveRunupRayleighDiscreteLocation(
                        new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                            locationX, GrassTopLayerType.ClosedSod));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupRayleighDiscreteLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const GrassTopLayerType topLayerType = (GrassTopLayerType) 99;

            double x = Random.NextDouble();
            var constructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveRunupRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, $"The location with position {NumericsHelper.ToString(x)} has an invalid top layer type.");
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupRayleighDiscreteLocationWithInvalidGeometry_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            var constructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, topLayerType);

            const double outerToeX = 0;
            const double crestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultTimeStep(builder);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20);
            builder.AddDikeProfileSegment(10, 20, 20, 20);
            builder.AddDikeProfileSegment(20, 20, crestX, 10);
            builder.AddDikeProfileSegment(crestX, 10, 40, 40);
            builder.AddDikeProfileSegment(40, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveRunupRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.False);

            IReadOnlyList<Event> events = result.Events;
            Assert.That(events, Has.Count.EqualTo(1));
            Assert.That(events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[0].Message, Is.Not.Empty);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupRayleighDiscreteLocationWithInvalidRoughnessCoefficients_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            var constructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, topLayerType);

            const double outerToeX = 0;
            const double crestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultTimeStep(builder);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20, 0.4);
            builder.AddDikeProfileSegment(10, 20, crestX, 25, 1.1);
            builder.AddDikeProfileSegment(crestX, 25, 40, 40);
            builder.AddDikeProfileSegment(40, 40, 50, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveRunupRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.False);

            IReadOnlyList<Event> events = result.Events;
            Assert.That(events, Has.Count.EqualTo(2));
            Assert.That(events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[0].Message, Is.Not.Empty);
            Assert.That(events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[1].Message, Is.Not.Empty);
        }

        [Test]
        public void
            GivenBuilderWithFullyConfiguredGrassWaveRunupRayleighDiscreteLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            const double x = 5;
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double criticalCumulativeOverload = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            double frontVelocityCu = Random.NextDouble();
            int fixedNumberOfWaves = Random.Next();

            var constructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                x, topLayerType)
            {
                InitialDamage = initialDamage,
                FailureNumber = failureNumber,
                CriticalCumulativeOverload = criticalCumulativeOverload,
                CriticalFrontVelocity = criticalFrontVelocity,
                IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS,
                AverageNumberOfWavesCtm = averageNumberOfWavesCtm,
                FrontVelocityCu = frontVelocityCu,
                FixedNumberOfWaves = fixedNumberOfWaves
            };

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveRunupRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveRunupRayleighDiscreteLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                averageNumberOfWavesCtm, locationDependentInput);

            GrassWaveRunupLocationDependentInputAssertHelper.AssertFrontVelocity(
                criticalFrontVelocity, frontVelocityCu, locationDependentInput);

            GrassWaveRunupRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                criticalCumulativeOverload, fixedNumberOfWaves, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveRunupRayleighDiscreteLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInpu()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.ClosedSod;
            const double x = 5;

            var constructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveRunupRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveRunupRayleighDiscreteLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassWaveRunupRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, locationDependentInput);

            GrassWaveRunupLocationDependentInputAssertHelper.AssertFrontVelocity(
                6.6, 1.1, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveRunupRayleighDiscreteLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.OpenSod;
            const double x = 5;

            var constructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveRunupRayleighDiscreteLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveRunupRayleighDiscreteLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassWaveRunupRayleighDiscreteLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, 10000, locationDependentInput);

            GrassWaveRunupLocationDependentInputAssertHelper.AssertFrontVelocity(
                4.3, 1.1, locationDependentInput);
        }

        #endregion

        #region Grass wave run-up Battjes-Groenendijk analytical

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupBattjesGroenendijkAnalyticalLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 0;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    AddDefaultForeshore(builder);
                    builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(
                        new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                            locationX, GrassTopLayerType.ClosedSod));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupBattjesGroenendijkAnalyticalLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 10;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    AddDefaultForeshore(builder);
                    builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(
                        new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                            locationX, GrassTopLayerType.ClosedSod));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupBattjesGroenendijkAnalyticalLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const GrassTopLayerType topLayerType = (GrassTopLayerType) 99;

            double x = Random.NextDouble();
            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            AddDefaultForeshore(builder);

            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, $"The location with position {NumericsHelper.ToString(x)} has an invalid top layer type.");
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupBattjesGroenendijkAnalyticalLocationWithInvalidGeometry_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                15, topLayerType);

            const double outerToeX = 0;
            const double crestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultTimeStep(builder);
            AddDefaultForeshore(builder);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20);
            builder.AddDikeProfileSegment(10, 20, 20, 20);
            builder.AddDikeProfileSegment(20, 20, crestX, 10);
            builder.AddDikeProfileSegment(crestX, 10, 40, 40);
            builder.AddDikeProfileSegment(40, 40, innerToeX, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.False);

            IReadOnlyList<Event> events = result.Events;
            Assert.That(events, Has.Count.EqualTo(1));
            Assert.That(events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[0].Message, Is.Not.Empty);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupBattjesGroenendijkAnalyticalLocationWithInvalidRoughnessCoefficients_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                15, topLayerType);

            const double outerToeX = 0;
            const double crestX = 30;
            const double innerToeX = 50;

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultTimeStep(builder);
            AddDefaultForeshore(builder);

            builder.AddDikeProfileSegment(outerToeX, 10, 10, 20, 0.4);
            builder.AddDikeProfileSegment(10, 20, crestX, 25, 1.1);
            builder.AddDikeProfileSegment(crestX, 25, 40, 40);
            builder.AddDikeProfileSegment(40, 40, 50, 60);
            builder.AddDikeProfilePoint(outerToeX, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(crestX, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(innerToeX, CharacteristicPointType.InnerToe);
            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.False);

            IReadOnlyList<Event> events = result.Events;
            Assert.That(events, Has.Count.EqualTo(2));
            Assert.That(events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[0].Message, Is.Not.Empty);
            Assert.That(events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(events[1].Message, Is.Not.Empty);
        }

        [Test]
        public void
            GivenBuilderWithGrassWaveRunupBattjesGroenendijkAnalyticalLocationWithoutForeshore_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            const double x = 5;

            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, "Foreshore is required.");
        }

        [Test]
        public void
            GivenBuilderWithFullyConfiguredGrassWaveRunupBattjesGroenendijkAnalyticalLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<GrassTopLayerType>();
            const double x = 5;
            double initialDamage = Random.NextDouble();
            double failureNumber = Random.NextDouble();
            double criticalCumulativeOverload = Random.NextDouble();
            double criticalFrontVelocity = Random.NextDouble();
            double increasedLoadTransitionAlphaM = Random.NextDouble();
            double reducedStrengthTransitionAlphaS = Random.NextDouble();
            double averageNumberOfWavesCtm = Random.NextDouble();
            double frontVelocityCu = Random.NextDouble();

            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                x, topLayerType)
            {
                InitialDamage = initialDamage,
                FailureNumber = failureNumber,
                CriticalCumulativeOverload = criticalCumulativeOverload,
                CriticalFrontVelocity = criticalFrontVelocity,
                IncreasedLoadTransitionAlphaM = increasedLoadTransitionAlphaM,
                ReducedStrengthTransitionAlphaS = reducedStrengthTransitionAlphaS,
                AverageNumberOfWavesCtm = averageNumberOfWavesCtm,
                FrontVelocityCu = frontVelocityCu
            };

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            AddDefaultForeshore(builder);
            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveRunupBattjesGroenendijkAnalyticalLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                increasedLoadTransitionAlphaM, reducedStrengthTransitionAlphaS, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                averageNumberOfWavesCtm, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertCumulativeOverload(
                criticalCumulativeOverload, locationDependentInput);

            GrassWaveRunupLocationDependentInputAssertHelper.AssertFrontVelocity(
                criticalFrontVelocity, frontVelocityCu, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredClosedSodGrassWaveRunupBattjesGroenendijkAnalyticalLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInpu()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.ClosedSod;
            const double x = 5;

            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            AddDefaultForeshore(builder);
            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveRunupBattjesGroenendijkAnalyticalLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, locationDependentInput);

            GrassWaveRunupLocationDependentInputAssertHelper.AssertFrontVelocity(
                6.6, 1.1, locationDependentInput);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredOpenSodGrassWaveRunupBattjesGroenendijkAnalyticalLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const GrassTopLayerType topLayerType = GrassTopLayerType.OpenSod;
            const double x = 5;

            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                x, topLayerType);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            AddDefaultForeshore(builder);
            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as GrassWaveRunupBattjesGroenendijkAnalyticalLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertTransitionAlpha(
                1, 1, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertAverageNumberOfWaves(
                0.92, locationDependentInput);

            GrassCumulativeOverloadLocationDependentInputAssertHelper.AssertCumulativeOverload(
                7000, locationDependentInput);

            GrassWaveRunupLocationDependentInputAssertHelper.AssertFrontVelocity(
                4.3, 1.1, locationDependentInput);
        }

        #endregion

        #region Natural stone wave impact

        [Test]
        public void GivenBuilderWithNaturalStoneWaveImpactLocationWithXOnOuterToe_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 0;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddNaturalStoneWaveImpactLocation(
                        new NaturalStoneWaveImpactLocationConstructionProperties(
                            locationX, NaturalStoneWaveImpactTopLayerType.NordicStone, Random.NextDouble(),
                            Random.NextDouble()));
                }, locationX);
        }

        [Test]
        public void GivenBuilderWithNaturalStoneWaveImpactLocationWithXOnOuterCrest_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            const double locationX = 10;

            GivenOuterSlopeLocationWithInvalidX_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent(
                builder =>
                {
                    builder.AddNaturalStoneWaveImpactLocation(
                        new NaturalStoneWaveImpactLocationConstructionProperties(
                            locationX, NaturalStoneWaveImpactTopLayerType.NordicStone, Random.NextDouble(),
                            Random.NextDouble()));
                }, locationX);
        }

        [Test]
        public void
            GivenBuilderWithNaturalStoneWaveImpactLocationWithInvalidTopLayerType_WhenBuild_ThenReturnsResultWithSuccessfulFalseAndEvent()
        {
            // Given
            const NaturalStoneWaveImpactTopLayerType topLayerType = (NaturalStoneWaveImpactTopLayerType) 99;

            double x = Random.NextDouble();
            var constructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                x, topLayerType, Random.NextDouble(), Random.NextDouble());

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddNaturalStoneWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            AssertResultWithSuccessfulFalseAndEvent(
                result, $"The location with position {NumericsHelper.ToString(x)} has an invalid top layer type.");
        }

        [Test]
        public void GivenBuilderWithFullyConfiguredNaturalStoneWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            var topLayerType = Random.NextEnumValue<NaturalStoneWaveImpactTopLayerType>();
            const double x = 5;
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

            var constructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                x, topLayerType, thicknessTopLayer, relativeDensity)
            {
                InitialDamage = initialDamage,
                FailureNumber = failureNumber,
                HydraulicLoadXib = hydraulicLoadXib,
                HydraulicLoadAp = hydraulicLoadAp,
                HydraulicLoadBp = hydraulicLoadBp,
                HydraulicLoadCp = hydraulicLoadCp,
                HydraulicLoadNp = hydraulicLoadNp,
                HydraulicLoadAs = hydraulicLoadAs,
                HydraulicLoadBs = hydraulicLoadBs,
                HydraulicLoadCs = hydraulicLoadCs,
                HydraulicLoadNs = hydraulicLoadNs,
                SlopeUpperLevelAus = slopeUpperLevelAus,
                SlopeLowerLevelAls = slopeLowerLevelAls,
                UpperLimitLoadingAul = upperLimitLoadingAul,
                UpperLimitLoadingBul = upperLimitLoadingBul,
                UpperLimitLoadingCul = upperLimitLoadingCul,
                LowerLimitLoadingAll = lowerLimitLoadingAll,
                LowerLimitLoadingBll = lowerLimitLoadingBll,
                LowerLimitLoadingCll = lowerLimitLoadingCll,
                DistanceMaximumWaveElevationAsmax = distanceMaximumWaveElevationAsmax,
                DistanceMaximumWaveElevationBsmax = distanceMaximumWaveElevationBsmax,
                NormativeWidthOfWaveImpactAwi = normativeWidthOfWaveImpactAwi,
                NormativeWidthOfWaveImpactBwi = normativeWidthOfWaveImpactBwi,
                WaveAngleImpactBetamax = waveAngleImpactBetamax
            };

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddNaturalStoneWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as NaturalStoneWaveImpactLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(
                initialDamage, failureNumber, locationDependentInput);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                relativeDensity, thicknessTopLayer, locationDependentInput);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertHydraulicLoads(
                hydraulicLoadAp, hydraulicLoadBp, hydraulicLoadCp, hydraulicLoadNp, hydraulicLoadAs, hydraulicLoadBs,
                hydraulicLoadCs, hydraulicLoadNs, hydraulicLoadXib, locationDependentInput.HydraulicLoads);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertSlope(
                slopeUpperLevelAus, slopeLowerLevelAls, locationDependentInput.Slope);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                upperLimitLoadingAul, upperLimitLoadingBul, upperLimitLoadingCul,
                locationDependentInput.UpperLimitLoading);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                lowerLimitLoadingAll, lowerLimitLoadingBll, lowerLimitLoadingCll,
                locationDependentInput.LowerLimitLoading);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertDistanceMaximumWaveElevation(
                distanceMaximumWaveElevationAsmax, distanceMaximumWaveElevationBsmax,
                locationDependentInput.DistanceMaximumWaveElevation);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertNormativeWidthOfWaveImpact(
                normativeWidthOfWaveImpactAwi, normativeWidthOfWaveImpactBwi,
                locationDependentInput.NormativeWidthOfWaveImpact);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                waveAngleImpactBetamax, locationDependentInput.WaveAngleImpact);
        }

        [Test]
        public void
            GivenBuilderWithNotFullyConfiguredNordicStoneNaturalStoneWaveImpactLocationAdded_WhenBuild_ThenReturnsResultWithCalculationInput()
        {
            // Given
            const NaturalStoneWaveImpactTopLayerType topLayerType = NaturalStoneWaveImpactTopLayerType.NordicStone;
            const double x = 5;
            double thicknessTopLayer = Random.NextDouble();
            double relativeDensity = Random.NextDouble();

            var constructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                x, topLayerType, thicknessTopLayer, relativeDensity);

            var builder = new CalculationInputBuilder(Random.NextDouble());
            AddDefaultProfileAndTimeStep(builder);
            builder.AddNaturalStoneWaveImpactLocation(constructionProperties);

            // When
            DataResult<ICalculationInput> result = builder.Build();

            // Then
            Assert.That(result.Successful, Is.True);

            IReadOnlyList<ILocationDependentInput> actualLocationDependentInputItems =
                result.Data.LocationDependentInputItems;
            Assert.That(actualLocationDependentInputItems, Has.Count.EqualTo(1));

            var locationDependentInput = actualLocationDependentInputItems[0]
                                             as NaturalStoneWaveImpactLocationDependentInput;
            Assert.That(locationDependentInput, Is.Not.Null);

            LocationDependentInputAssertHelper.AssertLocationProperties(x, locationDependentInput);

            LocationDependentInputAssertHelper.AssertDamageProperties(0, 1, locationDependentInput);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertGeneralProperties(
                relativeDensity, thicknessTopLayer, locationDependentInput);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertHydraulicLoads(
                4, 0, 0, -0.9, 0.8, 0, 0, 0.6, 2.9, locationDependentInput.HydraulicLoads);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertSlope(
                0.05, 1.5, locationDependentInput.Slope);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertUpperLimitLoading(
                0.1, 0.6, 4, locationDependentInput.UpperLimitLoading);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertLowerLimitLoading(
                0.1, 0.2, 4, locationDependentInput.LowerLimitLoading);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertDistanceMaximumWaveElevation(
                0.42, 0.9, locationDependentInput.DistanceMaximumWaveElevation);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertNormativeWidthOfWaveImpact(
                0.96, 0.11, locationDependentInput.NormativeWidthOfWaveImpact);

            NaturalStoneWaveImpactLocationDependentInputAssertHelper.AssertWaveAngleImpact(
                78, locationDependentInput.WaveAngleImpact);
        }

        #endregion

        #endregion
    }
}