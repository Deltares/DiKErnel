// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of
// Stichting Deltares and remain full property of Stichting Deltares at all times.
// All rights reserved.

using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.GrassRevetment;
using DiKErnel.Integration.Data.GrassRevetmentWaveRunup;
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

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.ClosedSod);

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.17424874554865, 40451);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.ClosedSod)
            {
                CriticalCumulativeOverload = 8000,
                CriticalFrontVelocity = 6.2
            };

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.67645627404328, 35682);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.ClosedSod)
            {
                FixedNumberOfWaves = 500,
                FrontVelocityCu = 1.15
            };

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.79080784328382, 35036);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.ClosedSod)
            {
                RepresentativeWaveRunup2PAru = 1.75,
                RepresentativeWaveRunup2PBru = 4.3,
                RepresentativeWaveRunup2PCru = 1.6
            };

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.58504284832686, 36169);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase5_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.OpenSod)
            {
                RepresentativeWaveRunup2PGammab = 0.7,
                RepresentativeWaveRunup2PGammaf = 0.7
            };

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.00238062787654, 53050);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase6_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.ClosedSod)
            {
                WaveAngleImpactAbeta = 0.0033,
                WaveAngleImpactBetamax = 30,
                AverageNumberOfWavesCtm = 1
            };

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.03411027331394, 45518);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase7_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.ClosedSod)
            {
                InitialDamage = 0.3,
                FailureNumber = 1.1
            };

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.47424874554865, 36979);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.OpenSod);

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.52484620520781, 35962);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.ClosedSod)
            {
                IncreasedLoadTransitionAlphaM = 1.8,
                ReducedStrengthTransitionAlphaS = 0.9
            };

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.51908455307175, 35645);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.ClosedSod);

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.11400976522333, 42138);
        }

        [Test]
        public void GivenCalculationInputForSchematization4Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization4();

            var locationConstructionProperties = new GrassRevetmentWaveRunupRayleighLocationConstructionProperties(
                3, 0.3, GrassRevetmentTopLayerType.ClosedSod);

            builder.AddGrassWaveRunupRayleighLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            Calculator calculator = PerformTest(calculationInput.Data);

            // Then
            AssertOutput(calculator, 1.17363142829280, 18856);
        }

        private static CalculationInputBuilder CreateBuilderForSchematization1()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(0, 3600, 0, 0.5, 3, 50);
            builder.AddTimeStep(3600, 7200, 0.1, 0.7, 3.5, 45);
            builder.AddTimeStep(7200, 10800, 0.2, 1, 4, 40);
            builder.AddTimeStep(10800, 14400, 0.3, 1.3, 4.3, 35);
            builder.AddTimeStep(14400, 18000, 0.4, 1.5, 4.5, 30);
            builder.AddTimeStep(18000, 21600, 0.5, 1.8, 4.8, 25);
            builder.AddTimeStep(21600, 25200, 0.6, 2.1, 5.2, 20);
            builder.AddTimeStep(25200, 28800, 0.7, 2.5, 5.5, 15);
            builder.AddTimeStep(28800, 32400, 0.7, 2.8, 5.8, 10);
            builder.AddTimeStep(32400, 36000, 0.6, 2.8, 6, 5);
            builder.AddTimeStep(36000, 39600, 0.5, 2.5, 6, 0);
            builder.AddTimeStep(39600, 43200, 0.4, 2.1, 5.8, 0);
            builder.AddTimeStep(43200, 46800, 0.3, 1.8, 5.5, 5);
            builder.AddTimeStep(46800, 50400, 0.2, 1.5, 5.2, 10);
            builder.AddTimeStep(50400, 54000, 0.1, 1.3, 4.8, 15);
            builder.AddTimeStep(54000, 57600, 0, 1, 4.5, 20);

            builder.AddDikeProfileSegment(0, 0, 25, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization2()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(0, 3600, 0, 0.3, 3, 50);
            builder.AddTimeStep(3600, 7200, 0.1, 0.4, 3.5, 45);
            builder.AddTimeStep(7200, 10800, 0.2, 0.5, 3.9, 40);
            builder.AddTimeStep(10800, 14400, 0.3, 0.6, 4.2, 35);
            builder.AddTimeStep(14400, 18000, 0.4, 0.7, 4.6, 30);
            builder.AddTimeStep(18000, 21600, 0.5, 0.8, 4.9, 25);
            builder.AddTimeStep(21600, 25200, 0.6, 0.9, 5.2, 20);
            builder.AddTimeStep(25200, 28800, 0.7, 1, 5.5, 15);
            builder.AddTimeStep(28800, 32400, 0.7, 1.1, 5.7, 10);
            builder.AddTimeStep(32400, 36000, 0.6, 1.1, 5.7, 5);
            builder.AddTimeStep(36000, 39600, 0.5, 1, 5.5, 0);
            builder.AddTimeStep(39600, 43200, 0.4, 0.9, 5.2, 0);
            builder.AddTimeStep(43200, 46800, 0.3, 0.8, 4.9, 5);
            builder.AddTimeStep(46800, 50400, 0.2, 0.7, 4.6, 10);
            builder.AddTimeStep(50400, 54000, 0.1, 0.6, 4.2, 15);
            builder.AddTimeStep(54000, 57600, 0, 0.5, 3.9, 20);

            builder.AddDikeProfileSegment(0, 0, 25, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization3()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(0, 3600, 0.5, 2.4, 4, 20);
            builder.AddTimeStep(3600, 7200, 0.6, 2.5, 4.2, 20);
            builder.AddTimeStep(7200, 10800, 0.7, 2.7, 4.4, 20);
            builder.AddTimeStep(10800, 14400, 0.8, 2.8, 4.5, 20);
            builder.AddTimeStep(14400, 18000, 0.9, 2.9, 4.8, 20);
            builder.AddTimeStep(18000, 21600, 0.95, 3, 5, 20);
            builder.AddTimeStep(21600, 25200, 1, 2.9, 5.2, 20);
            builder.AddTimeStep(25200, 28800, 0.95, 2.9, 5.5, 15);
            builder.AddTimeStep(28800, 32400, 0.8, 2.8, 5.8, 10);
            builder.AddTimeStep(32400, 36000, 0.6, 2.8, 6, 5);
            builder.AddTimeStep(36000, 39600, 0.5, 2.5, 6, 0);
            builder.AddTimeStep(39600, 43200, 0.4, 2.1, 5.8, 0);
            builder.AddTimeStep(43200, 46800, 0.3, 1.8, 5.5, 5);
            builder.AddTimeStep(46800, 50400, 0.2, 1.5, 5.2, 10);
            builder.AddTimeStep(50400, 54000, 0.1, 1.3, 4.8, 15);
            builder.AddTimeStep(54000, 57600, 0, 1, 4.5, 20);

            builder.AddDikeProfileSegment(0, 0, 25, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization4()
        {
            var builder = new CalculationInputBuilder();

            builder.AddTimeStep(-7200, -6840, 0, 0.5, 3, 50);
            builder.AddTimeStep(-6840, -6120, 0.1, 0.7, 3.5, 45);
            builder.AddTimeStep(-6120, -5040, 0.2, 1, 4, 40);
            builder.AddTimeStep(-5040, -3600, 0.3, 1.3, 4.3, 35);
            builder.AddTimeStep(-3600, -1800, 0.4, 1.5, 4.5, 30);
            builder.AddTimeStep(-1800, 360, 0.5, 1.8, 4.8, 25);
            builder.AddTimeStep(360, 2880, 0.6, 2.1, 5.2, 20);
            builder.AddTimeStep(2880, 5760, 0.7, 2.5, 5.5, 15);
            builder.AddTimeStep(5760, 9000, 0.7, 2.8, 5.8, 10);
            builder.AddTimeStep(9000, 12600, 0.6, 2.8, 6, 5);
            builder.AddTimeStep(12600, 16560, 0.5, 2.5, 6, 0);
            builder.AddTimeStep(16560, 20880, 0.4, 2.1, 5.8, 0);
            builder.AddTimeStep(20880, 25560, 0.3, 1.8, 5.5, 5);
            builder.AddTimeStep(25560, 30600, 0.2, 1.5, 5.2, 10);
            builder.AddTimeStep(30600, 36000, 0.1, 1.3, 4.8, 15);
            builder.AddTimeStep(36000, 43200, 0, 1, 4.5, 20);

            builder.AddDikeProfileSegment(0, 0, 25, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(25, CharacteristicPointType.OuterCrest);

            return builder;
        }
    }
}