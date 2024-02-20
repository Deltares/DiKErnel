Feature: GrassWaveRunupBattjesGroenendijkAnalytical2
As a user I want to perform grass wave run-up calculations based on Battjes-Groenendijk analytical.

The following testcases correspond with BM Gras benchmarks.

DiKErnel does not exactly produce the same results as BM Gras. This is mainly due to the following differences:
- BM Gras rounds the value of average number of waves to an integer. This is not the case in DiKErnel.
- BM Gras uses an older version of dikes.Overtopping.dll (version 19.1.1).
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
          | Characteristic point | Position |
          | Outer toe            | 0        |
          | Outer crest          | 25       |
        And the following calculation settings:
          | Setting                     | Value      |
          | Position                    | 40.4       |
          | Top layer type              | Closed sod |
          | Initial damage              | 0          |
          | Increased load transition   | 1          |
          | Reduced strength transition | 1          |
          | Failure number              | 1          |
          | Average number of waves     | 3.85       |
          | Front velocity              | 1.1        |

    Scenario Outline: BM Gras benchmark 14 - Variable input of critical velocity
        Given I change the property "critical front velocity" to a value of <Critical front velocity>
        When I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output value for the "damage" is <Damage>
        And the output value for the "cumulative overload" is <Cumulative overload>

        Examples:
          | Critical front velocity | Damage                | Cumulative overload   | Benchmark for BM Gras | BM Gras |
          | 3.5                     | 0.09912791114814828   | 693.895378037038      | 698.202               | 698.151 |
          | 4                       | 0.08240815773892438   | 576.8571041724706     | 588.477               | 588.395 |
          | 5.5                     | 0.0010160364930812532 | 7.112255451568773     | 7.162                 | 7.156   |
          | 6.5                     | 5.35959825332454e-09  | 3.751718777327178e-05 | 0                     | 0       |
          | 8                       | 0                     | 0                     | 0                     | 0       |

    Scenario Outline: BM Gras benchmark 15 - Variable input of level of interest
        Given the adjusted dike geometry:
          | X     | Z   | Roughness coefficient |
          | 0     | -10 | 1                     |
          | 30.56 | 0   | 1                     |
          | 61.12 | 10  | N.A.                  |
        And the following adjusted characteristic points:
          | Setting     | Value |
          | Outer toe   | 0     |
          | Outer crest | 61.12 |
        When I change the property "position" to a value of <Position>
        And I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output value for the "damage" is <Damage>
        And the output value for the "cumulative overload" is <Cumulative overload>

        Examples:
          | Position | Damage                 | Cumulative overload    | Benchmark for BM Gras | BM Gras |
          | 30.56    | 0                      |                        | 0                     | 0       |
          | 33.616   | 0.00016098541128284046 | 1.1268978789798831     | 1.136                 | 1.134   |
          | 36.672   | 0.00016098541128278394 | 1.1268978789794877     | 1.136                 | 1.134   |
          | 39.728   | 1.973187114472698e-05  | 0.13812309801308886    | 0.139                 | 0.139   |
          | 42.784   | 1.5496648932714766e-11 | 1.0847654252900337e-07 | 0                     | 0       |
          | 45.84    | 0                      | 0                      | 0                     | 0       |
          | 48.896   | 0                      | 0                      | 0                     | 0       |

    Scenario Outline: BM Gras benchmark 16 - Variable input of slope of the bottom
    Remark: the value of the slope of the foreshore should be between 0.004 and 0.05. In this testcase, no validation
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
        When I change the property "slope foreshore" to a value of <Slope foreshore>
        And I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output value for the "damage" is <Damage>
        And the output value for the "cumulative overload" is <Cumulative overload>

        Examples:
          | Slope foreshore | Damage                 | Cumulative overload | Benchmark for BM Gras | BM Gras |
          | 0               | 0.0001300542627438877  | 0.9103798392072139  | 0.918                 | N.A.    |
          | 0.004           | 0.00016098541128284046 | 1.1268978789798831  | 1.136                 | 1.134   |
          | 0.04            | 0.0019034054017018846  | 13.323837811913192  | 13.425                | 13.406  |
          | 0.1             | 0.006982414063938715   | 48.876898447571     | 49.205                | N.A.    |
          | 0.4             | 0.0068200858530393154  | 47.74060097127521   | 48.062                | N.A.    |
          | 10              | 0.006820085853039203   | 47.74060097127442   | 48.062                | N.A.    |
          | 100             | 0.006820085853039203   | 47.74060097127442   | 48.062                | N.A.    |
          | 250             | 0.006820085853039203   | 47.74060097127442   | 48.062                | N.A.    |

    Scenario Outline: BM Gras benchmark 17 - Variable input of water depth
    Remarks:
    - In BM Gras the value of water depth (water level - Foreshore bottom level) must be > 0 and <= 10 m. This validation is not performed by DiKErnel.
    - When (water level - Foreshore bottom level) equals 0 m, then division by zero occurs. No results are produced by DiKErnel (NaN) in this situation.

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
        When I change the property "foreshore bottom level" to a value of <Foreshore bottom level>
        And I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output value for the "damage" is <Damage>
        And the output value for the "cumulative overload" is <Cumulative overload>

        Examples:
          | Foreshore bottom level | Damage                | Cumulative overload | Benchmark for BM Gras | BM Gras   |
          | 0                      | NaN                   | NaN                 | 0                     | N.A.      |
          | -0.004                 | 18.899172206217422    | 132294.20544352196  | 133115.947            | N.A.      |
          | -0.04                  | 1.9530600918770284    | 13671.4206431392    | 13756.388             | 13755.272 |
          | -0.1                   | 0.8177090570008678    | 5723.963399006075   | 5729.582              | 5759.07   |
          | -0.4                   | 0.146449850472942     | 1025.1489533105942  | 1031.744              | 1031.437  |
          | -10                    | 0.0030480842313577797 | 21.33658961950446   | 21.469                | 21.453    |
          | -100                   | 0.002089438325616217  | 14.626068279313518  | N.A.                  | N.A.      |
          | -250                   | 0.002034264488518857  | 14.239851419631998  | N.A.                  | N.A.      |

    Scenario Outline: BM Gras benchmark 18 - Variable input of water depth and critical depth
    Remarks:
    - In BM Gras the value of water depth (water level - bottom foreshore level) must be > 0 and <= 10 m. This validation is not performed by DiKErnel.
    - When (water level - bottom foreshore level) equals 0 m, then division by zero occurs. No results are produced then by DiKErnel (NaN).

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
        When I change the property "foreshore bottom level" to a value of <Foreshore bottom level>
        And I change the property "critical cumulative overload" to a value of <Critical cumulative overload>
        And I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output value for the "damage" is <Damage>
        And the output value for the "cumulative overload" is <Cumulative overload>

        Examples:
          | Foreshore bottom level | Critical cumulative overload | Damage             | Cumulative overload | Benchmark for BM Gras | BM Gras   |
          | 0                      | 1000                         | NaN                | NaN                 | 0                     | N.A.      |
          | -0.004                 | 1000                         | 132.29420544352197 | 132294.20544352196  | 133115.947            | N.A.      |
          | -0.04                  | 100                          | 136.714206431392   | 13671.4206431392    | 13756.388             | 13755.272 |
          | -0.1                   | 10                           | 572.3963399006075  | 5723.963399006075   | 5759.582              | 5759.07   |
          | -0.4                   | 1                            | 1025.1489533105942 | 1025.1489533105942  | 1031.744              | 1031.437  |
          | -10                    | 1                            | 21.33658961950446  | 21.33658961950446   | 21.469                | 21.453    |
          | -100                   | 1                            | 14.626068279313518 | 14.626068279313518  | N.A.                  | N.A.      |
          | -250                   | 1                            | 14.239851419631998 | 14.239851419631998  | N.A.                  | N.A.      |