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

using DiKErnel.Core.Data;
using DiKErnel.Core.Exceptions;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.TestUtil;
using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactTimeDependentOutputTest
    {
     
        private static AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties CreateFullyConfiguredConstructionProperties()
        {
            return new AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties
            {
                IncrementDamage = Random.NextDouble(),
                Damage = Random.NextDouble(),
                TimeOfFailure = Random.Next(),
                LogFailureTension = Random.NextDouble(),
                MaximumPeakStress = Random.NextDouble(),
                StiffnessRelation = Random.NextDouble(),
                ComputationalThickness = Random.NextDouble(),
                EquivalentElasticModulus = Random.NextDouble()
            };
        }

        private static AsphaltRevetmentWaveImpactTimeDependentOutput CreateOutputWithConstructionPropertiesWithLogFailureTensionNull()
        {
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();
            
            constructionProperties.LogFailureTension = null;

            return new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
        }

        private static AsphaltRevetmentWaveImpactTimeDependentOutput CreateOutputWithConstructionPropertiesWithMaximumPeakStressNull()
        {
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.MaximumPeakStress = null;

            return new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
        }

        private static AsphaltRevetmentWaveImpactTimeDependentOutput CreateOutputWithConstructionPropertiesWithStiffnessRelationNull()
        {
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.StiffnessRelation = null;

            return new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
        }

        private static AsphaltRevetmentWaveImpactTimeDependentOutput CreateOutputWithConstructionPropertiesWithComputationalThicknessNull()
        {
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.ComputationalThickness = null;

            return new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
        }

        private static AsphaltRevetmentWaveImpactTimeDependentOutput CreateOutputWithConstructionPropertiesWithEquivalentElasticModulusNull()
        {
            AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties =
                CreateFullyConfiguredConstructionProperties();

            constructionProperties.EquivalentElasticModulus = null;

            return new AsphaltRevetmentWaveImpactTimeDependentOutput(constructionProperties);
        }

        [Test]
    public void Constructor_WithAllValuesSet_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var timeOfFailure = 3;
        var logFailureTension = 0.4;
        var maximumPeakStress = 0.5;
        var stiffnessRelation = 0.6;
        var computationalThickness = 0.7;
        var equivalentElasticModulus = 0.8;

        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.TimeOfFailure = timeOfFailure);
        constructionProperties._logFailureTension = logFailureTension);
        constructionProperties._maximumPeakStress = maximumPeakStress);
        constructionProperties._stiffnessRelation = stiffnessRelation);
        constructionProperties._computationalThickness = computationalThickness);
        constructionProperties._equivalentElasticModulus = equivalentElasticModulus);

        // Call
        const AsphaltRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        Assert.AreEqual(timeOfFailure, *output.GetTimeOfFailure());
        Assert.AreEqual(logFailureTension, output.GetLogFailureTension());
        Assert.AreEqual(maximumPeakStress, output.GetMaximumPeakStress());
        Assert.AreEqual(stiffnessRelation, output.GetStiffnessRelation());
        Assert.AreEqual(computationalThickness, output.GetComputationalThickness());
        Assert.AreEqual(equivalentElasticModulus, output.GetEquivalentElasticModulus());
    }

        [Test]
    public void Constructor_WithNullPtrValues_ExpectedValues()
    {
        // Setup
        var incrementDamage = 0.1;
        var damage = 0.2;
        var logFailureTension = 0.3;
        var maximumPeakStress = 0.4;
        var stiffnessRelation = 0.5;
        var computationalThickness = 0.6;
        var equivalentElasticModulus = 0.7;

        AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties constructionProperties;
        constructionProperties.IncrementDamage = incrementDamage);
        constructionProperties.Damage = damage);
        constructionProperties.TimeOfFailure = null;
        constructionProperties._logFailureTension = logFailureTension);
        constructionProperties._maximumPeakStress = maximumPeakStress);
        constructionProperties._stiffnessRelation = stiffnessRelation);
        constructionProperties._computationalThickness = computationalThickness);
        constructionProperties._equivalentElasticModulus = equivalentElasticModulus);

        // Call
        const AsphaltRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        Assert.IsNull(output.GetTimeOfFailure());
        Assert.AreEqual(logFailureTension, output.GetLogFailureTension());
        Assert.AreEqual(maximumPeakStress, output.GetMaximumPeakStress());
        Assert.AreEqual(stiffnessRelation, output.GetStiffnessRelation());
        Assert.AreEqual(computationalThickness, output.GetComputationalThickness());
        Assert.AreEqual(equivalentElasticModulus, output.GetEquivalentElasticModulus());
    }

        [Test]
    public void Constructor_LogFailureTensionNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithLogFailureTensionNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "logFailureTension must be set.");
    }

        [Test]
    public void Constructor_MaximumPeakStressNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithMaximumPeakStressNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "maximumPeakStress must be set.");
    }

        [Test]
    public void Constructor_StiffnessRelationNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action = &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithStiffnessRelationNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "stiffnessRelation must be set.");
    }

        [Test]
    public void Constructor_ComputationalThicknessNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action =
                &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithComputationalThicknessNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "computationalThickness must be set.");
    }

        [Test]
    public void Constructor_EquivalentElasticModulusNullPtr_ThrowsInvalidTimeDependentOutputException()
    {
        // Setup & Call
        const var action =
                &AsphaltRevetmentWaveImpactTimeDependentOutputTest::CreateOutputWithConstructionPropertiesWithEquivalentElasticModulusNullPtr;

        // Assert
        AssertHelper::AssertThrowsWithMessage<InvalidTimeDependentOutputException>(action, "equivalentElasticModulus must be set.");
    }    }

}
