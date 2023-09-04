Feature: NaturalStoneRevetmentCalculation3

Scenario: GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
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
		| 0           | 0           | 6.4       | 1.6       |
		| 6.4         | 1.6         | 12.4      | 1.8       |
		| 12.4        | 1.8         | 30        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 30 | OuterCrest              |
	And the following grass natural stone revetment location construction properties:
		| X | NaturalStoneRevetmentTopLayerType | ThicknessTopLayer | RelativeDensity |
		| 6 | NordicStone                       | 0.3               | 1.65            |
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization4Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 900     | 1.27       | 1.5           | 6              | 0         |
		| 900       | 1800    | 1.271      | 1.5           | 6              | 0         |
		| 1800      | 2700    | 1.272      | 1.5           | 6              | 0         |
		| 2700      | 3600    | 1.273      | 1.5           | 6              | 0         |
		| 3600      | 4500    | 2.531      | 1.5           | 6              | 0         |
		| 4500      | 5400    | 2.532      | 1.5           | 6              | 0         |
		| 5400      | 6300    | 2.533      | 1.5           | 6              | 0         |
		| 6300      | 7200    | 2.534      | 1.5           | 6              | 0         |
		| 7200      | 8100    | 2.535      | 1.5           | 6              | 0         |
		| 8100      | 9000    | 2.536      | 1.5           | 6              | 0         |
		| 9000      | 9900    | 2.537      | 1.5           | 6              | 0         |
		| 9900      | 10800   | 2.538      | 1.5           | 6              | 0         |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 0           | 0           | 30        | 7.5       |

	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 30 | OuterCrest              |
	And the following grass natural stone revetment location construction properties:
		| X | NaturalStoneRevetmentTopLayerType | ThicknessTopLayer | RelativeDensity | UpperLimitLoadingAul | UpperLimitLoadingBul | UpperLimitLoadingCul | LowerLimitLoadingAll | LowerLimitLoadingBll | LowerLimitLoadingCll | DistanceMaximumWaveElevationAsmax | DistanceMaximumWaveElevationBsmax | NormativeWidthOfWaveImpactAwi | NormativeWidthOfWaveImpactBwi |
		| 6 | NordicStone                       | 0.3               | 1.65            | 0.08                 | 0.7                  | 3.5                  | 0.08                 | 0.15                 | 5.5                  | 0.5                               | 0.8                               | 1.1                           | 0.15                          |
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization5Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| -3600     | -3420   | 1.4        | 1             | 5.5            | 30        |
		| -3420     | -3060   | 1.6        | 1.2           | 6              | 60        |
		| -3060     | -2520   | 1.7        | 1.2           | 6.5            | 90        |
		| -2520     | -1800   | 1.8        | 1.3           | 7              | 75        |
		| -1800     | -900    | 2          | 1.4           | 7              | 60        |
		| -900      | 180     | 2.1        | 1.3           | 7.5            | 45        |
		| 180       | 1440    | 2.1        | 1.6           | 8              | 30        |
		| 1440      | 2880    | 2.4        | 1.7           | 8              | 15        |
		| 2880      | 4500    | 2          | 2.4           | 8.5            | 0         |
		| 4500      | 6300    | 1.9        | 2.2           | 8              | 0         |
		| 6300      | 8280    | 1.6        | 1.8           | 7              | 0         |
		| 8280      | 10800   | 1.4        | 1.2           | 6              | 0         |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 0           | 0           | 30        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 30 | OuterCrest              |
	And the following grass natural stone revetment location construction properties:
		| X | NaturalStoneRevetmentTopLayerType | ThicknessTopLayer | RelativeDensity |
		| 6 | NordicStone                       | 0.4               | 1.65            |
	When I add the grass overtopping location
	And I run the calculation