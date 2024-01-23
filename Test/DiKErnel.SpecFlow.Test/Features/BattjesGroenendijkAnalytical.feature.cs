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
namespace DiKErnel.SpecFlow.Test.Features
{
    using TechTalk.SpecFlow;
    using System;
    using System.Linq;
    
    
    [System.CodeDom.Compiler.GeneratedCodeAttribute("TechTalk.SpecFlow", "3.9.0.0")]
    [System.Runtime.CompilerServices.CompilerGeneratedAttribute()]
    [NUnit.Framework.TestFixtureAttribute()]
    [NUnit.Framework.DescriptionAttribute("BattjesGroenendijkAnalytical")]
    public partial class BattjesGroenendijkAnalyticalFeature
    {
        
        private TechTalk.SpecFlow.ITestRunner testRunner;
        
        private string[] _featureTags = ((string[])(null));
        
#line 1 "BattjesGroenendijkAnalytical.feature"
#line hidden
        
        [NUnit.Framework.OneTimeSetUpAttribute()]
        public virtual void FeatureSetup()
        {
            testRunner = TechTalk.SpecFlow.TestRunnerManager.GetTestRunner();
            TechTalk.SpecFlow.FeatureInfo featureInfo = new TechTalk.SpecFlow.FeatureInfo(new System.Globalization.CultureInfo("en-US"), "Features", "BattjesGroenendijkAnalytical", "\tAs a user I want to perform grass wave runup calculations based on Battjes-Groen" +
                    "endijk Analytical.", ProgrammingLanguage.CSharp, ((string[])(null)));
            testRunner.OnFeatureStart(featureInfo);
        }
        
        [NUnit.Framework.OneTimeTearDownAttribute()]
        public virtual void FeatureTearDown()
        {
            testRunner.OnFeatureEnd();
            testRunner = null;
        }
        
        [NUnit.Framework.SetUpAttribute()]
        public virtual void TestInitialize()
        {
        }
        
        [NUnit.Framework.TearDownAttribute()]
        public virtual void TestTearDown()
        {
            testRunner.OnScenarioEnd();
        }
        
        public virtual void ScenarioInitialize(TechTalk.SpecFlow.ScenarioInfo scenarioInfo)
        {
            testRunner.OnScenarioInitialize(scenarioInfo);
            testRunner.ScenarioContext.ScenarioContainer.RegisterInstanceAs<NUnit.Framework.TestContext>(NUnit.Framework.TestContext.CurrentContext);
        }
        
        public virtual void ScenarioStart()
        {
            testRunner.OnScenarioStart();
        }
        
        public virtual void ScenarioCleanup()
        {
            testRunner.CollectScenarioErrors();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("Testcase 1 - Default with closed sod")]
        public virtual void Testcase1_DefaultWithClosedSod()
        {
            string[] tagsOfScenario = ((string[])(null));
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("Testcase 1 - Default with closed sod", null, tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 4
this.ScenarioInitialize(scenarioInfo);
#line hidden
            bool isScenarioIgnored = default(bool);
            bool isFeatureIgnored = default(bool);
            if ((tagsOfScenario != null))
            {
                isScenarioIgnored = tagsOfScenario.Where(__entry => __entry != null).Where(__entry => String.Equals(__entry, "ignore", StringComparison.CurrentCultureIgnoreCase)).Any();
            }
            if ((this._featureTags != null))
            {
                isFeatureIgnored = this._featureTags.Where(__entry => __entry != null).Where(__entry => String.Equals(__entry, "ignore", StringComparison.CurrentCultureIgnoreCase)).Any();
            }
            if ((isScenarioIgnored || isFeatureIgnored))
            {
                testRunner.SkipScenario();
            }
            else
            {
                this.ScenarioStart();
                TechTalk.SpecFlow.Table table1 = new TechTalk.SpecFlow.Table(new string[] {
                            "tijdstippen"});
                table1.AddRow(new string[] {
                            "0"});
                table1.AddRow(new string[] {
                            "3600"});
                table1.AddRow(new string[] {
                            "7200"});
                table1.AddRow(new string[] {
                            "10800"});
                table1.AddRow(new string[] {
                            "14400"});
                table1.AddRow(new string[] {
                            "18000"});
                table1.AddRow(new string[] {
                            "21600"});
                table1.AddRow(new string[] {
                            "25200"});
                table1.AddRow(new string[] {
                            "28800"});
                table1.AddRow(new string[] {
                            "32400"});
                table1.AddRow(new string[] {
                            "36000"});
                table1.AddRow(new string[] {
                            "39600"});
                table1.AddRow(new string[] {
                            "43200"});
                table1.AddRow(new string[] {
                            "46800"});
                table1.AddRow(new string[] {
                            "50400"});
                table1.AddRow(new string[] {
                            "54000"});
                table1.AddRow(new string[] {
                            "57600"});
#line 5
 testRunner.Given("the following tijdstippen:", ((string)(null)), table1, "Given ");
#line hidden
                TechTalk.SpecFlow.Table table2 = new TechTalk.SpecFlow.Table(new string[] {
                            "waterstanden",
                            "golfhoogtenHm0",
                            "golfperiodenTm10",
                            "golfrichtingen"});
                table2.AddRow(new string[] {
                            "3",
                            "0.5",
                            "3",
                            "50"});
                table2.AddRow(new string[] {
                            "3.1",
                            "0.7",
                            "3.5",
                            "45"});
                table2.AddRow(new string[] {
                            "3.2",
                            "1",
                            "4",
                            "40"});
                table2.AddRow(new string[] {
                            "3.3",
                            "1.3",
                            "4.3",
                            "35"});
                table2.AddRow(new string[] {
                            "3.4",
                            "1.5",
                            "4.5",
                            "30"});
                table2.AddRow(new string[] {
                            "3.5",
                            "1.8",
                            "4.8",
                            "25"});
                table2.AddRow(new string[] {
                            "3.6",
                            "2.1",
                            "5.2",
                            "20"});
                table2.AddRow(new string[] {
                            "3.7",
                            "2.5",
                            "5.5",
                            "15"});
                table2.AddRow(new string[] {
                            "3.7",
                            "2.8",
                            "5.8",
                            "10"});
                table2.AddRow(new string[] {
                            "3.6",
                            "2.8",
                            "6",
                            "5"});
                table2.AddRow(new string[] {
                            "3.5",
                            "2.5",
                            "6",
                            "0"});
                table2.AddRow(new string[] {
                            "3.4",
                            "2.1",
                            "5.8",
                            "0"});
                table2.AddRow(new string[] {
                            "3.3",
                            "1.8",
                            "5.5",
                            "5"});
                table2.AddRow(new string[] {
                            "3.2",
                            "1.5",
                            "5.2",
                            "10"});
                table2.AddRow(new string[] {
                            "3.1",
                            "1.3",
                            "4.8",
                            "15"});
                table2.AddRow(new string[] {
                            "3",
                            "1",
                            "4.5",
                            "20"});
#line 24
  testRunner.And("the following hydraulischeBelastingen:", ((string)(null)), table2, "And ");
#line hidden
                TechTalk.SpecFlow.Table table3 = new TechTalk.SpecFlow.Table(new string[] {
                            "dijkorientatie",
                            "posities",
                            "hoogten",
                            "ruwheidscoefficienten",
                            "teenBuitenzijde",
                            "kruinBuitenzijde"});
                table3.AddRow(new string[] {
                            "0",
                            "0",
                            "0",
                            "1.0",
                            "0",
                            "25"});
                table3.AddRow(new string[] {
                            "",
                            "25",
                            "7.5",
                            "",
                            "",
                            ""});
#line 42
    testRunner.And("the following dijkprofiel:", ((string)(null)), table3, "And ");
#line hidden
                TechTalk.SpecFlow.Table table4 = new TechTalk.SpecFlow.Table(new string[] {
                            "positie",
                            "rekenmethode",
                            "typeToplaag",
                            "beginschade",
                            "verhogingBelastingOvergangAlfaM",
                            "verlagingSterkteOvergangAlfaS"});
                table4.AddRow(new string[] {
                            "15",
                            "grasGolfoploop",
                            "grasGeslotenZode",
                            "0",
                            "1",
                            "1"});
#line 46
    testRunner.And("the following locaties:", ((string)(null)), table4, "And ");
#line hidden
                TechTalk.SpecFlow.Table table5 = new TechTalk.SpecFlow.Table(new string[] {
                            "rekenmethode",
                            "faalgetal",
                            "factorCtm",
                            "typeRekenprotocol",
                            "frontsnelheid",
                            "bodemVoorlandZ",
                            "tanAvl",
                            "typeToplaag",
                            "kritiekeCumulatieveOverbelasting",
                            "kritiekeFrontsnelheid"});
                table5.AddRow(new string[] {
                            "grasGolfoploop",
                            "1",
                            "0.92",
                            "battjesGroenendijkAnalytisch",
                            "1.1",
                            "-4.0",
                            "0.004",
                            "grasGeslotenZode",
                            "7000",
                            "6.6"});
#line 49
    testRunner.And("the following rekenmethoden:", ((string)(null)), table5, "And ");
#line hidden
#line 52
    testRunner.When("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
            }
            this.ScenarioCleanup();
        }
    }
}
#pragma warning restore
#endregion
