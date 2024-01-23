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
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.Util;
using NUnit.Framework;

namespace DiKErnel.System.Test
{
    [TestFixture]
    public class NaturalStoneWaveImpactCalculationTest : CalculationTest
    {
        [Test]
        public void GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                6, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.4, 1.65);

            builder.AddNaturalStoneLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.23043545607545, 7283);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                6, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.35, 1.6)
            {
                InitialDamage = 0.6
            };

            builder.AddNaturalStoneLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.45017739145778, 6424);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                6, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.25, 1.65)
            {
                HydraulicLoadXib = 2.1,
                HydraulicLoadAp = 6.68,
                HydraulicLoadBp = 0,
                HydraulicLoadCp = 0,
                HydraulicLoadNp = -0.723,
                HydraulicLoadAs = 12,
                HydraulicLoadBs = 1.5,
                HydraulicLoadCs = -3.12,
                HydraulicLoadNs = -1.5
            };

            builder.AddNaturalStoneLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.07139251615966, 7815);
        }

        [Test]
        public void GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization1();

            var locationConstructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                6, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.4, 1.65)
            {
                WaveAngleImpactBetamax = 30
            };

            builder.AddNaturalStoneLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.23139438041740, 7272);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                6, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.3, 1.65);

            builder.AddNaturalStoneLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.69080696566876, 5606);
        }

        [Test]
        public void GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization2();

            var locationConstructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                6, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.3, 1.65)
            {
                SlopeUpperLevelAus = 0.5,
                SlopeLowerLevelAls = 1
            };

            builder.AddNaturalStoneLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.69466545304923, 5570);
        }

        [Test]
        public void GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization3();

            var locationConstructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                6, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.3, 1.65);

            builder.AddNaturalStoneLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.19007096598985, 7942);
        }

        [Test]
        public void GivenCalculationInputForSchematization4Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization4();

            var locationConstructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                6, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.3, 1.65)
            {
                UpperLimitLoadingAul = 0.08,
                UpperLimitLoadingBul = 0.7,
                UpperLimitLoadingCul = 3.5,
                LowerLimitLoadingAll = 0.08,
                LowerLimitLoadingBll = 0.15,
                LowerLimitLoadingCll = 5.5,
                DistanceMaximumWaveElevationAsmax = 0.5,
                DistanceMaximumWaveElevationBsmax = 0.8,
                NormativeWidthOfWaveImpactAwi = 1.1,
                NormativeWidthOfWaveImpactBwi = 0.15
            };

            builder.AddNaturalStoneLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.09941459712287, 3894);
        }

        [Test]
        public void GivenCalculationInputForSchematization5Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            // Given
            CalculationInputBuilder builder = CreateBuilderForSchematization5();

            var locationConstructionProperties = new NaturalStoneWaveImpactLocationConstructionProperties(
                6, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.4, 1.65);

            builder.AddNaturalStoneLocation(locationConstructionProperties);

            DataResult<ICalculationInput> calculationInput = builder.Build();

            // When
            var calculator = new Calculator(calculationInput.Data);
            calculator.WaitForCompletion();

            // Then
            AssertOutput(calculator, 1.30817784966504, 2914);
        }

        private static CalculationInputBuilder CreateBuilderForSchematization1()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(0, 900, 1.4, 1, 5.5, 30);
            builder.AddTimeStep(900, 1800, 1.6, 1.2, 6, 60);
            builder.AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90);
            builder.AddTimeStep(2700, 3600, 1.8, 1.3, 7, 75);
            builder.AddTimeStep(3600, 4500, 2, 1.4, 7, 60);
            builder.AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45);
            builder.AddTimeStep(5400, 6300, 2.1, 1.6, 8, 30);
            builder.AddTimeStep(6300, 7200, 2.4, 1.7, 8, 15);
            builder.AddTimeStep(7200, 8100, 2, 2.4, 8.5, 0);
            builder.AddTimeStep(8100, 9000, 1.9, 2.2, 8, 0);
            builder.AddTimeStep(9000, 9900, 1.6, 1.8, 7, 0);
            builder.AddTimeStep(9900, 10800, 1.4, 1.2, 6, 0);

            builder.AddDikeProfileSegment(0, 0, 30, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization2()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(0, 900, 1.4, 1, 5.5, 30);
            builder.AddTimeStep(900, 1800, 1.6, 1.2, 6, 60);
            builder.AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90);
            builder.AddTimeStep(2700, 3600, 1.8, 1.3, 7, 75);
            builder.AddTimeStep(3600, 4500, 2, 1.4, 7, 60);
            builder.AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45);
            builder.AddTimeStep(5400, 6300, 2.1, 1.6, 8, 30);
            builder.AddTimeStep(6300, 7200, 2.4, 1.7, 8, 15);
            builder.AddTimeStep(7200, 8100, 2, 2.4, 8.5, 0);
            builder.AddTimeStep(8100, 9000, 1.9, 2.2, 8, 0);
            builder.AddTimeStep(9000, 9900, 1.6, 1.8, 7, 0);
            builder.AddTimeStep(9900, 10800, 1.4, 1.2, 6, 0);

            builder.AddDikeProfileSegment(0, 0, 6.4, 1.6);
            builder.AddDikeProfileSegment(6.4, 1.6, 12.4, 1.8);
            builder.AddDikeProfileSegment(12.4, 1.8, 30, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(6.4, CharacteristicPointType.CrestOuterBerm);
            builder.AddDikeProfilePoint(12.4, CharacteristicPointType.NotchOuterBerm);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization3()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(0, 900, 1.4, 1, 5.5, 30);
            builder.AddTimeStep(900, 1800, 1.6, 1.2, 6, 60);
            builder.AddTimeStep(1800, 2700, 1.7, 1.2, 6.5, 90);
            builder.AddTimeStep(2700, 3600, 1.8, 1.3, 7, 75);
            builder.AddTimeStep(3600, 4500, 2, 1.4, 7, 60);
            builder.AddTimeStep(4500, 5400, 2.1, 1.3, 7.5, 45);
            builder.AddTimeStep(5400, 6300, 2.1, 1.6, 8, 30);
            builder.AddTimeStep(6300, 7200, 2.4, 1.7, 8, 15);
            builder.AddTimeStep(7200, 8100, 2, 2.4, 8.5, 0);
            builder.AddTimeStep(8100, 9000, 1.9, 2.2, 8, 0);
            builder.AddTimeStep(9000, 9900, 1.6, 1.8, 7, 0);
            builder.AddTimeStep(9900, 10800, 1.4, 1.2, 6, 0);

            builder.AddDikeProfileSegment(0, 0, 6.4, 1.6);
            builder.AddDikeProfileSegment(6.4, 1.6, 12.4, 1.8);
            builder.AddDikeProfileSegment(12.4, 1.8, 30, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization4()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(0, 900, 1.27, 1.5, 6, 0);
            builder.AddTimeStep(900, 1800, 1.271, 1.5, 6, 0);
            builder.AddTimeStep(1800, 2700, 1.272, 1.5, 6, 0);
            builder.AddTimeStep(2700, 3600, 1.273, 1.5, 6, 0);
            builder.AddTimeStep(3600, 4500, 2.531, 1.5, 6, 0);
            builder.AddTimeStep(4500, 5400, 2.532, 1.5, 6, 0);
            builder.AddTimeStep(5400, 6300, 2.533, 1.5, 6, 0);
            builder.AddTimeStep(6300, 7200, 2.534, 1.5, 6, 0);
            builder.AddTimeStep(7200, 8100, 2.535, 1.5, 6, 0);
            builder.AddTimeStep(8100, 9000, 2.536, 1.5, 6, 0);
            builder.AddTimeStep(9000, 9900, 2.537, 1.5, 6, 0);
            builder.AddTimeStep(9900, 10800, 2.538, 1.5, 6, 0);

            builder.AddDikeProfileSegment(0, 0, 30, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.OuterCrest);

            return builder;
        }

        private static CalculationInputBuilder CreateBuilderForSchematization5()
        {
            var builder = new CalculationInputBuilder(0);

            builder.AddTimeStep(-3600, -3420, 1.4, 1, 5.5, 30);
            builder.AddTimeStep(-3420, -3060, 1.6, 1.2, 6, 60);
            builder.AddTimeStep(-3060, -2520, 1.7, 1.2, 6.5, 90);
            builder.AddTimeStep(-2520, -1800, 1.8, 1.3, 7, 75);
            builder.AddTimeStep(-1800, -900, 2, 1.4, 7, 60);
            builder.AddTimeStep(-900, 180, 2.1, 1.3, 7.5, 45);
            builder.AddTimeStep(180, 1440, 2.1, 1.6, 8, 30);
            builder.AddTimeStep(1440, 2880, 2.4, 1.7, 8, 15);
            builder.AddTimeStep(2880, 4500, 2, 2.4, 8.5, 0);
            builder.AddTimeStep(4500, 6300, 1.9, 2.2, 8, 0);
            builder.AddTimeStep(6300, 8280, 1.6, 1.8, 7, 0);
            builder.AddTimeStep(8280, 10800, 1.4, 1.2, 6, 0);

            builder.AddDikeProfileSegment(0, 0, 30, 7.5);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(30, CharacteristicPointType.OuterCrest);

            return builder;
        }
    }
}