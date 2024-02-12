Feature: GrassWaveRunupBattjesGroenendijkAnalytical
As a user I want to perform grass wave run-up calculations based on Battjes-Groenendijk analytical.

    Background:
        Given the following time steps and hydraulic loads:
          | Time step | Water level | Wave height Hm0 | Wave period Tm10 | Wave direction |
          | 0         | 3           | 0.5             | 3                | 50             |
          | 3600      | 3.1         | 0.7             | 3.5              | 45             |
          | 7200      | 3.2         | 1               | 4                | 40             |
          | 10800     | 3.3         | 1.3             | 4.3              | 35             |
          | 14400     | 3.4         | 1.5             | 4.5              | 30             |
          | 18000     | 3.5         | 1.8             | 4.8              | 25             |
          | 21600     | 3.6         | 2.1             | 5.2              | 20             |
          | 25200     | 3.7         | 2.5             | 5.5              | 15             |
          | 28800     | 3.7         | 2.8             | 5.8              | 10             |
          | 32400     | 3.6         | 2.8             | 6                | 5              |
          | 36000     | 3.5         | 2.5             | 6                | 0              |
          | 39600     | 3.4         | 2.1             | 5.8              | 0              |
          | 43200     | 3.3         | 1.8             | 5.5              | 5              |
          | 46800     | 3.2         | 1.5             | 5.2              | 10             |
          | 50400     | 3.1         | 1.3             | 4.8              | 15             |
          | 54000     | 3           | 1               | 4.5              | 20             |
          | 57600     |             |                 |                  |                |
        And the following dike profile and a dike orientation of 0:
          | X  | Z   | Roughness coefficient |
          | 0  | 0   | 1                     |
          | 25 | 7.5 |                       |
        And the following dike profile points:
          | Outer toe | Outer crest |
          | 0         | 25          |
        And the following calculation settings:
          | Setting                            | Value      |
          | Position                           | 15         |
          | Top layer type                     | Closed sod |
          | Initial damage                     | 0          |
          | Increased load transition alfa M   | 1          |
          | Reduced strength transition alfa S | 1          |
          | Failure number                     | 1          |
          | Average number of waves Ctm        | 0.92       |
          | Front velocity                     | 1.1        |
          | Foreshore bottom level             | -4         |
          | Slope foreshore                    | 0.004      |

    Scenario: Testcase 1 - Default with closed sod
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 5.964275964074616

    Scenario: Testcase 2 - Default with open sod
        Given the following calculation settings are adjusted:
          | Setting        | Value    |
          | Top layer type | Open sod |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 21.802708300783724

    Scenario: Testcase 3 - Adjusted critical values
        Given the following calculation settings are adjusted:
          | Setting                      | Value |
          | Critical cumulative overload | 8000  |
          | Critical front velocity      | 6.2   |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 7.042858339779344

    Scenario: Testcase 4 - Adjusted front velocity
        Given the following calculation settings are adjusted:
          | Setting        | Value |
          | Front velocity | 1.15  |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 8.10764303618132

    Scenario: Testcase 5 - Adjusted transition properties
        Given the following calculation settings are adjusted:
          | Setting                            | Value |
          | Increased load transition alfa M   | 1.8   |
          | Reduced strength transition alfa S | 0.9   |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 34.618492810973976

    Scenario: Testcase 6 - Adjusted foreshore properties
        Given the following calculation settings are adjusted:
          | Setting                | Value |
          | Foreshore bottom level | 0     |
          | Slope foreshore        | 0.05  |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 9.562492468848081

    Scenario: Testcase 7 - Adjusted failure conditions
        Given the following calculation settings are adjusted:
          | Setting        | Value |
          | Initial damage | 0.3   |
          | Damage number  | 1.2   |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 6.264275964074616

    Scenario: Testcase 8 - Calculations with a berm
        Given the following series are adjusted:
          | X  | Z   | Roughness coefficient |
          | 0  | 0   | 0.85                  |
          | 15 | 4   | 0.5                   |
          | 20 | 4.1 | 0.95                  |
          | 25 | 7.5 |                       |
        And the following calculation settings are adjusted:
          | Setting          | Value |
          | Dike orientation | 20    |
          | Position         | 15    |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 0.37123738545694945

    Scenario: Testcase 9 - Calculations with a berm & adjusted foreshore properties
        Given the following series are adjusted:
          | X  | Z   | Roughness coefficient |
          | 0  | 0   | 0.7                   |
          | 15 | 5   | 0.8                   |
          | 20 | 5.1 | 1                     |
          | 30 | 7.5 |                       |
        And the following calculation settings are adjusted:
          | Setting                | Value |
          | Dike orientation       | 30    |
          | Position               | 18    |
          | Foreshore bottom level | 1     |
          | Slope foreshore        | 0.009 |
          | Outer toe              | 0     |
          | Outer crest            | 30    |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 0.26854724503160177

    Scenario: Testcase 10 - Negative time steps & adjusted hydraulic loads
        Given the following series are adjusted:
          | Time step | Water level | Wave height Hm0 | Wave period Tm10 | Wave direction |
          | -6840     | 3.5         | 2.4             | 4                | 20             |
          | -6120     | 3.6         | 2.5             | 4.2              | 20             |
          | -5040     | 3.7         | 2.7             | 4.4              | 20             |
          | -3600     | 3.8         | 2.8             | 4.5              | 20             |
          | -1800     | 3.9         | 2.9             | 4.8              | 20             |
          | 360       | 3.95        | 3               | 5                | 20             |
          | 2880      | 4           | 2.9             | 5.2              | 20             |
          | 5760      | 3.95        | 2.9             | 5.5              | 15             |
          | 9000      | 3.8         | 2.8             | 5.8              | 10             |
          | 12600     | 3.6         | 2.8             | 6                | 5              |
          | 16560     | 3.5         | 2.5             | 6                | 0              |
          | 20880     | 3.4         | 2.1             | 5.8              | 0              |
          | 25560     | 3.3         | 1.8             | 5.5              | 5              |
          | 30600     | 3.2         | 1.5             | 5.2              | 10             |
          | 36000     | 3.1         | 1.3             | 4.8              | 15             |
          | 43200     | 3           | 1               | 4.5              | 20             |
          | 50400     |             |                 |                  |                |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 8.587822405580951

    Scenario: Testcase 11 - Negative time steps & adjusted hydraulic loads, dike profile properties (berm), foreshore properties
        Given the following series are adjusted:
          | Time step | Water level | Wave height Hm0 | Wave period Tm10 | Wave direction |
          | -6840     | 3.5         | 2.4             | 4                | 20             |
          | -6120     | 3.6         | 2.5             | 4.2              | 20             |
          | -5040     | 3.7         | 2.7             | 4.4              | 20             |
          | -3600     | 3.8         | 2.8             | 4.5              | 20             |
          | -1800     | 3.9         | 2.9             | 4.8              | 20             |
          | 360       | 3.95        | 3               | 5                | 20             |
          | 2880      | 4           | 2.9             | 5.2              | 20             |
          | 5760      | 3.95        | 2.9             | 5.5              | 15             |
          | 9000      | 3.8         | 2.8             | 5.8              | 10             |
          | 12600     | 3.6         | 2.8             | 6                | 5              |
          | 16560     | 3.5         | 2.5             | 6                | 0              |
          | 20880     | 3.4         | 2.1             | 5.8              | 0              |
          | 25560     | 3.3         | 1.8             | 5.5              | 5              |
          | 30600     | 3.2         | 1.5             | 5.2              | 10             |
          | 36000     | 3.1         | 1.3             | 4.8              | 15             |
          | 43200     | 3           | 1               | 4.5              | 20             |
          | 50400     |             |                 |                  |                |
        And the following series are adjusted:
          | X  | Z   | Roughness coefficient |
          | 0  | 0   | 0.85                  |
          | 15 | 4   | 0.5                   |
          | 20 | 4.1 | 0.95                  |
          | 25 | 7.5 |                       |
        And the following calculation settings are adjusted:
          | Setting                | Value |
          | Dike orientation       | 20    |
          | Position               | 15    |
          | Foreshore bottom level | 0.5   |
          | Slope foreshore        | 0.01  |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 0.6219200388310531

    Scenario: Testcase 12 - All properties adjusted
        Given the following series are adjusted:
          | Time step | Water level | Wave height Hm0 | Wave period Tm10 | Wave direction |
          | -6840     | 3.5         | 2.4             | 4                | 20             |
          | -6120     | 3.6         | 2.5             | 4.2              | 20             |
          | -5040     | 3.7         | 2.7             | 4.4              | 20             |
          | -3600     | 3.8         | 2.8             | 4.5              | 20             |
          | -1800     | 3.9         | 2.9             | 4.8              | 20             |
          | 360       | 3.95        | 3               | 5                | 20             |
          | 2880      | 4           | 2.9             | 5.2              | 20             |
          | 5760      | 3.95        | 2.9             | 5.5              | 15             |
          | 9000      | 3.8         | 2.8             | 5.8              | 10             |
          | 12600     | 3.6         | 2.8             | 6                | 5              |
          | 16560     | 3.5         | 2.5             | 6                | 0              |
          | 20880     | 3.4         | 2.1             | 5.8              | 0              |
          | 25560     | 3.3         | 1.8             | 5.5              | 5              |
          | 30600     | 3.2         | 1.5             | 5.2              | 10             |
          | 36000     | 3.1         | 1.3             | 4.8              | 15             |
          | 43200     | 3           | 1               | 4.5              | 20             |
          | 50400     |             |                 |                  |                |
        And the following series are adjusted:
          | X  | Z   | Roughness coefficient |
          | 0  | 0   | 0.85                  |
          | 15 | 4   | 0.5                   |
          | 20 | 4.1 | 0.95                  |
          | 25 | 7.5 |                       |
        And the following calculation settings are adjusted:
          | Setting                            | Value |
          | Dike orientation                   | 20    |
          | Position                           | 15    |
          | Initial damage                     | 0.1   |
          | Increased load transition alfa M   | 1.7   |
          | Reduced strength transition alfa S | 0.85  |
          | Failure number                     | 1.1   |
          | Average number of waves Ctm        | 0.89  |
          | Front velocity                     | 1.2   |
          | Foreshore bottom level             | -1    |
          | Slope foreshore                    | 0.008 |
          | Critical cumulative overload       | 7500  |
          | Critical front velocity            | 5     |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is 41.84703315170409

    Scenario: Testcase 13 - Robustness edge cases
    Remark: The time step 36000 - 43200 results in a 0 for the representative wave run-up (2 percent) Z2% .
    This results in a division by zero due to the wave run up transition and the wave run up root mean square being
    both 0. Therefore, no result will be produced by the DiKErnel (NaN)
        Given the following series are adjusted:
          | Time step | Water level | Wave height Hm0 | Wave period Tm10 | Wave direction |
          | -6840     | 3.53232     | 2.443434        | 4.132323         | 200.434343     |
          | 36000     | 3.19999     | 1.3             | 4.83             | 15.9999        |
          | 43200     | 7.5         | 1.1111          | 4.51111          | 20.43434       |
          | 50400     |             |                 |                  |                |
        And the following series are adjusted:
          | X      | Z      | Roughness coefficient |
          | 0      | 0      | 0.859999              |
          | 15.001 | 4.0005 | 0.51111               |
          | 20.999 | 4.1    | 0.95111               |
          | 25     | 7.5    |                       |
        And the following calculation settings are adjusted:
          | Setting                            | Value      |
          | Dike orientation                   | 179.5      |
          | Position                           | 17.04343   |
          | Foreshore bottom level             | -0.59999   |
          | Slope foreshore                    | 0.01111    |
          | Initial damage                     | 0.54545    |
          | Increased load transition alfa M   | 3.754545   |
          | Reduced strength transition alfa S | 0.111      |
          | Failure number                     | 10.32321   |
          | Average number of waves Ctm        | 0.1656454  |
          | Front velocity                     | 2.21243434 |
          | Critical cumulative overload       | 6212.32434 |
          | Critical front velocity            | 4.54434343 |
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the damage is NaN