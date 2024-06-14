Feature: Grass wave impact
As a user I want to perform grass wave impact calculations.

    Background:
        Given the following hydraulic loads:
          | Time step | Water level | Wave height | Wave period | Wave direction |
          | 0         | 0.5         | 0.5         | 3           | 0              |
          | 900       | 0.55        | 0.6         | 3           | 15             |
          | 1800      | 0.6         | 0.65        | 3           | 30             |
          | 2700      | 0.65        | 0.7         | 3           | 45             |
          | 3600      | 0.7         | 0.75        | 3           | 60             |
          | 4500      | 0.75        | 0.8         | 3           | 70             |
          | 5400      | 0.8         | 0.85        | 3           | 75             |
          | 6300      | 0.85        | 0.9         | 3           | 70             |
          | 7200      | 0.9         | 0.95        | 3           | 60             |
          | 8100      | 0.95        | 1           | 3           | 45             |
          | 9000      | 1           | 1.1         | 3           | 30             |
          | 9900      | 1.03        | 1.1         | 3           | 15             |
          | 10800     | 1.03        | 1.15        | 3           | 0              |
          | 11700     | 1           | 1.2         | 3           | 0              |
          | 12600     | 0.95        | 1.23        | 3           | 0              |
          | 13500     | 0.9         | 1.2         | 3           | 0              |
          | 14400     | 0.85        | 1.15        | 3           | 0              |
          | 15300     | 0.8         | 1.1         | 3           | 0              |
          | 16200     | 0.75        | 1           | 3           | 0              |
          | 17100     | 0.7         | 1           | 3           | 0              |
          | 18000     | 0.65        | 0.95        | 3           | 0              |
          | 18900     | 0.6         | 0.95        | 3           | 0              |
          | 19800     | 0.55        | 0.9         | 3           | 0              |
          | 20700     | 0.5         | 0.9         | 3           | 0              |
          | 21600     | N.A.        | N.A.        | N.A.        | N.A.           |
        And the following dike geometry:
          | X  | Z    |
          | 5  | -1   |
          | 55 | 11.5 |
        And the following dike properties:
          | Property    | Value |
          | Orientation | 0     |
        And the following characteristic points:
          | Characteristic point | Value |
          | Outer toe            | 5     |
          | Outer crest          | 55    |
        And the following calculation settings:
          | Setting        | Value      |
          | Position       | 11         |
          | Top layer type | Closed sod |

    Scenario: Default calculation with closed sod
        When I run the grass wave impact calculation
        Then the damage is 1.29228078520671
        And the rounded time of failure is 14375

    Scenario: Default calculation with open sod
        Given the following adjusted hydraulic loads:
          | Wave height |
          | 0.3         |
          | 0.4         |
          | 0.45        |
          | 0.5         |
          | 0.55        |
          | 0.6         |
          | 0.65        |
          | 0.7         |
          | 0.75        |
          | 0.8         |
          | 0.9         |
          | 0.9         |
          | 0.95        |
          | 1           |
          | 1.03        |
          | 1           |
          | 0.95        |
          | 0.9         |
          | 0.8         |
          | 0.8         |
          | 0.75        |
          | 0.75        |
          | 0.7         |
          | 0.7         |
        And the following adjusted calculation settings:
          | Setting        | Value    |
          | Top layer type | Open sod |
        When I run the grass wave impact calculation
        Then the damage is 1.74141684707082
        And the rounded time of failure is 13466

    Scenario: Calculation with adjusted sod
        Given the following adjusted calculation settings:
          | Setting     | Value    |
          | Time line a | 1.1      |
          | Time line b | -0.00003 |
          | Time line c | 0.3      |
        When I run the grass wave impact calculation
        Then the damage is 1.34810580442111
        And the rounded time of failure is 15809

    Scenario: Calculation with adjusted initial damage and failure number
        Given the following adjusted calculation settings:
          | Setting        | Value |
          | Initial damage | 0.4   |
          | Failure number | 1.2   |
        When I run the grass wave impact calculation
        Then the damage is 1.69228078520671
        And the rounded time of failure is 13429

    Scenario: Calculation with adjusted wave angle impact
        Given the following adjusted calculation settings:
          | Setting             | Value |
          | Wave angle impact n | 0.8   |
          | Wave angle impact q | 0.5   |
          | Wave angle impact r | 40    |
        When I run the grass wave impact calculation
        Then the damage is 1.28595658264855
        And the rounded time of failure is 14416

    Scenario: Calculation with adjusted impact zone
        Given the following adjusted calculation settings:
          | Setting             | Value |
          | Upper limit loading | 0.1   |
          | Lower limit loading | 0.45  |
        When I run the grass wave impact calculation
        Then the damage is 1.07849231778936
        And the rounded time of failure is 17130

    Scenario: Calculation with a non-equidistant time series and a negative start time
        Given the following adjusted hydraulic loads:
          | Time step |
          | -3600     |
          | -3510     |
          | -3330     |
          | -3060     |
          | -2700     |
          | -2250     |
          | -1710     |
          | -1080     |
          | -360      |
          | 450       |
          | 1350      |
          | 2340      |
          | 3420      |
          | 4590      |
          | 5850      |
          | 7200      |
          | 8640      |
          | 10170     |
          | 11790     |
          | 13500     |
          | 15300     |
          | 17190     |
          | 19170     |
          | 21240     |
          | 21600     |
        When I run the grass wave impact calculation
        Then the damage is 1.91616541078065
        And the rounded time of failure is 6938