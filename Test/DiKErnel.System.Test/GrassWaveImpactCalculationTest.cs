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
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.System.Test
{
    [TestFixture]
    public class GrassWaveImpactCalculationTest : CalculationTest
    {
        [Test]
        public void GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassWaveImpactLocationConstructionProperties(
                11, GrassTopLayerType.ClosedSod);

            builder.AddGrassWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.2922807852067, 14375);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassWaveImpactLocationConstructionProperties(
                11, GrassTopLayerType.ClosedSod)
            {
                TimeLineAgwi = 1.1,
                TimeLineBgwi = -0.00003,
                TimeLineCgwi = 0.3
            };

            builder.AddGrassWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.3481058044211, 15809);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassWaveImpactLocationConstructionProperties(
                11, GrassTopLayerType.ClosedSod)
            {
                InitialDamage = 0.4,
                FailureNumber = 1.2
            };

            builder.AddGrassWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.6922807852067, 13429);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassWaveImpactLocationConstructionProperties(
                11, GrassTopLayerType.ClosedSod)
            {
                WaveAngleImpactNwa = 0.8,
                WaveAngleImpactQwa = 0.5,
                WaveAngleImpactRwa = 40
            };

            builder.AddGrassWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.28595658264855, 14416);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase5_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassWaveImpactLocationConstructionProperties(
                11, GrassTopLayerType.ClosedSod)
            {
                UpperLimitLoadingAul = 0.1,
                LowerLimitLoadingAll = 0.45
            };

            builder.AddGrassWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.07849231778936, 17130);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new GrassWaveImpactLocationConstructionProperties(
                11, GrassTopLayerType.OpenSod);

            builder.AddGrassWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.74141684707082, 13466);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new GrassWaveImpactLocationConstructionProperties(
                11, GrassTopLayerType.ClosedSod);

            builder.AddGrassWaveImpactLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.91616541078064, 6938);
        }

        private static CalculationInputBuilder CreateBuilderForSchematization1()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(0, 900, 0.5, 0.5, 3, 0);
            builder.AddTimeStep(900, 1800, 0.55, 0.6, 3, 15);
            builder.AddTimeStep(1800, 2700, 0.6, 0.65, 3, 30);
            builder.AddTimeStep(2700, 3600, 0.65, 0.7, 3, 45);
            builder.AddTimeStep(3600, 4500, 0.7, 0.75, 3, 60);
            builder.AddTimeStep(4500, 5400, 0.75, 0.8, 3, 70);
            builder.AddTimeStep(5400, 6300, 0.8, 0.85, 3, 75);
            builder.AddTimeStep(6300, 7200, 0.85, 0.9, 3, 70);
            builder.AddTimeStep(7200, 8100, 0.9, 0.95, 3, 60);
            builder.AddTimeStep(8100, 9000, 0.95, 1, 3, 45);
            builder.AddTimeStep(9000, 9900, 1, 1.1, 3, 30);
            builder.AddTimeStep(9900, 10800, 1.03, 1.1, 3, 15);
            builder.AddTimeStep(10800, 11700, 1.03, 1.15, 3, 0);
            builder.AddTimeStep(11700, 12600, 1, 1.2, 3, 0);
            builder.AddTimeStep(12600, 13500, 0.95, 1.23, 3, 0);
            builder.AddTimeStep(13500, 14400, 0.9, 1.2, 3, 0);
            builder.AddTimeStep(14400, 15300, 0.85, 1.15, 3, 0);
            builder.AddTimeStep(15300, 16200, 0.8, 1.1, 3, 0);
            builder.AddTimeStep(16200, 17100, 0.75, 1, 3, 0);
            builder.AddTimeStep(17100, 18000, 0.7, 1, 3, 0);
            builder.AddTimeStep(18000, 18900, 0.65, 0.95, 3, 0);
            builder.AddTimeStep(18900, 19800, 0.6, 0.95, 3, 0);
            builder.AddTimeStep(19800, 20700, 0.55, 0.9, 3, 0);
            builder.AddTimeStep(20700, 21600, 0.5, 0.9, 3, 0);

            builder.AddDikeProfileSegment(5, -1, 55, 11.5);

            builder.AddDikeProfilePoint(5, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(55, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization2()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(0, 900, 0.5, 0.3, 3, 0);
            builder.AddTimeStep(900, 1800, 0.55, 0.4, 3, 15);
            builder.AddTimeStep(1800, 2700, 0.6, 0.45, 3, 30);
            builder.AddTimeStep(2700, 3600, 0.65, 0.5, 3, 45);
            builder.AddTimeStep(3600, 4500, 0.7, 0.55, 3, 60);
            builder.AddTimeStep(4500, 5400, 0.75, 0.6, 3, 70);
            builder.AddTimeStep(5400, 6300, 0.8, 0.65, 3, 75);
            builder.AddTimeStep(6300, 7200, 0.85, 0.7, 3, 70);
            builder.AddTimeStep(7200, 8100, 0.9, 0.75, 3, 60);
            builder.AddTimeStep(8100, 9000, 0.95, 0.8, 3, 45);
            builder.AddTimeStep(9000, 9900, 1, 0.9, 3, 30);
            builder.AddTimeStep(9900, 10800, 1.03, 0.9, 3, 15);
            builder.AddTimeStep(10800, 11700, 1.03, 0.95, 3, 0);
            builder.AddTimeStep(11700, 12600, 1, 1, 3, 0);
            builder.AddTimeStep(12600, 13500, 0.95, 1.03, 3, 0);
            builder.AddTimeStep(13500, 14400, 0.9, 1, 3, 0);
            builder.AddTimeStep(14400, 15300, 0.85, 0.95, 3, 0);
            builder.AddTimeStep(15300, 16200, 0.8, 0.9, 3, 0);
            builder.AddTimeStep(16200, 17100, 0.75, 0.8, 3, 0);
            builder.AddTimeStep(17100, 18000, 0.7, 0.8, 3, 0);
            builder.AddTimeStep(18000, 18900, 0.65, 0.75, 3, 0);
            builder.AddTimeStep(18900, 19800, 0.6, 0.75, 3, 0);
            builder.AddTimeStep(19800, 20700, 0.55, 0.7, 3, 0);
            builder.AddTimeStep(20700, 21600, 0.5, 0.7, 3, 0);

            builder.AddDikeProfileSegment(5, -1, 55, 11.5);

            builder.AddDikeProfilePoint(5, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(55, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization3()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(-3600, -3510, 0.5, 0.5, 3, 0);
            builder.AddTimeStep(-3510, -3330, 0.55, 0.6, 3, 15);
            builder.AddTimeStep(-3330, -3060, 0.6, 0.65, 3, 30);
            builder.AddTimeStep(-3060, -2700, 0.65, 0.7, 3, 45);
            builder.AddTimeStep(-2700, -2250, 0.7, 0.75, 3, 60);
            builder.AddTimeStep(-2250, -1710, 0.75, 0.8, 3, 70);
            builder.AddTimeStep(-1710, -1080, 0.8, 0.85, 3, 75);
            builder.AddTimeStep(-1080, -360, 0.85, 0.9, 3, 70);
            builder.AddTimeStep(-360, 450, 0.9, 0.95, 3, 60);
            builder.AddTimeStep(450, 1350, 0.95, 1, 3, 45);
            builder.AddTimeStep(1350, 2340, 1, 1.1, 3, 30);
            builder.AddTimeStep(2340, 3420, 1.03, 1.1, 3, 15);
            builder.AddTimeStep(3420, 4590, 1.03, 1.15, 3, 0);
            builder.AddTimeStep(4590, 5850, 1, 1.2, 3, 0);
            builder.AddTimeStep(5850, 7200, 0.95, 1.23, 3, 0);
            builder.AddTimeStep(7200, 8640, 0.9, 1.2, 3, 0);
            builder.AddTimeStep(8640, 10170, 0.85, 1.15, 3, 0);
            builder.AddTimeStep(10170, 11790, 0.8, 1.1, 3, 0);
            builder.AddTimeStep(11790, 13500, 0.75, 1, 3, 0);
            builder.AddTimeStep(13500, 15300, 0.7, 1, 3, 0);
            builder.AddTimeStep(15300, 17190, 0.65, 0.95, 3, 0);
            builder.AddTimeStep(17190, 19170, 0.6, 0.95, 3, 0);
            builder.AddTimeStep(19170, 21240, 0.55, 0.9, 3, 0);
            builder.AddTimeStep(21240, 21600, 0.5, 0.9, 3, 0);

            builder.AddDikeProfileSegment(5, -1, 55, 11.5);

            builder.AddDikeProfilePoint(5, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(55, CharacteristicPointType.OuterCrest);

            return builder;
        }
    }
}