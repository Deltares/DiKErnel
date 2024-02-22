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
                Context.GetDouble(GeneralDefinitions.CalculationPositionKey), Context.GetGrassTopLayerType())
            {
                FailureNumber = Context.GetNullableDouble(GeneralDefinitions.DamageKey),
                InitialDamage = Context.GetNullableDouble(GeneralDefinitions.InitialDamageKey),
                AverageNumberOfWavesCtm = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.AverageNumberOfWavesKey),
                CriticalFrontVelocity = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalFrontVelocityKey),
                FrontVelocityCwo = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.FrontVelocityKey),
                CriticalCumulativeOverload = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalCumulativeOverloadKey),
                IncreasedLoadTransitionAlphaM = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.IncreasedLoadTransitionKey),
                ReducedStrengthTransitionAlphaS = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.ReducedStrengthTransitionKey),
                AccelerationAlphaAForCrest = Context.GetNullableDouble("Acceleration crest"),
                AccelerationAlphaAForInnerSlope = Context.GetNullableDouble("Acceleration inner slope"),
                DikeHeight = Context.GetNullableDouble("Dike height")
            };

            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);
        }
    }
}