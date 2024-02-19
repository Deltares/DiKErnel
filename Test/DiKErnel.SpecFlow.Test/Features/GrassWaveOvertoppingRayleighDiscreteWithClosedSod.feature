Feature: GrassWaveOvertoppingRayleighDiscrete with closed sod
  As a user I want to perform grass wave overtopping calculations with a closed sod based on Rayleigh discrete.

  Background:
    Given the following time steps and hydraulic loads:
      | Time step | Water level | Wave height Hm0 | Wave period Tm10 | Wave direction |
      | 0         | 5.5         | 1.9             | 4.7              | 350            |
      | 3600      | 5.6         | 1.95            | 4.73             | 352            |
      | 7200      | 5.7         | 2               | 4.76             | 354            |
      | 10800     | 5.8         | 2.05            | 4.79             | 356            |
      | 14400     | 5.9         | 2.1             | 4.82             | 358            |
      | 18000     | 6           | 2.15            | 4.85             | 0              |
      | 21600     | 6.1         | 2.2             | 4.88             | 2              |
      | 25200     | 6.2         | 2.25            | 4.91             | 4              |
      | 28800     | 6.2         | 2.3             | 4.94             | 6              |
      | 32400     | 6.1         | 2.35            | 4.97             | 8              |
      | 36000     | 6           | 2.4             | 5                | 10             |
      | 39600     | 5.9         | 2.45            | 5.03             | 12             |
      | 43200     | 5.8         | 2.5             | 5.06             | 14             |
      | 46800     | 5.7         | 2.55            | 5.09             | 16             |
      | 50400     | 5.6         | 2.6             | 5.12             | 18             |
      | 54000     | 5.5         | 2.65            | 5.15             | 20             |
      | 57600     |             |                 |                  |                |
    And the following dike profile and a dike orientation of 0:
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
      | 60 | 0.5  |                       |
    And the following dike profile points:
      | Outer toe | Crest outer berm | Notch outer berm | Outer crest | Inner crest | Inner toe |
      | 5         | 15               | 22               | 30          | 35          | 60        |
    And the following calculation settings:
      | Setting                            | Value      |
      | Position                           | 50         |
      | Top layer type                     | Closed sod |
      | Initial damage                     | 0.02       |
      | Failure number                     | 1          |
      | Critical cumulative overload       | 7000       |
      | Critical front velocity            | 6.6        |
      | Increased load transition alfa M   | 1          |
      | Reduced strength transition alfa S | 1          |
      | Average number of waves Ctm        | 0.92       |
      | Number of fixed waves              | 10000      |
      | Front velocity Cwo                 | 1.45       |
      | Acceleration alfa A crest          | 1          |
      | Acceleration alfa A inner slope    | 1.4        |

  Scenario: Testcase 1 - Default
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the damage is 1.48214256643614
    And the expected rounded time of failure is 33913

  Scenario: Testcase 2 - Calculation with different position
    Given the following calculation settings are adjusted:
      | Setting  | Value |
      | Position | 33    |
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the damage is 0.07514904750839

  Scenario: Testcase 3 - Calculation with different position and various dike heights
    Given the following calculation settings are adjusted:
      | Setting  | Value |
      | Position | 33    |
    And I change the property Dike height to a value of <Dike height>
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the output value for <Damage> is

    Examples:
      | Dike height | Damage           |
      | 8           | 0.04031327976012 |
      | 5.65        | 0.36080579320214 |
