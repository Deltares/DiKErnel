// Copyright (C) Stichting Deltares and State of the Netherlands 2023. All rights reserved.
// 
// This file is part of DiKErnel.
// 
// DiKErnel is free software: you can redistribute it and/or modify it under the terms of the
// GNU Lesser General Public License as published by the Free Software Foundation, either
// version 3 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License along with this
// program. If not, see <http://www.gnu.org/licenses/>.
// 
// All names, logos, and references to "Deltares" are registered trademarks of Stichting
// Deltares and remain full property of Stichting Deltares at all times. All rights reserved.

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using DiKErnel.Core.Data;
using DiKErnel.Core.Extensions;
using NUnit.Framework;
using TechTalk.SpecFlow;
using TechTalk.SpecFlow.Assist;

namespace DiKErnel.SpecFlow.Test.Steps
{
    [Binding]
    public class GeneralSteps
    {
        private const string dikeOrientationKey = "Dike orientation";
        private const double tolerance = 1e-14;
        private const string outputKey = "Output";

        private readonly ScenarioContext context;

        public GeneralSteps(ScenarioContext context)
        {
            this.context = context;
        }

        [Given(@"the following dike profile and a dike orientation of (.*):")]
        public void GivenTheFollowingDikeProfile(string dikeOrientation, Table table)
        {
            context[dikeOrientationKey] = dikeOrientation;

            GivenTheFollowingCollectionsAreAdjusted(table);
        }
        
        [Given(@"the following(?: adjusted)? hydraulic loads:")]
        [Given(@"the following(?: adjusted)? dike geometry:")]
        public void GivenTheFollowingCollectionsAreAdjusted(Table table)
        {
            foreach (string property in table.Header)
            {
                context[property] = table.Rows.Select(r => r.GetString(property)).ToArray();
            }
        }

        [Given(@"the following(?: adjusted)? calculation settings:")]
        [Given(@"the following(?: adjusted)? dike properties:")]
        [Given(@"the following(?: adjusted)? characteristic points:")]
        public void GivenTheFollowingPropertiesAreAdjusted(Table table)
        {
            foreach (TableRow row in table.Rows)
            {
                context[row.Id()] = row.Value();
            }
        }

        [Given(@"the (.*) is adjusted to (.*)")]
        public void WhenIChangeTheValueOf(string propertyName, string value)
        {
            char[] characters = propertyName.ToCharArray();
            characters[0] = char.ToUpper(characters[0], CultureInfo.InvariantCulture);
            var adjustedPropertyName = new string(characters);
            
            context[adjustedPropertyName] = value;
        }

        [Then(@"the damage is (.*)")]
        public void ThenTheDamageIs(double expectedDamage)
        {
            var locationDependentOutput = (LocationDependentOutput) context[outputKey];

            IReadOnlyList<double> damages = locationDependentOutput.GetDamages();
            double actualDamage = damages[damages.Count - 1];
            Assert.That(actualDamage, Is.EqualTo(expectedDamage).Within(tolerance));
        }

        [Then(@"the rounded time of failure is (.*)")]
        public void ThenTheRoundedTimeOfFailureIs(string expectedValue)
        {
            var locationDependentOutput = (LocationDependentOutput) context[outputKey];

            double? timeOfFailure = locationDependentOutput.GetTimeOfFailure();
            if (timeOfFailure.HasValue)
            {
                timeOfFailure = Math.Ceiling(timeOfFailure.Value);
            }

            if (double.TryParse(expectedValue, out double expectedRoundedTimeOfFailure))
            {
                Assert.That(timeOfFailure, Is.EqualTo(expectedRoundedTimeOfFailure));
            }
            else
            {
                Assert.That(timeOfFailure, Is.Null);
            }
        }
    }
}