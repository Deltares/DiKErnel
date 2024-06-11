Feature: Asphalt wave impact
As a user I want to perform asphalt wave impact calculations with adjusted depth factors.

    Background:
        Given the following hydraulic loads:
          | Time step | Water level | Wave height | Wave period | Wave direction |
          | 0         | 2           | 1           | 4           | 0              |
          | 3600      | 2.2         | 1.5         | 5           | 0              |
          | 7200      | 2.4         | 2           | 5.5         | 0              |
          | 10800     | 2.6         | 2.4         | 6           | 0              |
          | 14400     | 2.8         | 2.5         | 6.2         | 0              |
          | 18000     | 3           | 2.6         | 6.3         | 0              |
          | 21600     | 2.8         | 2.7         | 6.5         | 0              |
          | 25200     | 2.6         | 2.6         | 6.6         | 0              |
          | 28800     | 2.4         | 2.5         | 6.3         | 0              |
          | 32400     | 2           | 2.4         | 6.2         | 0              |
          | 36000     | N.A.        | N.A.        | N.A.        | N.A.           |
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
          | Setting                     | Value |
          | Position                    | 10    |
          | Flexural strength           | 1.6   |
          | Soil elasticity             | 55    |
          | Thickness upper layer       | 0.40  |
          | Elastic modulus upper layer | 18000 |
        And the following depth factors:
          | Depth  | Probability |
          | -1     | 0.0244      |
          | -0.875 | 0.0544      |
          | -0.75  | 0.0938      |
          | -0.625 | 0.1407      |
          | -0.5   | 0.1801      |
          | -0.375 | 0.1632      |
          | -0.25  | 0.1426      |
          | -0.125 | 0.0994       |
          | 0      | 0.06        |
          | 0.125  | 0.0244      |
          | 0.25   | 0.0169      |

    Scenario: Default
        When I run the asphalt wave impact calculation
        Then the damage is 1.12993952544265
        And the rounded time of failure is 25720

    Scenario: Calculation with 2 layers
        Given the following adjusted calculation settings:
          | Setting                   | Value |
          | Thickness upper layer     | 0.15  |
          | Thickness sub layer       | 0.18  |
          | Elastic modulus sub layer | 15000 |
        When I run the asphalt wave impact calculation
        Then the damage is 1.53983898504504
        And the rounded time of failure is 23511

    Scenario: Adjusted impact factors
        Given the following adjusted calculation settings:
          | Setting               | Value |
          | Thickness upper layer | 0.30  |
        And the following adjusted impact factors:
          | Impact | Probability |
          | 0.4    | 0.349       |
          | 0.8    | 0.123       |
          | 1.2    | 0.152       |
          | 1.6    | 0.125       |
          | 2.0    | 0.088       |
          | 2.4    | 0.059       |
          | 2.8    | 0.038       |
          | 3.2    | 0.024       |
          | 3.6    | 0.016       |
          | 4.0    | 0.01        |
          | 4.4    | 0.007       |
          | 4.8    | 0.004       |
          | 5.2    | 0.003       |
          | 5.6    | 0.002       |
          | 6.0    | 0.001       |
        When I run the asphalt wave impact calculation
        Then the damage is 1.13998469842777
        And the rounded time of failure is 25237

    Scenario: Adjusted depth factors
        Given the following adjusted calculation settings:
          | Setting               | Value |
          | Thickness upper layer | 0.38  |
        And the following adjusted depth factors:
          | Depth | Probability |
          | -0.99 | 0.00009647  |
          | -0.9  | 0.0007544   |
          | -0.81 | 0.004299    |
          | -0.72 | 0.01785     |
          | -0.63 | 0.05403     |
          | -0.54 | 0.1192      |
          | -0.45 | 0.1916      |
          | -0.36 | 0.2244      |
          | -0.27 | 0.1916      |
          | -0.18 | 0.1192      |
          | -0.09 | 0.05403     |
          | 0.0   | 0.01785     |
          | 0.09  | 0.004299    |
          | 0.18  | 0.0007544   |
          | 0.27  | 0.00009647  |
        When I run the asphalt wave impact calculation
        Then the damage is 1.33022336665883
        And the rounded time of failure is 22915

    Scenario: Adjusted width factors
        Given the following adjusted calculation settings:
          | Setting               | Value |
          | Thickness upper layer | 0.45  |
        And the following adjusted width factors:
          | Width | Probability |
          | 0.1   | 0.0         |
          | 0.25  | 0.018       |
          | 0.4   | 0.09        |
          | 0.55  | 0.153       |
          | 0.7   | 0.168       |
          | 0.85  | 0.15        |
          | 1.0   | 0.119       |
          | 1.15  | 0.089       |
          | 1.3   | 0.064       |
          | 1.45  | 0.045       |
          | 1.6   | 0.031       |
          | 1.75  | 0.022       |
          | 1.9   | 0.015       |
          | 2.05  | 0.01        |
          | 2.2   | 0.007       |
        When I run the asphalt wave impact calculation
        Then the damage is 1.47912119894063
        And the rounded time of failure is 23892

    Scenario: Calculation with a non-equidistant time series and a negative start time
        Given the following adjusted hydraulic loads:
          | Time step |
          | -3600     |
          | -2880     |
          | -1440     |
          | 720       |
          | 3600      |
          | 7200      |
          | 11520     |
          | 16560     |
          | 22320     |
          | 28800     |
          | 36000     |
        When I run the asphalt wave impact calculation
        Then the damage is 1.46369311689636
        And the rounded time of failure is 15187

    Scenario: Calculation with a berm
        Given the following adjusted dike geometry:
          | X  | Z   |
          | 0  | 0   |
          | 8  | 2.0 |
          | 17 | 3.0 |
          | 35 | 7.5 |
        And the following adjusted characteristic points:
          | Characteristic point | Value |
          | Crest outer berm     | 8     |
          | Notch outer berm     | 17    |
          | Outer crest          | 35    |
        And the following adjusted calculation settings:
          | Setting  | Value |
          | Position | 12.5  |
        When I run the asphalt wave impact calculation
        Then the damage is 1.12993952544265
        And the rounded time of failure is 25720