/*                                      42 KEY MATRIX / LAYOUT MAPPING (Toucan2)

  ╭────────────────────────┬────────────────────────╮ ╭────────────────────────┬────────────────────────╮
  │  0   1   2   3   4   5 │  6   7   8   9  10  11 │ │Lout LT4 LT3 LT2 LT1 LT0│RT0 RT1 RT2 RT3 RT4 Rout│
  │ 12  13  14  15  16  17 │ 18  19  20  21  22  23 │ │Lout LM4 LM3 LM2 LM1 LM0│RM0 RM1 RM2 RM3 RM4 Rout│
  │ 24  25  26  27  28  29 │ 30  31  32  33  34  35 │ │Lout LB4 LB3 LB2 LB1 LB0│RB0 RB1 RB2 RB3 RB4 Rout│
  ╰──────────╮ 36  37  38 │ 39  40  41 ╭──────────╯ ╰──────────╮LH1 LH0 Lx │ RH0 RH1 Rx╭──────────╯
             ╰────────────┴────────────╯                        ╰───────────┴───────────╯           */

#pragma once

// Extra outermost pinky columns (not present on Ferris)
#define LoutT  0
#define LoutM 12
#define LoutB 24
#define RoutT 11
#define RoutM 23
#define RoutB 35

// Left-hand keys (inner to outer within the Ferris-mapped block)
#define LT0    5
#define LT1    4
#define LT2    3
#define LT3    2
#define LT4    1
#define LM0   17
#define LM1   16
#define LM2   15
#define LM3   14
#define LM4   13
#define LB0   29
#define LB1   28
#define LB2   27
#define LB3   26
#define LB4   25

// Right-hand keys
#define RT0    6
#define RT1    7
#define RT2    8
#define RT3    9
#define RT4   10
#define RM0   18
#define RM1   19
#define RM2   20
#define RM3   21
#define RM4   22
#define RB0   30
#define RB1   31
#define RB2   32
#define RB3   33
#define RB4   34

// Thumbs (left-to-right physically; LH1/LHx and RHx are the extra outermost keys)
#define LH1   36
#define LH0   37
#define LHx   38
#define RH0   39
#define RH1   40
#define RHx   41
