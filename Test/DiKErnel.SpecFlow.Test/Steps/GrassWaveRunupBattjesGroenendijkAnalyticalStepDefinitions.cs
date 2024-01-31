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
            context["hydraulischeBelastingen"] = table.CreateSet<HydraulicLoads>();
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
            ScenarioContext.StepIsPending();
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

        private class HydraulicLoads
        {
            public double Waterstanden { get; set; }
            public double GolfhoogtenHm0 { get; set; }
            public double GolfperiodenTm10 { get; set; }
            public double Golfrichtingen { get; set; }
        }

        private class Location
        {
            public double Positie { get; set; }
            public string TypeToplaag { get; set; }
            public string Beginschade { get; set; }
            public double VerhogingBelastingOvergangAlfaM { get; set; }
            public double VerlagingSterkteOvergangAlfaS { get; set; }
        }
    }
}