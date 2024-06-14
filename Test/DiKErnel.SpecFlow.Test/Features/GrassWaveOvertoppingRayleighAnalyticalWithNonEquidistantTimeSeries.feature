Feature: Grass wave overtopping Rayleigh analytical with non-equidistant time series
As a user I want to perform grass wave overtopping calculations with a non-equidistant time series based on Rayleigh analytical.

    Background:
        Given the following hydraulic loads:
          | Time step | Water level | Wave height | Wave period | Wave direction |
          | 0         | 5.7         | 2.05        | 5.2         | 350            |
          | 3600      | 6.2         | 2.1         | 5.23        | 352            |
          | 7200      | 6.8         | 2.15        | 5.26        | 354            |
          | 10800     | 6.8         | 2.2         | 5.29        | 356            |
          | 14400     | 6.8         | 2.25        | 5.32        | 358            |
          | 21600     | 6.7         | 2.3         | 5.35        | 0              |
          | 32400     | 6.6         | 2.35        | 5.38        | 2              |
          | 46800     | 6.4         | 2.4         | 5.41        | 4              |
          | 50400     | 6.2         | 2.45        | 5.44        | 6              |
          | 54000     | 6.1         | 2.5         | 5.47        | 8              |
          | 57600     | 6           | 2.55        | 5.5         | 10             |
          | 75600     | 5.7         | 2.6         | 5.53        | 12             |
          | 79200     | N.A.        | N.A.        | N.A.        | N.A.           |
        And the following dike geometry:
          | X     | Z     | Roughness coefficient |
          | -5    | -4    | 1                     |
          | -1.73 | -2.89 | 1                     |
          | 33.82 | 6.03  | 0.9                   |
          | 38.16 | 6.31  | 0.8                   |
          | 47.34 | 8.64  | 1                     |
          | 52    | 8.7   | 1                     |
          | 70    | 5     | 1                     |
          | 85    | 1     | 1                     |
          | 95    | 0     | N.A.                  |
        And the following dike properties:
          | Property    | Value |
          | Orientation | 0     |
        And the following characteristic points:
          | Characteristic point | Value |
          | Outer toe            | -1.73 |
          | Crest outer berm     | 33.82 |
          | Notch outer berm     | 38.16 |
          | Outer crest          | 47.34 |
          | Inner crest          | 52    |
          | Inner toe            | 85    |
        And the following calculation settings:
          | Setting                      | Value    |
          | Position                     | 60       |
          | Top layer type               | Open sod |
          | Initial damage               | 0        |
          | Critical cumulative overload | 7000     |
          | Critical front velocity      | 4.3      |
          | Increased load transition    | 1        |
          | Reduced strength transition  | 1        |
          | Failure number               | 1        |
          | Factor Ctm                   | 0.92     |
          | Front velocity               | 1.45     |
          | Acceleration crest           | 1        |
          | Acceleration inner slope     | 1.4      |

    Scenario: Default calculation
        When I run the grass wave overtopping Rayleigh analytical calculation
        Then the damage is 2.0041100577671633
        And the rounded time of failure is 33780

    Scenario: Calculation with adjusted position and dike height
        Given the following adjusted calculation settings:
          | Setting     | Value |
          | Position    | 50    |
          | Dike height | 6.7   |
        When I run the grass wave overtopping Rayleigh analytical calculation
        Then the damage is 13.00041443419839
        And the rounded time of failure is 23116

    Scenario: Calculation with adjusted calculation settings
        Given the following adjusted calculation settings:
          | Setting        | Value |
          | Position       | 50    |
          | Initial damage | 0.9   |
          | Dike height    | 9     |
        When I run the grass wave overtopping Rayleigh analytical calculation
        Then the damage is 1.038995100892069
        And the rounded time of failure is 47583

    Scenario: Robustness edge case
        Given the following adjusted calculation settings:
          | Setting                      | Value |
          | Position                     | 50    |
          | Critical cumulative overload | 7500  |
          | Critical front velocity      | 5.5   |
          | Increased load transition    | 1.25  |
          | Reduced strength transition  | 1.33  |
          | Factor Ctm                   | 0.85  |
          | Front velocity               | 1.6   |
          | Acceleration crest           | 1.1   |
          | Acceleration inner slope     | 1.5   |
        When I run the grass wave overtopping Rayleigh analytical calculation
        Then the damage is 0.4134930294528225
        And the rounded time of failure is undefined