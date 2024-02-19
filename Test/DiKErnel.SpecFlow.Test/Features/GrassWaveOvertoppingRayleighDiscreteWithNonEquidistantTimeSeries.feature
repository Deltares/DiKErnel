Feature: GrassWaveOvertoppingRayleighDiscrete with non-equidistant time series
  As a user I want to perform grass wave overtopping calculations with a non-equidistant time series based on Rayleigh discrete.

  Background:
    Given the following time steps and hydraulic loads:
      | Time step | Water level | Wave height Hm0 | Wave period Tm10 | Wave direction |
      | 0         | 5.7         | 2.05            | 5.2              | 350            |
      | 3600      | 6.2         | 2.1             | 5.23             | 352            |
      | 7200      | 6.8         | 2.15            | 5.26             | 354            |
      | 10800     | 6.8         | 2.2             | 5.29             | 356            |
      | 14400     | 6.8         | 2.25            | 5.32             | 358            |
      | 21600     | 6.7         | 2.3             | 5.35             | 0              |
      | 32400     | 6.6         | 2.35            | 5.38             | 2              |
      | 46800     | 6.4         | 2.4             | 5.41             | 4              |
      | 50400     | 6.2         | 2.45            | 5.44             | 6              |
      | 54000     | 6.1         | 2.5             | 5.47             | 8              |
      | 57600     | 6           | 2.55            | 5.5              | 10             |
      | 75600     | 5.7         | 2.6             | 5.53             | 12             |
      | 79200     |             |                 |                  |                |
    And the following dike profile and a dike orientation of 0:
      | X     | Z     | Roughness coefficient |
      | -5    | -4    | 1                     |
      | -1.73 | -2.89 | 1                     |
      | 33.82 | 6.03  | 0.9                   |
      | 38.16 | 6.31  | 0.8                   |
      | 47.34 | 8.64  | 1                     |
      | 52    | 8.7   | 1                     |
      | 70    | 5     | 1                     |
      | 85    | 1     | 1                     |
      | 95    | 0     |                       |
    And the following dike profile points:
      | Outer toe | Crest outer berm | Notch outer berm | Outer crest | Inner crest | Inner toe |
      | -1.73     | 33.82            | 38.16            | 47.34       | 52          | 85        |
    And the following calculation settings:
      | Setting                            | Value    |
      | Position                           | 60       |
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

  Scenario: Default
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the damage is 1.99284873782755
    And the rounded time of failure is 33915

  Scenario: Adjusted position and dike height
    Given the following calculation settings are adjusted:
      | Setting     | Value |
      | Position    | 50    |
      | Dike height | 6.7   |
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the damage is 12.99435588540268
    And the rounded time of failure is 23118

  Scenario: Adjusted calculation settings
    Given the following calculation settings are adjusted:
      | Setting               | Value |
      | Initial damage        | 0.9   |
      | Number of fixed waves | 15000 |
      | Dike height           | 9     |
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the damage is 1.03611132410722
    And the rounded time of failure is 48552

  Scenario: Robustness edge case
    Given the following calculation settings are adjusted:
      | Setting                            | Value |
      | Position                           | 50    |
      | Initial damage                     | 0.6   |
      | Critical cumulative overload       | 7500  |
      | Critical front velocity            | 5.5   |
      | Increased load transition alfa M   | 1.25  |
      | Reduced strength transition alfa S | 1.33  |
      | Average number of waves Ctm        | 0.85  |
      | Number of fixed waves              | 15000 |
      | Front velocity Cwo                 | 1.6   |
      | Acceleration alfa A crest          | 1.1   |
      | Acceleration alfa A inner slope    | 1.5   |
    When I run the grass wave overtopping Rayleigh discrete calculation
    Then the damage is 0.40767273974729
    And the rounded time of failure is undefined


