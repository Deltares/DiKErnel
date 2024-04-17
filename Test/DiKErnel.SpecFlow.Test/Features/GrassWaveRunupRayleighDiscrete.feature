﻿Feature: Grass wave run-up Rayleigh discrete
As a user I want to perform grass wave run-up calculations based on Rayleigh discrete.

    Background:
        Given the following hydraulic loads:
          | Time step | Water level | Wave height | Wave period | Wave direction |
          | 0         | 0           | 0.5         | 3           | 50             |
          | 3600      | 0.1         | 0.7         | 3.5         | 45             |
          | 7200      | 0.2         | 1           | 4           | 40             |
          | 10800     | 0.3         | 1.3         | 4.3         | 35             |
          | 14400     | 0.4         | 1.5         | 4.5         | 30             |
          | 18000     | 0.5         | 1.8         | 4.8         | 25             |
          | 21600     | 0.6         | 2.1         | 5.2         | 20             |
          | 25200     | 0.7         | 2.5         | 5.5         | 15             |
          | 28800     | 0.7         | 2.8         | 5.8         | 10             |
          | 32400     | 0.6         | 2.8         | 6           | 5              |
          | 36000     | 0.5         | 2.5         | 6           | 0              |
          | 39600     | 0.4         | 2.1         | 5.8         | 0              |
          | 43200     | 0.3         | 1.8         | 5.5         | 5              |
          | 46800     | 0.2         | 1.5         | 5.2         | 10             |
          | 50400     | 0.1         | 1.3         | 4.8         | 15             |
          | 54000     | 0           | 1           | 4.5         | 20             |
          | 57600     | N.A.        | N.A.        | N.A.        | N.A.           |
        And the following dike geometry:
          | X  | Z   |
          | 0  | 0   |
          | 25 | 7.5 |
        And the following dike properties:
          | Property    | Value |
          | Orientation | 0     |
        And the following characteristic points:
          | Characteristic point | Value |
          | Outer toe            | 0     |
          | Outer crest          | 25    |
        And the following calculation settings:
          | Setting        | Value      |
          | Position       | 3.0        |
          | Top layer type | Closed sod |
          | Slope angle    | 0.3        |

    Scenario: Default with closed sod
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.17424874554865

    Scenario: Default with open sod
        Given the following adjusted hydraulic loads:
          | Wave height | Wave period |
          | 0.3         | 3           |
          | 0.4         | 3.5         |
          | 0.5         | 3.9         |
          | 0.6         | 4.2         |
          | 0.7         | 4.6         |
          | 0.8         | 4.9         |
          | 0.9         | 5.2         |
          | 1           | 5.5         |
          | 1.1         | 5.7         |
          | 1.1         | 5.7         |
          | 1           | 5.5         |
          | 0.9         | 5.2         |
          | 0.8         | 4.9         |
          | 0.7         | 4.6         |
          | 0.6         | 4.2         |
          | 0.5         | 3.9         |
        And the following adjusted calculation settings:
          | Setting        | Value    |
          | Top layer type | Open sod |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.52484620520786

    Scenario: Adjusted sod
        Given the following adjusted calculation settings:
          | Setting                      | Value |
          | Critical cumulative overload | 8000  |
          | Critical front velocity      | 6.2   |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.67645627404328

    Scenario: Calculation with a transition zone
        Given the following adjusted hydraulic loads:
          | Wave height | Wave period |
          | 0.3         | 3           |
          | 0.4         | 3.5         |
          | 0.5         | 3.9         |
          | 0.6         | 4.2         |
          | 0.7         | 4.6         |
          | 0.8         | 4.9         |
          | 0.9         | 5.2         |
          | 1           | 5.5         |
          | 1.1         | 5.7         |
          | 1.1         | 5.7         |
          | 1           | 5.5         |
          | 0.9         | 5.2         |
          | 0.8         | 4.9         |
          | 0.7         | 4.6         |
          | 0.6         | 4.2         |
          | 0.5         | 3.9         |
        And the following adjusted calculation settings:
          | Setting                     | Value |
          | Increased load transition   | 1.8   |
          | Reduced strength transition | 0.9   |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.51908455307175

    Scenario: Adjusted front velocity and fixed number of waves
        Given the following adjusted calculation settings:
          | Setting               | Value |
          | Fixed number of waves | 500   |
          | Front velocity        | 1.15  |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.79080784328382

    Scenario: Adjusted representative wave run-up 2P
        Given the following adjusted calculation settings:
          | Setting                         | Value |
          | Representative wave run-up 2P a | 1.75  |
          | Representative wave run-up 2P b | 4.3   |
          | Representative wave run-up 2P c | 1.6   |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.58504284832686

    Scenario: Adjusted berm factor and roughness coefficient
        Given the following adjusted calculation settings:
          | Setting               | Value    |
          | Top layer type        | Open sod |
          | Berm factor           | 0.7      |
          | Roughness coefficient | 0.7      |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.00238062787654

    Scenario: Adjusted wave angle impact and average number of waves
        Given the following adjusted calculation settings:
          | Setting                   | Value  |
          | Wave angle impact aBeta   | 0.0033 |
          | Wave angle impact betaMax | 30.0   |
          | Average number of waves   | 1.0    |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.03411027331395

    Scenario: Calculation where the revetment is flooded for some time
        Given the following adjusted hydraulic loads:
          | Water level | Wave height | Wave period | Wave direction |
          | 0.5         | 2.4         | 4           | 20             |
          | 0.6         | 2.5         | 4.2         | 20             |
          | 0.7         | 2.7         | 4.4         | 20             |
          | 0.8         | 2.8         | 4.5         | 20             |
          | 0.9         | 2.9         | 4.8         | 20             |
          | 0.95        | 3.0         | 5           | 20             |
          | 1.0         | 2.9         | 5.2         | 20             |
          | 0.95        | 2.9         | 5.5         | 15             |
          | 0.8         | 2.8         | 5.8         | 10             |
          | 0.6         | 2.8         | 6           | 5              |
          | 0.5         | 2.5         | 6           | 0              |
          | 0.4         | 2.1         | 5.8         | 0              |
          | 0.3         | 1.8         | 5.5         | 5              |
          | 0.2         | 1.5         | 5.2         | 10             |
          | 0.1         | 1.3         | 4.8         | 15             |
          | 0.0         | 1.0         | 4.5         | 20             |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.11400976522333

    Scenario: Calculation with differing beginschade and faalgetal
        Given the following adjusted calculation settings:
          | Setting        | Value |
          | Initial damage | 0.3   |
          | Failure number | 1.1   |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.47424874554865

    Scenario: Calculation with a non-equidistant time series and a negative start time
        Given the following adjusted hydraulic loads:
          | Time step |
          | -7200     |
          | -6840     |
          | -6120     |
          | -5040     |
          | -3600     |
          | -1800     |
          | 360       |
          | 2880      |
          | 5760      |
          | 9000      |
          | 12600     |
          | 16560     |
          | 20880     |
          | 25560     |
          | 30600     |
          | 36000     |
          | 43200     |
        When I run the grass wave run-up Rayleigh discrete calculation
        Then the damage is 1.17363142829280