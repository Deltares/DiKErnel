Feature: GrassRevetmentWaveImpactCalculation2

Scenario: GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 900     | 0.5        | 0.3           | 3              | 0         |
		| 900       | 1800    | 0.55       | 0.4           | 3              | 15        |
		| 1800      | 2700    | 0.6        | 0.45          | 3              | 30        |
		| 2700      | 3600    | 0.65       | 0.5           | 3              | 45        |
		| 3600      | 4500    | 0.7        | 0.55          | 3              | 60        |
		| 4500      | 5400    | 0.75       | 0.6           | 3              | 70        |
		| 5400      | 6300    | 0.8        | 0.65          | 3              | 75        |
		| 6300      | 7200    | 0.85       | 0.7           | 3              | 70        |
		| 7200      | 8100    | 0.9        | 0.75          | 3              | 60        |
		| 8100      | 9000    | 0.95       | 0.8           | 3              | 45        |
		| 9000      | 9900    | 1          | 0.9           | 3              | 30        |
		| 9900      | 10800   | 1.03       | 0.9           | 3              | 15        |
		| 10800     | 11700   | 1.03       | 0.95          | 3              | 0         |
		| 11700     | 12600   | 1          | 1             | 3              | 0         |
		| 12600     | 13500   | 0.95       | 1.03          | 3              | 0         |
		| 13500     | 14400   | 0.9        | 1             | 3              | 0         |
		| 14400     | 15300   | 0.85       | 0.95          | 3              | 0         |
		| 15300     | 16200   | 0.8        | 0.9           | 3              | 0         |
		| 16200     | 17100   | 0.75       | 0.8           | 3              | 0         |
		| 17100     | 18000   | 0.7        | 0.8           | 3              | 0         |
		| 18000     | 18900   | 0.65       | 0.75          | 3              | 0         |
		| 18900     | 19800   | 0.6        | 0.75          | 3              | 0         |
		| 19800     | 20700   | 0.55       | 0.7           | 3              | 0         |
		| 20700     | 21600   | 0.5        | 0.7           | 3              | 0         |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 5           | -1          | 55        | 11.5      |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 5  | OuterToe                |
		| 55 | OuterCrest              |
	And the following location construction:
		| X  | GrassRevetmentTopLayerType |
		| 11 | ClosedSod                  |
	When I add the grass wave impact location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| -3600     | -3510   | 0.5        | 0.5           | 3              | 0         |
		| -3510     | -3330   | 0.55       | 0.6           | 3              | 15        |
		| - 3330    | -3060   | 0.6        | 0.65          | 3              | 30        |
		| - 3060    | -2700   | 0.65       | 0.7           | 3              | 45        |
		| - 2700    | -2250   | 0.7        | 0.75          | 3              | 60        |
		| - 2250    | -1710   | 0.75       | 0.8           | 3              | 70        |
		| - 1710    | -1080   | 0.8        | 0.85          | 3              | 75        |
		| - 1080    | -360    | 0.85       | 0.9           | 3              | 70        |
		| - 360     | 450     | 0.9        | 0.95          | 3              | 60        |
		| 450       | 1350    | 0.95       | 1             | 3              | 45        |
		| 1350      | 2340    | 1          | 1.1           | 3              | 30        |
		| 2340      | 3420    | 1.03       | 1.1           | 3              | 15        |
		| 3420      | 4590    | 1.03       | 1.15          | 3              | 0         |
		| 4590      | 5850    | 1          | 1.2           | 3              | 0         |
		| 5850      | 7200    | 0.95       | 1.23          | 3              | 0         |
		| 7200      | 8640    | 0.9        | 1.2           | 3              | 0         |
		| 8640      | 10170   | 0.85       | 1.15          | 3              | 0         |
		| 10170     | 11790   | 0.8        | 1.1           | 3              | 0         |
		| 11790     | 13500   | 0.75       | 1             | 3              | 0         |
		| 13500     | 15300   | 0.7        | 1             | 3              | 0         |
		| 15300     | 17190   | 0.65       | 0.95          | 3              | 0         |
		| 17190     | 19170   | 0.6        | 0.95          | 3              | 0         |
		| 19170     | 21240   | 0.55       | 0.9           | 3              | 0         |
		| 21240     | 21600   | 0.5        | 0.9           | 3              | 0         |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 5           | -1          | 55        | 11.5      |
	And the following dike profile point data:d
		| X  | CharacteristicPointType |
		| 5  | OuterToe                |
		| 55 | OuterCrest              |
	And the following location construction:
		| X  | GrassRevetmentTopLayerType |
		| 11 | ClosedSod                  |
	When I add the grass wave impact location
	And I run the calculation
