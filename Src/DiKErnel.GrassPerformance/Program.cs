using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Util;

namespace DiKErnel.GrassPerformance
{
    internal static class Program
    {
        private const double dikeOrientation = 0;

        private const double xStartCalculationZoneOuterSlope = 5;
        private const double xEndCalculationZoneOuterSlope = 15;
        private const double xStartCalculationZoneInnerSlope = 60;
        private const double xEndCalculationZoneInnerSlope = 70;

        private const string grassWaveImpactIdentifier = "GrassWaveImpact";
        private const string grassWaveOvertoppingRayleighAnalyticalIdentifier = "GrassWaveOvertoppingRayleighAnalytical";
        private const string grassWaveOvertoppingRayleighDiscreteIdentifier = "GrassWaveOvertoppingRayleighDiscrete";
        private const string grassWaveRunupBattjesGroenendijkAnalyticalIdentifier = "GrassWaveRunupBattjesGroenendijkAnalytical";
        private const string grassWaveRunupRayleighDiscreteIdentifier = "GrassWaveRunupRayleighDiscrete";

        private static void Main(string[] args)
        {
            var builder = new CalculationInputBuilder(dikeOrientation);

            AddDikeProfile(builder);

            AddLocations(args[0], int.Parse(args[1]), builder);

            switch (args[2])
            {
                case "1h":
                    AddTimeSteps(builder, 1, Resources.htime_1h, Resources.Hm0_1h, Resources.Tmm10_1h, Resources.WDir_1h);
                    break;
                case "12h":
                    AddTimeSteps(builder, 12, Resources.htime_12h, Resources.Hm0_12h, Resources.Tmm10_12h, Resources.WDir_12h);
                    break;
            }

            DataResult<ICalculationInput> result = builder.Build();

            var calculator = new Calculator(result.Data);
            calculator.WaitForCompletion();

            for (var i = 0; i < calculator.Result.Data.LocationDependentOutputItems.Count; i++)
            {
                IReadOnlyList<double> damages = calculator.Result.Data.LocationDependentOutputItems[i].GetDamages();

                Console.WriteLine($@"| X = {Math.Round(result.Data.LocationDependentInputItems[i].X, 2).ToString(CultureInfo.InvariantCulture),-5} | Damage = {Math.Round(damages[^1], 2).ToString(CultureInfo.InvariantCulture),-5} |");
            }
        }

        private static void AddDikeProfile(CalculationInputBuilder builder)
        {
            builder.AddDikeProfileSegment(0, 1, 15, 3, 1);
            builder.AddDikeProfileSegment(15, 3, 25, 3.2, 1);
            builder.AddDikeProfileSegment(25, 3.2, 45, 6, 0.75);
            builder.AddDikeProfileSegment(45, 6, 55, 6, 0.5);
            builder.AddDikeProfileSegment(55, 6, 80, 3, 0.8);
            builder.AddDikeProfileSegment(80, 3, 90, 2.9, 0.8);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(45, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(55, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(80, CharacteristicPointType.InnerToe);
        }

        private static void AddLocations(string calculationTypeIdentifier, int numberOfLocations, CalculationInputBuilder builder)
        {
            Action<double> addLocationAction = calculationTypeIdentifier switch
            {
                grassWaveImpactIdentifier => x => builder.AddGrassWaveImpactLocation(
                    new GrassWaveImpactLocationConstructionProperties(x, GrassTopLayerType.OpenSod)),
                grassWaveOvertoppingRayleighAnalyticalIdentifier => x => builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(
                    new GrassWaveOvertoppingRayleighLocationConstructionProperties(x, GrassTopLayerType.OpenSod)),
                grassWaveOvertoppingRayleighDiscreteIdentifier => x => builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(
                    new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(x, GrassTopLayerType.OpenSod)),
                grassWaveRunupBattjesGroenendijkAnalyticalIdentifier => x => builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(
                    new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(x, GrassTopLayerType.OpenSod)),
                grassWaveRunupRayleighDiscreteIdentifier => x => builder.AddGrassWaveRunupRayleighDiscreteLocation(
                    new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(x, GrassTopLayerType.OpenSod)),
                _ => throw new ArgumentException("Invalid calculation type")
            };

            foreach (double x in GetXValues(calculationTypeIdentifier, numberOfLocations))
            {
                addLocationAction(x);
            }
        }

        private static List<double> GetXValues(string calculationTypeIdentifier, int numberOfLocations)
        {
            var xValues = new List<double>();

            double xStartCalculationZone;
            double xEndCalculationZone;

            if (calculationTypeIdentifier == grassWaveOvertoppingRayleighAnalyticalIdentifier ||
                calculationTypeIdentifier == grassWaveOvertoppingRayleighDiscreteIdentifier)
            {
                xStartCalculationZone = xStartCalculationZoneInnerSlope;
                xEndCalculationZone = xEndCalculationZoneInnerSlope;
            }
            else
            {
                xStartCalculationZone = xStartCalculationZoneOuterSlope;
                xEndCalculationZone = xEndCalculationZoneOuterSlope;
            }

            switch (numberOfLocations)
            {
                case 1:
                    xValues.Add(xStartCalculationZone + (xEndCalculationZone - xStartCalculationZone) * 1 / 2);
                    break;
                case 2:
                    xValues.Add(xStartCalculationZone + (xEndCalculationZone - xStartCalculationZone) * 1 / 3);
                    xValues.Add(xStartCalculationZone + (xEndCalculationZone - xStartCalculationZone) * 2 / 3);
                    break;
                default:
                {
                    double increment = (xEndCalculationZone - xStartCalculationZone) / numberOfLocations;

                    xValues.AddRange(Enumerable.Range(0, numberOfLocations)
                                               .Select(i => xStartCalculationZone + i * increment));
                    break;
                }
            }

            return xValues;
        }

        private static void AddTimeSteps(CalculationInputBuilder builder, int hours, string commaSeparatedWaterLevels,
                                         string commaSeparatedWaveHeights, string commaSeparatedWavePeriods,
                                         string commaSeparatedWaveDirections)
        {
            double[] waterLevels = commaSeparatedWaterLevels.Split(',')
                                                            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                                            .ToArray();

            double[] waveHeights = commaSeparatedWaveHeights.Split(',')
                                                            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                                            .Select(d => d <= 0 ? 0.01 : d)
                                                            .ToArray();

            double[] wavePeriods = commaSeparatedWavePeriods.Split(',')
                                                            .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                                            .Select(d => d <= 0 ? 0.01 : d)
                                                            .ToArray();

            double[] waveDirections = commaSeparatedWaveDirections.Split(',')
                                                                  .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                                                  .ToArray();

            double[] times = Enumerable.Range(0, waterLevels.Length + 1)
                                       .Select(i => hours * 3600d * i)
                                       .ToArray();

            for (var i = 0; i <= waterLevels.Length - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeights[i], wavePeriods[i], waveDirections[i]);
            }

            Console.WriteLine($@"Number of time steps = {waterLevels.Length}");
        }
    }
}