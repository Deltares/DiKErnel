using System.Collections.Generic;
using DiKErnel.System.Test;
using DiKErnel.Integration;
using DiKErnel.Integration.Factories;
using TechTalk.SpecFlow.Assist;
using TechTalk.SpecFlow;
using DiKErnel.Core.Data;
using DiKErnel.Integration.Data.AsphaltRevetmentWaveImpact;
using DiKErnel.Core;
using DiKErnel.Util;
using System;
using System.Linq;

namespace SpecFlow.SystemTest.StepDefinitions
{
    [Binding]
    public sealed class AsphaltRevetmentWaveImpactStepDefinitions
    {
        ScenarioContext _scenarioContext;
        Calculator _calculator;
        AsphaltRevetmentWaveImpactLocationConstructionProperties asphaltRevetmentWaveImpactLocationConstructionProperties;
        public AsphaltRevetmentWaveImpactStepDefinitions(ScenarioContext context)
        {
            _scenarioContext = context;
        }
        CalculationInputBuilder builder = new CalculationInputBuilder();

        [Given(@"the following schematisation for time steps:")]
        public void GivenTheFollowingSchematisationForTimeSteps(Table table)
        {
            var profileDataFactoryPoints = table.CreateSet<TimeDependentInputFactoryData>();

            foreach (TimeDependentInputFactoryData item in profileDataFactoryPoints)
            {
                builder.AddTimeStep(item.BeginTime, item.EndTime, item.WaterLevel, item.WaveHeightHm0, item.WavePeriodTm10, item.WaveAngle);
            }
        }

        [Given(@"the follwoing Dike profile segments:")]
        public void GivenTheFollwoingDikeProfileSegments(Table table)
        {
            var profileDataFactorySegment = table.CreateSet<ProfileDataFactorySegment>();

            foreach (ProfileDataFactorySegment item in profileDataFactorySegment)
            {
                builder.AddDikeProfileSegment(item.StartPointX, item.StartPointZ, item.EndPointX, item.EndPointZ);
            }
        }

        [Given(@"the following dike profile point data:")]
        public void GivenTheFollowingDikeProfilePointData(Table table)
        {
            var profileDataFactoryPoint = table.CreateSet<ProfileDataFactoryPoint>();

            foreach (ProfileDataFactoryPoint item in profileDataFactoryPoint)
            {
                builder.AddDikeProfilePoint(item.X, item.CharacteristicPointType);
            }
        }

        [Given(@"the following location construction properties:")]
        public void GivenTheFollowingLocationConstructionProperties(Table table)
        {
            asphaltRevetmentWaveImpactLocationConstructionProperties = table.CreateInstance<AsphaltRevetmentWaveImpactLocationConstructionProperties>();          
        }

        [Given(@"location construction has the following impact factors:")]
        public void GivenLocationConstructionHasTheFollowingImpactFactors(Table table)
        {
            var impactFactors = asphaltRevetmentWaveImpactLocationConstructionProperties.ImpactFactors;
           // todo

        }


        [Given(@"the location constructionwith has the initial damage of (.*)")]
        public void GivenTheLocationConstructionwithHasTheInitialDamageOf(double initialDamage)
        {
            asphaltRevetmentWaveImpactLocationConstructionProperties.InitialDamage = initialDamage;
        }

        [Given(@"location construction has the thickness subLaye of (.*)")]
        public void GivenLocationConstructionHasTheThicknessSubLayeOf(double thicknessSubLayer)
        {
            asphaltRevetmentWaveImpactLocationConstructionProperties.ThicknessSubLayer = thicknessSubLayer;
        }

        [Given(@"location construction has the elastic modulus subLayer of (.*)")]
        public void GivenLocationConstructionHasTheElasticModulusSubLayerOf(double elasticModulusSubLayer)
        {
            asphaltRevetmentWaveImpactLocationConstructionProperties.ElasticModulusSubLayer = elasticModulusSubLayer;
        }


        [When(@"I add the asphalt wave impact location")]
        public void WhenIAddTheAsphaltWaveImpactLocation()
        {
            builder.AddAsphaltWaveImpactLocation(asphaltRevetmentWaveImpactLocationConstructionProperties);
        }


        [When(@"I run the calculation")]
        public void WhenIRunTheCalculation()
        {
            DataResult<ICalculationInput> calculationInput = builder.Build();

            _calculator = new Calculator(calculationInput.Data);
            _calculator.WaitForCompletion();
        }

        [Then(@"the ExpectedDamage is (.*) in a (.*)")]
        public void ThenTheExpectedDamageIsInA(double expectedDamage, int expectedTimeOfFailure)
        {
            Support.CalculationTest.AssertOutput(_calculator, expectedDamage, expectedTimeOfFailure);
        }
    }
}