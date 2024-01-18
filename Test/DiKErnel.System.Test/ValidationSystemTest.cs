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

using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassOvertopping;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.System.Test
{
    [TestFixture]
    public class ValidationSystemTest
    {
        [Test]
        public void GivenCalculationInputWithInvalidTimeStep_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(90, 100, 10, -1, 30, -10);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(
                new GrassWaveImpactLocationConstructionProperties(15, GrassTopLayerType.ClosedSod));

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Failed));
            Assert.That(validationResult.Events, Has.Count.EqualTo(3));
            Assert.That(validationResult.Events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[0].Message, Is.EqualTo("WaveHeightHm0 must be larger than 0."));
            Assert.That(validationResult.Events[1].Type, Is.EqualTo(EventType.Warning));
            Assert.That(validationResult.Events[1].Message, Is.EqualTo("WavePeriodTm10 should be in range {0.5, 25}."));
            Assert.That(validationResult.Events[2].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[2].Message, Is.EqualTo("WaveDirection must be in range [0, 360]."));
        }

        [Test]
        public void GivenCalculationInputWithInvalidProfileData_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var builder = new CalculationInputBuilder(-10);
            builder.AddDikeProfileSegment(10, 5, 20, 10, 1.5);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);

            var asphaltWaveImpactLocationConstructionProperties = new AsphaltWaveImpactLocationConstructionProperties(
                12, AsphaltTopLayerType.HydraulicAsphaltConcrete, 1, 0.5, 3, 2);

            builder.AddAsphaltWaveImpactLocation(asphaltWaveImpactLocationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Failed));
            Assert.That(validationResult.Events, Has.Count.EqualTo(2));
            Assert.That(validationResult.Events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[0].Message, Is.EqualTo("Dike orientation must be in range [0, 360]."));
            Assert.That(validationResult.Events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[1].Message, Is.EqualTo("Roughness coefficient must be in range [0.5, 1]."));
        }

        [Test]
        public void GivenCalculationInputWithInvalidAsphaltRevetmentWaveImpactLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties = new AsphaltWaveImpactLocationConstructionProperties(
                15, AsphaltTopLayerType.HydraulicAsphaltConcrete, 0, 0, -1, -8)
            {
                InitialDamage = -0.1,
                FailureNumber = -1,
                DensityOfWater = 800,
                FatigueAlpha = 0,
                FatigueBeta = 0,
                ImpactNumberC = -0.5,
                StiffnessRelationNu = -10,
                ThicknessSubLayer = 0,
                ElasticModulusSubLayer = 0,
                AverageNumberOfWavesCtm = 0
            };

            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddAsphaltWaveImpactLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Failed));
            Assert.That(validationResult.Events, Has.Count.EqualTo(14));
            Assert.That(validationResult.Events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[0].Message, Is.EqualTo("InitialDamage must be equal to 0 or larger."));
            Assert.That(validationResult.Events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[1].Message, Is.EqualTo("FailureNumber must be equal to InitialDamage or larger."));
            Assert.That(validationResult.Events[2].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[2].Message, Is.EqualTo("FatigueAlpha must be larger than 0."));
            Assert.That(validationResult.Events[3].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[3].Message, Is.EqualTo("FatigueBeta must be larger than 0."));
            Assert.That(validationResult.Events[4].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[4].Message, Is.EqualTo("FlexuralStrength must be larger than 0."));
            Assert.That(validationResult.Events[5].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[5].Message, Is.EqualTo("ImpactNumberC must be larger than 0."));
            Assert.That(validationResult.Events[6].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[6].Message, Is.EqualTo("DensityOfWater must be in range [950, 1050]."));
            Assert.That(validationResult.Events[7].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[7].Message, Is.EqualTo("SoilElasticity must be larger than 0."));
            Assert.That(validationResult.Events[8].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[8].Message, Is.EqualTo("StiffnessRelationNu must be larger than 0."));
            Assert.That(validationResult.Events[9].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[9].Message, Is.EqualTo("Thickness must be larger than 0."));
            Assert.That(validationResult.Events[10].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[10].Message, Is.EqualTo("ElasticModulus must be larger than 0."));
            Assert.That(validationResult.Events[11].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[11].Message, Is.EqualTo("Thickness must be larger than 0."));
            Assert.That(validationResult.Events[12].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[12].Message, Is.EqualTo("ElasticModulus must be larger than 0."));
            Assert.That(validationResult.Events[13].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[13].Message, Is.EqualTo("AverageNumberOfWavesCtm must be larger than 0."));
        }

        [Test]
        public void GivenCalculationInputWithInvalidGrassRevetmentWaveImpactLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties =
                new GrassWaveImpactLocationConstructionProperties(15, GrassTopLayerType.ClosedSod)
                {
                    InitialDamage = -0.1,
                    FailureNumber = -1,
                    TimeLineAgwi = -2,
                    TimeLineBgwi = 0,
                    TimeLineCgwi = -0.5,
                    MinimumWaveHeightTemax = 8000,
                    MaximumWaveHeightTemin = 11,
                    WaveAngleImpactNwa = 3,
                    WaveAngleImpactQwa = 6,
                    WaveAngleImpactRwa = 0,
                    UpperLimitLoadingAul = 1,
                    LowerLimitLoadingAll = 1
                };

            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Failed));
            Assert.That(validationResult.Events, Has.Count.EqualTo(11));

            Assert.That(validationResult.Events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[0].Message, Is.EqualTo("InitialDamage must be equal to 0 or larger."));
            Assert.That(validationResult.Events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[1].Message, Is.EqualTo("FailureNumber must be equal to InitialDamage or larger."));
            Assert.That(validationResult.Events[2].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[2].Message, Is.EqualTo("TimeLineAgwi must be larger than TimeLineCgwi."));
            Assert.That(validationResult.Events[3].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[3].Message, Is.EqualTo("TimeLineBgwi must be smaller than 0."));
            Assert.That(validationResult.Events[4].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[4].Message, Is.EqualTo("TimeLineCgwi must be equal to 0 or larger."));
            Assert.That(validationResult.Events[5].Type, Is.EqualTo(EventType.Warning));
            Assert.That(validationResult.Events[5].Message, Is.EqualTo("MinimumWaveHeightTemax should be in range {1000000, 3600000]."));
            Assert.That(validationResult.Events[6].Type, Is.EqualTo(EventType.Warning));
            Assert.That(validationResult.Events[6].Message, Is.EqualTo("MaximumWaveHeightTemin should be in range [3.6, 10}."));
            Assert.That(validationResult.Events[7].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[7].Message, Is.EqualTo("WaveAngleImpactNwa must be equal to 1 or smaller."));
            Assert.That(validationResult.Events[8].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[8].Message, Is.EqualTo("WaveAngleImpactQwa must be in range [0, 1]."));
            Assert.That(validationResult.Events[9].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[9].Message, Is.EqualTo("WaveAngleImpactRwa must be larger than 0."));
            Assert.That(validationResult.Events[10].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[10].Message, Is.EqualTo("UpperLimitLoadingAul must be smaller than LowerLimitLoadingAll."));
        }

        [Test]
        public void
            GivenCalculationInputWithInvalidGrassRevetmentWaveRunupRayleighLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod)
            {
                InitialDamage = -0.1,
                FailureNumber = -1,
                CriticalCumulativeOverload = -2,
                CriticalFrontVelocity = -1,
                IncreasedLoadTransitionAlphaM = -11,
                ReducedStrengthTransitionAlphaS = -3,
                AverageNumberOfWavesCtm = 0,
                FixedNumberOfWaves = 0,
                FrontVelocityCu = -1
            };

            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Failed));
            Assert.That(validationResult.Events, Has.Count.EqualTo(9));
            Assert.That(validationResult.Events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[0].Message, Is.EqualTo("InitialDamage must be equal to 0 or larger."));
            Assert.That(validationResult.Events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[1].Message, Is.EqualTo("FailureNumber must be equal to InitialDamage or larger."));
            Assert.That(validationResult.Events[2].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[2].Message, Is.EqualTo("CriticalCumulativeOverload must be larger than 0."));
            Assert.That(validationResult.Events[3].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[3].Message, Is.EqualTo("CriticalFrontVelocity must be equal to 0 or larger."));
            Assert.That(validationResult.Events[4].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[4].Message, Is.EqualTo("IncreasedLoadTransitionAlphaM must be equal to 0 or larger."));
            Assert.That(validationResult.Events[5].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[5].Message, Is.EqualTo("ReducedStrengthTransitionAlphaS must be equal to 0 or larger."));
            Assert.That(validationResult.Events[6].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[6].Message, Is.EqualTo("AverageNumberOfWavesCtm must be larger than 0."));
            Assert.That(validationResult.Events[7].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[7].Message, Is.EqualTo("FixedNumberOfWaves must be larger than 0."));
            Assert.That(validationResult.Events[8].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[8].Message, Is.EqualTo("FrontVelocityCu must be larger than 0."));
        }

        [Test]
        public void GivenCalculationInputWithInvalidGrassRevetmentOvertoppingLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties = new GrassOvertoppingLocationConstructionProperties(
                25, GrassTopLayerType.ClosedSod)
            {
                DikeHeight = 15,
                InitialDamage = -0.1,
                FailureNumber = -1,
                CriticalCumulativeOverload = -2,
                CriticalFrontVelocity = -1,
                AccelerationAlphaAForCrest = -0.1,
                AccelerationAlphaAForInnerSlope = -0.1,
                FixedNumberOfWaves = 0,
                FrontVelocityCwo = -0.1,
                AverageNumberOfWavesCtm = 0,
                IncreasedLoadTransitionAlphaM = -11,
                ReducedStrengthTransitionAlphaS = -3
            };

            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfileSegment(20, 10, 30, 10);
            builder.AddDikeProfileSegment(30, 10, 40, 5);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(40, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Failed));
            Assert.That(validationResult.Events, Has.Count.EqualTo(11));
            Assert.That(validationResult.Events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[0].Message, Is.EqualTo("InitialDamage must be equal to 0 or larger."));
            Assert.That(validationResult.Events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[1].Message, Is.EqualTo("FailureNumber must be equal to InitialDamage or larger."));
            Assert.That(validationResult.Events[2].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[2].Message, Is.EqualTo("CriticalCumulativeOverload must be larger than 0."));
            Assert.That(validationResult.Events[3].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[3].Message, Is.EqualTo("CriticalFrontVelocity must be equal to 0 or larger."));
            Assert.That(validationResult.Events[4].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[4].Message, Is.EqualTo("IncreasedLoadTransitionAlphaM must be equal to 0 or larger."));
            Assert.That(validationResult.Events[5].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[5].Message, Is.EqualTo("ReducedStrengthTransitionAlphaS must be equal to 0 or larger."));
            Assert.That(validationResult.Events[6].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[6].Message, Is.EqualTo("AverageNumberOfWavesCtm must be larger than 0."));
            Assert.That(validationResult.Events[7].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[7].Message, Is.EqualTo("FixedNumberOfWaves must be larger than 0."));
            Assert.That(validationResult.Events[8].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[8].Message, Is.EqualTo("AccelerationAlphaA must be equal to 0 or larger."));
            Assert.That(validationResult.Events[9].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[9].Message, Is.EqualTo("AccelerationAlphaA must be equal to 0 or larger."));
            Assert.That(validationResult.Events[10].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[10].Message, Is.EqualTo("FrontVelocityCwo must be larger than 0."));
        }

        [Test]
        public void
            GivenCalculationInputWithGrassRevetmentOvertoppingLocationAndWaterLevelHigherThanEnforcedDikeHeight_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            const double dikeHeight = 10.0;
            const double waterLevel = dikeHeight + 0.1;

            var constructionProperties = new GrassOvertoppingLocationConstructionProperties(
                25, GrassTopLayerType.ClosedSod)
            {
                DikeHeight = dikeHeight
            };

            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, waterLevel, 5, 10, 30);
            builder.AddTimeStep(100, 150, waterLevel, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfileSegment(20, 10, 30, 10);
            builder.AddDikeProfileSegment(30, 10, 40, 5);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(40, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Successful));
            Assert.That(validationResult.Events, Has.Count.EqualTo(1));
            Assert.That(validationResult.Events[0].Type, Is.EqualTo(EventType.Warning));
            Assert.That(validationResult.Events[0].Message, Is.EqualTo("For one or more time steps the water level " +
                                                                       "exceeds the dike height. No damage will be " +
                                                                       "calculated for these time steps."));
        }

        [Test]
        public void
            GivenCalculationInputWithGrassRevetmentOvertoppingLocationAndWaterLevelEqualToEnforcedDikeHeight_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            const double dikeHeight = 10.0;

            var constructionProperties = new GrassOvertoppingLocationConstructionProperties(
                25, GrassTopLayerType.ClosedSod)
            {
                DikeHeight = dikeHeight
            };

            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, dikeHeight, 5, 10, 30);
            builder.AddTimeStep(100, 150, dikeHeight, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfileSegment(20, 10, 30, 10);
            builder.AddDikeProfileSegment(30, 10, 40, 5);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(40, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Successful));
            Assert.That(validationResult.Events, Has.Count.EqualTo(0));
        }

        [Test]
        public void
            GivenCalculationInputWithGrassRevetmentOvertoppingLocationAndWaterLevelHigherThanDerivedDikeHeight_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            const double heightOuterCrest = 10.0;
            const double waterLevel = heightOuterCrest + 0.1;

            var constructionProperties = new GrassOvertoppingLocationConstructionProperties(
                25, GrassTopLayerType.ClosedSod);

            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, waterLevel, 5, 10, 30);
            builder.AddTimeStep(100, 150, waterLevel, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, heightOuterCrest);
            builder.AddDikeProfileSegment(20, heightOuterCrest, 30, 10);
            builder.AddDikeProfileSegment(30, 10, 40, 5);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(40, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Successful));
            Assert.That(validationResult.Events, Has.Count.EqualTo(1));
            Assert.That(validationResult.Events[0].Type, Is.EqualTo(EventType.Warning));
            Assert.That(validationResult.Events[0].Message, Is.EqualTo("For one or more time steps the water level " +
                                                                       "exceeds the dike height. No damage will be " +
                                                                       "calculated for these time steps."));
        }

        [Test]
        public void
            GivenCalculationInputWithGrassRevetmentOvertoppingLocationAndWaterLevelEqualToDerivedDikeHeight_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            const double heightOuterCrest = 10.0;

            var constructionProperties = new GrassOvertoppingLocationConstructionProperties(
                25, GrassTopLayerType.ClosedSod);

            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, heightOuterCrest, 5, 10, 30);
            builder.AddTimeStep(100, 150, heightOuterCrest, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, heightOuterCrest);
            builder.AddDikeProfileSegment(20, heightOuterCrest, 30, 10);
            builder.AddDikeProfileSegment(30, 10, 40, 5);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(40, CharacteristicPointType.InnerToe);
            builder.AddGrassOvertoppingLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Successful));
            Assert.That(validationResult.Events, Has.Count.EqualTo(0));
        }

        [Test]
        public void GivenValidCalculationInput_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddTimeStep(100, 150, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10.0, 5.0, 20.0, 10.0);
            builder.AddDikeProfileSegment(20, 10, 30, 10);
            builder.AddDikeProfileSegment(30, 10, 40, 5);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(40, CharacteristicPointType.InnerToe);

            var asphaltWaveImpactLocationConstructionProperties = new AsphaltWaveImpactLocationConstructionProperties(
                12, AsphaltTopLayerType.HydraulicAsphaltConcrete, 1, 0.5, 3, 2);

            var grassWaveImpactLocationConstructionProperties =
                new GrassWaveImpactLocationConstructionProperties(14, GrassTopLayerType.ClosedSod);

            var grassRevetmentWaveRunupRayleighLocationConstructionProperties = new
                GrassRevetmentWaveRunupRayleighLocationConstructionProperties(19, GrassTopLayerType.ClosedSod);

            var naturalStoneRevetmentLocationConstructionProperties =
                new NaturalStoneRevetmentLocationConstructionProperties(
                    15, NaturalStoneTopLayerType.NordicStone, 0.5, 4.6);

            var grassOvertoppingLocationConstructionProperties =
                new GrassOvertoppingLocationConstructionProperties(25, GrassTopLayerType.ClosedSod);

            builder.AddAsphaltWaveImpactLocation(asphaltWaveImpactLocationConstructionProperties);
            builder.AddGrassWaveImpactLocation(grassWaveImpactLocationConstructionProperties);
            builder.AddGrassWaveRunupRayleighLocation(grassRevetmentWaveRunupRayleighLocationConstructionProperties);
            builder.AddNaturalStoneLocation(naturalStoneRevetmentLocationConstructionProperties);
            builder.AddGrassOvertoppingLocation(grassOvertoppingLocationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Successful));
            Assert.That(validationResult.Events, Has.Count.EqualTo(0));
        }

        [Test]
        public void GivenCalculationInputWithInvalidNaturalStoneRevetmentLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties = new NaturalStoneRevetmentLocationConstructionProperties(
                15, NaturalStoneTopLayerType.NordicStone, 0, 10)
            {
                InitialDamage = -0.1,
                FailureNumber = -1,
                SlopeUpperLevelAus = 0.3,
                SlopeLowerLevelAls = 0
            };

            var builder = new CalculationInputBuilder(0);
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddNaturalStoneLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.That(validationResult.Successful, Is.True);
            Assert.That(validationResult.Data, Is.EqualTo(ValidationResultType.Failed));
            Assert.That(validationResult.Events, Has.Count.EqualTo(6));

            Assert.That(validationResult.Events[0].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[0].Message, Is.EqualTo("InitialDamage must be equal to 0 or larger."));
            Assert.That(validationResult.Events[1].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[1].Message, Is.EqualTo("FailureNumber must be equal to InitialDamage or larger."));
            Assert.That(validationResult.Events[2].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[2].Message, Is.EqualTo("RelativeDensity must be in range {0, 10}."));
            Assert.That(validationResult.Events[3].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[3].Message, Is.EqualTo("ThicknessTopLayer must be in range {0, 1}."));
            Assert.That(validationResult.Events[4].Type, Is.EqualTo(EventType.Warning));
            Assert.That(validationResult.Events[4].Message, Is.EqualTo("SlopeUpperLevelAus should be in range [0.01, 0.2]."));
            Assert.That(validationResult.Events[5].Type, Is.EqualTo(EventType.Error));
            Assert.That(validationResult.Events[5].Message, Is.EqualTo("SlopeLowerLevelAls must be larger than 0."));
        }
    }
}