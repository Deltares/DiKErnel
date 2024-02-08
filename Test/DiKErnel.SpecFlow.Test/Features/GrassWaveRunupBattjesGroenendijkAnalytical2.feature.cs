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
            TechTalk.SpecFlow.FeatureInfo featureInfo = new TechTalk.SpecFlow.FeatureInfo(new System.Globalization.CultureInfo("en-US"), "Features", "GrassWaveRunupBattjesGroenendijkAnalytical2", @"As a user I want to perform grass wave run-up calculations based on Battjes-Groenendijk analytical.

The following testcases correspond with BM Gras benchmarks.

DiKErnel does not produce exactly the same results as BM Gras. This is mainly due to the following differences:
- BM Gras rounds the value of averageNumberOfWaves to an integer. This is not the case in DiKErnel.
- BM Gras uses an older version of dikes.Overtopping.dll (version 19.1.1).
- BM Gras is a user interface and performs validation of input parameters. This is not the case in DiKErnel.", ProgrammingLanguage.CSharp, ((string[])(null)));
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
#line 11
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
#line 12
        testRunner.Given("the following tijdstippen and hydraulischeBelastingen:", ((string)(null)), table25, "Given ");
#line hidden
            TechTalk.SpecFlow.Table table26 = new TechTalk.SpecFlow.Table(new string[] {
                        "posities",
                        "hoogten",
                        "ruwheidscoefficienten"});
            table26.AddRow(new string[] {
                        "0",
                        "-10",
                        "1"});
            table26.AddRow(new string[] {
                        "40",
                        "0",
                        "1"});
            table26.AddRow(new string[] {
                        "80",
                        "10",
                        ""});
#line 16
        testRunner.And("the following dijkprofiel and a dijkorientatie of 0:", ((string)(null)), table26, "And ");
#line hidden
            TechTalk.SpecFlow.Table table27 = new TechTalk.SpecFlow.Table(new string[] {
                        "teenBuitenzijde",
                        "kruinBuitenzijde"});
            table27.AddRow(new string[] {
                        "0",
                        "80"});
#line 21
        testRunner.And("the following karakteristiekePunten:", ((string)(null)), table27, "And ");
#line hidden
            TechTalk.SpecFlow.Table table28 = new TechTalk.SpecFlow.Table(new string[] {
                        "Setting",
                        "Value"});
            table28.AddRow(new string[] {
                        "positie",
                        "40.4"});
            table28.AddRow(new string[] {
                        "typeToplaag",
                        "grasGeslotenZode"});
            table28.AddRow(new string[] {
                        "beginSchade",
                        "0"});
            table28.AddRow(new string[] {
                        "verhogingBelastingOvergangAlfaM",
                        "1"});
            table28.AddRow(new string[] {
                        "verlagingSterkteOvergangAlfaS",
                        "1"});
            table28.AddRow(new string[] {
                        "faalgetal",
                        "1"});
            table28.AddRow(new string[] {
                        "factorCtm",
                        "3.85"});
            table28.AddRow(new string[] {
                        "frontsnelheid",
                        "1.10"});
            table28.AddRow(new string[] {
                        "bodemVoorlandZ",
                        "-3.0"});
            table28.AddRow(new string[] {
                        "tanAvl",
                        "0.004"});
#line 24
        testRunner.And("the following rekeninstellingen:", ((string)(null)), table28, "And ");
#line hidden
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 14 - Variable input of critical velocity")]
        [NUnit.Framework.TestCaseAttribute("3.5", "0.09912791114814828", "693.895378037038", "698.202", "698.151", null)]
        [NUnit.Framework.TestCaseAttribute("4", "0.08240815773892438", "576.8571041724706", "588.477", "588.395", null)]
        [NUnit.Framework.TestCaseAttribute("5.5", "0.0010160364930812532", "7.112255451568773", "7.162", "7.156", null)]
        [NUnit.Framework.TestCaseAttribute("6.5", "5.35959825332454e-09", "3.751718777327178e-05", "0.000", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("8", "0.0", "0.0", "0.000", "0.000", null)]
        public virtual void BMGrasBenchmark14_VariableInputOfCriticalVelocity(string kritiekeFrontsnelheid, string schadegetal, string cumulatieveOverbelastingTijdstap, string benchmarkForBMGras, string bMGras, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("kritiekeFrontsnelheid", kritiekeFrontsnelheid);
            argumentsOfScenario.Add("schadegetal", schadegetal);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            argumentsOfScenario.Add("Benchmark for BM Gras", benchmarkForBMGras);
            argumentsOfScenario.Add("BM Gras", bMGras);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 14 - Variable input of critical velocity", null, tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 37
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
#line 11
    this.FeatureBackground();
#line hidden
#line 38
        testRunner.When(string.Format("I change the property kritiekeFrontsnelheid to a value of {0}", kritiekeFrontsnelheid), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 39
        testRunner.And("I run the Battjes-Groenendijk Wave Runup Calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 40
        testRunner.Then(string.Format("the output values for {0} and {1} are", schadegetal, cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 15 - Variable input of level of interest")]
        [NUnit.Framework.TestCaseAttribute("30.5600", "0.0", "", "0.000", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("33.6160", "0.00016098541128284046", "1.1268978789798831", "1.136", "1.134", null)]
        [NUnit.Framework.TestCaseAttribute("36.6720", "0.00016098541128278394", "1.1268978789794877", "1.136", "1.134", null)]
        [NUnit.Framework.TestCaseAttribute("39.7280", "1.973187114472698e-05", "0.13812309801308886", "0.139", "0.139", null)]
        [NUnit.Framework.TestCaseAttribute("42.7840", "1.5496648932714766e-11", "1.0847654252900337e-07", "0.000", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("45.8400", "0.0", "0.0", "0.000", "0.000", null)]
        [NUnit.Framework.TestCaseAttribute("48.8960", "0.0", "0.0", "0.000", "0.000", null)]
        public virtual void BMGrasBenchmark15_VariableInputOfLevelOfInterest(string positie, string schadegetal, string cumulatieveOverbelastingTijdstap, string benchmarkForBMGras, string bMGras, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("positie", positie);
            argumentsOfScenario.Add("schadegetal", schadegetal);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            argumentsOfScenario.Add("Benchmark for BM Gras", benchmarkForBMGras);
            argumentsOfScenario.Add("BM Gras", bMGras);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 15 - Variable input of level of interest", null, tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 50
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
#line 11
    this.FeatureBackground();
#line hidden
                TechTalk.SpecFlow.Table table29 = new TechTalk.SpecFlow.Table(new string[] {
                            "posities",
                            "hoogten",
                            "ruwheidscoefficienten"});
                table29.AddRow(new string[] {
                            "0",
                            "-10.0",
                            "1.0"});
                table29.AddRow(new string[] {
                            "30.56",
                            "0.0",
                            "1.0"});
                table29.AddRow(new string[] {
                            "61.12",
                            "10.0",
                            ""});
#line 52
        testRunner.Given("the following series are adjusted:", ((string)(null)), table29, "Given ");
#line hidden
                TechTalk.SpecFlow.Table table30 = new TechTalk.SpecFlow.Table(new string[] {
                            "Setting",
                            "Value"});
                table30.AddRow(new string[] {
                            "teenBuitenzijde",
                            "0"});
                table30.AddRow(new string[] {
                            "kruinBuitenzijde",
                            "61.12"});
#line 57
        testRunner.And("the following rekeninstellingen are adjusted:", ((string)(null)), table30, "And ");
#line hidden
#line 61
        testRunner.When(string.Format("I change the property positie to a value of {0}", positie), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 62
        testRunner.And("I run the Battjes-Groenendijk Wave Runup Calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 63
        testRunner.Then(string.Format("the output values for {0} and {1} are", schadegetal, cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 16 - Variable input of slope of the bottom")]
        [NUnit.Framework.TestCaseAttribute("0", "0.0001300542627438877", "0.9103798392072139", "0.918", "", null)]
        [NUnit.Framework.TestCaseAttribute("0.004", "0.00016098541128284046", "1.1268978789798831", "1.136", "1.134", null)]
        [NUnit.Framework.TestCaseAttribute("0.04", "0.0019034054017018846", "13.323837811913192", "13.425", "13.406", null)]
        [NUnit.Framework.TestCaseAttribute("0.1", "0.006982414063938715", "48.876898447571", "49.205", "", null)]
        [NUnit.Framework.TestCaseAttribute("0.4", "0.0068200858530393154", "47.74060097127521", "48.062", "", null)]
        [NUnit.Framework.TestCaseAttribute("10", "0.006820085853039203", "47.74060097127442", "48.062", "", null)]
        [NUnit.Framework.TestCaseAttribute("100", "0.006820085853039203", "47.74060097127442", "48.062", "", null)]
        [NUnit.Framework.TestCaseAttribute("250", "0.006820085853039203", "47.74060097127442", "48.062", "", null)]
        public virtual void BMGrasBenchmark16_VariableInputOfSlopeOfTheBottom(string tanAvl, string schadegetal, string cumulatieveOverbelastingTijdstap, string benchmarkForBMGras, string bMGras, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("tanAvl", tanAvl);
            argumentsOfScenario.Add("schadegetal", schadegetal);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            argumentsOfScenario.Add("Benchmark for BM Gras", benchmarkForBMGras);
            argumentsOfScenario.Add("BM Gras", bMGras);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 16 - Variable input of slope of the bottom", @"    Remark: the value of tanAvl should be between 0.004 and 0.05. In this testcase, no validation of results is performed by DiKErnel.
    This is why DiKErnel produces results for every situation. The validation of results is however performed by BM Gras.", tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 75
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
#line 11
    this.FeatureBackground();
#line hidden
                TechTalk.SpecFlow.Table table31 = new TechTalk.SpecFlow.Table(new string[] {
                            "posities",
                            "hoogten",
                            "ruwheidscoefficienten"});
                table31.AddRow(new string[] {
                            "0",
                            "-10.0",
                            "1.0"});
                table31.AddRow(new string[] {
                            "30.56",
                            "0.0",
                            "1.0"});
                table31.AddRow(new string[] {
                            "61.12",
                            "10.0",
                            ""});
#line 80
        testRunner.Given("the following series are adjusted:", ((string)(null)), table31, "Given ");
#line hidden
                TechTalk.SpecFlow.Table table32 = new TechTalk.SpecFlow.Table(new string[] {
                            "Setting",
                            "Value"});
                table32.AddRow(new string[] {
                            "positie",
                            "30.8656"});
                table32.AddRow(new string[] {
                            "teenBuitenzijde",
                            "0"});
                table32.AddRow(new string[] {
                            "kruinBuitenzijde",
                            "61.12"});
#line 85
        testRunner.And("the following rekeninstellingen are adjusted:", ((string)(null)), table32, "And ");
#line hidden
#line 90
        testRunner.When(string.Format("I change the property tanAvl to a value of {0}", tanAvl), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 91
        testRunner.And("I run the Battjes-Groenendijk Wave Runup Calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 92
        testRunner.Then(string.Format("the output values for {0} and {1} are", schadegetal, cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 17 - Variable input of water depth")]
        [NUnit.Framework.TestCaseAttribute("0", "NaN", "NaN", "0.000", "", null)]
        [NUnit.Framework.TestCaseAttribute("-0.004", "18.899172206217422", "132294.20544352196", "133115.947", "", null)]
        [NUnit.Framework.TestCaseAttribute("-0.04", "1.9530600918770284", "13671.4206431392", "13756.388", "13755.272", null)]
        [NUnit.Framework.TestCaseAttribute("-0.1", "0.8177090570008678", "5723.963399006075", "5729.582", "5759.070", null)]
        [NUnit.Framework.TestCaseAttribute("-0.4", "0.146449850472942", "1025.1489533105942", "1031.744", "1031.437", null)]
        [NUnit.Framework.TestCaseAttribute("-10", "0.0030480842313577797", "21.33658961950446", "21.469", "21.453", null)]
        [NUnit.Framework.TestCaseAttribute("-100", "0.002089438325616217", "14.626068279313518", "", "", null)]
        [NUnit.Framework.TestCaseAttribute("-250", "0.002034264488518857", "14.239851419631998", "", "", null)]
        public virtual void BMGrasBenchmark17_VariableInputOfWaterDepth(string bodemVoorlandZ, string schadegetal, string cumulatieveOverbelastingTijdstap, string benchmarkForBMGras, string bMGras, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("bodemVoorlandZ", bodemVoorlandZ);
            argumentsOfScenario.Add("schadegetal", schadegetal);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            argumentsOfScenario.Add("Benchmark for BM Gras", benchmarkForBMGras);
            argumentsOfScenario.Add("BM Gras", bMGras);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 17 - Variable input of water depth", @"    Remarks:
    - In BM Gras the value of water depth (water level - bodemVoorlandZ) must be > 0 and <= 10 m. This validation is not performed by DiKErnel.
    - When (water level - bodemVoorlandZ) equals to 0 m, then division by zero occurs. No results are produced then by DiKErnel (NaN).", tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 105
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
#line 11
    this.FeatureBackground();
#line hidden
                TechTalk.SpecFlow.Table table33 = new TechTalk.SpecFlow.Table(new string[] {
                            "posities",
                            "hoogten",
                            "ruwheidscoefficienten"});
                table33.AddRow(new string[] {
                            "0",
                            "-10.0",
                            "1.0"});
                table33.AddRow(new string[] {
                            "30.56",
                            "0.0",
                            "1.0"});
                table33.AddRow(new string[] {
                            "61.12",
                            "10.0",
                            ""});
#line 111
        testRunner.Given("the following series are adjusted:", ((string)(null)), table33, "Given ");
#line hidden
                TechTalk.SpecFlow.Table table34 = new TechTalk.SpecFlow.Table(new string[] {
                            "Setting",
                            "Value"});
                table34.AddRow(new string[] {
                            "positie",
                            "30.8656"});
                table34.AddRow(new string[] {
                            "teenBuitenzijde",
                            "0"});
                table34.AddRow(new string[] {
                            "kruinBuitenzijde",
                            "61.12"});
#line 116
        testRunner.And("the following rekeninstellingen are adjusted:", ((string)(null)), table34, "And ");
#line hidden
#line 121
        testRunner.When(string.Format("I change the property bodemVoorlandZ to a value of {0}", bodemVoorlandZ), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 122
        testRunner.And("I run the Battjes-Groenendijk Wave Runup Calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 123
        testRunner.Then(string.Format("the output values for {0} and {1} are", schadegetal, cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
            }
            this.ScenarioCleanup();
        }
        
        [NUnit.Framework.TestAttribute()]
        [NUnit.Framework.DescriptionAttribute("BM Gras benchmark 18 - Variable input of water depth and critical depth")]
        [NUnit.Framework.TestCaseAttribute("0", "1000", "NaN", "NaN", "0.000", "", null)]
        [NUnit.Framework.TestCaseAttribute("-0.004", "1000", "132.29420544352197", "132294.20544352196", "133115.947", "", null)]
        [NUnit.Framework.TestCaseAttribute("-0.04", "100", "136.714206431392", "13671.4206431392", "13756.388", "13755.272", null)]
        [NUnit.Framework.TestCaseAttribute("-0.1", "10", "572.3963399006075", "5723.963399006075", "5759.582", "5759.070", null)]
        [NUnit.Framework.TestCaseAttribute("-0.4", "1", "1025.1489533105942", "1025.1489533105942", "1031.744", "1031.437", null)]
        [NUnit.Framework.TestCaseAttribute("-10", "1", "21.33658961950446", "21.33658961950446", "21.469", "21.453", null)]
        [NUnit.Framework.TestCaseAttribute("-100", "1", "14.626068279313518", "14.626068279313518", "", "", null)]
        [NUnit.Framework.TestCaseAttribute("-250", "1", "14.239851419631998", "14.239851419631998", "", "", null)]
        public virtual void BMGrasBenchmark18_VariableInputOfWaterDepthAndCriticalDepth(string bodemVoorlandZ, string kritiekeCumulatieveOverbelasting, string schadegetal, string cumulatieveOverbelastingTijdstap, string benchmarkForBMGras, string bMGras, string[] exampleTags)
        {
            string[] tagsOfScenario = exampleTags;
            System.Collections.Specialized.OrderedDictionary argumentsOfScenario = new System.Collections.Specialized.OrderedDictionary();
            argumentsOfScenario.Add("bodemVoorlandZ", bodemVoorlandZ);
            argumentsOfScenario.Add("kritiekeCumulatieveOverbelasting", kritiekeCumulatieveOverbelasting);
            argumentsOfScenario.Add("schadegetal", schadegetal);
            argumentsOfScenario.Add("cumulatieveOverbelastingTijdstap", cumulatieveOverbelastingTijdstap);
            argumentsOfScenario.Add("Benchmark for BM Gras", benchmarkForBMGras);
            argumentsOfScenario.Add("BM Gras", bMGras);
            TechTalk.SpecFlow.ScenarioInfo scenarioInfo = new TechTalk.SpecFlow.ScenarioInfo("BM Gras benchmark 18 - Variable input of water depth and critical depth", @"    Remarks:
    - In BM Gras the value of water depth (water level - bodemVoorlandZ) must be > 0 and <= 10 m. This validation is not performed by DiKErnel.
    - When (water level - bodemVoorlandZ) equals to 0 m, then division by zero occurs. No results are produced then by DiKErnel (NaN).", tagsOfScenario, argumentsOfScenario, this._featureTags);
#line 136
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
#line 11
    this.FeatureBackground();
#line hidden
                TechTalk.SpecFlow.Table table35 = new TechTalk.SpecFlow.Table(new string[] {
                            "posities",
                            "hoogten",
                            "ruwheidscoefficienten"});
                table35.AddRow(new string[] {
                            "0",
                            "-10.0",
                            "1.0"});
                table35.AddRow(new string[] {
                            "30.56",
                            "0.0",
                            "1.0"});
                table35.AddRow(new string[] {
                            "61.12",
                            "10.0",
                            ""});
#line 142
        testRunner.Given("the following series are adjusted:", ((string)(null)), table35, "Given ");
#line hidden
                TechTalk.SpecFlow.Table table36 = new TechTalk.SpecFlow.Table(new string[] {
                            "Setting",
                            "Value"});
                table36.AddRow(new string[] {
                            "positie",
                            "30.8656"});
                table36.AddRow(new string[] {
                            "teenBuitenzijde",
                            "0"});
                table36.AddRow(new string[] {
                            "kruinBuitenzijde",
                            "61.12"});
#line 147
        testRunner.And("the following rekeninstellingen are adjusted:", ((string)(null)), table36, "And ");
#line hidden
#line 152
        testRunner.When(string.Format("I change the property bodemVoorlandZ to a value of {0}", bodemVoorlandZ), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "When ");
#line hidden
#line 153
        testRunner.And(string.Format("I change the property kritiekeCumulatieveOverbelasting to a value of {0}", kritiekeCumulatieveOverbelasting), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 154
        testRunner.And("I run the Battjes-Groenendijk Wave Runup Calculation", ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "And ");
#line hidden
#line 155
        testRunner.Then(string.Format("the output values for {0} and {1} are", schadegetal, cumulatieveOverbelastingTijdstap), ((string)(null)), ((TechTalk.SpecFlow.Table)(null)), "Then ");
#line hidden
            }
            this.ScenarioCleanup();
        }
    }
}
#pragma warning restore
#endregion
