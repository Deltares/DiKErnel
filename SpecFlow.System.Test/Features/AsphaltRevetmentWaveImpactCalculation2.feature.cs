﻿// ------------------------------------------------------------------------------
//  <auto-generated>
//      This code was generated by SpecFlow (https://www.specflow.org/).
//      SpecFlow Version:3.9.0.0
//      SpecFlow Generator Version:3.9.0.0
// 
//      Changes to this file may cause incorrect behavior and will be lost if
//      the code is regenerated.
//  </auto-generated>
// ------------------------------------------------------------------------------
#region Designer generated code
#pragma warning disable
namespace SpecFlow.SystemTest.Features
{
    using TechTalk.SpecFlow;
    using System;
    using System.Linq;
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("TechTalk.SpecFlow", "3.9.0.0")]
    [System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    [NUnit.Framework.TestFixtureAttribute()]
    [NUnit.Framework.DescriptionAttribute("TestAsphaltRevetmentWaveImpactCalculation2")]
    public partial class TestAsphaltRevetmentWaveImpactCalculation2Feature
    {
        
        private TechTalk.SpecFlow.ITestRunner testRunner;
        
        private static string[] featureTags = ((string[])(null));
        
#line 1 "AsphaltRevetmentWaveImpactCalculation2.feature"
#line hidden
        
        [NUnit.Framework.OneTimeSetUpAttribute()]
        public virtual void FeatureSetup()
        {
            testRunner = TechTalk.SpecFlow.TestRunnerManager.GetTestRunner();
            TechTalk.SpecFlow.FeatureInfo featureInfo = new TechTalk.SpecFlow.FeatureInfo(new System.Globalization.CultureInfo("en-US"), "Features", "TestAsphaltRevetmentWaveImpactCalculation2", null, ProgrammingLanguage.CSharp, featureTags);
            testRunner.OnFeatureStart(featureInfo);
        }
        
        [NUnit.Framework.OneTimeTearDownAttribute()]
        public virtual void FeatureTearDown()
        {
            testRunner.OnFeatureEnd();
            testRunner = null;
        }
        
        [NUnit.Framework.SetUpAttribute()]
        public void TestInitialize()
        {
        }
        
        [NUnit.Framework.TearDownAttribute()]
        public void TestTearDown()
        {
            testRunner.OnScenarioEnd();
        }
        
        public void ScenarioInitialize(TechTalk.SpecFlow.ScenarioInfo scenarioInfo)
        {
            testRunner.OnScenarioInitialize(scenarioInfo);
            testRunner.ScenarioContext.ScenarioContainer.RegisterInstanceAs<NUnit.Framework.TestContext>(NUnit.Framework.TestContext.CurrentContext);
        }
        
        public void ScenarioStart()
        {
            testRunner.OnScenarioStart();
        }
        
        public void ScenarioCleanup()
        {
            testRunner.CollectScenarioErrors();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpec" +
            "tedCalculationResult")]
        public void GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            string[] tagsOfScenario = ((string[])(null));
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpec" +
                    "tedCalculationResult", null, tagsOfScenario, argumentsOfScenario, featureTags);
#line 4
this.ScenarioInitialize(scenarioInfo);
#line hidden
            if ((TagHelper.ContainsIgnoreTag(tagsOfScenario) || TagHelper.ContainsIgnoreTag(featureTags)))
            {
                testRunner.SkipScenario();
            }
            else
            {
                this.ScenarioStart();
                TechTalk.SpecFlow.Table table15 = new TechTalk.SpecFlow.Table(new string[] {
                            "BeginTime",
                            "EndTime",
                            "WaterLevel",
                            "WaveHeightHm0",
                            "WavePeriodTm10",
                            "WaveAngle"});
                table15.AddRow(new string[] {
                            "-3600",
                            "-2880",
                            "2",
                            "1",
                            "4",
                            "0"});
                table15.AddRow(new string[] {
                            "-2880",
                            "-1440",
                            "2.2",
                            "1.5",
                            "5",
                            "0"});
                table15.AddRow(new string[] {
                            "-1440",
                            "720",
                            "2.4",
                            "2",
                            "5.5",
                            "0"});
                table15.AddRow(new string[] {
                            "720",
                            "3600",
                            "2.6",
                            "2.4",
                            "6",
                            "0"});
                table15.AddRow(new string[] {
                            "3600",
                            "7200",
                            "2.8",
                            "2.5",
                            "6.2",
                            "0"});
                table15.AddRow(new string[] {
                            "7200",
                            "11520",
                            "3",
                            "2.6",
                            "6.3",
                            "0"});
                table15.AddRow(new string[] {
                            "11520",
                            "16560",
                            "2.8",
                            "2.7",
                            "6.5",
                            "0"});
                table15.AddRow(new string[] {
                            "16560",
                            "22320",
                            "2.6",
                            "2.6",
                            "6.6",
                            "0"});
                table15.AddRow(new string[] {
                            "22320",
                            "28800",
                            "2.4",
                            "2.5",
                            "6.3",
                            "0"});
                table15.AddRow(new string[] {
                            "28800",
                            "36000",
                            "2",
                            "2.4",
                            "6.2",
                            "0"});
#line 5
 testRunner.Given("the following schematisation for time steps:", ((string)(null)), table15, "Given ");
#line hidden
                TechTalk.SpecFlow.Table table16 = new TechTalk.SpecFlow.Table(new string[] {
                            "StartPointX",
                            "StartPointZ",
                            "EndPointX",
                            "EndPointZ"});
                table16.AddRow(new string[] {
                            "0",
                            "0",
                            "30",
                            "7.5"});
#line 17
 testRunner.And("the follwoing Dike profile segments:", ((string)(null)), table16, "And ");
#line hidden
                TechTalk.SpecFlow.Table table17 = new TechTalk.SpecFlow.Table(new string[] {
                            "X",
                            "CharacteristicPointType"});
                table17.AddRow(new string[] {
                            "0",
                            "OuterToe"});
                table17.AddRow(new string[] {
                            "30",
                            "OuterCrest"});
#line 20
 testRunner.And("the following dike profile point data:", ((string)(null)), table17, "And ");
#line hidden
                TechTalk.SpecFlow.Table table18 = new TechTalk.SpecFlow.Table(new string[] {
                            "X",
                            "AsphaltRevetmentTopLayerType",
                            "FailureTension",
                            "SoilElasticity",
                            "ThicknessUpperLayer",
                            "ElasticModulusUpperLayer"});
                table18.AddRow(new string[] {
                            "10",
                            "HydraulicAsphaltConcrete",
                            "1.6",
                            "55",
                            "0.4",
                            "18000"});
#line 24
 testRunner.And("the following location construction properties:", ((string)(null)), table18, "And ");
#line hidden
#line 27
 testRunner.When("I add the asphalt wave impact location", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 28
 testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpec" +
            "tedCalculationResult")]
        public void GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            string[] tagsOfScenario = ((string[])(null));
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpec" +
                    "tedCalculationResult", null, tagsOfScenario, argumentsOfScenario, featureTags);
#line 30
this.ScenarioInitialize(scenarioInfo);
#line hidden
            if ((TagHelper.ContainsIgnoreTag(tagsOfScenario) || TagHelper.ContainsIgnoreTag(featureTags)))
            {
                testRunner.SkipScenario();
            }
            else
            {
                this.ScenarioStart();
                TechTalk.SpecFlow.Table table19 = new TechTalk.SpecFlow.Table(new string[] {
                            "BeginTime",
                            "EndTime",
                            "WaterLevel",
                            "WaveHeightHm0",
                            "WavePeriodTm10",
                            "WaveAngle"});
                table19.AddRow(new string[] {
                            "0",
                            "3600",
                            "2",
                            "1",
                            "4",
                            "0"});
                table19.AddRow(new string[] {
                            "3600",
                            "7200",
                            "2.2",
                            "1.5",
                            "5",
                            "0"});
                table19.AddRow(new string[] {
                            "7200",
                            "10800",
                            "2.4",
                            "2",
                            "5.5",
                            "0"});
                table19.AddRow(new string[] {
                            "10800",
                            "14400",
                            "2.6",
                            "2.4",
                            "6",
                            "0"});
                table19.AddRow(new string[] {
                            "14400",
                            "18000",
                            "2.8",
                            "2.5",
                            "6.2",
                            "0"});
                table19.AddRow(new string[] {
                            "18000",
                            "21600",
                            "3",
                            "2.6",
                            "6.3",
                            "0"});
                table19.AddRow(new string[] {
                            "21600",
                            "25200",
                            "2.8",
                            "2.7",
                            "6.5",
                            "0"});
                table19.AddRow(new string[] {
                            "25200",
                            "28800",
                            "2.6",
                            "2.6",
                            "6.6",
                            "0"});
                table19.AddRow(new string[] {
                            "28800",
                            "32400",
                            "2.4",
                            "2.5",
                            "6.3",
                            "0"});
                table19.AddRow(new string[] {
                            "32400",
                            "36000",
                            "2",
                            "2.4",
                            "6.2",
                            "0"});
#line 31
 testRunner.Given("the following schematisation for time steps:", ((string)(null)), table19, "Given ");
#line hidden
                TechTalk.SpecFlow.Table table20 = new TechTalk.SpecFlow.Table(new string[] {
                            "StartPointX",
                            "StartPointZ",
                            "EndPointX",
                            "EndPointZ"});
                table20.AddRow(new string[] {
                            "0",
                            "0",
                            "8",
                            "2"});
                table20.AddRow(new string[] {
                            "8",
                            "2",
                            "17",
                            "3"});
                table20.AddRow(new string[] {
                            "17",
                            "3",
                            "35",
                            "7.5"});
#line 43
 testRunner.And("the follwoing Dike profile segments:", ((string)(null)), table20, "And ");
#line hidden
                TechTalk.SpecFlow.Table table21 = new TechTalk.SpecFlow.Table(new string[] {
                            "X",
                            "CharacteristicPointType"});
                table21.AddRow(new string[] {
                            "0",
                            "OuterToe"});
                table21.AddRow(new string[] {
                            "8",
                            "CrestOuterBerm"});
                table21.AddRow(new string[] {
                            "17",
                            "NotchOuterBerm"});
                table21.AddRow(new string[] {
                            "35",
                            "OuterCrest"});
#line 48
 testRunner.And("the following dike profile point data:", ((string)(null)), table21, "And ");
#line hidden
                TechTalk.SpecFlow.Table table22 = new TechTalk.SpecFlow.Table(new string[] {
                            "X",
                            "AsphaltRevetmentTopLayerType",
                            "FailureTension",
                            "SoilElasticity",
                            "ThicknessUpperLayer",
                            "ElasticModulusUpperLayer"});
                table22.AddRow(new string[] {
                            "12.5",
                            "HydraulicAsphaltConcrete",
                            "1.6",
                            "55",
                            "0.4",
                            "16000"});
#line 54
 testRunner.And("the following location construction properties:", ((string)(null)), table22, "And ");
#line hidden
#line 57
 testRunner.When("I add the asphalt wave impact location", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 58
 testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
            }
            this.ScenarioCleanup();
        }
    }
}
#pragma warning restore
#endregion
