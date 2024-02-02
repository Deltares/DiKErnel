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
            SetCollectionValues(table);
        }

        [Given(@"the following hydraulischeBelastingen:")]
        public void GivenTheFollowingHydraulischeBelastingen(Table table)
        {
            SetCollectionValues(table);
        }

        [Given(@"the following dijkprofiel:")]
        public void GivenTheFollowingDijkprofiel(Table table)
        {
            context["dijkorientatie"] = table.Rows[0].GetString("dijkorientatie");
            context["teenBuitenzijde"] = table.Rows[0].GetString("teenBuitenzijde");
            context["kruinBuitenzijde"] = table.Rows[0].GetString("kruinBuitenzijde");

            context["posities"] = table.Rows.Select(row => row.GetString("posities")).ToArray();
            context["hoogten"] = table.Rows.Select(row => row.GetString("hoogten")).ToArray();
            context["ruwheidscoefficienten"] = table.Rows.Select(row => row.GetString("ruwheidscoefficienten")).ToArray();
        }

        [Given(@"the following locaties:")]
        public void GivenTheFollowingLocaties(Table table)
        {
            SetPropertyValues(table);
        }

        [Given(@"the following rekenmethoden:")]
        public void GivenTheFollowingRekenmethoden(Table table)
        {
            SetPropertyValues(table);
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

        [Given(@"the following series are adjusted:")]
        public void GivenTheFollowingSeriesAreAdjusted(Table table)
        {
            SetCollectionValues(table);
        }

        [Given(@"the following values are adjusted:")]
        public void GivenTheFollowingValuesAreAdjusted(Table table)
        {
            SetPropertyValues(table);
        }

        [Then(@"the schadegetal is (.*)")]
        public void ThenTheSchadegetalIs(decimal expectedDamage)
        {
            Assert.That(context["damage"], Is.EqualTo(expectedDamage).Within(1e-14));
        }

        [Given(@"the following constant inputs:")]
        public void GivenTheFollowingConstantInputs(Table table)
        {
            SetPropertyValues(table);
        }

        [When(@"I change the property (\w*) to a value of (.*)")]
        public void WhenIChangeTheValueOf(string propertyName, string value)
        {
            context[propertyName] = value;
        }

        [Then(@"the output value for (.*) is")]
        public void ThenTheOutputValueForIs(float expectedValue)
        {
            Assert.That(context["damage"], Is.EqualTo(expectedValue).Within(1e-14));
        }

        private void SetCollectionValues(Table table)
        {
            foreach (string property in table.Header)
            {
                context[property] = table.Rows.Select(r => r.GetString(property)).ToArray();
            }
        }

        private void SetPropertyValues(Table table)
        {
            foreach (string property in table.Header)
            {
                context[property] = table.Rows[0].GetString(property);
            }
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
    }
}