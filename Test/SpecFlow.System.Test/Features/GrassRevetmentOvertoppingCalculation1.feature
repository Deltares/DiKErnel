Feature: GrassRevetmentOvertoppingCalculation1


Background:
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 3600    | 5.5        | 1.9           | 4.7            | -10       |
		| 3600      | 7200    | 5.6        | 1.95          | 4.73           | -8        |
		| 7200      | 10800   | 5.7        | 2             | 4.76           | -6        |
		| 10800     | 14400   | 5.8        | 2.05          | 4.79           | -4        |
		| 14400     | 18000   | 5.9        | 2.1           | 4.82           | -2        |
		| 18000     | 21600   | 6          | 2.15          | 4.85           | 0         |
		| 21600     | 25200   | 6.1        | 2.2           | 4.88           | 2         |
		| 25200     | 28800   | 6.2        | 2.25          | 4.91           | 4         |
		| 28800     | 32400   | 6.2        | 2.3           | 4.94           | 6         |
		| 32400     | 36000   | 6.1        | 2.35          | 4.97           | 8         |
		| 36000     | 39600   | 6          | 2.4           | 5              | 10        |
		| 39600     | 43200   | 5.9        | 2.45          | 5.03           | 12        |
		| 43200     | 46800   | 5.8        | 2.5           | 5.06           | 14        |
		| 46800     | 50400   | 5.7        | 2.55          | 5.09           | 16        |
		| 50400     | 54000   | 5.6        | 2.6           | 5.12           | 18        |
		| 54000     | 57600   | 5.5        | 2.65          | 5.15           | 20        |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ | roughnessCoefficient |
		| 0           | -0.1        | 5         | 0         | 1                    |
		| 5           | 0           | 15        | 3         | 1                    |
		| 15          | 3           | 22        | 3.2       | 0.75                 |
		| 22          | 3.2         | 30        | 7.5       | 0.5                  |
		| 30          | 7.5         | 31        | 7.6       | 0.8                  |
		| 31          | 7.6         | 34        | 7.7       | 0.8                  |
		| 34          | 7.7         | 35        | 7.4       | 0.8                  |
		| 35          | 7.4         | 45        | 5         | 0.8                  |
		| 45          | 5           | 60        | 0.5       | 0.8                  |
		| 60          | 0.5         | 70        | 0.5       | 0.8                  |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 5  | OuterToe                |
		| 15 | CrestOuterBerm          |
		| 22 | NotchOuterBerm          |
		| 30 | OuterCrest              |
		| 35 | InnerCrest              |
		| 60 | InnerToe                |

Scenario: GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType | InitialDamage |
		| 50 | ClosedSod                  | 0.2           |
	#And the location constructionwith has the initial damage of 0.2
	When I add the grass overtopping location
	And I run the calculation
		
Scenario: GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType | InitialDamage |
		| 33 | ClosedSod                  | 0.02          |
	#And the location constructionwith has the initial damage of 0.02
	When I add the grass overtopping location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType | InitialDamage | DikeHeight |
		| 33 | ClosedSod                  | 0.02          | 8          |
	#And the location constructionwith has the initial damage of 0.02
	#And the location constructionwith has the dike hight of 8
	When I add the grass overtopping location
	And I run the calculation
Scenario: GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction:
		| X  | GrassRevetmentTopLayerType | InitialDamage | DikeHeight |
		| 33 | ClosedSod                  | 0.02          | 5.65       |
	#And the location constructionwith has the initial damage of 0.02
	#And the location constructionwith has the dike hight of 5.65
	When I add the grass overtopping location