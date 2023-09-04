Feature: TestAsphaltRevetmentWaveImpactCalculation2


Scenario: GivenCalculationInputForSchematization2Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| -3600     | -2880   | 2          | 1             | 4              | 0         |
		| -2880     | -1440   | 2.2        | 1.5           | 5              | 0         |
		| -1440     | 720     | 2.4        | 2             | 5.5            | 0         |
		| 720       | 3600    | 2.6        | 2.4           | 6              | 0         |
		| 3600      | 7200    | 2.8        | 2.5           | 6.2            | 0         |
		| 7200      | 11520   | 3          | 2.6           | 6.3            | 0         |
		| 11520     | 16560   | 2.8        | 2.7           | 6.5            | 0         |
		| 16560     | 22320   | 2.6        | 2.6           | 6.6            | 0         |
		| 22320     | 28800   | 2.4        | 2.5           | 6.3            | 0         |
		| 28800     | 36000   | 2          | 2.4           | 6.2            | 0         |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 0           | 0           | 30        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 30 | OuterCrest              |
	And the following location construction properties:
		| X  | AsphaltRevetmentTopLayerType | FailureTension | SoilElasticity | ThicknessUpperLayer | ElasticModulusUpperLayer |
		| 10 | HydraulicAsphaltConcrete     | 1.6            | 55             | 0.4                 | 18000                    |
	When I add the asphalt wave impact location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization3Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 3600    | 2          | 1             | 4              | 0         |
		| 3600      | 7200    | 2.2        | 1.5           | 5              | 0         |
		| 7200      | 10800   | 2.4        | 2             | 5.5            | 0         |
		| 10800     | 14400   | 2.6        | 2.4           | 6              | 0         |
		| 14400     | 18000   | 2.8        | 2.5           | 6.2            | 0         |
		| 18000     | 21600   | 3          | 2.6           | 6.3            | 0         |
		| 21600     | 25200   | 2.8        | 2.7           | 6.5            | 0         |
		| 25200     | 28800   | 2.6        | 2.6           | 6.6            | 0         |
		| 28800     | 32400   | 2.4        | 2.5           | 6.3            | 0         |
		| 32400     | 36000   | 2          | 2.4           | 6.2            | 0         |
	And the follwoing Dike profile segments:
		| StartPointX | StartPointZ | EndPointX | EndPointZ |
		| 0           | 0           | 8         | 2         |
		| 8           | 2           | 17        | 3         |
		| 17          | 3           | 35        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 8  | CrestOuterBerm          |
		| 17 | NotchOuterBerm          |
		| 35 | OuterCrest              |
	And the following location construction properties:
		| X    | AsphaltRevetmentTopLayerType | FailureTension | SoilElasticity | ThicknessUpperLayer | ElasticModulusUpperLayer |
		| 12.5 | HydraulicAsphaltConcrete     | 1.6            | 55             | 0.4                 | 16000                    |
	When I add the asphalt wave impact location
	And I run the calculation
