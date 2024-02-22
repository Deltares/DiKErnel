using DiKErnel.Integration;
using DiKErnel.Integration.Data.GrassWaveOvertopping;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    [Binding]
    public class GrassWaveOvertoppingRayleighAnalyticalStepDefinitions : StepDefinitionsBase
    {
        public GrassWaveOvertoppingRayleighAnalyticalStepDefinitions(ScenarioContext context) : base(context) {}

        [When(@"I run the grass wave overtopping Rayleigh analytical calculation")]
        public void WhenIRunTheGrassWaveOvertoppingRayleighAnalyticalCalculation()
        {
            RunCalculation();
        }

        protected override void AddLocation(CalculationInputBuilder builder)
        {
            var constructionProperties = new GrassWaveOvertoppingRayleighLocationConstructionProperties(
                GetDouble(GeneralDefinitions.CalculationPositionKey), GetGrassTopLayerType(GeneralDefinitions.TopLayerTypeKey))
            {
                FailureNumber = GetNullableDouble(GeneralDefinitions.DamageKey),
                InitialDamage = GetNullableDouble(GeneralDefinitions.InitialDamageKey),
                AverageNumberOfWavesCtm = GetNullableDouble(GrassCumulativeOverloadDefinitions.AverageNumberOfWavesKey),
                CriticalFrontVelocity = GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalFrontVelocityKey),
                FrontVelocityCwo = GetNullableDouble(GrassCumulativeOverloadDefinitions.FrontVelocityKey),
                CriticalCumulativeOverload = GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalCumulativeOverloadKey),
                IncreasedLoadTransitionAlphaM = GetNullableDouble(GrassCumulativeOverloadDefinitions.IncreasedLoadTransitionKey),
                ReducedStrengthTransitionAlphaS = GetNullableDouble(GrassCumulativeOverloadDefinitions.ReducedStrengthTransitionKey),
                AccelerationAlphaAForCrest = GetNullableDouble("Acceleration crest"),
                AccelerationAlphaAForInnerSlope = GetNullableDouble("Acceleration inner slope"),
                DikeHeight = GetNullableDouble("Dike height")
            };

            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);
        }
    }
}