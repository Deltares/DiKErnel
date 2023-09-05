Feature: GrassRevetmentWaveRunupRayleighCalculation2


Scenario: GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 3600    | 0          | 0.3           | 3              | 50        |
		| 3600      | 7200    | 0.1        | 0.4           | 3.5            | 45        |
		| 7200      | 10800   | 0.2        | 0.5           | 3.9            | 40        |
		| 10800     | 14400   | 0.3        | 0.6           | 4.2            | 35        |
		| 14400     | 18000   | 0.4        | 0.7           | 4.6            | 30        |
		| 18000     | 21600   | 0.5        | 0.8           | 4.9            | 25        |
		| 21600     | 25200   | 0.6        | 0.9           | 5.2            | 20        |
		| 25200     | 28800   | 0.7        | 1             | 5.5            | 15        |
		| 28800     | 32400   | 0.7        | 1.1           | 5.7            | 10        |
		| 32400     | 36000   | 0.6        | 1.1           | 5.7            | 5         |
		| 36000     | 39600   | 0.5        | 1             | 5.5            | 0         |
		| 39600     | 43200   | 0.4        | 0.9           | 5.2            | 0         |
		| 43200     | 46800   | 0.3        | 0.8           | 4.9            | 5         |
		| 46800     | 50400   | 0.2        | 0.7           | 4.6            | 10        |
		| 50400     | 54000   | 0.1        | 0.6           | 4.2            | 15        |
		| 54000     | 57600   | 0          | 0.5           | 3.9            | 20        |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 0           | 0           | 25        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 25 | OuterCrest              |
	Given the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType |
		| 3 | 0.3        | OpenSod                    |
	When I add the grass wave runup rayleigh location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization2Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 3600    | 0          | 0.3           | 3              | 50        |
		| 3600      | 7200    | 0.1        | 0.4           | 3.5            | 45        |
		| 7200      | 10800   | 0.2        | 0.5           | 3.9            | 40        |
		| 10800     | 14400   | 0.3        | 0.6           | 4.2            | 35        |
		| 14400     | 18000   | 0.4        | 0.7           | 4.6            | 30        |
		| 18000     | 21600   | 0.5        | 0.8           | 4.9            | 25        |
		| 21600     | 25200   | 0.6        | 0.9           | 5.2            | 20        |
		| 25200     | 28800   | 0.7        | 1             | 5.5            | 15        |
		| 28800     | 32400   | 0.7        | 1.1           | 5.7            | 10        |
		| 32400     | 36000   | 0.6        | 1.1           | 5.7            | 5         |
		| 36000     | 39600   | 0.5        | 1             | 5.5            | 0         |
		| 39600     | 43200   | 0.4        | 0.9           | 5.2            | 0         |
		| 43200     | 46800   | 0.3        | 0.8           | 4.9            | 5         |
		| 46800     | 50400   | 0.2        | 0.7           | 4.6            | 10        |
		| 50400     | 54000   | 0.1        | 0.6           | 4.2            | 15        |
		| 54000     | 57600   | 0          | 0.5           | 3.9            | 20        |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 0           | 0           | 25        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 25 | OuterCrest              |
	And the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType | IncreasedLoadTransitionAlphaM | ReducedStrengthTransitionAlphaS |
		| 3 | 0.3        | ClosedSod                  | 1.8                           | 0.9                             |
	When I add the grass wave runup rayleigh location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 3600    | 0.5        | 2.4           | 4              | 20        |
		| 3600      | 7200    | 0.6        | 2.5           | 4.2            | 20        |
		| 7200      | 10800   | 0.7        | 2.7           | 4.4            | 20        |
		| 10800     | 14400   | 0.8        | 2.8           | 4.5            | 20        |
		| 14400     | 18000   | 0.9        | 2.9           | 4.8            | 20        |
		| 18000     | 21600   | 0.95       | 3             | 5              | 20        |
		| 21600     | 25200   | 1          | 2.9           | 5.2            | 20        |
		| 25200     | 28800   | 0.95       | 2.9           | 5.5            | 15        |
		| 28800     | 32400   | 0.8        | 2.8           | 5.8            | 10        |
		| 32400     | 36000   | 0.6        | 2.8           | 6              | 5         |
		| 36000     | 39600   | 0.5        | 2.5           | 6              | 0         |
		| 39600     | 43200   | 0.4        | 2.1           | 5.8            | 0         |
		| 43200     | 46800   | 0.3        | 1.8           | 5.5            | 5         |
		| 46800     | 50400   | 0.2        | 1.5           | 5.2            | 10        |
		| 50400     | 54000   | 0.1        | 1.3           | 4.8            | 15        |
		| 54000     | 57600   | 0          | 1             | 4.5            | 20        |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 0           | 0           | 25        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 25 | OuterCrest              |
	And the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType |
		| 3 | 0.3        | ClosedSod                  |
	When I add the grass wave runup rayleigh location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization4Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| -7200     | -6840   | 0          | 0.5           | 3              | 50        |
		| -6840     | -6120   | 0.1        | 0.7           | 3.5            | 45        |
		| -6120     | -5040   | 0.2        | 1             | 4              | 40        |
		| -5040     | -3600   | 0.3        | 1.3           | 4.3            | 35        |
		| -3600     | -1800   | 0.4        | 1.5           | 4.5            | 30        |
		| -1800     | 360     | 0.5        | 1.8           | 4.8            | 25        |
		| 360       | 2880    | 0.6        | 2.1           | 5.2            | 20        |
		| 2880      | 5760    | 0.7        | 2.5           | 5.5            | 15        |
		| 5760      | 9000    | 0.7        | 2.8           | 5.8            | 10        |
		| 9000      | 12600   | 0.6        | 2.8           | 6              | 5         |
		| 12600     | 16560   | 0.5        | 2.5           | 6              | 0         |
		| 16560     | 20880   | 0.4        | 2.1           | 5.8            | 0         |
		| 20880     | 25560   | 0.3        | 1.8           | 5.5            | 5         |
		| 25560     | 30600   | 0.2        | 1.5           | 5.2            | 10        |
		| 30600     | 36000   | 0.1        | 1.3           | 4.8            | 15        |
		| 36000     | 43200   | 0          | 1             | 4.5            | 20        |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 0           | 0           | 25        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 25 | OuterCrest              |
	And the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType |
		| 3 | 0.3        | ClosedSod                  |
	When I add the grass wave runup rayleigh location
	And I run the calculation