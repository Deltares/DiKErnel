using DiKErnel.Integration;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    [Binding]
    public class GrassWaveOvertoppingRayleighAnalyticalStepDefinitions : StepDefinitionsBase
    {
        private const string calculationPositionKey = "Position";
        private const string topLayerTypeKey = "Top layer type";
        private const string damageKey = "Failure number";
        private const string initialDamageKey = "Initial damage";
        private const string averageNumberOfWavesKey = "Average number of waves";
        private const string criticalFrontVelocityKey = "Critical front velocity";
        private const string frontVelocityKey = "Front velocity";
        private const string criticalCumulativeOverloadKey = "Critical cumulative overload";
        private const string increasedLoadTransitionKey = "Increased load transition";
        private const string reducedStrengthTransitionKey = "Reduced strength transition";

        public GrassWaveOvertoppingRayleighAnalyticalStepDefinitions(ScenarioContext context) : base(context) {}

        [When(@"I run the grass wave overtopping Rayleigh analytical calculation")]
        public void WhenIRunTheGrassWaveOvertoppingRayleighAnalyticalCalculation()
        {
            RunCalculation();
        }

        protected override void AddLocation(CalculationInputBuilder builder)
        {
            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                GetDouble(calculationPositionKey), GetGrassTopLayerType(topLayerTypeKey))
            {
                FailureNumber = GetNullableDouble(damageKey),
                InitialDamage = GetNullableDouble(initialDamageKey),
                AverageNumberOfWavesCtm = GetNullableDouble(averageNumberOfWavesKey),
                CriticalFrontVelocity = GetNullableDouble(criticalFrontVelocityKey),
                FrontVelocityCwo = GetNullableDouble(frontVelocityKey),
                CriticalCumulativeOverload = GetNullableDouble(criticalCumulativeOverloadKey),
                IncreasedLoadTransitionAlphaM = GetNullableDouble(increasedLoadTransitionKey),
                ReducedStrengthTransitionAlphaS = GetNullableDouble(reducedStrengthTransitionKey),
                AccelerationAlphaAForCrest = GetNullableDouble("Acceleration crest"),
                AccelerationAlphaAForInnerSlope = GetNullableDouble("Acceleration inner slope"),
                DikeHeight = GetNullableDouble("Dike height")
            };

            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);
        }
    }
}