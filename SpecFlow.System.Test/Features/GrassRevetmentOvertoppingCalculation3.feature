Feature: GrassRevetmentOvertoppingCalculation3


Background:
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 3600    | 5.7        | 2.05          | 5.2            | -10       |
		| 3600      | 7200    | 6.2        | 2.1           | 5.23           | -8        |
		| 7200      | 10800   | 6.8        | 2.15          | 5.26           | -6        |
		| 10800     | 14400   | 6.8        | 2.2           | 5.29           | -4        |
		| 14400     | 21600   | 6.8        | 2.25          | 5.32           | -2        |
		| 21600     | 32400   | 6.7        | 2.3           | 5.35           | 0         |
		| 32400     | 46800   | 6.6        | 2.35          | 5.38           | 2         |
		| 46800     | 50400   | 6.4        | 2.4           | 5.41           | 4         |
		| 50400     | 54000   | 6.2        | 2.45          | 5.44           | 6         |
		| 54000     | 57600   | 6.1        | 2.5           | 5.47           | 8         |
		| 57600     | 75600   | 6          | 2.55          | 5.5            | 10        |
		| 75600     | 79200   | 5.7        | 2.6           | 5.53           | 12        |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ | roughnessCoefficient |
		| -5          | -4          | -1.73     | -2.89     | 1                    |
		| -1.73       | -2.89       | 33.82     | 6.03      | 1                    |
		| 33.82       | 6.03        | 38.16     | 6.31      | 0.9                  |
		| 38.16       | 6.31        | 47.34     | 8.64      | 0.8                  |
		| 47.34       | 8.64        | 52        | 8.7       | 1                    |
		| 52          | 8.7         | 70        | 5         | 1                    |
		| 70          | 5           | 85        | 1         | 1                    |
		| 85          | 1           | 95        | 0         | 1                    |
	And the following dike profile point data:
		| X     | CharacteristicPointType |
		| -1.73 | OuterToe                |
		| 33.82 | CrestOuterBerm          |
		| 38.16 | NotchOuterBerm          |
		| 47.34 | OuterCrest              |
		| 52    | InnerCrest              |
		| 85    | InnerToe                |

Scenario: GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType |
		| 60 | OpenSod                    |
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization3Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType | DikeHeight |
		| 50 | OpenSod                    | 6.7        |
	#And the location constructionwith has the dike hight of 6.7
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization3Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType | InitialDamage | FixedNumberOfWaves | DikeHeight |
		| 35 | OpenSod                    | 0.9           | 15000              | 9          |
			#Given the following location construction properties:
			#| initialDamage |
	#And the location constructionwith has the initial damage of 0.9
	#And the location constructionwith has fixed number of waves 15000
	#And the location constructionwith has the dike hight of 9
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization3Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType |
		| 35 | OpenSod                    |

	And the following location construction properties:
		| CriticalCumulativeOverload | CriticalFrontVelocity | IncreasedLoadTransitionAlphaM | ReducedStrengthTransitionAlphaS | AverageNumberOfWavesCtm | FixedNumberOfWaves | FrontVelocityCwo | AccelerationAlphaAForCrest | AccelerationAlphaAForInnerSlope |
		| 7500                       | 5.5                   | 1.25                          | 1.33                            | 0.85                    | 15000              | 1.6              | 1.1                        | 1.5                             |
	When I add the grass overtopping location
	And I run the calculation