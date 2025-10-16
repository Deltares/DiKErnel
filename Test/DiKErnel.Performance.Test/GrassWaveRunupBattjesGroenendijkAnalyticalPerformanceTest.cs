using System;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveRunup;

namespace DiKErnel.Performance.Test
{
    public class GrassWaveRunupBattjesGroenendijkAnalyticalPerformanceTest : PerformanceTestBase
    {
        protected override double ExpectedDamage => 47.41;

        protected override Action<CalculationInputBuilder> AddLocationForFailureMechanismAction =>
            builder => builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(
                new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(10, GrassTopLayerType.OpenSod));
    }
}