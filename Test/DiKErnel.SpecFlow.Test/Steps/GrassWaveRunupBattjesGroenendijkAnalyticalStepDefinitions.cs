using System.Collections.Generic;
using System.Linq;
using DiKErnel.Core;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.Util;
using NUnit.Framework;
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

            IReadOnlyList<SegmentData> segmentData = table.CreateSet<SegmentData>().ToArray();
            context["posities"] = segmentData.Select(sd => sd.Posities).ToArray();
            context["hoogten"] = segmentData.Select(sd => sd.Hoogten).ToArray();
            context["ruwheidscoefficienten"] = segmentData.Select(sd => sd.Ruwheidscoefficienten).ToArray();
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
            var builder = new CalculationInputBuilder(GetValueFromContext<double>("dijkOrientatie"));
            AddTimeSteps(builder);
            AddDikeProfile(builder);
            AddProfilePoints(builder);
            AddForeshore(builder);
            AddLocation(builder);

            DataResult<ICalculationInput>? result = builder.Build();
            var calculator = new Calculator(result.Data);
            calculator.WaitForCompletion();

            IReadOnlyList<double> damages = calculator.Result.Data.LocationDependentOutputItems[0].GetDamages();
            context["damage"] = damages.Last();
        }

        [Given(@"the following is adjusted:")]
        public void GivenTheFollowingIsAdjusted(Table table)
        {
            ScenarioContext.StepIsPending();
        }

        [Then(@"the schadegetal is (.*)")]
        public void ThenTheSchadegetalIs(decimal p0)
        {
            Assert.That(context["damage"], Is.EqualTo(p0));
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

        private void AddDikeProfile(CalculationInputBuilder builder)
        {
            var xLocations = GetValueFromContext<IReadOnlyList<double>>("posities");
            var zLocations = GetValueFromContext<IReadOnlyList<double>>("hoogten");
            var roughnessCoefficients = GetValueFromContext<IReadOnlyList<double?>>("ruwheidscoefficienten");
            for (var i = 0; i < xLocations.Count - 1; i++)
            {
                double startPointX = xLocations[i];
                double startPointZ = zLocations[i];
                double endPointX = xLocations[i + 1];
                double endPointZ = zLocations[i + 1];

                double? roughnessCoefficient = roughnessCoefficients[i];
                if (roughnessCoefficient.HasValue)
                {
                    builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ,
                                                  roughnessCoefficient.Value);
                }
                else
                {
                    builder.AddDikeProfileSegment(startPointX, startPointZ, endPointX, endPointZ);
                }
            }
        }

        private void AddProfilePoints(CalculationInputBuilder builder)
        {
            builder.AddDikeProfilePoint(GetValueFromContext<double>("teenbuitenzijde"),
                                        CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(GetValueFromContext<double>("kruinBuitenzijde"),
                                        CharacteristicPointType.OuterCrest);
        }

        private void AddForeshore(CalculationInputBuilder builder)
        {
            var foreshoreSlope = GetValueFromContext<double>("tanAvl");
            var bottomForeshoreZ = GetValueFromContext<double>("bodemVoorlandZ");

            builder.AddForeshore(foreshoreSlope, bottomForeshoreZ);
        }

        private void AddLocation(CalculationInputBuilder builder)
        {
            GrassTopLayerType topLayerType = GetValueFromContext<string>("typeToplaag") == "grasGeslotenZode"
                                                 ? GrassTopLayerType.ClosedSod
                                                 : GrassTopLayerType.OpenSod;

            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                GetValueFromContext<double>("positie"), topLayerType)
            {
                FailureNumber = GetValueFromContext<double?>("faalGetal"),
                InitialDamage = GetValueFromContext<double?>("beginSchade"),
                AverageNumberOfWavesCtm = GetValueFromContext<double?>("factorCtm"),
                CriticalFrontVelocity = GetValueFromContext<double?>("kritiekeFrontSnelheid"),
                FrontVelocityCu = GetValueFromContext<double?>("frontsnelheid"),
                CriticalCumulativeOverload = GetValueFromContext<double?>("kritiekeFrontsnelheid"),
                IncreasedLoadTransitionAlphaM = GetValueFromContext<double?>("verhogingBelastingOvergangAlfaM"),
                ReducedStrengthTransitionAlphaS = GetValueFromContext<double?>("verlagingSterkteOvergangAlfaS")
            };

            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);
        }

        private class SegmentData
        {
            public double Posities { get; set; }
            public double Hoogten { get; set; }
            public double? Ruwheidscoefficienten { get; set; }
        }

        private class CalculationMethod
        {
            public double Faalgetal { get; set; }
            public double FactorCtm { get; set; }
            public double Frontsnelheid { get; set; }
            public double BodemVoorlandZ { get; set; }
            public double TanAvl { get; set; }
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