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
            context["tijdstippen"] = table.Rows.Select(row => row.GetString("tijdstippen")).ToArray();
        }

        [Given(@"the following hydraulischeBelastingen:")]
        public void GivenTheFollowingHydraulischeBelastingen(Table table)
        {
            context["waterstanden"] = table.Rows.Select(row => row.GetString("waterstanden")).ToArray();
            context["golfhoogtenHm0"] = table.Rows.Select(row => row.GetString("golfhoogtenHm0")).ToArray();
            context["golfperiodenTm10"] = table.Rows.Select(row => row.GetString("golfperiodenTm10")).ToArray();
            context["golfrichtingen"] = table.Rows.Select(row => row.GetString("golfrichtingen")).ToArray();
        }

        [Given(@"the following dijkprofiel:")]
        public void GivenTheFollowingDijkprofiel(Table table)
        {
            context["dijkorientatie"] = table.Rows[0].GetString("dijkorientatie");
            context["teenBuitenzijde"] = table.Rows[0].GetString("teenBuitenzijde");
            context["kruinBuitenzijde"] = table.Rows[0].GetString("kruinBuitenzijde");

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
            var builder = new CalculationInputBuilder(GetDouble("dijkorientatie"));
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
            // Check row count, if row count == 1, then read as a single line
            if (table.RowCount == 1)
            {
                foreach (string property in table.Header)
                {
                    context[property] = table.Rows[0].GetString(property);
                }
            }
            else
            {
                foreach (string property in table.Header)
                {
                    context[property] = table.Rows.Select(r => r.GetString(property)).ToArray();
                }
            }
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

        private GrassTopLayerType GetGrassTopLayerType()
        {
            var value = (string) context["typeToplaag"];
            return value == "grasGeslotenZode" ? GrassTopLayerType.ClosedSod : GrassTopLayerType.OpenSod;
        }

        private double GetDouble(string id)
        {
            var value = (string) context[id];
            return double.Parse(value);
        }

        private double? GetNullableDouble(string id)
        {
            if (context.TryGetValue(id, out object? retrievedValue))
            {
                var value = (string) retrievedValue;
                return string.IsNullOrWhiteSpace(value) ? (double?) null : double.Parse(value);
            }

            return null;
        }

        private IReadOnlyList<double> GetDoubleCollection(string id)
        {
            var values = (IReadOnlyList<string>) context[id];
            return values.Select(double.Parse).ToList();
        }

        private IReadOnlyList<double?> GetNullableDoubleCollection(string id)
        {
            var values = (IReadOnlyList<string>) context[id];
            var parsedValues = new List<double?>();
            foreach (string value in values)
            {
                if (string.IsNullOrWhiteSpace(value))
                {
                    parsedValues.Add(null);
                }
                else
                {
                    parsedValues.Add(double.Parse(value));
                }
            }

            return parsedValues;
        }

        private void AddTimeSteps(CalculationInputBuilder builder)
        {
            IReadOnlyList<double> times = GetDoubleCollection("tijdstippen");
            IReadOnlyList<double> waterLevels = GetDoubleCollection("waterstanden");
            IReadOnlyList<double> waveHeightsHm0 = GetDoubleCollection("golfhoogtenHm0");
            IReadOnlyList<double> wavePeriodsTm10 = GetDoubleCollection("golfperiodenTm10");
            IReadOnlyList<double> waveDirections = GetDoubleCollection("golfrichtingen");

            for (var i = 0; i < times.Count - 1; i++)
            {
                builder.AddTimeStep(times[i], times[i + 1], waterLevels[i], waveHeightsHm0[i], wavePeriodsTm10[i],
                                    waveDirections[i]);
            }
        }

        private void AddDikeProfile(CalculationInputBuilder builder)
        {
            IReadOnlyList<double> xLocations = GetDoubleCollection("posities");
            IReadOnlyList<double> zLocations = GetDoubleCollection("hoogten");
            IReadOnlyList<double?> roughnessCoefficients = GetNullableDoubleCollection("ruwheidscoefficienten");

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
            builder.AddDikeProfilePoint(GetDouble("teenBuitenzijde"),
                                        CharacteristicPointType.OuterToe);
            builder.AddDikeProfilePoint(GetDouble("kruinBuitenzijde"),
                                        CharacteristicPointType.OuterCrest);
        }

        private void AddForeshore(CalculationInputBuilder builder)
        {
            double foreshoreSlope = GetDouble("tanAvl");
            double bottomForeshoreZ = GetDouble("bodemVoorlandZ");

            builder.AddForeshore(foreshoreSlope, bottomForeshoreZ);
        }

        private void AddLocation(CalculationInputBuilder builder)
        {
            GrassTopLayerType topLayerType = GetGrassTopLayerType();

            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                GetDouble("positie"), topLayerType)
            {
                FailureNumber = GetNullableDouble("faalGetal"),
                InitialDamage = GetNullableDouble("beginSchade"),
                AverageNumberOfWavesCtm = GetNullableDouble("factorCtm"),
                CriticalFrontVelocity = GetNullableDouble("kritiekeFrontSnelheid"),
                FrontVelocityCu = GetNullableDouble("frontsnelheid"),
                CriticalCumulativeOverload = GetNullableDouble("kritiekeFrontsnelheid"),
                IncreasedLoadTransitionAlphaM = GetNullableDouble("verhogingBelastingOvergangAlfaM"),
                ReducedStrengthTransitionAlphaS = GetNullableDouble("verlagingSterkteOvergangAlfaS")
            };

            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);
        }

        private class SegmentData
        {
            public string Posities { get; set; }
            public string Hoogten { get; set; }
            public string Ruwheidscoefficienten { get; set; }
        }

        private class CalculationMethod
        {
            public string Faalgetal { get; set; }
            public string FactorCtm { get; set; }
            public string Frontsnelheid { get; set; }
            public string BodemVoorlandZ { get; set; }
            public string TanAvl { get; set; }
        }

        private class Location
        {
            public string Positie { get; set; }
            public string TypeToplaag { get; set; }
            public string Beginschade { get; set; }
            public string VerhogingBelastingOvergangAlfaM { get; set; }
            public string VerlagingSterkteOvergangAlfaS { get; set; }
        }
    }
}