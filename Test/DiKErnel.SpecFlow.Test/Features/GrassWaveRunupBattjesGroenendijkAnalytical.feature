Feature: Grass wave run-up Battjes-Groenendijk analytical
  As a user I want to perform grass wave run-up calculations based on Battjes-Groenendijk analytical.

  Background:
    Given the following hydraulic loads:
      | Time step | Water level | Wave height | Wave period | Wave direction |
      | 0         | 3           | 0.5         | 3           | 50             |
      | 3600      | 3.1         | 0.7         | 3.5         | 45             |
      | 7200      | 3.2         | 1           | 4           | 40             |
      | 10800     | 3.3         | 1.3         | 4.3         | 35             |
      | 14400     | 3.4         | 1.5         | 4.5         | 30             |
      | 18000     | 3.5         | 1.8         | 4.8         | 25             |
      | 21600     | 3.6         | 2.1         | 5.2         | 20             |
      | 25200     | 3.7         | 2.5         | 5.5         | 15             |
      | 28800     | 3.7         | 2.8         | 5.8         | 10             |
      | 32400     | 3.6         | 2.8         | 6           | 5              |
      | 36000     | 3.5         | 2.5         | 6           | 0              |
      | 39600     | 3.4         | 2.1         | 5.8         | 0              |
      | 43200     | 3.3         | 1.8         | 5.5         | 5              |
      | 46800     | 3.2         | 1.5         | 5.2         | 10             |
      | 50400     | 3.1         | 1.3         | 4.8         | 15             |
      | 54000     | 3           | 1           | 4.5         | 20             |
      | 57600     | N.A.        | N.A.        | N.A.        | N.A.           |
    And the following dike geometry:
      | X  | Z   | Roughness coefficient |
      | 0  | 0   | 1                     |
      | 25 | 7.5 | N.A.                  |
    And the following dike properties:
      | Property               | Value |
      | Orientation            | 0     |
      | Slope foreshore        | 0.004 |
      | Bottom level foreshore | -4    |
    And the following characteristic points:
      | Characteristic point | Value |
      | Outer toe            | 0     |
      | Outer crest          | 25    |
    And the following calculation settings:
      | Setting                     | Value      |
      | Position                    | 15         |
      | Top layer type              | Closed sod |
      | Initial damage              | 0          |
      | Increased load transition   | 1          |
      | Reduced strength transition | 1          |
      | Failure number              | 1          |
      | Factor Ctm                  | 0.92       |
      | Front velocity              | 1.1        |

  Scenario: Default calculation with closed sod
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 5.96427596407462
    And the rounded time of failure is 27615

  Scenario: Default calculation with open sod
    Given the following adjusted calculation settings:
      | Setting        | Value    |
      | Top layer type | Open sod |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 21.80270830078372
    And the rounded time of failure is 14511

  Scenario: Calculation with adjusted critical values
    Given the following adjusted calculation settings:
      | Setting                      | Value |
      | Critical cumulative overload | 8000  |
      | Critical front velocity      | 6.2   |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 7.04285833977934
    And the rounded time of failure is 26198

  Scenario: Calculation with adjusted front velocity
    Given the following adjusted calculation settings:
      | Setting        | Value |
      | Front velocity | 1.15  |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 8.10764303618132
    And the rounded time of failure is 25872

  Scenario: Calculation with adjusted transition properties
    Given the following adjusted calculation settings:
      | Setting                     | Value |
      | Increased load transition   | 1.8   |
      | Reduced strength transition | 0.9   |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 34.61849281097397
    And the rounded time of failure is 13555

  Scenario: Calculation with adjusted foreshore properties
    Given the following adjusted dike properties:
      | Property               | Value |
      | Bottom level foreshore | 0     |
      | Slope foreshore        | 0.05  |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 9.56249246884808
    And the rounded time of failure is 26067

  Scenario: Calculation with adjusted failure conditions
    Given the following adjusted calculation settings:
      | Setting        | Value |
      | Initial damage | 0.3   |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 6.26427596407462
    And the rounded time of failure is 26188

  Scenario: Calculation with a berm
    Given the following adjusted dike geometry:
      | X  | Z   | Roughness coefficient |
      | 0  | 0   | 0.85                  |
      | 15 | 4   | 0.5                   |
      | 20 | 4.1 | 0.95                  |
      | 25 | 7.5 | N.A.                  |
    And the following adjusted dike properties:
      | Property    | Value |
      | Orientation | 20    |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 0.37123738545695
    And the rounded time of failure is undefined

  Scenario: Calculation with a berm and adjusted foreshore properties
    Given the following adjusted dike geometry:
      | X  | Z   | Roughness coefficient |
      | 0  | 0   | 0.7                   |
      | 15 | 5   | 0.8                   |
      | 20 | 5.1 | 1                     |
      | 30 | 7.5 | N.A.                  |
    And the following adjusted dike properties:
      | Property               | Value |
      | Orientation            | 30    |
      | Bottom level foreshore | 1     |
      | Slope foreshore        | 0.009 |
    And the following adjusted characteristic points:
      | Characteristic point | Value |
      | Outer toe            | 0     |
      | Outer crest          | 30    |
    And the following adjusted calculation settings:
      | Setting  | Value |
      | Position | 18    |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 0.268547245031602
    And the rounded time of failure is undefined

  Scenario: Calculation with negative time steps and adjusted hydraulic loads
    Given the following adjusted hydraulic loads:
      | Time step | Water level | Wave height | Wave period | Wave direction |
      | -6840     | 3.5         | 2.4         | 4           | 20             |
      | -6120     | 3.6         | 2.5         | 4.2         | 20             |
      | -5040     | 3.7         | 2.7         | 4.4         | 20             |
      | -3600     | 3.8         | 2.8         | 4.5         | 20             |
      | -1800     | 3.9         | 2.9         | 4.8         | 20             |
      | 360       | 3.95        | 3           | 5           | 20             |
      | 2880      | 4           | 2.9         | 5.2         | 20             |
      | 5760      | 3.95        | 2.9         | 5.5         | 15             |
      | 9000      | 3.8         | 2.8         | 5.8         | 10             |
      | 12600     | 3.6         | 2.8         | 6           | 5              |
      | 16560     | 3.5         | 2.5         | 6           | 0              |
      | 20880     | 3.4         | 2.1         | 5.8         | 0              |
      | 25560     | 3.3         | 1.8         | 5.5         | 5              |
      | 30600     | 3.2         | 1.5         | 5.2         | 10             |
      | 36000     | 3.1         | 1.3         | 4.8         | 15             |
      | 43200     | 3           | 1           | 4.5         | 20             |
      | 50400     | N.A.        | N.A.        | N.A.        | N.A.           |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 8.58782240558095
    And the rounded time of failure is 1365

  Scenario: Calculation with negative time steps and adjusted hydraulic loads, dike profile properties (berm) and foreshore properties
    Given the following adjusted hydraulic loads:
      | Time step | Water level | Wave height | Wave period | Wave direction |
      | -6840     | 3.5         | 2.4         | 4           | 20             |
      | -6120     | 3.6         | 2.5         | 4.2         | 20             |
      | -5040     | 3.7         | 2.7         | 4.4         | 20             |
      | -3600     | 3.8         | 2.8         | 4.5         | 20             |
      | -1800     | 3.9         | 2.9         | 4.8         | 20             |
      | 360       | 3.95        | 3           | 5           | 20             |
      | 2880      | 4           | 2.9         | 5.2         | 20             |
      | 5760      | 3.95        | 2.9         | 5.5         | 15             |
      | 9000      | 3.8         | 2.8         | 5.8         | 10             |
      | 12600     | 3.6         | 2.8         | 6           | 5              |
      | 16560     | 3.5         | 2.5         | 6           | 0              |
      | 20880     | 3.4         | 2.1         | 5.8         | 0              |
      | 25560     | 3.3         | 1.8         | 5.5         | 5              |
      | 30600     | 3.2         | 1.5         | 5.2         | 10             |
      | 36000     | 3.1         | 1.3         | 4.8         | 15             |
      | 43200     | 3           | 1           | 4.5         | 20             |
      | 50400     | N.A.        | N.A.        | N.A.        | N.A.           |
    And the following adjusted dike geometry:
      | X  | Z   | Roughness coefficient |
      | 0  | 0   | 0.85                  |
      | 15 | 4   | 0.5                   |
      | 20 | 4.1 | 0.95                  |
      | 25 | 7.5 | N.A.                  |
    And the following adjusted dike properties:
      | Property               | Value |
      | Orientation            | 20    |
      | Bottom level foreshore | 0.5   |
      | Slope foreshore        | 0.01  |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 0.62192003883105
    And the rounded time of failure is undefined

  Scenario: Calculation with all properties adjusted
    Given the following adjusted hydraulic loads:
      | Time step | Water level | Wave height | Wave period | Wave direction |
      | -6840     | 3.5         | 2.4         | 4           | 20             |
      | -6120     | 3.6         | 2.5         | 4.2         | 20             |
      | -5040     | 3.7         | 2.7         | 4.4         | 20             |
      | -3600     | 3.8         | 2.8         | 4.5         | 20             |
      | -1800     | 3.9         | 2.9         | 4.8         | 20             |
      | 360       | 3.95        | 3           | 5           | 20             |
      | 2880      | 4           | 2.9         | 5.2         | 20             |
      | 5760      | 3.95        | 2.9         | 5.5         | 15             |
      | 9000      | 3.8         | 2.8         | 5.8         | 10             |
      | 12600     | 3.6         | 2.8         | 6           | 5              |
      | 16560     | 3.5         | 2.5         | 6           | 0              |
      | 20880     | 3.4         | 2.1         | 5.8         | 0              |
      | 25560     | 3.3         | 1.8         | 5.5         | 5              |
      | 30600     | 3.2         | 1.5         | 5.2         | 10             |
      | 36000     | 3.1         | 1.3         | 4.8         | 15             |
      | 43200     | 3           | 1           | 4.5         | 20             |
      | 50400     | N.A.        | N.A.        | N.A.        | N.A.           |
    And the following adjusted dike geometry:
      | X  | Z   | Roughness coefficient |
      | 0  | 0   | 0.85                  |
      | 15 | 4   | 0.5                   |
      | 20 | 4.1 | 0.95                  |
      | 25 | 7.5 | N.A.                  |
    And the following adjusted dike properties:
      | Property               | Value |
      | Orientation            | 20    |
      | Bottom level foreshore | -1    |
      | Slope foreshore        | 0.008 |
    And the following adjusted calculation settings:
      | Setting                      | Value |
      | Initial damage               | 0.1   |
      | Increased load transition    | 1.7   |
      | Reduced strength transition  | 0.85  |
      | Failure number               | 1.1   |
      | Factor Ctm                   | 0.89  |
      | Front velocity               | 1.2   |
      | Critical cumulative overload | 7500  |
      | Critical front velocity      | 5     |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is 41.84703315170409
    And the rounded time of failure is -5604

  Scenario: Robustness edge case
  Remark: The time step 36000 - 43200 results in a 0 for the representative wave run-up (2 percent).
  This results in a division by zero due to the wave run-up transition and the wave run-up root mean square being
  both 0. Therefore, no result will be produced by the DiKErnel (NaN).
    Given the following adjusted hydraulic loads:
      | Time step | Water level | Wave height | Wave period | Wave direction |
      | -6840     | 3.53232     | 2.443434    | 4.132323    | 200.434343     |
      | 36000     | 3.19999     | 1.3         | 4.83        | 15.9999        |
      | 43200     | 7.5         | 1.1111      | 4.51111     | 20.43434       |
      | 50400     | N.A.        | N.A.        | N.A.        | N.A.           |
    And the following adjusted dike geometry:
      | X      | Z      | Roughness coefficient |
      | 0      | 0      | 0.859999              |
      | 15.001 | 4.0005 | 0.51111               |
      | 20.999 | 4.1    | 0.95111               |
      | 25     | 7.5    | N.A.                  |
    And the following adjusted dike properties:
      | Property               | Value    |
      | Orientation            | 179.5    |
      | Bottom level foreshore | -0.59999 |
      | Slope foreshore        | 0.01111  |
    And the following adjusted calculation settings:
      | Setting                      | Value      |
      | Position                     | 17.04343   |
      | Initial damage               | 0.54545    |
      | Increased load transition    | 3.754545   |
      | Reduced strength transition  | 0.111      |
      | Failure number               | 10.32321   |
      | Factor Ctm                   | 0.1656454  |
      | Front velocity               | 2.21243434 |
      | Critical cumulative overload | 6212.32434 |
      | Critical front velocity      | 4.54434343 |
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is NaN
    And the rounded time of failure is undefined