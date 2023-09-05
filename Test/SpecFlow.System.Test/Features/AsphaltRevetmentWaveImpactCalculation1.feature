Feature: TestAsphaltRevetmentWaveImpactCalculation1


Background:
	Given the following schematisation for time steps:
		| BeginTime | EndTime | WaterLevel | WaveHeightHm0 | WavePeriodTm10 | WaveAngle |
		| 0         | 3600    | 2          | 1             | 4              | 0         |
		| 3600      | 7200    | 2.2        | 1.5           | 5              | 8         |
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
		| 0           | 0           | 30        | 7.5       |
	And the following dike profile point data:
		| X  | CharacteristicPointType |
		| 0  | OuterToe                |
		| 30 | OuterCrest              |


Scenario: GivenCalculationInputForSchematization1Testcase1_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction properties:
		| X  | AsphaltRevetmentTopLayerType | FailureTension | SoilElasticity | ThicknessUpperLayer | ElasticModulusUpperLayer |
		| 10 | HydraulicAsphaltConcrete     | 1.6            | 55             | 0.4                 | 18000                    |
	When I add the asphalt wave impact location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase2_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction properties:
		| X  | AsphaltRevetmentTopLayerType | FailureTension | SoilElasticity | ThicknessUpperLayer | ElasticModulusUpperLayer |
		| 10 | HydraulicAsphaltConcrete     | 1.75           | 60             | 0.3                 | 16000                    |
	And the location constructionwith has the initial damage of 0.4
	When I add the asphalt wave impact location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase3_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction properties:
		| X  | AsphaltRevetmentTopLayerType | FailureTension | SoilElasticity | ThicknessUpperLayer | ElasticModulusUpperLayer | ThicknessSubLayer | ElasticModulusSubLayer |
		| 10 | HydraulicAsphaltConcrete     | 1.6            | 55             | 0.15                | 18000                    | 0.18              | 15000                  |
	#And location construction has the thickness subLaye of 0.18
	#And location construction has the elastic modulus subLayer of 15000
	When I add the asphalt wave impact location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase4_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction properties:
		| X  | AsphaltRevetmentTopLayerType | FailureTension | SoilElasticity | ThicknessUpperLayer | ElasticModulusUpperLayer |
		| 10 | HydraulicAsphaltConcrete     | 1.6            | 55             | 0.3                 | 18000                    |
	And location construction has the following impact factors:
	                | Key | Value |
	                | 0.4 | 0.349 |
	                | 0.8 | 0.123 |
	                | 1.2 | 0.152 |
	                | 1.6 | 0.125 |
	                | 2.0 | 0.088 |
	                | 2.4 | 0.059 |
	                | 2.8 | 0.038 |
	                | 3.2 | 0.024 |
	                | 3.6 | 0.016 |
	                | 4.0 | 0.01  |
	                | 4.4 | 0.007 |
	                | 4.8 | 0.004 |
	                | 5.2 | 0.003 |
	                | 5.6 | 0.002 |
	                | 6.0 | 0.001 |
	When I add the asphalt wave impact location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase5_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction properties:
		| X  | AsphaltRevetmentTopLayerType | FailureTension | SoilElasticity | ThicknessUpperLayer | ElasticModulusUpperLayer |
		| 10 | HydraulicAsphaltConcrete     | 1.6            | 55             | 0.38                | 18000                    |
	And location construction has the following impact factors:
		| Key   | Value      |
		| 0.99  | 0.00009647 |
		| -0.9  | 0.0007544  |
		| -0.81 | 0.004299   |
		| -0.72 | 0.01785    |
		| -0.63 | 0.05403    |
		| -0.54 | 0.1192     |
		| -0.45 | 0.1916     |
		| -0.36 | 0.2244     |
		| -0.27 | 0.1916     |
		| -0.18 | 0.1192     |
		| -0.09 | 0.05403    |
		| 0.0   | 0.01785    |
		| 0.09  | 0.004299   |
		| 0.18  | 0.0007544  |
		| 0.27  | 0.00009647 |
	When I add the asphalt wave impact location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase6_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction properties:
		| X  | AsphaltRevetmentTopLayerType | FailureTension | SoilElasticity | ThicknessUpperLayer | ElasticModulusUpperLayer |
		| 10 | HydraulicAsphaltConcrete     | 1.6            | 55             | 0.45                | 18000                    |
	And location construction has the following impact factors:
		| Key  | Value |
		| 0.1  | 0.0   |
		| 0.25 | 0.018 |
		| 0.4  | 0.09  |
		| 0.55 | 0.153 |
		| 0.7  | 0.168 |
		| 0.85 | 0.15  |
		| 1.0  | 0.119 |
		| 1.15 | 0.089 |
		| 1.3  | 0.064 |
		| 1.45 | 0.045 |
		| 1.6  | 0.031 |
		| 1.75 | 0.022 |
		| 1.9  | 0.015 |
		| 2.05 | 0.01  |
		| 2.2  | 0.007 |
	When I add the asphalt wave impact location
	And I run the calculation

Scenario: GivenCalculationInputForSchematization1Testcase7_WhenCalculating_ThenReturnsExpectedCalculationResult
	Given the following location construction properties:
		| X  | AsphaltRevetmentTopLayerType | FailureTension | SoilElasticity | ThicknessUpperLayer | ElasticModulusUpperLayer |
		| 10 | HydraulicAsphaltConcrete     | 1.6            | 55             | 0.35                | 18000                    |
	And the following Asphalt wave impact location
		| StiffnessRelationNu | FatigueAlpha | FatigueBeta | AverageNumberOfWavesCtm | ImpactNumberC | DensityOfWater |
		| 0.3                 | 0.4          | 4.5         | 0.9                     | 0.95          | 1000           |
	When I run the calculation
