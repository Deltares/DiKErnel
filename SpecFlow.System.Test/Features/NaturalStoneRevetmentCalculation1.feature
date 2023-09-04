Feature: GrassRevetmentWaveRunupRayleighCalculation1

Background:
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 900     | 1.4        | 1             | 5.5            | 30        |
		| 900       | 1800    | 1.6        | 1.2           | 6              | 60        |
		| 1800      | 2700    | 1.7        | 1.2           | 6.5            | 90        |
		| 2700      | 3600    | 1.8        | 1.3           | 7              | 75        |
		| 3600      | 4500    | 2          | 1.4           | 7              | 60        |
		| 4500      | 5400    | 2.1        | 1.3           | 7.5            | 45        |
		| 5400      | 6300    | 2.1        | 1.6           | 8              | 30        |
		| 6300      | 7200    | 2.4        | 1.7           | 8              | 15        |
		| 7200      | 8100    | 2          | 2.4           | 8.5            | 0         |
		| 8100      | 9000    | 1.9        | 2.2           | 8              | 0         |
		| 9000      | 9900    | 1.6        | 1.8           | 7              | 0         |
		| 9900      | 10800   | 1.4        | 1.2           | 6              | 0         |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 0           | 0           | 30        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 30 | OuterCrest              |

Scenario: GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass natural stone revetment location construction properties:
		| X | NaturalStoneRevetmentTopLayerType | ThicknessTopLayer | RelativeDensity |
		| 6 | NordicStone                       | 0.4               | 1.65            |
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass natural stone revetment location construction properties:
		| X | NaturalStoneRevetmentTopLayerType | ThicknessTopLayer | RelativeDensity | InitialDamage |
		| 6 | NordicStone                       | 0.35              | 1.6             | 0.6           |
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass natural stone revetment location construction properties:
		| X | NaturalStoneRevetmentTopLayerType | ThicknessTopLayer | RelativeDensity | HydraulicLoadXib | HydraulicLoadAp | HydraulicLoadBp | HydraulicLoadCp | HydraulicLoadNp | HydraulicLoadAs | HydraulicLoadBs | HydraulicLoadCs | HydraulicLoadNs |
		| 6 | NordicStone                       | 0.25              | 1.65            | 2.1              | 6.68            | 0               | 0               | -0.723          | 12              | 1.5             | -3.12           | -1.5            |
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass natural stone revetment location construction properties:
		| X | NaturalStoneRevetmentTopLayerType | ThicknessTopLayer | RelativeDensity | WaveAngleImpactBetamax |
		| 6 | NordicStone                       | 0.4               | 1.65            | 30                     |
	When I add the grass overtopping location
	And I run the calculation