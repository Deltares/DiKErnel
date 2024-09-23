using System;
using System.Collections.Generic;
using System.Diagnostics;
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
        private const double dikeOrientation = 10;

        private const double xStartCalculationZoneOuterSlope = 5;
        private const double xEndCalculationZoneOuterSlope = 15;
        private const double xStartCalculationZoneInnerSlope = 24;
        private const double xEndCalculationZoneInnerSlope = 32;

        private const string grassWaveImpactIdentifier = "GrassWaveImpact";
        private const string grassWaveOvertoppingRayleighAnalyticalIdentifier = "GrassWaveOvertoppingRayleighAnalytical";
        private const string grassWaveOvertoppingRayleighDiscreteIdentifier = "GrassWaveOvertoppingRayleighDiscrete";
        private const string grassWaveRunupBattjesGroenendijkAnalyticalIdentifier = "GrassWaveRunupBattjesGroenendijkAnalytical";
        private const string grassWaveRunupRayleighDiscreteIdentifier = "GrassWaveRunupRayleighDiscrete";

        private const string oneHourTimeStepIdentifier = "1h";
        private const string twelveHoursTimeStepIdentifier = "12h";

        private static void Main(string[] args)
        {
            var builder = new CalculationInputBuilder(dikeOrientation);

            AddDikeProfile(builder);

            AddLocations(builder, args[0], int.Parse(args[1], CultureInfo.InvariantCulture));

            AddTimeSteps(builder, args[2]);

            DataResult<ICalculationInput> result = builder.Build();

            if (!result.Successful)
            {
                Console.WriteLine($"Validation error: {result.Events.First(e => e.Type == EventType.Error).Message}");
                return;
            }

            CalculateAndWriteOutput(result.Data, args[0]);
        }

        private static void AddDikeProfile(CalculationInputBuilder builder)
        {
            builder.AddDikeProfileSegment(0, 7.09, 18.39, 13.22, 1);
            builder.AddDikeProfileSegment(18.39, 13.22, 23.39, 13.22, 1);
            builder.AddDikeProfileSegment(23.39, 13.22, 33.05, 10, 1);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(18.39, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(23.39, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(33.05, CharacteristicPointType.InnerToe);
        }

        private static void AddLocations(CalculationInputBuilder builder, string calculationTypeArgument, int numberOfLocations)
        {
            Action<double> addLocationAction = calculationTypeArgument switch
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

            foreach (double x in GetXValues(calculationTypeArgument, numberOfLocations))
            {
                addLocationAction(x);
            }
        }

        private static List<double> GetXValues(string calculationTypeArgument, int numberOfLocations)
        {
            var xValues = new List<double>();

            double xStartCalculationZone;
            double xEndCalculationZone;

            if (calculationTypeArgument == grassWaveOvertoppingRayleighAnalyticalIdentifier ||
                calculationTypeArgument == grassWaveOvertoppingRayleighDiscreteIdentifier)
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

        private static void AddTimeSteps(CalculationInputBuilder builder, string timeStepArgument)
        {
            switch (timeStepArgument)
            {
                case oneHourTimeStepIdentifier:
                    AddTimeSteps(builder, 1, Resources.htime_1h, Resources.Hm0_1h, Resources.Tmm10_1h, Resources.WDir_1h);
                    break;
                case twelveHoursTimeStepIdentifier:
                    AddTimeSteps(builder, 12, Resources.htime_12h, Resources.Hm0_12h, Resources.Tmm10_12h, Resources.WDir_12h);
                    break;
            }
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
        }

        private static void CalculateAndWriteOutput(ICalculationInput calculationInput, string calculationTypeArgument)
        {
            var stopWatch = new Stopwatch();

            stopWatch.Start();

            DataResult<CalculationOutput> result = Calculator.Calculate(calculationInput);

            stopWatch.Stop();

            Console.WriteLine();
            Console.WriteLine($"Duration = {Math.Round(stopWatch.Elapsed.TotalSeconds, 2)} seconds");
            Console.WriteLine();
            Console.WriteLine($"Number of locations = {calculationInput.LocationDependentInputItems.Count}");
            Console.WriteLine($"Number of time steps = {calculationInput.TimeDependentInputItems.Count}");
            Console.WriteLine($"Calculation type = {calculationTypeArgument}");
            Console.WriteLine();
            Console.WriteLine("Output results");
            Console.WriteLine("---------------------------------");

            for (var i = 0; i < result.Data.LocationDependentOutputItems.Count; i++)
            {
                IReadOnlyList<double> damages = result.Data.LocationDependentOutputItems[i].GetDamages();

                var x = Math.Round(calculationInput.LocationDependentInputItems[i].X, 2).ToString(CultureInfo.InvariantCulture);
                var damage = Math.Round(damages[^1], 2).ToString(CultureInfo.InvariantCulture);

                Console.WriteLine($"| X = {x,-5} | Damage = {damage,-8} |");
            }

            Console.WriteLine("---------------------------------");
            Console.WriteLine();
        }
    }
}