using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.AsphaltWaveImpact;
using DiKErnel.Util;

namespace DiKErnel.GpuConsole
{
    internal static class Program
    {
        private const double xStartCalculationZoneOuterSlope = 7;
        private const double xEndCalculationZoneOuterSlope = 11;

        private const string oneHourTimeStepIdentifier = "1h";
        private const string twelveHoursTimeStepIdentifier = "12h";

        private static void Main(string[] args)
        {
            var builder = new CalculationInputBuilder(0);

            AddDikeProfile(builder);

            AddLocations(builder, int.Parse(args[0], CultureInfo.InvariantCulture));

            AddTimeSteps(builder, args[1]);

            DataResult<ICalculationInput> result = builder.Build();

            CalculateAndWriteOutput(result.Data);
        }

        private static void AddDikeProfile(CalculationInputBuilder builder)
        {
            builder.AddDikeProfileSegment(0, 7.09, 18.39, 13.22, 1);
            builder.AddDikeProfileSegment(18.39, 13.22, 23.39, 13.22, 1);
            builder.AddDikeProfileSegment(23.39, 13.22, 33.05, 0, 1);

            builder.AddDikeProfilePoint(0, CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(18.39, CharacteristicPointType.OuterCrest);
            builder.AddDikeProfilePoint(23.39, CharacteristicPointType.InnerCrest);
            builder.AddDikeProfilePoint(33.05, CharacteristicPointType.InnerToe);
        }

        private static void AddLocations(CalculationInputBuilder builder, int numberOfLocations)
        {
            foreach (double x in GetXValues(numberOfLocations))
            {
                builder.AddAsphaltWaveImpactLocation(
                    new AsphaltWaveImpactLocationConstructionProperties(x, AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete, 1.75, 60,
                                                                        0.3, 16000));
            }
        }

        private static List<double> GetXValues(int numberOfLocations)
        {
            var xValues = new List<double>();

            switch (numberOfLocations)
            {
                case 1:
                    xValues.Add(xStartCalculationZoneOuterSlope +
                                (xEndCalculationZoneOuterSlope - xStartCalculationZoneOuterSlope) * 1 / 2);
                    break;
                case 2:
                    xValues.Add(xStartCalculationZoneOuterSlope +
                                (xEndCalculationZoneOuterSlope - xStartCalculationZoneOuterSlope) * 1 / 3);
                    xValues.Add(xStartCalculationZoneOuterSlope +
                                (xEndCalculationZoneOuterSlope - xStartCalculationZoneOuterSlope) * 2 / 3);
                    break;
                default:
                {
                    double increment = (xEndCalculationZoneOuterSlope - xStartCalculationZoneOuterSlope) / (numberOfLocations - 1);

                    xValues.AddRange(Enumerable.Range(0, numberOfLocations)
                                               .Select(i => xStartCalculationZoneOuterSlope + i * increment));
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

        private static void CalculateAndWriteOutput(ICalculationInput calculationInput)
        {
            const CalculationMode locationCalculationMode = CalculationMode.Sequential;
            const CalculationMode timeStepCalculationMode = CalculationMode.Parallel;

            var stopWatch = new Stopwatch();

            stopWatch.Start();

            DataResult<CalculationOutput> result = Calculator.Calculate(calculationInput, locationCalculationMode, timeStepCalculationMode);

            stopWatch.Stop();

            string outputMessage = "AsphaltWaveImpact;" +
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