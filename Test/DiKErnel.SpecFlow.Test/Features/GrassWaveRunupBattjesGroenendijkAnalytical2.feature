Feature: GrassWaveRunupBattjesGroenendijkAnalytical2
	BM Gras benchmarks
	
		Background: 
		Given the following tijdstippen and hydraulischeBelastingen:
			| tijdstippen | waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
			| 0           | 0            | 1.5            | 4.20             | 0              |
			| 900         |              |                |                  |                |
	    And the following dijkprofiel and a dijkorientatie of 0:
     		| posities | hoogten | ruwheidscoefficienten |
	        | 0        |  -10    | 1                     |
	        | 40       |   0     | 1                     |
	        | 80       |   10    |                       |
		And the following karakteristiekePunten:
			| teenBuitenzijde | kruinBuitenzijde |
			| 0               | 80               |
	    And the following locaties:
	        | positie | typeToplaag       | beginschade | verhogingBelastingOvergangAlfaM | verlagingSterkteOvergangAlfaS |
	        | 40.4    |  grasGeslotenZode |      0      |  1                              |   1                           |
	    And  the following rekenmethoden:
	        | faalgetal | factorCtm | frontsnelheid | bodemVoorlandZ | tanAvl | typeToplaag      |
	        |     1     |    3.85   |      1.10     |       -3       | 0.004  | grasGeslotenZode |          
			
	Scenario Outline: BM Gras benchmark 14
		When I change the property kritiekeFrontsnelheid to a value of <kritiekeFrontsnelheid>
		And I run the calculation
		Then the output value for <cumulatieveOverbelastingTijdstap> is
		
		Examples: 
		  	| kritiekeFrontsnelheid | cumulatieveOverbelastingTijdstap |
			| 3.5                   | 698.151                          |
			| 4                     | 588.395                          |
			| 5.5                   | 7.156                            |
			| 6.5                   | 0.000                            |
			| 8                     | 0.000                            |
    
	Scenario Outline: BM Gras benchmark 15
   		When I change the property bodemVoorlandZ to a value of <bodemVoorlandZ>
   		And I run the calculation
   		Then the output value for <cumulatieveOverbelastingTijdstap> is
   		
   		Examples: 
   			| bodemVoorlandZ | cumulatieveOverbelastingTijdstap |
		    | 0              | 0.000                            |
		    | 2              | 1.134                            |
		    | 2              | 1.134                            |
		    | 3              | 0.139                            |
		    | 4              | 0.000                            |
		    | 5              | 0.000                            |
		    | 6              | 0.000                            |
      
	Scenario Outline: BM Gras benchmark 16
   		When I change the property tanAvl to a value of <hellingVoorland>
   		And I run the calculation
   		Then the output value for <cumulatieveOverbelastingTijdstap> is
   		
   		Examples: 
   			| hellingVoorland | cumulatieveOverbelastingTijdstap |
		    | 0               | 0.918                            |
		    | 0.004           | 1.134                            |
		    | 0.04            | 13.406                           |
		    | 0.1             | 49.205                           |
		    | 0.4             | 48.062                           |
		    | 10              | 48.062                           |
		    | 100             | 48.062                           |
		    | 250             | 48.062                           |

	Scenario Outline: BM Gras benchmark 17
   		When I change the property bodemVoorlandZ to a value of <diepteVoorland>
   		And I run the calculation
   		Then the output value for <cumulatieveOverbelastingTijdstap> is
   		
   		Examples: 
   			| diepteVoorland | cumulatieveOverbelastingTijdstap |
		    | 0              | 0.000                            |
		    | 0.004          | 133115.947                       |
		    | 0.04           | 13755.272                        |
		    | 0.1            | 5759.070                         |
		    | 0.4            | 1031.437                         |
		    | 10             | 21.453                           |
		    | 100            |                                  |
		    | 250            |                                  |
      
	Scenario Outline: BM Gras benchmark 18
   		When I change the property bodemVoorlandZ to a value of <diepteVoorland>
   		And I change the property kritiekeCumulatieveOverbelasting to a value of <kritiekeCumulatieveOverbelasting>
		And I run the calculation
		Then the output value for <cumulatieveOverbelastingTijdstap> is
		
		Examples: 
			| diepteVoorland | kritiekeCumulatieveOverbelasting | cumulatieveOverbelastingTijdstap |
			| 0              | 1000                             | 0.000                            |
			| 0.004          | 1000                             | 133115.947                       |
			| 0.04           | 100                              | 13755.272                        |
			| 0.1            | 10                               | 5759.070                         |
			| 0.4            | 1                                | 1031.437                         |
			| 10             | 1                                | 21.453                           |
			| 100            | 1                                |                                  |
			| 250            | 1                                |                                  |