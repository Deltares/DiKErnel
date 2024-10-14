using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveImpact;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;
using DiKErnel.Util;

namespace DiKErnel.PerformanceConsole
{
    internal static class Program
    {
        private const double xStartCalculationZoneOuterSlope = 7;
        private const double xEndCalculationZoneOuterSlope = 11;
        private const double xStartCalculationZoneInnerSlope = 24;
        private const double xEndCalculationZoneInnerSlope = 32;

        private const string asphaltWaveImpactIdentifier = "AsphaltWaveImpact";
        private const string grassWaveImpactIdentifier = "GrassWaveImpact";
        private const string grassWaveOvertoppingRayleighAnalyticalIdentifier = "GrassWaveOvertoppingRayleighAnalytical";
        private const string grassWaveOvertoppingRayleighDiscreteIdentifier = "GrassWaveOvertoppingRayleighDiscrete";
        private const string grassWaveRunupBattjesGroenendijkAnalyticalIdentifier = "GrassWaveRunupBattjesGroenendijkAnalytical";
        private const string grassWaveRunupRayleighDiscreteIdentifier = "GrassWaveRunupRayleighDiscrete";
        private const string naturalStoneWaveImpactIdentifier = "NaturalStoneWaveImpact";

        private const string oneHourTimeStepIdentifier = "1h";
        private const string twelveHoursTimeStepIdentifier = "12h";

        private static void Main(string[] args)
        {
            var builder = new CalculationInputBuilder(0);

            AddDikeProfile(builder);

            AddLocations(builder, args[0], int.Parse(args[1], CultureInfo.InvariantCulture));

            AddTimeSteps(builder, args[2]);

            DataResult<ICalculationInput> result = builder.Build();

            CalculateAndWriteOutput(result.Data, args[0], args[3], args[4]);
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

        private static void AddLocations(CalculationInputBuilder builder, string failureMechanismArgument, int numberOfLocations)
        {
            Action<double> addLocationAction = failureMechanismArgument switch
            {
                asphaltWaveImpactIdentifier => x => builder.AddAsphaltWaveImpactLocation(
                    new AsphaltWaveImpactLocationConstructionProperties(x, AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete, 1.75, 60,
                                                                        0.3, 16000)),
                grassWaveImpactIdentifier => x => builder.AddGrassWaveImpactLocation(
                    new GrassWaveImpactLocationConstructionProperties(x, GrassTopLayerType.OpenSod)),
                grassWaveOvertoppingRayleighAnalyticalIdentifier => x => builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(
                    new GrassWaveOvertoppingRayleighLocationConstructionProperties(x, GrassTopLayerType.OpenSod)
                    {
                        DikeHeight = 11
                    }),
                grassWaveOvertoppingRayleighDiscreteIdentifier => x => builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(
                    new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(x, GrassTopLayerType.OpenSod)
                    {
                        DikeHeight = 11
                    }),
                grassWaveRunupBattjesGroenendijkAnalyticalIdentifier => x => builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(
                    new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(x, GrassTopLayerType.OpenSod)),
                grassWaveRunupRayleighDiscreteIdentifier => x => builder.AddGrassWaveRunupRayleighDiscreteLocation(
                    new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(x, GrassTopLayerType.OpenSod)),
                naturalStoneWaveImpactIdentifier => x => builder.AddNaturalStoneWaveImpactLocation(
                    new NaturalStoneWaveImpactLocationConstructionProperties(x, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.4, 1.65))
            };

            foreach (double x in GetXValues(failureMechanismArgument, numberOfLocations))
            {
                addLocationAction(x);
            }
        }

        private static List<double> GetXValues(string failureMechanismArgument, int numberOfLocations)
        {
            var xValues = new List<double>();

            double xStartCalculationZone;
            double xEndCalculationZone;

            if (failureMechanismArgument == grassWaveOvertoppingRayleighAnalyticalIdentifier ||
                failureMechanismArgument == grassWaveOvertoppingRayleighDiscreteIdentifier)
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
                    double increment = (xEndCalculationZone - xStartCalculationZone) / (numberOfLocations - 1);

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
                    AddTimeSteps(builder, 1, Resources.htime_1h, Resources.Hm0_1h, Resources.Tmm10_1h);
                    break;
                case twelveHoursTimeStepIdentifier:
                    AddTimeSteps(builder, 12, Resources.htime_12h, Resources.Hm0_12h, Resources.Tmm10_12h);
                    break;
            }
        }

        private static void AddTimeSteps(CalculationInputBuilder builder, int hours, string commaSeparatedWaterLevels,
                                         string commaSeparatedWaveHeights, string commaSeparatedWavePeriods)
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

            double[] times = Enumerable.Range(0, waterLevels.Length + 1)
                                       .Select(i => hours * 3600d * i)
                                       .ToArray();

            for (var i = 0; i <= waterLevels.Length - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeights[i], wavePeriods[i], 0);
            }
        }

        private static void CalculateAndWriteOutput(ICalculationInput calculationInput, string failureMechanismArgument,
                                                    string locationCalculationModeArgument, string timeStepCalculationModeArgument)
        {
            Enum.TryParse(locationCalculationModeArgument, out CalculationMode locationCalculationMode);
            Enum.TryParse(timeStepCalculationModeArgument, out CalculationMode timeStepCalculationMode);

            var stopWatch = new Stopwatch();

            stopWatch.Start();

            DataResult<CalculationOutput> result = Calculator.Calculate(calculationInput, locationCalculationMode, timeStepCalculationMode);

            stopWatch.Stop();

            string outputMessage = $"{failureMechanismArgument,43};" +
                                   $"{calculationInput.LocationDependentInputItems.Count,4};" +
                                   $"{calculationInput.TimeDependentInputItems.Count,8};" +
                                   $"{locationCalculationMode,15};" +
                                   $"{timeStepCalculationMode,15};" +
                                   $"{Math.Round(stopWatch.Elapsed.TotalSeconds, 2).ToString(CultureInfo.InvariantCulture),7};";

            for (var i = 0; i < result.Data.LocationDependentOutputItems.Count; i++)
            {
                IReadOnlyList<double> cumulativeDamages =
                    result.Data.LocationDependentOutputItems[i]
                          .GetCumulativeDamages(calculationInput.LocationDependentInputItems[i].InitialDamage);

                var x = Math.Round(calculationInput.LocationDependentInputItems[i].X, 2).ToString(CultureInfo.InvariantCulture);
                var damage = Math.Round(cumulativeDamages[cumulativeDamages.Count - 1], 2).ToString(CultureInfo.InvariantCulture);

                outputMessage += $" {x,5}; {damage,8};";
            }

            Console.Write(outputMessage.Remove(outputMessage.Length - 1, 1));
        }
    }
}