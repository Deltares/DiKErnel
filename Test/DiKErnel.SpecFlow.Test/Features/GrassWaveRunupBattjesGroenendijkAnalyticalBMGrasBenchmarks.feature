Feature: Grass wave run-up Battjes-Groenendijk analytical with BM Gras benchmarks
  As a user I want to perform grass wave run-up calculations based on Battjes-Groenendijk analytical.

  The following testcases correspond with BM Gras benchmarks.

  DiKErnel does not produce the exact same results as BM Gras. This is mainly due to the following differences:
  - BM Gras rounds the value of average number of waves to an integer. This is not the case in DiKErnel.
  - BM Gras uses an older version of DikesOvertopping (version 19.1.1).
  - BM Gras is a user interface and performs validation of input parameters. This is not the case in DiKErnel.

  Background:
    Given the following hydraulic loads:
      | Time step | Water level | Wave height | Wave period | Wave direction |
      | 0         | 0           | 1.5         | 4.2         | 0              |
      | 900       | N.A.        | N.A.        | N.A.        | N.A.           |
    And the following dike geometry:
      | X  | Z   | Roughness coefficient |
      | 0  | -10 | 1                     |
      | 40 | 0   | 1                     |
      | 80 | 10  | N.A.                  |
    And the following dike properties:
      | Property               | Value |
      | Orientation            | 0     |
      | Slope foreshore        | 0.004 |
      | Bottom level foreshore | -3    |
    And the following characteristic points:
      | Characteristic point | Value |
      | Outer toe            | 0     |
      | Outer crest          | 80    |
    And the following calculation settings:
      | Setting                     | Value      |
      | Position                    | 40.4       |
      | Top layer type              | Closed sod |
      | Initial damage              | 0          |
      | Increased load transition   | 1          |
      | Reduced strength transition | 1          |
      | Failure number              | 1          |
      | Factor Ctm                  | 3.85       |
      | Front velocity              | 1.1        |

  Scenario Outline: BM Gras benchmark 14 - Variable input of critical front velocity
    Given the critical front velocity is adjusted to <Critical front velocity>
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is <Damage>
    And the cumulative overload is <Cumulative overload>

    Examples:
      | Critical front velocity | Damage               | Cumulative overload  | Benchmark for BM Gras | BM Gras |
      | 3.5                     | 0.09912791114815     | 693.895378037038     | 698.202               | 698.151 |
      | 4                       | 0.08240815773892     | 576.8571041724706    | 588.477               | 588.395 |
      | 5.5                     | 0.00101603649308     | 7.11225545156877     | 7.162                 | 7.156   |
      | 6.5                     | 5.35959825332454e-09 | 3.75171877732718e-05 | 0                     | 0       |
      | 8                       | 0                    | 0                    | 0                     | 0       |

  Scenario Outline: BM Gras benchmark 15 - Variable input of level of interest
    Given the following adjusted dike geometry:
      | X     | Z   | Roughness coefficient |
      | 0     | -10 | 1                     |
      | 30.56 | 0   | 1                     |
      | 61.12 | 10  | N.A.                  |
    And the following adjusted characteristic points:
      | Characteristic point | Value |
      | Outer toe            | 0     |
      | Outer crest          | 61.12 |
    And the position is adjusted to <Position>
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is <Damage>
    And the cumulative overload is <Cumulative overload>

    Examples:
      | Position | Damage               | Cumulative overload  | Benchmark for BM Gras | BM Gras |
      | 30.56    | 0                    |                      | 0                     | 0       |
      | 33.616   | 0.00016098541128     | 1.12689787897988     | 1.136                 | 1.134   |
      | 36.672   | 0.00016098541128     | 1.12689787897949     | 1.136                 | 1.134   |
      | 39.728   | 1.97318711447270e-05 | 0.13812309801309     | 0.139                 | 0.139   |
      | 42.784   | 1.54966489327148e-11 | 1.08476542529003e-07 | 0                     | 0       |
      | 45.84    | 0                    | 0                    | 0                     | 0       |
      | 48.896   | 0                    | 0                    | 0                     | 0       |

  Scenario Outline: BM Gras benchmark 16 - Variable input of the slope of the bottom
  Remark: The value of the slope of the foreshore should be between 0.004 and 0.05. In this testcase, no validation
  of results is performed by DiKErnel. This is why DiKErnel produces results for every situation. The validation of
  results is however performed by BM Gras.

    Given the following adjusted dike geometry:
      | X     | Z   | Roughness coefficient |
      | 0     | -10 | 1                     |
      | 30.56 | 0   | 1                     |
      | 61.12 | 10  | N.A.                  |
    And the following adjusted characteristic points:
      | Characteristic point | Value |
      | Outer toe            | 0     |
      | Outer crest          | 61.12 |
    And the following adjusted calculation settings:
      | Setting  | Value   |
      | Position | 30.8656 |
    And the slope foreshore is adjusted to <Slope foreshore>
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is <Damage>
    And the cumulative overload is <Cumulative overload>

    Examples:
      | Slope foreshore | Damage           | Cumulative overload | Benchmark for BM Gras | BM Gras |
      | 0               | 0.00013005426274 | 0.91037983920721    | 0.918                 | N.A.    |
      | 0.004           | 0.00016098541128 | 1.12689787897988    | 1.136                 | 1.134   |
      | 0.04            | 0.00190340540170 | 13.32383781191319   | 13.425                | 13.406  |
      | 0.1             | 0.00698241406394 | 48.876898447571     | 49.205                | N.A.    |
      | 0.4             | 0.00682008585304 | 47.74060097127521   | 48.062                | N.A.    |
      | 10              | 0.00682008585304 | 47.74060097127442   | 48.062                | N.A.    |
      | 100             | 0.00682008585304 | 47.74060097127442   | 48.062                | N.A.    |
      | 250             | 0.00682008585304 | 47.74060097127442   | 48.062                | N.A.    |

  Scenario Outline: BM Gras benchmark 17 - Variable input of water depth
  Remarks:
  - In BM Gras the value of water depth (water level - bottom level foreshore) must be > 0 and <= 10 m. This validation is not performed by DiKErnel.
  - When the value of water depth (water level - bottom level foreshore) equals 0 m, then division by zero occurs. No results are produced by DiKErnel (NaN) in this situation.

    Given the following adjusted dike geometry:
      | X     | Z   | Roughness coefficient |
      | 0     | -10 | 1                     |
      | 30.56 | 0   | 1                     |
      | 61.12 | 10  | N.A.                  |
    And the following adjusted characteristic points:
      | Characteristic point | Value |
      | Outer toe            | 0     |
      | Outer crest          | 61.12 |
    And the following adjusted calculation settings:
      | Setting  | Value   |
      | Position | 30.8656 |
    And the bottom level foreshore is adjusted to <Bottom level foreshore>
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is <Damage>
    And the cumulative overload is <Cumulative overload>

    Examples:
      | Bottom level foreshore | Damage            | Cumulative overload | Benchmark for BM Gras | BM Gras   |
      | 0                      | NaN               | NaN                 | 0                     | N.A.      |
      | -0.004                 | 18.89917220621742 | 132294.20544352196  | 133115.947            | N.A.      |
      | -0.04                  | 1.95306009187703  | 13671.4206431392    | 13756.388             | 13755.272 |
      | -0.1                   | 0.81770905700087  | 5723.963399006075   | 5729.582              | 5759.07   |
      | -0.4                   | 0.14644985047294  | 1025.1489533105942  | 1031.744              | 1031.437  |
      | -10                    | 0.00304808423136  | 21.33658961950446   | 21.469                | 21.453    |
      | -100                   | 0.00208943832562  | 14.62606827931352   | N.A.                  | N.A.      |
      | -250                   | 0.00203426448852  | 14.23985141963199   | N.A.                  | N.A.      |

  Scenario Outline: BM Gras benchmark 18 - Variable input of water depth and critical depth
  Remarks:
  - In BM Gras the value of water depth (water level - bottom level foreshore) must be > 0 and <= 10 m. This validation is not performed by DiKErnel.
  - When the value of water depth (water level - bottom level foreshore) equals 0 m, then division by zero occurs. No results are produced then by DiKErnel (NaN).

    Given the following adjusted dike geometry:
      | X     | Z   | Roughness coefficient |
      | 0     | -10 | 1                     |
      | 30.56 | 0   | 1                     |
      | 61.12 | 10  | N.A.                  |
    And the following adjusted characteristic points:
      | Characteristic point | Value |
      | Outer toe            | 0     |
      | Outer crest          | 61.12 |
    And the following adjusted calculation settings:
      | Setting  | Value   |
      | Position | 30.8656 |
    And the bottom level foreshore is adjusted to <Bottom level foreshore>
    And the critical cumulative overload is adjusted to <Critical cumulative overload>
    When I run the grass wave run-up Battjes-Groenendijk analytical calculation
    Then the damage is <Damage>
    And the cumulative overload is <Cumulative overload>

    Examples:
      | Bottom level foreshore | Critical cumulative overload | Damage              | Cumulative overload   | Benchmark for BM Gras | BM Gras   |
      | 0                      | 1000                         | NaN                 | NaN                   | 0                     | N.A.      |
      | -0.004                 | 1000                         | 132.29420544352197  | 132294.20544352196157 | 133115.947            | N.A.      |
      | -0.04                  | 100                          | 136.71420643139200  | 13671.42064313919946  | 13756.388             | 13755.272 |
      | -0.1                   | 10                           | 572.39633990060747  | 5723.96339900607472   | 5759.582              | 5759.07   |
      | -0.4                   | 1                            | 1025.14895331059415 | 1025.14895331059415   | 1031.744              | 1031.437  |
      | -10                    | 1                            | 21.33658961950446   | 21.33658961950446     | 21.469                | 21.453    |
      | -100                   | 1                            | 14.62606827931352   | 14.62606827931352     | N.A.                  | N.A.      |
      | -250                   | 1                            | 14.23985141963199   | 14.23985141963199     | N.A.                  | N.A.      |