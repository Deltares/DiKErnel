using System;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveOvertopping;

namespace DiKErnel.Performance.Test
{
    public class GrassWaveOvertoppingRayleighAnalyticalPerformanceTest : PerformanceTestBase
    {
        protected override double ExpectedDamage => double.NaN;

        protected override Action<CalculationInputBuilder> AddLocationForFailureMechanismAction =>
            builder => builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(
                new GrassWaveOvertoppingRayleighLocationConstructionProperties(26, GrassTopLayerType.OpenSod)
                {
                    DikeHeight = 11
                });
    }
}