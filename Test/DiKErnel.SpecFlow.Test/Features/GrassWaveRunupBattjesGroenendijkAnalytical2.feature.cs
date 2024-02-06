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
    [NUnit.Framework.DescriptionAttribute("GrassWaveRunupBattjesGroenendijkAnalytical2")]
    public partial class GrassWaveRunupBattjesGroenendijkAnalytical2Feature
    {
        
        private TechTalk.SpecFlow.ITestRunner testRunner;
        
        private string[] _featureTags = ((string[])(null));
        
#line 1 "GrassWaveRunupBattjesGroenendijkAnalytical2.feature"
#line hidden
        
        [NUnit.Framework.OneTimeSetUpAttribute()]
        public virtual void FeatureSetup()
        {
            testRunner = TechTalk.SpecFlow.TestRunnerManager.GetTestRunner();
            TechTalk.SpecFlow.FeatureInfo featureInfo = new TechTalk.SpecFlow.FeatureInfo(new System.Globalization.CultureInfo("en-US"), "Features", "GrassWaveRunupBattjesGroenendijkAnalytical2", "\tBM Gras benchmarks", ProgrammingLanguage.CSharp, ((string[])(null)));
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
        
        public virtual void FeatureBackground()
        {
#line 4
  #line hidden
            TechTalk.SpecFlow.Table table25 = new TechTalk.SpecFlow.Table(new string[] {
                        "tijdstippen",
                        "waterstanden",
                        "golfhoogtenHm0",
                        "golfperiodenTm10",
                        "golfrichtingen"});
            table25.AddRow(new string[] {
                        "0",
                        "0",
                        "1.5",
                        "4.20",
                        "0"});
            table25.AddRow(new string[] {
                        "900",
                        "",
                        "",
                        "",
                        ""});
#line 5
  testRunner.Given("the following tijdstippen and hydraulischeBelastingen:", ((string)(null)), table25, "Given ");
#line hidden
            TechTalk.SpecFlow.Table table26 = new TechTalk.SpecFlow.Table(new string[] {
                        "posities",
                        "hoogten",
                        "ruwheidscoefficienten",
                        "teenBuitenzijde",
                        "kruinBuitenzijde"});
            table26.AddRow(new string[] {
                        "0",
                        "-10",
                        "1",
                        "0",
                        "80"});
            table26.AddRow(new string[] {
                        "40",
                        "0",
                        "1",
                        "",
                        ""});
            table26.AddRow(new string[] {
                        "80",
                        "10",
                        "",
                        "",
                        ""});
#line 9
     testRunner.And("the following dijkprofiel and a dikeorientatie of 0:", ((string)(null)), table26, "And ");
#line hidden
            TechTalk.SpecFlow.Table table27 = new TechTalk.SpecFlow.Table(new string[] {
                        "positie",
                        "typeToplaag",
                        "beginschade",
                        "verhogingBelastingOvergangAlfaM",
                        "verlagingSterkteOvergangAlfaS"});
            table27.AddRow(new string[] {
                        "40.4",
                        "grasGeslotenZode",
                        "0",
                        "1",
                        "1"});
#line 14
     testRunner.And("the following locaties:", ((string)(null)), table27, "And ");
#line hidden
            TechTalk.SpecFlow.Table table28 = new TechTalk.SpecFlow.Table(new string[] {
                        "faalgetal",
                        "factorCtm",
                        "frontsnelheid",
                        "bodemVoorlandZ",
                        "tanAvl",
                        "typeToplaag"});
            table28.AddRow(new string[] {
                        "1",
                        "3.85",
                        "1.10",
                        "-3",
                        "0.004",
                        "grasGeslotenZode"});
#line 17
     testRunner.And("the following rekenmethoden:", ((string)(null)), table28, "And ");
#line hidden
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 14")]
        [NUnit.Framework.TestCaseAttribute("3.5", "698.151", null)]
        [NUnit.Framework.TestCaseAttribute("4", "588.395", null)]
        [NUnit.Framework.TestCaseAttribute("5.5", "7.156", null)]
        [NUnit.Framework.TestCaseAttribute("6.5", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("8", "0.000", null)]
        public virtual void BMGrasBenchmark14(string kritiekeFrontsnelheid, string cumulatieveOverbelastingTijdstap, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("kritiekeFrontsnelheid", kritiekeFrontsnelheid);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 14", null, tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 21
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
#line 4
  this.FeatureBackground();
#line hidden
#line 22
  testRunner.When(string.Format("I change the property kritiekeFrontsnelheid to a value of {0}", kritiekeFrontsnelheid), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 23
  testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 24
  testRunner.Then(string.Format("the output value for {0} is", cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 15")]
        [NUnit.Framework.TestCaseAttribute("0", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("2", "1.134", null)]
        [NUnit.Framework.TestCaseAttribute("2", "1.134", null)]
        [NUnit.Framework.TestCaseAttribute("3", "0.139", null)]
        [NUnit.Framework.TestCaseAttribute("4", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("5", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("6", "0.000", null)]
        public virtual void BMGrasBenchmark15(string bodemVoorlandZ, string cumulatieveOverbelastingTijdstap, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("bodemVoorlandZ", bodemVoorlandZ);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 15", null, tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 34
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
#line 4
  this.FeatureBackground();
#line hidden
#line 35
     testRunner.When(string.Format("I change the property bodemVoorlandZ to a value of {0}", bodemVoorlandZ), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 36
     testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 37
     testRunner.Then(string.Format("the output value for {0} is", cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 16")]
        [NUnit.Framework.TestCaseAttribute("0", "0.918", null)]
        [NUnit.Framework.TestCaseAttribute("0.004", "1.134", null)]
        [NUnit.Framework.TestCaseAttribute("0.04", "13.406", null)]
        [NUnit.Framework.TestCaseAttribute("0.1", "49.205", null)]
        [NUnit.Framework.TestCaseAttribute("0.4", "48.062", null)]
        [NUnit.Framework.TestCaseAttribute("10", "48.062", null)]
        [NUnit.Framework.TestCaseAttribute("100", "48.062", null)]
        [NUnit.Framework.TestCaseAttribute("250", "48.062", null)]
        public virtual void BMGrasBenchmark16(string hellingVoorland, string cumulatieveOverbelastingTijdstap, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("hellingVoorland", hellingVoorland);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 16", null, tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 49
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
#line 4
  this.FeatureBackground();
#line hidden
#line 50
     testRunner.When(string.Format("I change the property tanAvl to a value of {0}", hellingVoorland), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 51
     testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 52
     testRunner.Then(string.Format("the output value for {0} is", cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 17")]
        [NUnit.Framework.TestCaseAttribute("0", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("0.004", "133115.947", null)]
        [NUnit.Framework.TestCaseAttribute("0.04", "13755.272", null)]
        [NUnit.Framework.TestCaseAttribute("0.1", "5759.070", null)]
        [NUnit.Framework.TestCaseAttribute("0.4", "1031.437", null)]
        [NUnit.Framework.TestCaseAttribute("10", "21.453", null)]
        [NUnit.Framework.TestCaseAttribute("100", "", null)]
        [NUnit.Framework.TestCaseAttribute("250", "", null)]
        public virtual void BMGrasBenchmark17(string diepteVoorland, string cumulatieveOverbelastingTijdstap, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("diepteVoorland", diepteVoorland);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 17", null, tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 65
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
#line 4
  this.FeatureBackground();
#line hidden
#line 66
     testRunner.When(string.Format("I change the property bodemVoorlandZ to a value of {0}", diepteVoorland), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 67
     testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 68
     testRunner.Then(string.Format("the output value for {0} is", cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 18")]
        [NUnit.Framework.TestCaseAttribute("0", "1000", "0.000", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("0.004", "1000", "133115.947", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("0.04", "100", "13755.272", "0.007", null)]
        [NUnit.Framework.TestCaseAttribute("0.1", "10", "5759.070", "0.002", null)]
        [NUnit.Framework.TestCaseAttribute("0.4", "1", "1031.437", "0.001", null)]
        [NUnit.Framework.TestCaseAttribute("10", "1", "21.453", "0.047", null)]
        [NUnit.Framework.TestCaseAttribute("100", "1", "", "", null)]
        [NUnit.Framework.TestCaseAttribute("250", "1", "", "", null)]
        public virtual void BMGrasBenchmark18(string diepteVoorland, string kritiekeCumulatieveOverbelasting, string cumulatieveOverbelastingTijdstap, string fos, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("diepteVoorland", diepteVoorland);
            argumentsOfScenario.Add("kritiekeCumulatieveOverbelasting", kritiekeCumulatieveOverbelasting);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            argumentsOfScenario.Add("Fos", fos);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 18", null, tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 81
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
#line 4
  this.FeatureBackground();
#line hidden
#line 82
     testRunner.When(string.Format("I change the property bodemVoorlandZ to a value of {0}", diepteVoorland), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 83
     testRunner.And(string.Format("I change the property kritiekeCumulatieveOverbelasting to a value of {0}", kritiekeCumulatieveOverbelasting), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 84
  testRunner.And("I run the calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 85
  testRunner.Then(string.Format("the output value for {0} is", cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
#line 86
  testRunner.And("the output value for <FoS> is", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
            }
            this.ScenarioCleanup();
        }
    }
}
#pragma warning restore
#endregion
