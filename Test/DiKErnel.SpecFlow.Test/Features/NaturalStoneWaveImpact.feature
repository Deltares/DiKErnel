Feature: Natural stone wave impact
As a user I want to perform natural stone wave impact calculations.

    Background:
        Given the following hydraulic loads:
          | Time step | Water level | Wave height | Wave period | Wave direction |
          | 0         | 1.4         | 1.0         | 5.5         | 30.0           |
          | 900       | 1.6         | 1.2         | 6.0         | 60.0           |
          | 1800      | 1.7         | 1.2         | 6.5         | 90.0           |
          | 2700      | 1.8         | 1.3         | 7.0         | 75.0           |
          | 3600      | 2.0         | 1.4         | 7.0         | 60.0           |
          | 4500      | 2.1         | 1.3         | 7.5         | 45.0           |
          | 5400      | 2.1         | 1.6         | 8.0         | 30.0           |
          | 6300      | 2.4         | 1.7         | 8.0         | 15.0           |
          | 7200      | 2.0         | 2.4         | 8.5         | 0.0            |
          | 8100      | 1.9         | 2.2         | 8.0         | 0.0            |
          | 9000      | 1.6         | 1.8         | 7.0         | 0.0            |
          | 9900      | 1.4         | 1.2         | 6.0         | 0.0            |
          | 10800     | N.A.        | N.A.        | N.A.        | N.A.           |
        And the following dike geometry:
          | X  | Z   |
          | 0  | 0   |
          | 30 | 7.5 |
        And the following dike properties:
          | Property    | Value |
          | Orientation | 0     |
        And the following characteristic points:
          | Characteristic point | Value |
          | Outer toe            | 0     |
          | Outer crest          | 30    |
        And the following calculation settings:
          | Setting             | Value |
          | Position            | 6     |
          | Relative density    | 1.65  |
          | Thickness top layer | 0.4   |

    Scenario: Default
        When I run the natural stone wave impact calculation
        Then the damage is 1.23043545607545
        And the rounded time of failure is 7283

    Scenario: Calculation with adjusted calculation settings
        Given the following adjusted calculation settings:
          | Setting             | Value |
          | Relative density    | 1.6   |
          | Thickness top layer | 0.35  |
          | Initial damage      | 0.6   |
        When I run the natural stone wave impact calculation
        Then the damage is 1.45017739145779
        And the rounded time of failure is 6423

    Scenario: Calculation with adjusted values for the stability comparison
        Given the following adjusted calculation settings:
          | Setting             | Value  |
          | Thickness top layer | 0.25   |
          | Hydraulic load Xib  | 2.1    |
          | Hydraulic load Ap   | 6.68   |
          | Hydraulic load Bp   | 0      |
          | Hydraulic load Cp   | 0      |
          | Hydraulic load Np   | -0.723 |
          | Hydraulic load As   | 12     |
          | Hydraulic load Bs   | 1.5    |
          | Hydraulic load Cs   | -3.12  |
          | Hydraulic load Ns   | -1.5   |
          When I run the natural stone wave impact calculation
          Then the damage is 1.07139251615967
          And the rounded time of failure is 7815

    Scenario: 4 Calculation with a varying buitentalud and a berm

    Scenario: 5 Calculation with a varying buitentalud and no berm

    Scenario: 6 Calculation with an adjusted setting for the impact angle

    Scenario: 7 Calculation with an adjusted load setting

    Scenario: 8 Calculation with a non-equidistant time series and a negative start time

    Scenario: 9 Calculation with adjusted slope settings