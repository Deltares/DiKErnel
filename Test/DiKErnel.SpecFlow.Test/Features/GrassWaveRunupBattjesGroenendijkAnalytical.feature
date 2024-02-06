Feature: GrassWaveRunupBattjesGroenendijkAnalytical
As a user I want to perform grass wave run-up calculations based on Battjes-Groenendijk analytical.

    Background:
        Given the following tijdstippen and hydraulischeBelastingen:
          | tijdstippen | waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
          | 0           | 3            | 0.5            | 3                | 50             |
          | 3600        | 3.1          | 0.7            | 3.5              | 45             |
          | 7200        | 3.2          | 1              | 4                | 40             |
          | 10800       | 3.3          | 1.3            | 4.3              | 35             |
          | 14400       | 3.4          | 1.5            | 4.5              | 30             |
          | 18000       | 3.5          | 1.8            | 4.8              | 25             |
          | 21600       | 3.6          | 2.1            | 5.2              | 20             |
          | 25200       | 3.7          | 2.5            | 5.5              | 15             |
          | 28800       | 3.7          | 2.8            | 5.8              | 10             |
          | 32400       | 3.6          | 2.8            | 6                | 5              |
          | 36000       | 3.5          | 2.5            | 6                | 0              |
          | 39600       | 3.4          | 2.1            | 5.8              | 0              |
          | 43200       | 3.3          | 1.8            | 5.5              | 5              |
          | 46800       | 3.2          | 1.5            | 5.2              | 10             |
          | 50400       | 3.1          | 1.3            | 4.8              | 15             |
          | 54000       | 3            | 1              | 4.5              | 20             |
          | 57600       |              |                |                  |                |
        And the following dijkprofiel and dikeorientatie of 0:
          | posities | hoogten | ruwheidscoefficienten | teenBuitenzijde | kruinBuitenzijde |
          | 0        | 0       | 1.0                   | 0               | 25               |
          | 25       | 7.5     |                       |                 |                  |
        And the following locaties:
          | positie | rekenmethode   | typeToplaag      | beginschade | verhogingBelastingOvergangAlfaM | verlagingSterkteOvergangAlfaS |
          | 15      | grasGolfoploop | grasGeslotenZode | 0           | 1                               | 1                             |
        And the following rekenmethoden:
          | rekenmethode   | faalgetal | factorCtm | typeRekenprotocol            | frontsnelheid | bodemVoorlandZ | tanAvl | typeToplaag      |
          | grasGolfoploop | 1         | 0.92      | battjesGroenendijkAnalytisch | 1.1           | -4.0           | 0.004  | grasGeslotenZode |

    Scenario: Testcase 1 - Default with closed sod
        When I run the calculation
        Then the schadegetal is 5.964275964074616

    Scenario: Testcase 2 - Default with open sod
        Given the following values are adjusted:
          | typeToplaag  |
          | grasOpenZode |
        When I run the calculation
        Then the schadegetal is 21.802708300783724

    Scenario: Testcase 3
        Given the following values are adjusted:
          | kritiekeCumulatieveOverbelasting | kritiekeFrontsnelheid |
          | 8000                             | 6.2                   |
        When I run the calculation
        Then the schadegetal is 7.042858339779344

    Scenario: Testcase 4
        Given the following values are adjusted:
          | frontsnelheid |
          | 1.15          |
        When I run the calculation
        Then the schadegetal is 8.10764303618132

    Scenario: Testcase 5
        Given the following values are adjusted:
          | verhogingBelastingOvergangAlfaM | verlagingSterkteOvergangAlfaS |
          | 1.8                             | 0.9                           |
        When I run the calculation
        Then the schadegetal is 34.618492810973976

    Scenario: Testcase 6
        Given the following values are adjusted:
          | bodemVoorlandZ | tanAvl |
          | 0              | 0.05   |
        When I run the calculation
        Then the schadegetal is 9.562492468848081

    Scenario: Testcase 7
        Given the following values are adjusted:
          | beginschade | faalgetal |
          | 0.3         | 1.2       |
        When I run the calculation
        Then the schadegetal is 6.264275964074616

    Scenario: Testcase 8
        Given the following series are adjusted:
          | posities | hoogten | ruwheidscoefficienten |
          | 0        | 0       | 0.85                  |
          | 15       | 4       | 0.5                   |
          | 20       | 4.1     | 0.95                  |
          | 25       | 7.5     |                       |
        And the following values are adjusted:
          | dijkorientatie | positie |
          | 20             | 15      |
        When I run the calculation
        Then the schadegetal is 0.37123738545694945

    Scenario: Testcase 9
        Given the following series are adjusted:
          | posities | hoogten | ruwheidscoefficienten |
          | 0        | 0       | 0.7                   |
          | 15       | 5       | 0.8                   |
          | 20       | 5.1     | 1                     |
          | 30       | 7.5     |                       |
        And the following values are adjusted:
          | dijkorientatie | positie | bodemVoorlandZ | tanAvl | teenBuitenzijde | kruinBuitenzijde |
          | 30             | 18      | 1              | 0.009  | 0               | 30               |
        When I run the calculation
        Then the schadegetal is 0.26854724503160177

    Scenario: Testcase 10
        Given the following series are adjusted:
          | tijdstippen | waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
          | -6840       | 3.5          | 2.4            | 4                | 20             |
          | -6120       | 3.6          | 2.5            | 4.2              | 20             |
          | -5040       | 3.7          | 2.7            | 4.4              | 20             |
          | -3600       | 3.8          | 2.8            | 4.5              | 20             |
          | -1800       | 3.9          | 2.9            | 4.8              | 20             |
          | 360         | 3.95         | 3              | 5                | 20             |
          | 2880        | 4            | 2.9            | 5.2              | 20             |
          | 5760        | 3.95         | 2.9            | 5.5              | 15             |
          | 9000        | 3.8          | 2.8            | 5.8              | 10             |
          | 12600       | 3.6          | 2.8            | 6                | 5              |
          | 16560       | 3.5          | 2.5            | 6                | 0              |
          | 20880       | 3.4          | 2.1            | 5.8              | 0              |
          | 25560       | 3.3          | 1.8            | 5.5              | 5              |
          | 30600       | 3.2          | 1.5            | 5.2              | 10             |
          | 36000       | 3.1          | 1.3            | 4.8              | 15             |
          | 43200       | 3            | 1              | 4.5              | 20             |
          | 50400       |              |                |                  |                |
        When I run the calculation
        Then the schadegetal is 8.587822405580951

    Scenario: Testcase 11
        Given the following series are adjusted:
          | tijdstippen | waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
          | -6840       | 3.5          | 2.4            | 4                | 20             |
          | -6120       | 3.6          | 2.5            | 4.2              | 20             |
          | -5040       | 3.7          | 2.7            | 4.4              | 20             |
          | -3600       | 3.8          | 2.8            | 4.5              | 20             |
          | -1800       | 3.9          | 2.9            | 4.8              | 20             |
          | 360         | 3.95         | 3              | 5                | 20             |
          | 2880        | 4            | 2.9            | 5.2              | 20             |
          | 5760        | 3.95         | 2.9            | 5.5              | 15             |
          | 9000        | 3.8          | 2.8            | 5.8              | 10             |
          | 12600       | 3.6          | 2.8            | 6                | 5              |
          | 16560       | 3.5          | 2.5            | 6                | 0              |
          | 20880       | 3.4          | 2.1            | 5.8              | 0              |
          | 25560       | 3.3          | 1.8            | 5.5              | 5              |
          | 30600       | 3.2          | 1.5            | 5.2              | 10             |
          | 36000       | 3.1          | 1.3            | 4.8              | 15             |
          | 43200       | 3            | 1              | 4.5              | 20             |
          | 50400       |              |                |                  |                |
        And the following series are adjusted:
          | posities | hoogten | ruwheidscoefficienten |
          | 0        | 0       | 0.85                  |
          | 15       | 4       | 0.5                   |
          | 20       | 4.1     | 0.95                  |
          | 25       | 7.5     |                       |
        And the following values are adjusted:
          | dijkorientatie | positie | bodemVoorlandZ | tanAvl |
          | 20             | 15      | 0.5            | 0.01   |
        When I run the calculation
        Then the schadegetal is 0.669391470228952

    Scenario: Testcase 12
        Given the following series are adjusted:
          | tijdstippen | waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
          | -6840       | 3.5          | 2.4            | 4                | 20             |
          | -6120       | 3.6          | 2.5            | 4.2              | 20             |
          | -5040       | 3.7          | 2.7            | 4.4              | 20             |
          | -3600       | 3.8          | 2.8            | 4.5              | 20             |
          | -1800       | 3.9          | 2.9            | 4.8              | 20             |
          | 360         | 3.95         | 3              | 5                | 20             |
          | 2880        | 4            | 2.9            | 5.2              | 20             |
          | 5760        | 3.95         | 2.9            | 5.5              | 15             |
          | 9000        | 3.8          | 2.8            | 5.8              | 10             |
          | 12600       | 3.6          | 2.8            | 6                | 5              |
          | 16560       | 3.5          | 2.5            | 6                | 0              |
          | 20880       | 3.4          | 2.1            | 5.8              | 0              |
          | 25560       | 3.3          | 1.8            | 5.5              | 5              |
          | 30600       | 3.2          | 1.5            | 5.2              | 10             |
          | 36000       | 3.1          | 1.3            | 4.8              | 15             |
          | 43200       | 3            | 1              | 4.5              | 20             |
          | 50400       |              |                |                  |                |
        And the following series are adjusted:
          | posities | hoogten | ruwheidscoefficienten |
          | 0        | 0       | 0.85                  |
          | 15       | 4       | 0.5                   |
          | 20       | 4.1     | 0.95                  |
          | 25       | 7.5     |                       |
        And the following values are adjusted:
          | dijkorientatie | positie |
          | 20             | 15      |
        And the following values are adjusted:
          | beginschade | verhogingBelastingOvergangAlfaM | verlagingSterkteOvergangAlfaS |
          | 0.1         | 1.7                             | 0.85                          |
        And the following values are adjusted:
          | faalgetal | factorCtm | frontsnelheid | kritiekeCumulatieveOverbelasting | kritiekeFrontsnelheid | bodemVoorlandZ | tanAvl |
          | 1.1       | 0.89      | 1.2           | 7500                             | 5                     | -1             | 0.008  |
        When I run the calculation
        Then the schadegetal is 45.67201925900045

    Scenario: Testcase 13
        Given the following series are adjusted:
          | waterstanden |
          | -3.9         |
          | 8            |
        When I run the calculation
    #Then the schadegetal is .*