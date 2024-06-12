Feature: Grass wave overtopping Rayleigh analytical with closed sod
As a user I want to perform grass wave overtopping calculations with a closed sod based on Rayleigh analytical.

    Background:
        Given the following hydraulic loads:
          | Time step | Water level | Wave height | Wave period | Wave direction |
          | 0         | 5.5         | 1.9         | 4.7         | 350            |
          | 3600      | 5.6         | 1.95        | 4.73        | 352            |
          | 7200      | 5.7         | 2           | 4.76        | 354            |
          | 10800     | 5.8         | 2.05        | 4.79        | 356            |
          | 14400     | 5.9         | 2.1         | 4.82        | 358            |
          | 18000     | 6           | 2.15        | 4.85        | 0              |
          | 21600     | 6.1         | 2.2         | 4.88        | 2              |
          | 25200     | 6.2         | 2.25        | 4.91        | 4              |
          | 28800     | 6.2         | 2.3         | 4.94        | 6              |
          | 32400     | 6.1         | 2.35        | 4.97        | 8              |
          | 36000     | 6           | 2.4         | 5           | 10             |
          | 39600     | 5.9         | 2.45        | 5.03        | 12             |
          | 43200     | 5.8         | 2.5         | 5.06        | 14             |
          | 46800     | 5.7         | 2.55        | 5.09        | 16             |
          | 50400     | 5.6         | 2.6         | 5.12        | 18             |
          | 54000     | 5.5         | 2.65        | 5.15        | 20             |
          | 57600     | N.A.        | N.A.        | N.A.        | N.A.           |
        And the following dike geometry:
          | X  | Z    | Roughness coefficient |
          | 0  | -0.1 | 1                     |
          | 5  | 0    | 1                     |
          | 15 | 3    | 0.75                  |
          | 22 | 3.2  | 0.5                   |
          | 30 | 7.5  | 0.8                   |
          | 31 | 7.6  | 0.8                   |
          | 34 | 7.7  | 0.8                   |
          | 35 | 7.4  | 0.8                   |
          | 45 | 5    | 0.8                   |
          | 60 | 0.5  | 0.8                   |
          | 70 | 0.5  | N.A.                  |
        And the following dike properties:
          | Property    | Value |
          | Orientation | 0     |
        And the following characteristic points:
          | Characteristic point | Value |
          | Outer toe            | 5     |
          | Crest outer berm     | 15    |
          | Notch outer berm     | 22    |
          | Outer crest          | 30    |
          | Inner crest          | 35    |
          | Inner toe            | 60    |
        And the following calculation settings:
          | Setting                      | Value      |
          | Position                     | 50         |
          | Top layer type               | Closed sod |
          | Initial damage               | 0.02       |
          | Critical cumulative overload | 7000       |
          | Critical front velocity      | 6.6        |
          | Increased load transition    | 1          |
          | Reduced strength transition  | 1          |
          | Failure number               | 1          |
          | Factor Ctm                   | 0.92       |
          | Front velocity               | 1.45       |
          | Acceleration crest           | 1          |
          | Acceleration inner slope     | 1.4        |

    Scenario: Default
        When I run the grass wave overtopping Rayleigh analytical calculation
        Then the damage is 1.4908105117027979
        And the rounded time of failure is 33817

    Scenario: Adjusted position
        Given the following adjusted calculation settings:
          | Setting  | Value |
          | Position | 33    |
        When I run the grass wave overtopping Rayleigh analytical calculation
        Then the damage is 0.07776240092792007
        And the rounded time of failure is undefined

    Scenario Outline: Adjusted position and various dike heights
        Given the following adjusted calculation settings:
          | Setting  | Value |
          | Position | 33    |
        And the dike height is adjusted to <Dike height>
        When I run the grass wave overtopping Rayleigh analytical calculation
        Then the damage is <Damage>
        And the rounded time of failure is undefined

        Examples:
          | Dike height | Damage              |
          | 8           | 0.04233958224615242 |
          | 5.65        | 0.3619578997839564  |