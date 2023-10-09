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
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Data.GrassRevetmentOvertopping;
using DiKErnel.Integration.Data.GrassRevetmentWaveImpact;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneRevetment;
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
            var builder = new CalculationInputBuilder();
            builder.AddTimeStep(90, 100, 10, -1, 30, -10);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(
                new GrassRevetmentWaveImpactLocationConstructionProperties(15, GrassRevetmentTopLayerType.ClosedSod));

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Failed, validationResult.Data);
            Assert.AreEqual(3, validationResult.Events.Count);
            Assert.AreEqual(EventType.Error, validationResult.Events[0].Type);
            Assert.AreEqual("WaveHeightHm0 must be larger than 0.", validationResult.Events[0].Message);
            Assert.AreEqual(EventType.Warning, validationResult.Events[1].Type);
            Assert.AreEqual("WavePeriodTm10 should be in range {0.5, 25}.", validationResult.Events[1].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[2].Type);
            Assert.AreEqual("WaveDirection must be in range [0, 360].", validationResult.Events[2].Message);
        }

        [Test]
        public void GivenCalculationInputWithInvalidProfileData_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.SetDikeOrientation(-10);
            builder.AddDikeProfileSegment(10, 5, 20, 10, 1.5);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);

            var asphaltRevetmentWaveImpactLocationConstructionProperties =
                new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                    12, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1, 0.5, 3, 2);

            builder.AddAsphaltWaveImpactLocation(asphaltRevetmentWaveImpactLocationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Failed, validationResult.Data);
            Assert.AreEqual(2, validationResult.Events.Count);
            Assert.AreEqual(EventType.Error, validationResult.Events[0].Type);
            Assert.AreEqual("Dike orientation must be in range [0, 360].", validationResult.Events[0].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[1].Type);
            Assert.AreEqual("Roughness coefficient must be in range [0.5, 1].", validationResult.Events[1].Message);
        }

        [Test]
        public void GivenCalculationInputWithInvalidAsphaltRevetmentWaveImpactLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties = new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                15, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 0, 0, -1, -8)
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

            var builder = new CalculationInputBuilder();
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddAsphaltWaveImpactLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Failed, validationResult.Data);
            Assert.AreEqual(14, validationResult.Events.Count);
            Assert.AreEqual(EventType.Error, validationResult.Events[0].Type);
            Assert.AreEqual("InitialDamage must be equal to 0 or larger.", validationResult.Events[0].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[1].Type);
            Assert.AreEqual("FailureNumber must be equal to InitialDamage or larger.",
                            validationResult.Events[1].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[2].Type);
            Assert.AreEqual("FatigueAlpha must be larger than 0.", validationResult.Events[2].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[3].Type);
            Assert.AreEqual("FatigueBeta must be larger than 0.", validationResult.Events[3].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[4].Type);
            Assert.AreEqual("FailureTension must be larger than 0.", validationResult.Events[4].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[5].Type);
            Assert.AreEqual("ImpactNumberC must be larger than 0.", validationResult.Events[5].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[6].Type);
            Assert.AreEqual("DensityOfWater must be in range [950, 1050].", validationResult.Events[6].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[7].Type);
            Assert.AreEqual("SoilElasticity must be larger than 0.", validationResult.Events[7].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[8].Type);
            Assert.AreEqual("StiffnessRelationNu must be larger than 0.", validationResult.Events[8].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[9].Type);
            Assert.AreEqual("Thickness must be larger than 0.", validationResult.Events[9].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[10].Type);
            Assert.AreEqual("ElasticModulus must be larger than 0.", validationResult.Events[10].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[11].Type);
            Assert.AreEqual("Thickness must be larger than 0.", validationResult.Events[11].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[12].Type);
            Assert.AreEqual("ElasticModulus must be larger than 0.", validationResult.Events[12].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[13].Type);
            Assert.AreEqual("AverageNumberOfWavesCtm must be larger than 0.", validationResult.Events[13].Message);
        }

        [Test]
        public void GivenCalculationInputWithInvalidGrassRevetmentWaveImpactLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties =
                new GrassRevetmentWaveImpactLocationConstructionProperties(15, GrassRevetmentTopLayerType.ClosedSod)
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

            var builder = new CalculationInputBuilder();
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveImpactLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Failed, validationResult.Data);
            Assert.AreEqual(11, validationResult.Events.Count);

            Assert.AreEqual(EventType.Error, validationResult.Events[0].Type);
            Assert.AreEqual("InitialDamage must be equal to 0 or larger.", validationResult.Events[0].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[1].Type);
            Assert.AreEqual("FailureNumber must be equal to InitialDamage or larger.",
                            validationResult.Events[1].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[2].Type);
            Assert.AreEqual("TimeLineAgwi must be larger than TimeLineCgwi.", validationResult.Events[2].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[3].Type);
            Assert.AreEqual("TimeLineBgwi must be smaller than 0.", validationResult.Events[3].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[4].Type);
            Assert.AreEqual("TimeLineCgwi must be equal to 0 or larger.", validationResult.Events[4].Message);
            Assert.AreEqual(EventType.Warning, validationResult.Events[5].Type);
            Assert.AreEqual("MinimumWaveHeightTemax should be in range {1000000, 3600000].",
                            validationResult.Events[5].Message);
            Assert.AreEqual(EventType.Warning, validationResult.Events[6].Type);
            Assert.AreEqual("MaximumWaveHeightTemin should be in range [3.6, 10}.", validationResult.Events[6].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[7].Type);
            Assert.AreEqual("WaveAngleImpactNwa must be equal to 1 or smaller.", validationResult.Events[7].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[8].Type);
            Assert.AreEqual("WaveAngleImpactQwa must be in range [0, 1].", validationResult.Events[8].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[9].Type);
            Assert.AreEqual("WaveAngleImpactRwa must be larger than 0.", validationResult.Events[9].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[10].Type);
            Assert.AreEqual("UpperLimitLoadingAul must be smaller than LowerLimitLoadingAll.",
                            validationResult.Events[10].Message);
        }

        [Test]
        public void
            GivenCalculationInputWithInvalidGrassRevetmentWaveRunupRayleighLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                15, 20, GrassRevetmentTopLayerType.ClosedSod)
            {
                InitialDamage = -0.1,
                FailureNumber = -1,
                CriticalCumulativeOverload = -2,
                RepresentativeWaveRunup2PGammab = 0,
                RepresentativeWaveRunup2PGammaf = -0.5,
                CriticalFrontVelocity = -1,
                IncreasedLoadTransitionAlphaM = -11,
                ReducedStrengthTransitionAlphaS = -3,
                AverageNumberOfWavesCtm = 0,
                FixedNumberOfWaves = 0,
                FrontVelocityCu = -1
            };

            var builder = new CalculationInputBuilder();
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddGrassWaveRunupRayleighLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Failed, validationResult.Data);
            Assert.AreEqual(12, validationResult.Events.Count);
            Assert.AreEqual(EventType.Error, validationResult.Events[0].Type);
            Assert.AreEqual("InitialDamage must be equal to 0 or larger.", validationResult.Events[0].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[1].Type);
            Assert.AreEqual("FailureNumber must be equal to InitialDamage or larger.",
                            validationResult.Events[1].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[2].Type);
            Assert.AreEqual("CriticalCumulativeOverload must be larger than 0.", validationResult.Events[2].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[3].Type);
            Assert.AreEqual("RepresentativeWaveRunup2PGammab must be in range [0.6, 1].",
                            validationResult.Events[3].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[4].Type);
            Assert.AreEqual("RepresentativeWaveRunup2PGammaf must be in range [0.5, 1].",
                            validationResult.Events[4].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[5].Type);
            Assert.AreEqual("CriticalFrontVelocity must be equal to 0 or larger.", validationResult.Events[5].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[6].Type);
            Assert.AreEqual("IncreasedLoadTransitionAlphaM must be equal to 0 or larger.",
                            validationResult.Events[6].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[7].Type);
            Assert.AreEqual("ReducedStrengthTransitionAlphaS must be equal to 0 or larger.",
                            validationResult.Events[7].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[8].Type);
            Assert.AreEqual("OuterSlope must be in range {0, 1}.", validationResult.Events[8].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[9].Type);
            Assert.AreEqual("AverageNumberOfWavesCtm must be larger than 0.", validationResult.Events[9].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[10].Type);
            Assert.AreEqual("FixedNumberOfWaves must be larger than 0.", validationResult.Events[10].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[11].Type);
            Assert.AreEqual("FrontVelocityCu must be larger than 0.", validationResult.Events[11].Message);
        }

        [Test]
        public void GivenCalculationInputWithInvalidGrassRevetmentOvertoppingLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                25, GrassRevetmentTopLayerType.ClosedSod)
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

            var builder = new CalculationInputBuilder();
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
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Failed, validationResult.Data);
            Assert.AreEqual(11, validationResult.Events.Count);
            Assert.AreEqual(EventType.Error, validationResult.Events[0].Type);
            Assert.AreEqual("InitialDamage must be equal to 0 or larger.", validationResult.Events[0].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[1].Type);
            Assert.AreEqual("FailureNumber must be equal to InitialDamage or larger.",
                            validationResult.Events[1].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[2].Type);
            Assert.AreEqual("CriticalCumulativeOverload must be larger than 0.", validationResult.Events[2].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[3].Type);
            Assert.AreEqual("CriticalFrontVelocity must be equal to 0 or larger.", validationResult.Events[3].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[4].Type);
            Assert.AreEqual("AccelerationAlphaA must be equal to 0 or larger.", validationResult.Events[4].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[5].Type);
            Assert.AreEqual("AccelerationAlphaA must be equal to 0 or larger.", validationResult.Events[5].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[6].Type);
            Assert.AreEqual("FixedNumberOfWaves must be larger than 0.", validationResult.Events[6].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[7].Type);
            Assert.AreEqual("FrontVelocityCwo must be larger than 0.", validationResult.Events[7].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[8].Type);
            Assert.AreEqual("AverageNumberOfWavesCtm must be larger than 0.", validationResult.Events[8].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[9].Type);
            Assert.AreEqual("IncreasedLoadTransitionAlphaM must be equal to 0 or larger.",
                            validationResult.Events[9].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[10].Type);
            Assert.AreEqual("ReducedStrengthTransitionAlphaS must be equal to 0 or larger.",
                            validationResult.Events[10].Message);
        }

        [Test]
        public void
            GivenCalculationInputWithGrassRevetmentOvertoppingLocationAndWaterLevelHigherThanEnforcedDikeHeight_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            const double dikeHeight = 10.0;
            const double waterLevel = dikeHeight + 0.1;

            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                25, GrassRevetmentTopLayerType.ClosedSod)
            {
                DikeHeight = dikeHeight
            };

            var builder = new CalculationInputBuilder();
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
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Successful, validationResult.Data);
            Assert.AreEqual(1, validationResult.Events.Count);
            Assert.AreEqual(EventType.Warning, validationResult.Events[0].Type);
            Assert.AreEqual("For one or more time steps the water level exceeds the dike height. No damage will be " +
                            "calculated for these time steps.", validationResult.Events[0].Message);
        }

        [Test]
        public void
            GivenCalculationInputWithGrassRevetmentOvertoppingLocationAndWaterLevelEqualToEnforcedDikeHeight_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            const double dikeHeight = 10.0;

            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                25, GrassRevetmentTopLayerType.ClosedSod)
            {
                DikeHeight = dikeHeight
            };

            var builder = new CalculationInputBuilder();
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
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Successful, validationResult.Data);
            Assert.AreEqual(0, validationResult.Events.Count);
        }

        [Test]
        public void
            GivenCalculationInputWithGrassRevetmentOvertoppingLocationAndWaterLevelHigherThanDerivedDikeHeight_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            const double heightOuterCrest = 10.0;
            const double waterLevel = heightOuterCrest + 0.1;

            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                25, GrassRevetmentTopLayerType.ClosedSod);

            var builder = new CalculationInputBuilder();
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
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Successful, validationResult.Data);
            Assert.AreEqual(1, validationResult.Events.Count);
            Assert.AreEqual(EventType.Warning, validationResult.Events[0].Type);
            Assert.AreEqual("For one or more time steps the water level exceeds the dike height. No damage will be " +
                            "calculated for these time steps.", validationResult.Events[0].Message);
        }

        [Test]
        public void
            GivenCalculationInputWithGrassRevetmentOvertoppingLocationAndWaterLevelEqualToDerivedDikeHeight_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            const double heightOuterCrest = 10.0;

            var constructionProperties = new GrassRevetmentOvertoppingLocationConstructionProperties(
                25, GrassRevetmentTopLayerType.ClosedSod);

            var builder = new CalculationInputBuilder();
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
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Successful, validationResult.Data);
            Assert.AreEqual(0, validationResult.Events.Count);
        }

        [Test]
        public void GivenValidCalculationInput_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var builder = new CalculationInputBuilder();
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddTimeStep(100, 150, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10.0, 5.0, 20.0, 10.0);
            builder.AddDikeProfileSegment(20, 10, 30, 10);
            builder.AddDikeProfileSegment(30, 10, 40, 5);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(40, CharacteristicPointType.InnerToe);

            var asphaltRevetmentWaveImpactLocationConstructionProperties =
                new AsphaltRevetmentWaveImpactLocationConstructionProperties(
                    12, AsphaltRevetmentTopLayerType.HydraulicAsphaltConcrete, 1, 0.5, 3, 2);

            var grassRevetmentWaveImpactLocationConstructionProperties =
                new GrassRevetmentWaveImpactLocationConstructionProperties(
                    14, GrassRevetmentTopLayerType.ClosedSod);

            var grassRevetmentWaveRunupRayleighLocationConstructionProperties = new
                GrassRevetmentWaveRunupRayleighLocationConstructionProperties
                (19, 0.71, GrassRevetmentTopLayerType.ClosedSod);

            var naturalStoneRevetmentLocationConstructionProperties =
                new NaturalStoneRevetmentLocationConstructionProperties(
                    15, NaturalStoneRevetmentTopLayerType.NordicStone, 0.5, 4.6);

            var grassRevetmentOvertoppingLocationConstructionProperties =
                new GrassRevetmentOvertoppingLocationConstructionProperties(
                    25, GrassRevetmentTopLayerType.ClosedSod);

            builder.AddAsphaltWaveImpactLocation(asphaltRevetmentWaveImpactLocationConstructionProperties);
            builder.AddGrassWaveImpactLocation(grassRevetmentWaveImpactLocationConstructionProperties);
            builder.AddGrassWaveRunupRayleighLocation(grassRevetmentWaveRunupRayleighLocationConstructionProperties);
            builder.AddNaturalStoneLocation(naturalStoneRevetmentLocationConstructionProperties);
            builder.AddGrassOvertoppingLocation(grassRevetmentOvertoppingLocationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Successful, validationResult.Data);
            Assert.AreEqual(0, validationResult.Events.Count);
        }

        [Test]
        public void GivenCalculationInputWithInvalidNaturalStoneRevetmentLocation_WhenValidating_ThenReturnsExpectedValidationResult()
        {
            // Given
            var constructionProperties = new NaturalStoneRevetmentLocationConstructionProperties(
                15, NaturalStoneRevetmentTopLayerType.NordicStone, 0, 10)
            {
                InitialDamage = -0.1,
                FailureNumber = -1,
                SlopeUpperLevelAus = 0.3,
                SlopeLowerLevelAls = 0
            };

            var builder = new CalculationInputBuilder();
            builder.AddTimeStep(0, 100, 10, 5, 10, 30);
            builder.AddDikeProfileSegment(10, 5, 20, 10);
            builder.AddDikeProfilePoint(10, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(20, CharacteristicPointType.OuterCrest);
            builder.AddNaturalStoneLocation(constructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            DataResult<ValidationResultType> validationResult = Validator.Validate(calculationInput.Data);

            // Then
            Assert.True(validationResult.Successful);
            Assert.AreEqual(ValidationResultType.Failed, validationResult.Data);
            Assert.AreEqual(6, validationResult.Events.Count);

            Assert.AreEqual(EventType.Error, validationResult.Events[0].Type);
            Assert.AreEqual("InitialDamage must be equal to 0 or larger.", validationResult.Events[0].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[1].Type);
            Assert.AreEqual("FailureNumber must be equal to InitialDamage or larger.",
                            validationResult.Events[1].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[2].Type);
            Assert.AreEqual("RelativeDensity must be in range {0, 10}.", validationResult.Events[2].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[3].Type);
            Assert.AreEqual("ThicknessTopLayer must be in range {0, 1}.", validationResult.Events[3].Message);
            Assert.AreEqual(EventType.Warning, validationResult.Events[4].Type);
            Assert.AreEqual("SlopeUpperLevelAus should be in range [0.01, 0.2].", validationResult.Events[4].Message);
            Assert.AreEqual(EventType.Error, validationResult.Events[5].Type);
            Assert.AreEqual("SlopeLowerLevelAls must be larger than 0.", validationResult.Events[5].Message);
        }
    }
}