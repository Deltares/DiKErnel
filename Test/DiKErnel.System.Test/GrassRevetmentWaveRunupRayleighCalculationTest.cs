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
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.System.Test
{
    [TestFixture]
    public class GrassRevetmentWaveRunupRayleighCalculationTest : CalculationTest
    {
        [Test]
        public void GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod);

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.17319166638798, 40475);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod)
            {
                CriticalCumulativeOverload = 8000,
                CriticalFrontVelocity = 6.2
            };

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.67514451030233, 35690);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod)
            {
                FixedNumberOfWaves = 500,
                FrontVelocityCu = 1.15
            };

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.78933048403964, 35043);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod)
            {
                InitialDamage = 0.3
            };

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.47319166638799, 35549);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.OpenSod);

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.51245044476551, 35971);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod)
            {
                IncreasedLoadTransitionAlphaM = 1.8,
                ReducedStrengthTransitionAlphaS = 0.9
            };

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.51861479666960, 35647);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod);

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.69846474391984);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3(20);

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.OpenSod);

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 7.24141421738371, 23824);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3(20, 0.5, 0.7, 0.8);

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod)
            {
                AverageNumberOfWavesCtm = 1
            };

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 0.01075989442725);
        }

        [Test]
        public void GivenCalculationInputForSchematization4Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization4();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod);

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.70123523079437, 32693);
        }

        [Test]
        public void GivenCalculationInputForSchematization5Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization5();

            var locationConstructionProperties = new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(
                15, GrassTopLayerType.ClosedSod);

            builder.AddGrassWaveRunupRayleighDiscreteLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.17257472297294, 18880);
        }

        private static CalculationInputBuilder CreateBuilderForSchematization1()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(0, 3600, 3, 0.5, 3, 50);
            builder.AddTimeStep(3600, 7200, 3.1, 0.7, 3.5, 45);
            builder.AddTimeStep(7200, 10800, 3.2, 1, 4, 40);
            builder.AddTimeStep(10800, 14400, 3.3, 1.3, 4.3, 35);
            builder.AddTimeStep(14400, 18000, 3.4, 1.5, 4.5, 30);
            builder.AddTimeStep(18000, 21600, 3.5, 1.8, 4.8, 25);
            builder.AddTimeStep(21600, 25200, 3.6, 2.1, 5.2, 20);
            builder.AddTimeStep(25200, 28800, 3.7, 2.5, 5.5, 15);
            builder.AddTimeStep(28800, 32400, 3.7, 2.8, 5.8, 10);
            builder.AddTimeStep(32400, 36000, 3.6, 2.8, 6, 5);
            builder.AddTimeStep(36000, 39600, 3.5, 2.5, 6, 0);
            builder.AddTimeStep(39600, 43200, 3.4, 2.1, 5.8, 0);
            builder.AddTimeStep(43200, 46800, 3.3, 1.8, 5.5, 5);
            builder.AddTimeStep(46800, 50400, 3.2, 1.5, 5.2, 10);
            builder.AddTimeStep(50400, 54000, 3.1, 1.3, 4.8, 15);
            builder.AddTimeStep(54000, 57600, 3, 1, 4.5, 20);

            builder.AddDikeProfileSegment(0, 0, 25, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization2()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(0, 3600, 3, 0.3, 3, 50);
            builder.AddTimeStep(3600, 7200, 3.1, 0.4, 3.5, 45);
            builder.AddTimeStep(7200, 10800, 3.2, 0.5, 3.9, 40);
            builder.AddTimeStep(10800, 14400, 3.3, 0.6, 4.2, 35);
            builder.AddTimeStep(14400, 18000, 3.4, 0.7, 4.6, 30);
            builder.AddTimeStep(18000, 21600, 3.5, 0.8, 4.9, 25);
            builder.AddTimeStep(21600, 25200, 3.6, 0.9, 5.2, 20);
            builder.AddTimeStep(25200, 28800, 3.7, 1, 5.5, 15);
            builder.AddTimeStep(28800, 32400, 3.7, 1.1, 5.7, 10);
            builder.AddTimeStep(32400, 36000, 3.6, 1.1, 5.7, 5);
            builder.AddTimeStep(36000, 39600, 3.5, 1, 5.5, 0);
            builder.AddTimeStep(39600, 43200, 3.4, 0.9, 5.2, 0);
            builder.AddTimeStep(43200, 46800, 3.3, 0.8, 4.9, 5);
            builder.AddTimeStep(46800, 50400, 3.2, 0.7, 4.6, 10);
            builder.AddTimeStep(50400, 54000, 3.1, 0.6, 4.2, 15);
            builder.AddTimeStep(54000, 57600, 3, 0.5, 3.9, 20);

            builder.AddDikeProfileSegment(0, 0, 25, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization3(double orientation = 0,
                                                                               double roughnessCoefficient1 = 1,
                                                                               double roughnessCoefficient2 = 1,
                                                                               double roughnessCoefficient3 = 1)
        {
            var builder = new CalculationInputBuilder(orientation);

            builder.AddTimeStep(0, 3600, 3, 0.5, 3, 50);
            builder.AddTimeStep(3600, 7200, 3.1, 0.7, 3.5, 45);
            builder.AddTimeStep(7200, 10800, 3.2, 1, 4, 40);
            builder.AddTimeStep(10800, 14400, 3.3, 1.3, 4.3, 35);
            builder.AddTimeStep(14400, 18000, 3.4, 1.5, 4.5, 30);
            builder.AddTimeStep(18000, 21600, 3.5, 1.8, 4.8, 25);
            builder.AddTimeStep(21600, 25200, 3.6, 2.1, 5.2, 20);
            builder.AddTimeStep(25200, 28800, 3.7, 2.5, 5.5, 15);
            builder.AddTimeStep(28800, 32400, 3.7, 2.8, 5.8, 10);
            builder.AddTimeStep(32400, 36000, 3.6, 2.8, 6, 5);
            builder.AddTimeStep(36000, 39600, 3.5, 2.5, 6, 0);
            builder.AddTimeStep(39600, 43200, 3.4, 2.1, 5.8, 0);
            builder.AddTimeStep(43200, 46800, 3.3, 1.8, 5.5, 5);
            builder.AddTimeStep(46800, 50400, 3.2, 1.5, 5.2, 10);
            builder.AddTimeStep(50400, 54000, 3.1, 1.3, 4.8, 15);
            builder.AddTimeStep(54000, 57600, 3, 1, 4.5, 20);

            builder.AddDikeProfileSegment(0, 0, 15, 4, roughnessCoefficient1);
            builder.AddDikeProfileSegment(15, 4, 20, 4.1, roughnessCoefficient2);
            builder.AddDikeProfileSegment(20, 4.1, 25, 7.5, roughnessCoefficient3);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization4()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(0, 3600, 3.5, 2.4, 4, 20);
            builder.AddTimeStep(3600, 7200, 3.6, 2.5, 4.2, 20);
            builder.AddTimeStep(7200, 10800, 3.7, 2.7, 4.4, 20);
            builder.AddTimeStep(10800, 14400, 3.8, 2.8, 4.5, 20);
            builder.AddTimeStep(14400, 18000, 3.9, 2.9, 4.8, 20);
            builder.AddTimeStep(18000, 21600, 3.95, 3, 5, 20);
            builder.AddTimeStep(21600, 25200, 4, 2.9, 5.2, 20);
            builder.AddTimeStep(25200, 28800, 3.95, 2.9, 5.5, 15);
            builder.AddTimeStep(28800, 32400, 3.8, 2.8, 5.8, 10);
            builder.AddTimeStep(32400, 36000, 3.6, 2.8, 6, 5);
            builder.AddTimeStep(36000, 39600, 3.5, 2.5, 6, 0);
            builder.AddTimeStep(39600, 43200, 3.4, 2.1, 5.8, 0);
            builder.AddTimeStep(43200, 46800, 3.3, 1.8, 5.5, 5);
            builder.AddTimeStep(46800, 50400, 3.2, 1.5, 5.2, 10);
            builder.AddTimeStep(50400, 54000, 3.1, 1.3, 4.8, 15);
            builder.AddTimeStep(54000, 57600, 3, 1, 4.5, 20);

            builder.AddDikeProfileSegment(0, 0, 25, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization5()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(-7200, -6840, 3, 0.5, 3, 50);
            builder.AddTimeStep(-6840, -6120, 3.1, 0.7, 3.5, 45);
            builder.AddTimeStep(-6120, -5040, 3.2, 1, 4, 40);
            builder.AddTimeStep(-5040, -3600, 3.3, 1.3, 4.3, 35);
            builder.AddTimeStep(-3600, -1800, 3.4, 1.5, 4.5, 30);
            builder.AddTimeStep(-1800, 360, 3.5, 1.8, 4.8, 25);
            builder.AddTimeStep(360, 2880, 3.6, 2.1, 5.2, 20);
            builder.AddTimeStep(2880, 5760, 3.7, 2.5, 5.5, 15);
            builder.AddTimeStep(5760, 9000, 3.7, 2.8, 5.8, 10);
            builder.AddTimeStep(9000, 12600, 3.6, 2.8, 6, 5);
            builder.AddTimeStep(12600, 16560, 3.5, 2.5, 6, 0);
            builder.AddTimeStep(16560, 20880, 3.4, 2.1, 5.8, 0);
            builder.AddTimeStep(20880, 25560, 3.3, 1.8, 5.5, 5);
            builder.AddTimeStep(25560, 30600, 3.2, 1.5, 5.2, 10);
            builder.AddTimeStep(30600, 36000, 3.1, 1.3, 4.8, 15);
            builder.AddTimeStep(36000, 43200, 3, 1, 4.5, 20);

            builder.AddDikeProfileSegment(0, 0, 25, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }
    }
}