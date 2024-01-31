using System.Linq;
using TechTalk.SpecFlow;
using TechTalk.SpecFlow.Assist;

namespace DiKErnel.SpecFlow.Test.Steps
{
    [Binding]
    public class GrassWaveRunupBattjesGroenendijkAnalyticalStepDefinitions
    {
        private readonly ScenarioContext context;

        public GrassWaveRunupBattjesGroenendijkAnalyticalStepDefinitions(ScenarioContext context)
        {
            this.context = context;
        }

        [Given(@"the following tijdstippen:")]
        public void GivenTheFollowingTijdstippen(Table table)
        {
            context["tijdstippen"] = table.Rows.Select(row => row.GetDouble("tijdstippen")).ToArray();
        }

        [Given(@"the following hydraulischeBelastingen:")]
        public void GivenTheFollowingHydraulischeBelastingen(Table table)
        {
            context["waterstanden"] = table.Rows.Select(row => row.GetDouble("waterstanden")).ToArray();
            context["golfhoogtenHm0"] = table.Rows.Select(row => row.GetDouble("golfhoogtenHm0")).ToArray();
            context["golfperiodenTm10"] = table.Rows.Select(row => row.GetDouble("golfperiodenTm10")).ToArray();
            context["golfrichtingen"] = table.Rows.Select(row => row.GetDouble("golfrichtingen")).ToArray();
        }

        [Given(@"the following dijkprofiel:")]
        public void GivenTheFollowingDijkprofiel(Table table)
        {
            context["dijkorientatie"] = table.Rows[0].GetDouble("dijkorientatie");
            context["teenBuitenZijde"] = table.Rows[0].GetDouble("teenBuitenzijde");
            context["kruinBuitenzijde"] = table.Rows[0].GetDouble("kruinBuitenzijde");

            context["posities"] = table.Rows.Select(row => row.GetDouble("posities")).ToArray();
            context["hoogten"] = table.Rows.Select(row => row.GetDouble("hoogten")).ToArray();
            context["ruwheidscoefficienten"] = table.Rows.Select(row => row.GetDouble("ruwheidscoefficienten")).ToArray();
        }

        [Given(@"the following locaties:")]
        public void GivenTheFollowingLocaties(Table table)
        {
            var locationData = table.CreateInstance<Location>();

            context["positie"] = locationData.Positie;
            context["typeToplaag"] = locationData.TypeToplaag;
            context["beginschade"] = locationData.Beginschade;
            context["verhogingBelastingOvergangAlfaM"] = locationData.VerhogingBelastingOvergangAlfaM;
            context["verlagingSterkteOvergangAlfaS"] = locationData.VerlagingSterkteOvergangAlfaS;
        }

        [Given(@"the following rekenmethoden:")]
        public void GivenTheFollowingRekenmethoden(Table table)
        {
            var calculationMethodData = table.CreateInstance<CalculationMethod>();

            context["faalgetal"] = calculationMethodData.Faalgetal;
            context["factorCtm"] = calculationMethodData.FactorCtm;
            context["frontsnelheid"] = calculationMethodData.Frontsnelheid;
            context["bodemVoorlandZ"] = calculationMethodData.BodemVoorlandZ;
            context["tanAvl"] = calculationMethodData.TanAvl;
        }

        [When(@"I run the calculation")]
        public void WhenIRunTheCalculation()
        {
            ScenarioContext.StepIsPending();
        }

        [Given(@"the following is adjusted:")]
        public void GivenTheFollowingIsAdjusted(Table table)
        {
            ScenarioContext.StepIsPending();
        }

        [Then(@"the schadegetal is (.*)")]
        public void ThenTheSchadegetalIs(decimal p0)
        {
            ScenarioContext.StepIsPending();
        }

        [Given(@"the following constant inputs:")]
        public void GivenTheFollowingConstantInputs(Table table)
        {
            ScenarioContext.StepIsPending();
        }

        [When(@"I change the value of (.*)")]
        public void WhenIChangeTheValueOf(string uc)
        {
            ScenarioContext.StepIsPending();
        }

        [Then(@"the output value for (.*) is")]
        public void ThenTheOutputValueForIs(string dload, Table table)
        {
            ScenarioContext.StepIsPending();
        }

        private T GetValueFromContext<T>(string id)
        {
            if (!context.ContainsKey(id))
            {
                return default;
            }

            return (T) context[id];
        }

        private void AddTimeSteps(CalculationInputBuilder builder)
        {
            var times = GetValueFromContext<IReadOnlyList<double>>("tijdstippen");
            var waterLevels = GetValueFromContext<IReadOnlyList<double>>("waterstanden");
            var waveHeightsHm0 = GetValueFromContext<IReadOnlyList<double>>("golfhoogtenHm0");
            var wavePeriodsTm10 = GetValueFromContext<IReadOnlyList<double>>("golfperiodenTm10");
            var waveDirections = GetValueFromContext<IReadOnlyList<double>>("golfrichtingen");

            for (var i = 0; i < times.Count - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeightsHm0[i], wavePeriodsTm10[i],
                                    waveDirections[i]);
            }
        }
        }

        private class CalculationMethod
        {
            public double Faalgetal { get; set; }
            public double FactorCtm { get; set; }
            public double Frontsnelheid { get; set; }
            public double BodemVoorlandZ { get; set; }
            public double TanAvl { get; set; }
        }
    }
}