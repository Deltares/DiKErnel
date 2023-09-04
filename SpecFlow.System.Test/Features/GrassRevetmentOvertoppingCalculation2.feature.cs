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
    [NUnit.Framework.DescriptionAttribute("GrassRevetmentOvertoppingCalculation2")]
    public partial class GrassRevetmentOvertoppingCalculation2Feature
    {
        
        private TechTalk.SpecFlow.ITestRunner testRunner;
        
        private static string[] featureTags = ((string[])(null));
        
#line 1 "GrassRevetmentOvertoppingCalculation2.feature"
#line hidden
        
        [NUnit.Framework.OneTimeSetUpAttribute()]
        public virtual void FeatureSetup()
        {
            testRunner = TechTalk.SpecFlow.TestRunnerManager.GetTestRunner();
            TechTalk.SpecFlow.FeatureInfo featureInfo = new TechTalk.SpecFlow.FeatureInfo(new System.Globalization.CultureInfo("en-US"), "Features", "GrassRevetmentOvertoppingCalculation2", null, ProgrammingLanguage.CSharp, featureTags);
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
        
        public virtual void FeatureBackground()
        {
#line 5
#line hidden
            TechTalk.SpecFlow.Table table30 = new TechTalk.SpecFlow.Table(new string[] {
                        "BeginTime",
                        "EndTime",
                        "WaterLevel",
                        "WaveHeightHm0",
                        "WavePeriodTm10",
                        "WaveAngle"});
            table30.AddRow(new string[] {
                        "0",
                        "3600",
                        "5",
                        "2.35",
                        "5.2",
                        "-10"});
            table30.AddRow(new string[] {
                        "3600",
                        "7200",
                        "5.1",
                        "2.4",
                        "5.23",
                        "-8"});
            table30.AddRow(new string[] {
                        "7200",
                        "10800",
                        "5.2",
                        "2.45",
                        "5.26",
                        "-6"});
            table30.AddRow(new string[] {
                        "10800",
                        "14400",
                        "5.3",
                        "2.5",
                        "5.29",
                        "-4"});
            table30.AddRow(new string[] {
                        "14400",
                        "18000",
                        "5.4",
                        "2.55",
                        "5.32",
                        "-2"});
            table30.AddRow(new string[] {
                        "18000",
                        "21600",
                        "5.5",
                        "2.6",
                        "5.35",
                        "0"});
            table30.AddRow(new string[] {
                        "21600",
                        "25200",
                        "5.6",
                        "2.65",
                        "5.38",
                        "2"});
            table30.AddRow(new string[] {
                        "25200",
                        "28800",
                        "5.7",
                        "2.7",
                        "5.41",
                        "4"});
            table30.AddRow(new string[] {
                        "28800",
                        "32400",
                        "5.7",
                        "2.75",
                        "5.44",
                        "6"});
            table30.AddRow(new string[] {
                        "32400",
                        "36000",
                        "5.6",
                        "2.8",
                        "5.47",
                        "8"});
            table30.AddRow(new string[] {
                        "36000",
                        "39600",
                        "5.5",
                        "2.85",
                        "5.5",
                        "10"});
            table30.AddRow(new string[] {
                        "39600",
                        "43200",
                        "5.4",
                        "2.9",
                        "5.53",
                        "12"});
            table30.AddRow(new string[] {
                        "43200",
                        "46800",
                        "5.3",
                        "2.95",
                        "5.56",
                        "14"});
            table30.AddRow(new string[] {
                        "46800",
                        "50400",
                        "5.2",
                        "3",
                        "5.59",
                        "16"});
            table30.AddRow(new string[] {
                        "50400",
                        "54000",
                        "5.1",
                        "3.05",
                        "5.62",
                        "18"});
            table30.AddRow(new string[] {
                        "54000",
                        "57600",
                        "5",
                        "3.1",
                        "5.65",
                        "20"});
#line 6
 testRunner.Given("the following schematisation for time steps:", ((string)(null)), table30, "Given ");
#line hidden
            TechTalk.SpecFlow.Table table31 = new TechTalk.SpecFlow.Table(new string[] {
                        "StartPointX",
                        "StartPointZ",
                        "EndPointX",
                        "EndPointZ",
                        "roughnessCoefficient"});
            table31.AddRow(new string[] {
                        "0",
                        "-0.1",
                        "5",
                        "0",
                        "1"});
            table31.AddRow(new string[] {
                        "5",
                        "0",
                        "30",
                        "7.5",
                        "1"});
            table31.AddRow(new string[] {
                        "30",
                        "7.5",
                        "31",
                        "7.6",
                        "0.8"});
            table31.AddRow(new string[] {
                        "31",
                        "7.6",
                        "34",
                        "7.7",
                        "0.8"});
            table31.AddRow(new string[] {
                        "34",
                        "7.7",
                        "35",
                        "7.4",
                        "0.8"});
            table31.AddRow(new string[] {
                        "35",
                        "7.4",
                        "45",
                        "5",
                        "0.8"});
            table31.AddRow(new string[] {
                        "45",
                        "5",
                        "60",
                        "0.5",
                        "0.8"});
            table31.AddRow(new string[] {
                        "60",
                        "0.5",
                        "70",
                        "0.5",
                        "0.8"});
#line 24
 testRunner.And("the follwoing Dike profile segments:", ((string)(null)), table31, "And ");
#line hidden
            TechTalk.SpecFlow.Table table32 = new TechTalk.SpecFlow.Table(new string[] {
                        "X",
                        "CharacteristicPointType"});
            table32.AddRow(new string[] {
                        "5",
                        "OuterToe"});
            table32.AddRow(new string[] {
                        "30",
                        "OuterCrest"});
            table32.AddRow(new string[] {
                        "35",
                        "InnerCrest"});
            table32.AddRow(new string[] {
                        "60",
                        "InnerToe"});
#line 34
 testRunner.And("the following dike profile point data:", ((string)(null)), table32, "And ");
#line hidden
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
#line 41
this.ScenarioInitialize(scenarioInfo);
#line hidden
            if ((TagHelper.ContainsIgnoreTag(tagsOfScenario) || TagHelper.ContainsIgnoreTag(featureTags)))
            {
                testRunner.SkipScenario();
            }
            else
            {
                this.ScenarioStart();
#line 5
this.FeatureBackground();
#line hidden
                TechTalk.SpecFlow.Table table33 = new TechTalk.SpecFlow.Table(new string[] {
                            "X",
                            "GrassRevetmentTopLayerType"});
                table33.AddRow(new string[] {
                            "40",
                            "OpenSod"});
#line 42
 testRunner.Given("the following location construction:", ((string)(null)), table33, "Given ");
#line hidden
#line 45
 testRunner.When("I add the grass overtopping location", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 46
 testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpec" +
            "tedCalculationResult")]
        public void GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            string[] tagsOfScenario = ((string[])(null));
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpec" +
                    "tedCalculationResult", null, tagsOfScenario, argumentsOfScenario, featureTags);
#line 48
this.ScenarioInitialize(scenarioInfo);
#line hidden
            if ((TagHelper.ContainsIgnoreTag(tagsOfScenario) || TagHelper.ContainsIgnoreTag(featureTags)))
            {
                testRunner.SkipScenario();
            }
            else
            {
                this.ScenarioStart();
#line 5
this.FeatureBackground();
#line hidden
                TechTalk.SpecFlow.Table table34 = new TechTalk.SpecFlow.Table(new string[] {
                            "X",
                            "GrassRevetmentTopLayerType",
                            "DikeHeight"});
                table34.AddRow(new string[] {
                            "30",
                            "OpenSod",
                            "9.5"});
#line 49
 testRunner.Given("the following location construction:", ((string)(null)), table34, "Given ");
#line hidden
#line 53
 testRunner.When("I add the grass overtopping location", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 54
 testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("GivenCalculationInputForSchematization2Testcase3_WhenCalculating_ThenReturnsExpec" +
            "tedCalculationResult")]
        public void GivenCalculationInputForSchematization2Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            string[] tagsOfScenario = ((string[])(null));
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("GivenCalculationInputForSchematization2Testcase3_WhenCalculating_ThenReturnsExpec" +
                    "tedCalculationResult", null, tagsOfScenario, argumentsOfScenario, featureTags);
#line 56
this.ScenarioInitialize(scenarioInfo);
#line hidden
            if ((TagHelper.ContainsIgnoreTag(tagsOfScenario) || TagHelper.ContainsIgnoreTag(featureTags)))
            {
                testRunner.SkipScenario();
            }
            else
            {
                this.ScenarioStart();
#line 5
this.FeatureBackground();
#line hidden
                TechTalk.SpecFlow.Table table35 = new TechTalk.SpecFlow.Table(new string[] {
                            "X",
                            "GrassRevetmentTopLayerType",
                            "DikeHeight",
                            "IncreasedLoadTransitionAlphaM"});
                table35.AddRow(new string[] {
                            "35",
                            "OpenSod",
                            "9.56",
                            "1.2"});
#line 57
 testRunner.Given("the following location construction:", ((string)(null)), table35, "Given ");
#line hidden
#line 62
 testRunner.When("I add the grass overtopping location", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 63
 testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("GivenCalculationInputForSchematization2Testcase4_WhenCalculating_ThenReturnsExpec" +
            "tedCalculationResult")]
        public void GivenCalculationInputForSchematization2Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult()
        {
            string[] tagsOfScenario = ((string[])(null));
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("GivenCalculationInputForSchematization2Testcase4_WhenCalculating_ThenReturnsExpec" +
                    "tedCalculationResult", null, tagsOfScenario, argumentsOfScenario, featureTags);
#line 65
this.ScenarioInitialize(scenarioInfo);
#line hidden
            if ((TagHelper.ContainsIgnoreTag(tagsOfScenario) || TagHelper.ContainsIgnoreTag(featureTags)))
            {
                testRunner.SkipScenario();
            }
            else
            {
                this.ScenarioStart();
#line 5
this.FeatureBackground();
#line hidden
                TechTalk.SpecFlow.Table table36 = new TechTalk.SpecFlow.Table(new string[] {
                            "X",
                            "GrassRevetmentTopLayerType",
                            "IncreasedLoadTransitionAlphaM",
                            "ReducedStrengthTransitionAlphaS",
                            "FixedNumberOfWaves",
                            "DikeHeight"});
                table36.AddRow(new string[] {
                            "35",
                            "OpenSod",
                            "1.2",
                            "1.3",
                            "5000",
                            "9.7"});
#line 66
 testRunner.Given("the following location construction:", ((string)(null)), table36, "Given ");
#line hidden
#line 73
 testRunner.When("I add the grass overtopping location", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 74
 testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
            }
            this.ScenarioCleanup();
        }
    }
}
#pragma warning restore
#endregion
