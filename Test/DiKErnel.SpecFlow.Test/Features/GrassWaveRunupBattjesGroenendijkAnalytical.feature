Feature: GrassWaveRunupBattjesGroenendijkAnalytical
	As a user I want to perform grass wave run-up calculations based on Battjes-Groenendijk analytical.
	
	Background: 
		Given the following tijdstippen:
			| tijdstippen |
			| 0           |
			| 3600        |
			| 7200        |
			| 10800       |
			| 14400       |
			| 18000       |
			| 21600       |
			| 25200       |
			| 28800       |
			| 32400       |
			| 36000       |
			| 39600       |
			| 43200       |
			| 46800       |
			| 50400       |
			| 54000       |
			| 57600       |
 		And the following hydraulischeBelastingen:
 			| waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
		    | 3            | 0.5            | 3                | 50             |
		    | 3.1          | 0.7            | 3.5              | 45             |
		    | 3.2          | 1              | 4                | 40             |
		    | 3.3          | 1.3            | 4.3              | 35             |
		    | 3.4          | 1.5            | 4.5              | 30             |
		    | 3.5          | 1.8            | 4.8              | 25             |
		    | 3.6          | 2.1            | 5.2              | 20             |
		    | 3.7          | 2.5            | 5.5              | 15             |
		    | 3.7          | 2.8            | 5.8              | 10             |
		    | 3.6          | 2.8            | 6                | 5              |
		    | 3.5          | 2.5            | 6                | 0              |
		    | 3.4          | 2.1            | 5.8              | 0              |
		    | 3.3          | 1.8            | 5.5              | 5              |
		    | 3.2          | 1.5            | 5.2              | 10             |
		    | 3.1          | 1.3            | 4.8              | 15             |
		    | 3            | 1              | 4.5              | 20             |
	    And the following dijkprofiel:
     		| dijkorientatie | posities | hoogten | ruwheidscoefficienten | teenBuitenzijde | kruinBuitenzijde |
     		| 0              | 0        | 0       | 1.0                   | 0               | 25               |
     		|                | 25       | 7.5     |                       |                 |                  |
	    And the following locaties:
     		| positie | rekenmethode   | typeToplaag      | beginschade | verhogingBelastingOvergangAlfaM | verlagingSterkteOvergangAlfaS |
	        | 15      | grasGolfoploop | grasGeslotenZode | 0           | 1                               | 1                             |
	    And  the following rekenmethoden:
     		| rekenmethode   | faalgetal | factorCtm | typeRekenprotocol            | frontsnelheid | bodemVoorlandZ | tanAvl | typeToplaag      | kritiekeCumulatieveOverbelasting | kritiekeFrontsnelheid |
	        | grasGolfoploop | 1         | 0.92      | battjesGroenendijkAnalytisch | 1.1           | -4.0           | 0.004  | grasGeslotenZode | 7000                             | 6.6                   |
	    
	Scenario: Testcase 1 - Default with closed sod
		When I run the calculation
		Then the schadegetal is 5.964275964074604
	
	Scenario: Testcase 2 - Default with open sod
		Given the following is adjusted:
			| typeToplaag  |
			| grasOpenZode |
   		When I run the calculation
   		#Then the schadegetal is
   		
   	Scenario: Testcase 3
	    Given the following is adjusted:
	      	| kritiekeCumulatieveOverbelasting | kritiekeFrontsnelheid |
	    When I run the calculation
		#Then the schadegetal is
	
	Scenario: Testcase 4
		Given the following is adjusted:
			| kritiekeFrontsnelheid|
		When I run the calculation
		#Then the schadegetal is
	
	Scenario: Testcase 5
		Given the following is adjusted:
			| verhogingBelastingOvergangAlfaM | verlagingSterkteOvergangAlfaS |
		When I run the calculation
		#Then the schadegetal is
		
	Scenario: Testcase 6
		Given the following is adjusted:
			| bodemVoorlandZ | tanAvl |
		When I run the calculation
		#Then the schadegetal is
		
	Scenario: Testcase 7
		Given the following is adjusted:
			| beginschade | faalgetal |
		When I run the calculation
		#Then the schadegetal is
		
	Scenario: Testcase 8
		Given the following is adjusted:
			| posities | hoogten | dijkorientatie | ruwheidscoefficienten | positie |
		When I run the calculation
		#Then the schadegetal is
		
	Scenario: Testcase 9
		Given the following is adjusted:
			| posities | hoogten | dijkorientatie | ruwheidscoefficienten | positie | bodemVoorlandZ | tanAvl |
		When I run the calculation
		#Then the schadegetal is
		
	Scenario: Testcase 10
		Given the following is adjusted:
			| tijdstippen | waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
		When I run the calculation
		#Then the schadegetal is
		
	Scenario: Testcase 11
		Given the following is adjusted:
			| tijdstippen | waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
    	And the following is adjusted:
			| posities | hoogten | dijkorientatie | ruwheidscoefficienten | positie | bodemVoorlandZ | tanAvl |
		When I run the calculation
		#Then the schadegetal is
		
	Scenario: Testcase 12
		Given the following is adjusted:
			| tijdstippen | waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
		And the following is adjusted:
			| posities | hoogten | dijkorientatie | ruwheidscoefficienten |
    	And the following is adjusted:
    		| positie | beginschade | verhogingBelastingOvergangAlfaM | verlagingSterkteOvergangAlfaS |
     	And the following is adjusted:
     		| faalgetal | factorCtm | frontsnelheid | kritiekeCumulatieveOverbelasting | kritiekeFrontsnelheid | bodemVoorlandZ | tanAvl |
		When I run the calculation
		#Then the schadegetal is
		
	Scenario: Testcase 13
		#all parameters changed with unrealistic values to test robustness
		
	Scenario Outline: BM Gras benchmark 14
		Given the following constant inputs:
			| bodemVoorlandZ | golfhoogtenHm0 | d | tan   | factorCtm | kritiekeCumulatieveOverbelasting |
			| 0.1            | 1.5            | 3 | 0.004 | 3.85      | 7000                             |
		When I change the value of <kritiekeFrontsnelheid>
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
		Given the following constant inputs:
			| kritiekeFrontsnelheid | golfhoogtenHm0 | d | tan   | factorCtm | kritiekeCumulatieveOverbelasting |
			| 6.6                   | 1.5            | 3 | 0.004 | 3.85      | 7000                             |
   		When I change the value of <bodemVoorlandZ>
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
		Given the following constant inputs:
			| kritiekeFrontsnelheid | golfhoogtenHm0 | d | bodemVoorlandZ | factorCtm | kritiekeCumulatieveOverbelasting |
			| 6.6                   | 1.5            | 3 | 0.1            | 3.85      | 7000                             |
   		When I change the value of <tan>
   		And I run the calculation
   		Then the output value for <cumulatieveOverbelastingTijdstap> is
   		
   		Examples: 
   			| tan   | cumulatieveOverbelastingTijdstap |
		    | 0.004 | 1.134                            |
		    | 0.04  | 13.406                           |

	Scenario Outline: BM Gras benchmark 17
		Given the following constant inputs:
			| kritiekeFrontsnelheid | golfhoogtenHm0 | tan   | bodemVoorlandZ | factorCtm | kritiekeCumulatieveOverbelasting |
			| 6.6                   | 1.5            | 0.004 | 0.1            | 3.85      | 7000                             |
   		When I change the value of <d>
   		And I run the calculation
   		Then the output value for <cumulatieveOverbelastingTijdstap> is
   		
   		Examples: 
   			| d    | cumulatieveOverbelastingTijdstap |
		    | 0.04 | 13755.272                        |
		    | 0.1  | 5759.070                         |
		    | 0.4  | 1031.437                         |
		    | 10   | 21.453                           |
      
	Scenario Outline: BM Gras benchmark 18
		Given the following constant inputs:
			| kritiekeFrontsnelheid | golfhoogtenHm0 | tan   | bodemVoorlandZ | factorCtm |
			| 6.6                   | 1.5            | 0.004 | 0.1            | 3.85      |
   		When I change the value of <d>
   		And I change the value of <Dcrit>
		And I run the calculation
		Then the output value for <cumulatieveOverbelastingTijdstap> is
		And the output value for <FoS> is
		
		Examples: 
			| d    | Dcrit | cumulatieveOverbelastingTijdstap | Fos   |
			| 0.04 | 100   | 13755.272                        | 0.007 |
			| 0.1  | 10    | 5759.070                         | 0.002 |
			| 0.4  | 1     | 1031.437                         | 0.001 |
			| 10   | 1     | 21.453                           | 0.047 |