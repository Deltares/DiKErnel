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

using System.Globalization;
using System.Linq;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using NUnit.Framework;

namespace DiKErnel.Performance.Test
{
    [TestFixture]
    public class PerformanceTest
    {
        private CalculationInputBuilder builder;

        [SetUp]
        public void Setup()
        {
            builder = new CalculationInputBuilder(10);

            AddDikeProfile(builder);

            AddTimeSteps(builder);
        }

        private static void AddDikeProfile(CalculationInputBuilder builder)
        {
            builder.AddForeshore(0.004, -4);

            builder.AddDikeProfileSegment(0, 7.09, 18.39, 13.22, 1);
            builder.AddDikeProfileSegment(18.39, 13.22, 23.39, 13.22, 1);
            builder.AddDikeProfileSegment(23.39, 13.22, 33.05, 0, 1);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(18.39, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(23.39, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(33.05, CharacteristicPointType.InnerToe);
        }

        private void AddTimeSteps(CalculationInputBuilder builder)
        {
            double[] waterLevels = commaSeparatedWaterLevels.Split(',')
                                                            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                                            .ToArray();

            double[] waveHeights = commaSeparatedWaveHeights.Split(',')
                                                            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                                            .ToArray();

            double[] wavePeriods = commaSeparatedWavePeriods.Split(',')
                                                            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                                            .ToArray();

            double[] waveDirections = commaSeparatedWaveDirections.Split(',')
                                                                  .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                                                  .ToArray();

            double[] times = Enumerable.Range(0, waterLevels.Length + 1)
                                       .Select(i => 12 * 3600d * i)
                                       .ToArray();

            for (var i = 0; i <= waterLevels.Length - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeights[i], wavePeriods[i], waveDirections[i]);
            }
        }
    }
}