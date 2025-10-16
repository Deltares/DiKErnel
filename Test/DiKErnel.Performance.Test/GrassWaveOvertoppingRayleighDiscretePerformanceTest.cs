using System;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveOvertopping;

namespace DiKErnel.Performance.Test
{
    public class GrassWaveOvertoppingRayleighDiscretePerformanceTest : PerformanceTestBase
    {
        protected override double ExpectedDamage => 19.01;

        protected override Action<CalculationInputBuilder> AddLocationForFailureMechanismAction =>
            builder => builder.AddGrassWaveOvertoppingRayleighDiscreteLocation(
                new GrassWaveOvertoppingRayleighDiscreteLocationConstructionProperties(26, GrassTopLayerType.OpenSod)
                {
                    DikeHeight = 11
                });
    }
}