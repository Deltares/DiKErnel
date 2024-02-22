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
                Context.GetDouble(GeneralDefinitions.CalculationPosition), Context.GetGrassTopLayerType())
            {
                FailureNumber = Context.GetNullableDouble(GeneralDefinitions.Damage),
                InitialDamage = Context.GetNullableDouble(GeneralDefinitions.InitialDamage),
                AverageNumberOfWavesCtm = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.AverageNumberOfWaves),
                CriticalFrontVelocity = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalFrontVelocity),
                FrontVelocityCwo = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.FrontVelocity),
                CriticalCumulativeOverload = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalCumulativeOverload),
                IncreasedLoadTransitionAlphaM = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.IncreasedLoadTransition),
                ReducedStrengthTransitionAlphaS = Context.GetNullableDouble(GrassCumulativeOverloadDefinitions.ReducedStrengthTransition),
                AccelerationAlphaAForCrest = Context.GetNullableDouble(GrassWaveOvertoppingDefinitions.AccelerationCrest),
                AccelerationAlphaAForInnerSlope = Context.GetNullableDouble(GrassWaveOvertoppingDefinitions.AccelerationInnerSlope),
                DikeHeight = Context.GetNullableDouble(GrassWaveOvertoppingDefinitions.DikeHeight)
            };

            builder.AddGrassWaveOvertoppingRayleighAnalyticalLocation(constructionProperties);
        }
    }
}