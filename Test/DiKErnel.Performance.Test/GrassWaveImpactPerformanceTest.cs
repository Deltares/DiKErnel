using System;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveImpact;

namespace DiKErnel.Performance.Test
{
    public class GrassWaveImpactPerformanceTest : PerformanceTestBase
    {
        protected override double ExpectedDamage => 3.82;

        protected override Action<CalculationInputBuilder> AddLocationForFailureMechanismAction =>
            builder => builder.AddGrassWaveImpactLocation(
                new GrassWaveImpactLocationConstructionProperties(10, GrassTopLayerType.OpenSod));
    }
}