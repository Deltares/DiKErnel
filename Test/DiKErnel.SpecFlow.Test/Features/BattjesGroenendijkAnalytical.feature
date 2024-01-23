Feature: BattjesGroenendijkAnalytical
	As a user I want to perform grass wave runup calculations based on Battjes-Groenendijk Analytical.

Scenario Outline: Testcase 1 - Default with closed sod
	Given the following tijdstippen:
		Examples:
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
 		Examples:
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
     	Examples:
     	| dijkorientatie | posities | hoogten | ruwheidscoefficienten | teenBuitenzijde | kruinBuitenzijde |
     	| 0              | 0        | 0       | 1.0                   | 0               | 25               |
     	|                | 25       | 7.5     |                       |                 |                  |
    And the following locaties:
     	Examples: 
     	| positie | rekenmethode   | typeToplaag      | beginschade | verhogingBelastingOvergangAlfaM | verlagingSterkteOvergangAlfaS |
        | 15      | grasGolfoploop | grasGeslotenZode | 0           | 1                               | 1                             |
    And  the following rekenmethoden:
     	Examples:
     	| rekenmethode   | faalgetal | factorCtm | typeRekenprotocol            | frontsnelheid | bodemVoorlandZ | tanAvl | typeToplaag      | kritiekeCumulatieveOverbelasting | kritiekeFrontsnelheid |
        | grasGolfoploop | 1         | 0.92      | battjesGroenendijkAnalytisch | 1.1           | -4.0           | 0.004  | grasGeslotenZode | 7000                             | 6.6                   |
    When I run the calculation
	# Then the schadegetal is