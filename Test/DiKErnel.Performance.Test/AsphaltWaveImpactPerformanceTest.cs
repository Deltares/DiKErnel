using System;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.AsphaltWaveImpact;

namespace DiKErnel.Performance.Test
{
    public class AsphaltWaveImpactPerformanceTest : PerformanceTestBase
    {
        protected override double ExpectedDamage => double.NaN;

        protected override Action<CalculationInputBuilder> AddLocationForFailureMechanismAction =>
            builder => builder.AddAsphaltWaveImpactLocation(
                new AsphaltWaveImpactLocationConstructionProperties(
                    10, AsphaltWaveImpactTopLayerType.HydraulicAsphaltConcrete, 1.75, 60, 0.3, 16000));
    }
}