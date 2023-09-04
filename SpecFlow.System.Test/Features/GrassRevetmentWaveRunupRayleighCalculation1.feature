Feature: GrassRevetmentWaveImpactCalculation1


Background:
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 3600    | 0          | 0.5           | 3              | 50        |
		| 3600      | 7200    | 0.1        | 0.7           | 3.5            | 45        |
		| 7200      | 10800   | 0.2        | 1             | 4              | 40        |
		| 10800     | 14400   | 0.3        | 1.3           | 4.3            | 35        |
		| 14400     | 18000   | 0.4        | 1.5           | 4.5            | 30        |
		| 18000     | 21600   | 0.5        | 1.8           | 4.8            | 25        |
		| 21600     | 25200   | 0.6        | 2.1           | 5.2            | 20        |
		| 25200     | 28800   | 0.7        | 2.5           | 5.5            | 15        |
		| 28800     | 32400   | 0.7        | 2.8           | 5.8            | 10        |
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

Scenario: GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType |
		| 3 | 0.3        | ClosedSod                  |
	When I add the grass wave runup rayleigh location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType | CriticalCumulativeOverload | CriticalFrontVelocity |
		| 3 | 0.3        | ClosedSod                  | 8000                       | 6.2                   |
	When I add the grass wave runup rayleigh location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType | FixedNumberOfWaves | FrontVelocityCu |
		| 3 | 0.3        | ClosedSod                  | 500                | 1.15            |
	When I add the grass wave runup rayleigh location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType | RepresentativeWaveRunup2PAru | RepresentativeWaveRunup2PBru | RepresentativeWaveRunup2PCru |
		| 3 | 0.3        | ClosedSod                  | 1.75                         | 4.3                          | 1,6                          |
	When I add the grass wave runup rayleigh location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase5_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType | RepresentativeWaveRunup2PGammab | RepresentativeWaveRunup2PGammaf |
		| 3 | 0.3        | OpenSod                    | 0.7                             | 0.7                             |
	When I add the grass wave runup rayleigh location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase6_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType | WaveAngleImpactAbeta | WaveAngleImpactBetamax | AverageNumberOfWavesCtm |
		| 3 | 0.3        | ClosedSod                  | 0.0033               | 30                     | 1                       |
	When I add the grass wave runup rayleigh location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase7_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following grass revetment wave runup location construction properties:
		| X | outerSlope | GrassRevetmentTopLayerType | InitialDamage | FailureNumber |
		| 3 | 0.3        | ClosedSod                  | 0.3           | 1.1           |
	When I add the grass wave runup rayleigh location
	And I run the calculation