using System;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.NaturalStoneWaveImpact;

namespace DiKErnel.Performance.Test
{
    public class NaturalStoneWaveImpactPerformanceTest : PerformanceTestBase
    {
        protected override double ExpectedDamage => 0.53;

        protected override Action<CalculationInputBuilder> AddLocationForFailureMechanismAction =>
            builder => builder.AddNaturalStoneWaveImpactLocation(
                new NaturalStoneWaveImpactLocationConstructionProperties(10, NaturalStoneWaveImpactTopLayerType.NordicStone, 0.4, 1.65));
    }
}