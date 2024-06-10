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

    Scenario: Calculation with a varying outer slope and a berm
        Given the following adjusted dike geometry:
          | X    | Z   |
          | 0    | 0.0 |
          | 6.4  | 1.6 |
          | 12.4 | 1.8 |
          | 30   | 7.5 |
        And the following adjusted characteristic points:
          | Setting          | Value |
          | Crest outer berm | 6.4   |
          | Notch outer berm | 12.4  |
        And the following adjusted calculation settings:
          | Setting             | Value |
          | Thickness top layer | 0.3   |
        When I run the natural stone wave impact calculation
        Then the damage is 1.69080696566877
        And the rounded time of failure is 5605

    Scenario: Calculation with a varying outer slope and no berm
        Given the following adjusted dike geometry:
          | X    | Z   |
          | 0    | 0.0 |
          | 6.4  | 1.6 |
          | 12.4 | 1.8 |
          | 30   | 7.5 |
        And the following adjusted calculation settings:
          | Setting             | Value |
          | Thickness top layer | 0.3   |
        When I run the natural stone wave impact calculation
        Then the damage is 1.19007096598986
        And the rounded time of failure is 7941

    Scenario: Calculation with adjusted wave angle impact
        Given the following adjusted calculation settings:
          | Setting                   | Value |
          | Wave angle impact Betamax | 30    |
        When I run the natural stone wave impact calculation
        Then the damage is 1.23139438041740
        And the rounded time of failure is 7272

    Scenario: Calculation with adjusted hydraulic loads and impact zone
        Given the following adjusted hydraulic loads:
          | Water level | Wave height | Wave period | Wave direction |
          | 1.27        | 1.5         | 6           | 0              |
          | 1.271       | 1.5         | 6           | 0              |
          | 1.272       | 1.5         | 6           | 0              |
          | 1.273       | 1.5         | 6           | 0              |
          | 2.531       | 1.5         | 6           | 0              |
          | 2.532       | 1.5         | 6           | 0              |
          | 2.533       | 1.5         | 6           | 0              |
          | 2.534       | 1.5         | 6           | 0              |
          | 2.535       | 1.5         | 6           | 0              |
          | 2.536       | 1.5         | 6           | 0              |
          | 2.537       | 1.5         | 6           | 0              |
          | 2.538       | 1.5         | 6           | 0              |
        And the following adjusted calculation settings:
          | Setting                               | Value |
          | Thickness top layer                   | 0.3   |
          | Upper limit loading Aul               | 0.08  |
          | Upper limit loading Bul               | 0.7   |
          | Upper limit loading Cul               | 3.5   |
          | Lower limit loading All               | 0.08  |
          | Lower limit loading Bll               | 0.15  |
          | Lower limit loading Cll               | 5.5   |
          | Distance maximum wave elevation Asmax | 0.5   |
          | Distance maximum wave elevation Bsmax | 0.8   |
          | Normative width of wave impact Awi    | 1.1   |
          | Normative width of wave impact Bwi    | 0.15  |
        When I run the natural stone wave impact calculation
        Then the damage is 1.09941459712288
        And the rounded time of failure is 3893

    Scenario: Calculation with a non-equidistant time series and a negative start time
        Given the following adjusted hydraulic loads:
          | Time step |
          | -3600     |
          | -3420     |
          | -3060     |
          | -2520     |
          | -1800     |
          | -900      |
          | 180       |
          | 1440      |
          | 2880      |
          | 4500      |
          | 6300      |
          | 8280      |
          | 10800     |
        When I run the natural stone wave impact calculation
        Then the damage is 1.30817784966504
        And the rounded time of failure is 2914

    Scenario: Calculation with adjusted slope settings
        Given the following adjusted dike geometry:
          | X    | Z   |
          | 0    | 0.0 |
          | 6.4  | 1.6 |
          | 12.4 | 1.8 |
          | 30   | 7.5 |
        And the following adjusted characteristic points:
          | Setting          | Value |
          | Crest outer berm | 6.4   |
          | Notch outer berm | 12.4  |
        And the following adjusted calculation settings:
          | Setting               | Value |
          | Thickness top layer   | 0.3   |
          | Slope upper level Aus | 0.5   |
          | Slope lower level Als | 1.0   |
        When I run the natural stone wave impact calculation
        Then the damage is 1.69466545304923
        And the rounded time of failure is 5570