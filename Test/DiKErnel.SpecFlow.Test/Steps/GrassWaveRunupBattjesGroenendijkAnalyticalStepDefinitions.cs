// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
//
// This file is part of DiKErnel.
//
// This program is free software; you can redistribute it and/or modify it under the terms of
// the GNU Lesser General Public License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License along with this
// program; if not, see <https://www.gnu.org/licenses/>.
//
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System.Linq;
using DiKErnel.Core.Data;
using DiKErnel.Integration;
using DiKErnel.Integration.Data.Grass;
using DiKErnel.Integration.Data.GrassWaveRunup;
using DiKErnel.SpecFlow.Test.Steps.Definitions;
using NUnit.Framework;
using TechTalk.SpecFlow;

namespace DiKErnel.SpecFlow.Test.Steps
{
    [Binding]
    public class GrassWaveRunupBattjesGroenendijkAnalyticalStepDefinitions : StepDefinitionsBase
    {
        private const double tolerance = 1e-14;
        public GrassWaveRunupBattjesGroenendijkAnalyticalStepDefinitions(ScenarioContext context) : base(context) {}

        [When(@"I run the grass wave run-up Battjes-Groenendijk analytical calculation")]
        public void WhenIRunTheBattjesGroenendijkWaveRunupCalculation()
        {
            RunCalculation();
        }

        [Then(@"the cumulative overload is (.*)")]
        [Scope(Feature = "Grass wave run-up Battjes-Groenendijk analytical with BM Gras Benchmarks")]
        public void ThenTheCumulativeOverloadIs(double? expectedCumulativeOverload)
        {
            var output = (LocationDependentOutput) Context[GeneralDefinitions.OutputKey];

            GrassCumulativeOverloadTimeDependentOutput[] cumulativeOverLoadOutputs =
                output.TimeDependentOutputItems.Cast<GrassCumulativeOverloadTimeDependentOutput>().ToArray();

            Assert.That(cumulativeOverLoadOutputs[cumulativeOverLoadOutputs.Length - 1].CumulativeOverload,
                        Is.EqualTo(expectedCumulativeOverload).Within(tolerance));
        }

        protected override void ConfigureBuilder(CalculationInputBuilder builder)
        {
            base.ConfigureBuilder(builder);
            AddForeshore(builder);
        }

        protected override void AddLocation(CalculationInputBuilder builder)
        {
            var constructionProperties = new GrassWaveRunupBattjesGroenendijkAnalyticalLocationConstructionProperties(
                GetDouble(GeneralDefinitions.CalculationPositionKey), GetGrassTopLayerType(GeneralDefinitions.TopLayerTypeKey))
            {
                FailureNumber = GetNullableDouble(GeneralDefinitions.DamageKey),
                InitialDamage = GetNullableDouble(GeneralDefinitions.InitialDamageKey),
                AverageNumberOfWavesCtm = GetNullableDouble(GrassCumulativeOverloadDefinitions.AverageNumberOfWavesKey),
                CriticalFrontVelocity = GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalFrontVelocityKey),
                FrontVelocityCu = GetNullableDouble(GrassCumulativeOverloadDefinitions.FrontVelocityKey),
                CriticalCumulativeOverload = GetNullableDouble(GrassCumulativeOverloadDefinitions.CriticalCumulativeOverloadKey),
                IncreasedLoadTransitionAlphaM = GetNullableDouble(GrassCumulativeOverloadDefinitions.IncreasedLoadTransitionKey),
                ReducedStrengthTransitionAlphaS = GetNullableDouble(GrassCumulativeOverloadDefinitions.ReducedStrengthTransitionKey)
            };

            builder.AddGrassWaveRunupBattjesGroenendijkAnalyticalLocation(constructionProperties);
        }

        private void AddForeshore(CalculationInputBuilder builder)
        {
            builder.AddForeshore(GetDouble(DikeProfileDefinitions.SlopeForeshoreKey), 
                                 GetDouble(DikeProfileDefinitions.BottomZForeshoreKey));
        }
    }
}