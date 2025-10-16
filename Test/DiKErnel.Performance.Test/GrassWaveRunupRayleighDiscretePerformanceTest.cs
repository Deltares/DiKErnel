using System;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveRunup;

namespace DiKErnel.Performance.Test
{
    public class GrassWaveRunupRayleighDiscretePerformanceTest : PerformanceTestBase
    {
        protected override double ExpectedDamage => 12.78;

        protected override Action<CalculationInputBuilder> AddLocationForFailureMechanismAction =>
            builder => builder.AddGrassWaveRunupRayleighDiscreteLocation(
                new GrassWaveRunupRayleighDiscreteLocationConstructionProperties(10, GrassTopLayerType.OpenSod));
    }
}