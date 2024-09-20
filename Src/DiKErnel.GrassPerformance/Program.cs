using System.Globalization;
using DiKErnel.GrassPerformance;
using DiKErnel.Integration;

internal class Program
{
    private static void Main(string[] args)
    {
        var builder = new CalculationInputBuilder(0);

        switch (args[0])
        {
            case "1h":
                AddTimeSteps(builder, 1, Resources.htime_1h, Resources.Hm0_1h, Resources.Tmm10_1h, Resources.WDir_1h);
                break;
            case "12h":
                AddTimeSteps(builder, 12, Resources.htime_12h, Resources.Hm0_12h, Resources.Tmm10_12h, Resources.WDir_12h);
                break;
        }
    }

    private static void AddTimeSteps(CalculationInputBuilder builder,
                                     int hours,
                                     string waterLevelsFile,
                                     string waveHeightsFile,
                                     string wavePeriodsFile,
                                     string waveDirectionsFile)
    {
        double[] waterLevels = waterLevelsFile.Split(',')
                                              .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                              .ToArray();

        double[] waveHeights = waveHeightsFile.Split(',')
                                              .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                              .Select(d => d <= 0 ? 0.01 : d)
                                              .ToArray();

        double[] wavePeriods = wavePeriodsFile.Split(',')
                                              .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                              .Select(d => d <= 0 ? 0.01 : d)
                                              .ToArray();

        double[] waveDirections = waveDirectionsFile.Split(',')
                                                    .Select(s => double.Parse(s, CultureInfo.InvariantCulture))
                                                    .ToArray();

        double[] times = Enumerable.Range(0, waterLevels.Length + 1)
                                   .Select(i => hours * 3600d * i)
                                   .ToArray();

        for (var i = 0; i <= waterLevels.Length - 1; i++)
        {
            builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeights[i], wavePeriods[i], waveDirections[i]);
        }

        Console.WriteLine($"Performing calculation(s) for {waterLevels.Length} time steps");
    }
}