Feature: GrassRevetmentOvertoppingCalculation2



Background:
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 3600    | 5          | 2.35          | 5.2            | -10       |
		| 3600      | 7200    | 5.1        | 2.4           | 5.23           | -8        |
		| 7200      | 10800   | 5.2        | 2.45          | 5.26           | -6        |
		| 10800     | 14400   | 5.3        | 2.5           | 5.29           | -4        |
		| 14400     | 18000   | 5.4        | 2.55          | 5.32           | -2        |
		| 18000     | 21600   | 5.5        | 2.6           | 5.35           | 0         |
		| 21600     | 25200   | 5.6        | 2.65          | 5.38           | 2         |
		| 25200     | 28800   | 5.7        | 2.7           | 5.41           | 4         |
		| 28800     | 32400   | 5.7        | 2.75          | 5.44           | 6         |
		| 32400     | 36000   | 5.6        | 2.8           | 5.47           | 8         |
		| 36000     | 39600   | 5.5        | 2.85          | 5.5            | 10        |
		| 39600     | 43200   | 5.4        | 2.9           | 5.53           | 12        |
		| 43200     | 46800   | 5.3        | 2.95          | 5.56           | 14        |
		| 46800     | 50400   | 5.2        | 3             | 5.59           | 16        |
		| 50400     | 54000   | 5.1        | 3.05          | 5.62           | 18        |
		| 54000     | 57600   | 5          | 3.1           | 5.65           | 20        |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ | roughnessCoefficient |
		| 0           | -0.1        | 5         | 0         | 1                    |
		| 5           | 0           | 30        | 7.5       | 1                    |
		| 30          | 7.5         | 31        | 7.6       | 0.8                  |
		| 31          | 7.6         | 34        | 7.7       | 0.8                  |
		| 34          | 7.7         | 35        | 7.4       | 0.8                  |
		| 35          | 7.4         | 45        | 5         | 0.8                  |
		| 45          | 5           | 60        | 0.5       | 0.8                  |
		| 60          | 0.5         | 70        | 0.5       | 0.8                  |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 5  | OuterToe                |
		| 30 | OuterCrest              |
		| 35 | InnerCrest              |
		| 60 | InnerToe                |

Scenario: GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType |
		| 40 | OpenSod                    |
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType | DikeHeight |
		| 30 | OpenSod                    | 9.5        |
	#And the location constructionwith has the dike hight of 9.5
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization2Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType | DikeHeight | IncreasedLoadTransitionAlphaM |
		| 35 | OpenSod                    | 9.56       | 1.2                           |
		#And the Load Transition AlphaM increased with 1.2 points
		#And the location constructionwith has the dike hight of 9.6
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization2Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType | IncreasedLoadTransitionAlphaM | ReducedStrengthTransitionAlphaS | FixedNumberOfWaves | DikeHeight |
		| 35 | OpenSod                    | 1.2                           | 1.3                             | 5000               | 9.7        |
	#And the Load Transition AlphaM increased with 1.2 points
	#And the Load Transition AlphaS increased with 1.3 points
	#And the location constructionwith has fixed number of waves 5000
	#And the location constructionwith has the dike hight of 9.7
	When I add the grass overtopping location
	And I run the calculation