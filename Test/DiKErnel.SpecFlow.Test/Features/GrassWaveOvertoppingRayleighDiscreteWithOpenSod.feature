Feature: GrassWaveOvertoppingRayleighDiscrete with open sod
  As a user I want to perform grass wave overtopping calculations with an open sod based on Rayleigh discrete.

  Background:
    Given the following time steps and hydraulic loads:
      | Time step | Water level | Wave height Hm0 | Wave period Tm10 | Wave direction |
      | 0         | 5           | 2.35            | 5.2              | 350            |
      | 3600      | 5.1         | 2.4             | 5.23             | 352            |
      | 7200      | 5.2         | 2.45            | 5.26             | 354            |
      | 10800     | 5.3         | 2.5             | 5.29             | 356            |
      | 14400     | 5.4         | 2.55            | 5.32             | 358            |
      | 18000     | 5.5         | 2.6             | 5.35             | 0              |
      | 21600     | 5.6         | 2.65            | 5.38             | 2              |
      | 25200     | 5.7         | 2.7             | 5.41             | 4              |
      | 28800     | 5.7         | 2.75            | 5.44             | 6              |
      | 32400     | 5.6         | 2.8             | 5.47             | 8              |
      | 36000     | 5.5         | 2.85            | 5.5              | 10             |
      | 39600     | 5.4         | 2.9             | 5.53             | 12             |
      | 43200     | 5.3         | 2.95            | 5.56             | 14             |
      | 46800     | 5.2         | 3               | 5.59             | 16             |
      | 50400     | 5.1         | 3.05            | 5.62             | 18             |
      | 54000     | 5           | 3.1             | 5.65             | 20             |
      | 57600     |             |                 |                  |                |
    And the following dike profile and a dike orientation of 0:
      | X  | Z    | Roughness coefficient |
      | 0  | -0.1 | 1                     |
      | 5  | 0    | 1                     |
      | 30 | 7.5  | 0.8                   |
      | 31 | 7.6  | 0.8                   |
      | 34 | 7.7  | 0.8                   |
      | 35 | 7.4  | 0.8                   |
      | 45 | 5    | 0.8                   |
      | 60 | 0.5  | 0.8                   |
      | 70 | 0.5  |                       |
    And the following dike profile points:
      | Outer toe | Outer crest | Inner crest | Inner toe |
      | 5         | 30          | 35          | 60        |
    And the following calculation settings:
      | Setting                            | Value    |
      | Position                           | 40       |
      | Top layer type                     | Open sod |
      | Initial damage                     | 0        |
      | Failure number                     | 1        |
      | Critical cumulative overload       | 7000     |
      | Critical front velocity            | 4.3      |
      | Increased load transition alfa M   | 1        |
      | Reduced strength transition alfa S | 1        |
      | Average number of waves Ctm        | 0.92     |
      | Number of fixed waves              | 10000    |
      | Front velocity Cwo                 | 1.45     |
      | Acceleration alfa A crest          | 1        |
      | Acceleration alfa A inner slope    | 1.4      |

  Scenario: Testcase 1 - Default
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the damage is 24.68131275788636
    And the rounded time of failure is 5311

  Scenario: Testcase 2 - Adjusted position and dike height:
    Given the following calculation settings are adjusted:
      | Setting     | Value |
      | Position    | 30    |
      | Dike height | 9.5   |
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the damage is 0.86861734396724
    And the rounded time of failure is undefined

  Scenario: Testcase 3 - Adjusted position, dike height and transition
    Given the following calculation settings are adjusted:
      | Setting                          | Value |
      | Position                         | 35    |
      | Dike height                      | 9.6   |
      | Increased load transition alfa M | 1.2   |
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the damage is 1.11910058435611
    And the rounded time of failure is 51672