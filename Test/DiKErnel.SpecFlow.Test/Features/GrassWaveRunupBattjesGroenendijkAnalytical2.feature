Feature: GrassWaveRunupBattjesGroenendijkAnalytical2
As a user I want to perform grass wave run-up calculations based on Battjes-Groenendijk analytical.

The following testcases correspond with BM Gras benchmarks.

DiKErnel does not produce exactly the same results as BM Gras. This is mainly due to the following differences:
- BM Gras rounds the value of averageNumberOfWaves to an integer. This is not the case in DiKErnel.
- BM Gras uses an older version of dikes.Overtopping.dll (version 19.1.1).
- BM Gras is a user interface and performs validation of input parameters. This is not the case in DiKErnel.

    Background:
        Given the following tijdstippen and hydraulischeBelastingen:
          | tijdstippen | waterstanden | golfhoogtenHm0 | golfperiodenTm10 | golfrichtingen |
          | 0           | 0            | 1.5            | 4.20             | 0              |
          | 900         |              |                |                  |                |
        And the following dijkprofiel and a dijkorientatie of 0:
          | posities | hoogten | ruwheidscoefficienten |
          | 0        | -10     | 1                     |
          | 40       | 0       | 1                     |
          | 80       | 10      |                       |
        And the following karakteristiekePunten:
          | teenBuitenzijde | kruinBuitenzijde |
          | 0               | 80               |
        And the following rekeninstellingen:
          | Setting                         | Value            |
          | positie                         | 40.4             |
          | typeToplaag                     | grasGeslotenZode |
          | beginSchade                     | 0                |
          | verhogingBelastingOvergangAlfaM | 1                |
          | verlagingSterkteOvergangAlfaS   | 1                |
          | faalgetal                       | 1                |
          | factorCtm                       | 3.85             |
          | frontsnelheid                   | 1.10             |
          | bodemVoorlandZ                  | -3.0             |
          | tanAvl                          | 0.004            |

    Scenario Outline: BM Gras benchmark 14 - Variable input of critical velocity
        When I change the property kritiekeFrontsnelheid to a value of <kritiekeFrontsnelheid>
        And I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output values for <schadegetal> and <cumulatieveOverbelastingTijdstap> are

        Examples:
          | kritiekeFrontsnelheid | schadegetal           | cumulatieveOverbelastingTijdstap | Benchmark for BM Gras | BM Gras |
          | 3.5                   | 0.09912791114814828   | 693.895378037038                 | 698.202               | 698.151 |
          | 4                     | 0.08240815773892438   | 576.8571041724706                | 588.477               | 588.395 |
          | 5.5                   | 0.0010160364930812532 | 7.112255451568773                | 7.162                 | 7.156   |
          | 6.5                   | 5.35959825332454e-09  | 3.751718777327178e-05            | 0.000                 | 0.000   |
          | 8                     | 0.0                   | 0.0                              | 0.000                 | 0.000   |

    Scenario Outline: BM Gras benchmark 15 - Variable input of level of interest

        Given the following series are adjusted:
          | posities | hoogten | ruwheidscoefficienten |
          | 0        | -10.0   | 1.0                   |
          | 30.56    | 0.0     | 1.0                   |
          | 61.12    | 10.0    |                       |
        And the following rekeninstellingen are adjusted:
          | Setting          | Value |
          | teenBuitenzijde  | 0     |
          | kruinBuitenzijde | 61.12 |
        When I change the property positie to a value of <positie>
        And I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output values for <schadegetal> and <cumulatieveOverbelastingTijdstap> are

        Examples:
          | positie | schadegetal            | cumulatieveOverbelastingTijdstap | Benchmark for BM Gras | BM Gras |
          | 30.5600 | 0.0                    |                                  | 0.000                 | 0.000   |
          | 33.6160 | 0.00016098541128284046 | 1.1268978789798831               | 1.136                 | 1.134   |
          | 36.6720 | 0.00016098541128278394 | 1.1268978789794877               | 1.136                 | 1.134   |
          | 39.7280 | 1.973187114472698e-05  | 0.13812309801308886              | 0.139                 | 0.139   |
          | 42.7840 | 1.5496648932714766e-11 | 1.0847654252900337e-07           | 0.000                 | 0.000   |
          | 45.8400 | 0.0                    | 0.0                              | 0.000                 | 0.000   |
          | 48.8960 | 0.0                    | 0.0                              | 0.000                 | 0.000   |

    Scenario Outline: BM Gras benchmark 16 - Variable input of slope of the bottom

    Remark: the value of tanAvl should be between 0.004 and 0.05. In this testcase, no validation of results is performed by DiKErnel.
    This is why DiKErnel produces results for every situation. The validation of results is however performed by BM Gras.

        Given the following series are adjusted:
          | posities | hoogten | ruwheidscoefficienten |
          | 0        | -10.0   | 1.0                   |
          | 30.56    | 0.0     | 1.0                   |
          | 61.12    | 10.0    |                       |
        And the following rekeninstellingen are adjusted:
          | Setting          | Value           |
          | positie          | 30.8656         |
          | teenBuitenzijde  | 0               |
          | kruinBuitenzijde | 61.12           |
        When I change the property tanAvl to a value of <tanAvl>
        And I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output values for <schadegetal> and <cumulatieveOverbelastingTijdstap> are

        Examples:
          | tanAvl | schadegetal            | cumulatieveOverbelastingTijdstap | Benchmark for BM Gras | BM Gras |
          | 0      | 0.0001300542627438877  | 0.9103798392072139               | 0.918                 |         |
          | 0.004  | 0.00016098541128284046 | 1.1268978789798831               | 1.136                 | 1.134   |
          | 0.04   | 0.0019034054017018846  | 13.323837811913192               | 13.425                | 13.406  |
          | 0.1    | 0.006982414063938715   | 48.876898447571                  | 49.205                |         |
          | 0.4    | 0.0068200858530393154  | 47.74060097127521                | 48.062                |         |
          | 10     | 0.006820085853039203   | 47.74060097127442                | 48.062                |         |
          | 100    | 0.006820085853039203   | 47.74060097127442                | 48.062                |         |
          | 250    | 0.006820085853039203   | 47.74060097127442                | 48.062                |         |

    Scenario Outline: BM Gras benchmark 17 - Variable input of water depth

    Remarks:
    - In BM Gras the value of water depth (water level - bodemVoorlandZ) must be > 0 and <= 10 m. This validation is not performed by DiKErnel.
    - When (water level - bodemVoorlandZ) equals to 0 m, then division by zero occurs. No results are produced then by DiKErnel (NaN).

        Given the following series are adjusted:
          | posities | hoogten | ruwheidscoefficienten |
          | 0        | -10.0   | 1.0                   |
          | 30.56    | 0.0     | 1.0                   |
          | 61.12    | 10.0    |                       |
        And the following rekeninstellingen are adjusted:
          | Setting          | Value   |
          | positie          | 30.8656 |
          | teenBuitenzijde  | 0       |
          | kruinBuitenzijde | 61.12   |
        When I change the property bodemVoorlandZ to a value of <bodemVoorlandZ>
        And I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output values for <schadegetal> and <cumulatieveOverbelastingTijdstap> are

        Examples:
          | bodemVoorlandZ | schadegetal           | cumulatieveOverbelastingTijdstap | Benchmark for BM Gras | BM Gras   |
          | 0              | NaN                   | NaN                              | 0.000                 |           |
          | -0.004         | 18.899172206217422    | 132294.20544352196               | 133115.947            |           |
          | -0.04          | 1.9530600918770284    | 13671.4206431392                 | 13756.388             | 13755.272 |
          | -0.1           | 0.8177090570008678    | 5723.963399006075                | 5729.582              | 5759.070  |
          | -0.4           | 0.146449850472942     | 1025.1489533105942               | 1031.744              | 1031.437  |
          | -10            | 0.0030480842313577797 | 21.33658961950446                | 21.469                | 21.453    |
          | -100           | 0.002089438325616217  | 14.626068279313518               |                       |           |
          | -250           | 0.002034264488518857  | 14.239851419631998               |                       |           |

    Scenario Outline: BM Gras benchmark 18 - Variable input of water depth and critical depth

    Remarks:
    - In BM Gras the value of water depth (water level - bodemVoorlandZ) must be > 0 and <= 10 m. This validation is not performed by DiKErnel.
    - When (water level - bodemVoorlandZ) equals to 0 m, then division by zero occurs. No results are produced then by DiKErnel (NaN).

        Given the following series are adjusted:
          | posities | hoogten | ruwheidscoefficienten |
          | 0        | -10.0   | 1.0                   |
          | 30.56    | 0.0     | 1.0                   |
          | 61.12    | 10.0    |                       |
        And the following rekeninstellingen are adjusted:
          | Setting          | Value   |
          | positie          | 30.8656 |
          | teenBuitenzijde  | 0       |
          | kruinBuitenzijde | 61.12   |
        When I change the property bodemVoorlandZ to a value of <bodemVoorlandZ>
        And I change the property kritiekeCumulatieveOverbelasting to a value of <kritiekeCumulatieveOverbelasting>
        And I run the grass wave run-up Battjes-Groenendijk analytical calculation
        Then the output values for <schadegetal> and <cumulatieveOverbelastingTijdstap> are

        Examples:
          | bodemVoorlandZ | kritiekeCumulatieveOverbelasting | schadegetal        | cumulatieveOverbelastingTijdstap | Benchmark for BM Gras | BM Gras   |
          | 0              | 1000                             | NaN                | NaN                              | 0.000                 |           |
          | -0.004         | 1000                             | 132.29420544352197 | 132294.20544352196               | 133115.947            |           |
          | -0.04          | 100                              | 136.714206431392   | 13671.4206431392                 | 13756.388             | 13755.272 |
          | -0.1           | 10                               | 572.3963399006075  | 5723.963399006075                | 5759.582              | 5759.070  |
          | -0.4           | 1                                | 1025.1489533105942 | 1025.1489533105942               | 1031.744              | 1031.437  |
          | -10            | 1                                | 21.33658961950446  | 21.33658961950446                | 21.469                | 21.453    |
          | -100           | 1                                | 14.626068279313518 | 14.626068279313518               |                       |           |
          | -250           | 1                                | 14.239851419631998 | 14.239851419631998               |                       |           |