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

using NUnit.Framework;

namespace DiKErnel.Integration.Test.Data.Output
{
    [TestFixture]
    public class AsphaltRevetmentWaveImpactTimeDependentOutputTest
    {
        

    struct AsphaltRevetmentWaveImpactTimeDependentOutputTest : Test
    {
        static unique_ptr<AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties> CreateFullyConfiguredConstructionProperties()
        {
            var constructionProperties = make_unique<AsphaltRevetmentWaveImpactTimeDependentOutputConstructionProperties>();
            constructionProperties->_incrementDamage = make_unique<double>(0.1);
            constructionProperties->_damage = make_unique<double>(0.2);
            constructionProperties->_timeOfFailure = make_unique<int>(3);
            constructionProperties->_logFailureTension = make_unique<double>(0.4);
            constructionProperties->_maximumPeakStress = make_unique<double>(0.5);
            constructionProperties->_stiffnessRelation = make_unique<double>(0.6);
            constructionProperties->_computationalThickness = make_unique<double>(0.7);
            constructionProperties->_equivalentElasticModulus = make_unique<double>(0.8);

            return constructionProperties;
        }

        static void CreateOutputWithConstructionPropertiesWithLogFailureTensionNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_logFailureTension = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithMaximumPeakStressNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_maximumPeakStress = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithStiffnessRelationNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_stiffnessRelation = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithComputationalThicknessNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_computationalThickness = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }

        static void CreateOutputWithConstructionPropertiesWithEquivalentElasticModulusNullPtr()
        {
            // Setup
            const var constructionProperties = CreateFullyConfiguredConstructionProperties();
            constructionProperties->_equivalentElasticModulus = nullptr;

            // Call
            const AsphaltRevetmentWaveImpactTimeDependentOutput output(*constructionProperties);
        }
    };

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
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = make_unique<int>(timeOfFailure);
        constructionProperties._logFailureTension = make_unique<double>(logFailureTension);
        constructionProperties._maximumPeakStress = make_unique<double>(maximumPeakStress);
        constructionProperties._stiffnessRelation = make_unique<double>(stiffnessRelation);
        constructionProperties._computationalThickness = make_unique<double>(computationalThickness);
        constructionProperties._equivalentElasticModulus = make_unique<double>(equivalentElasticModulus);

        // Call
        const AsphaltRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        ASSERT_EQ(timeOfFailure, *output.GetTimeOfFailure());
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
        constructionProperties._incrementDamage = make_unique<double>(incrementDamage);
        constructionProperties._damage = make_unique<double>(damage);
        constructionProperties._timeOfFailure = nullptr;
        constructionProperties._logFailureTension = make_unique<double>(logFailureTension);
        constructionProperties._maximumPeakStress = make_unique<double>(maximumPeakStress);
        constructionProperties._stiffnessRelation = make_unique<double>(stiffnessRelation);
        constructionProperties._computationalThickness = make_unique<double>(computationalThickness);
        constructionProperties._equivalentElasticModulus = make_unique<double>(equivalentElasticModulus);

        // Call
        const AsphaltRevetmentWaveImpactTimeDependentOutput output(constructionProperties);

        // Assert
        Assert.IsInstanceOf<TimeDependentOutput>(&output);
        Assert.AreEqual(incrementDamage, output.GetIncrementDamage());
        Assert.AreEqual(damage, output.GetDamage());
        ASSERT_EQ(nullptr, output.GetTimeOfFailure());
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
