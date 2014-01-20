// Thermistor lookup table for one thermistor or
// identical thermistors in all places.

/*
   This table doesn't depend on the type of electronics, but on the type of
   thermistor(s) you use. You want one table for each thermistor type you use.
*/

// How many thermistor tables we have.
#define NUMTABLES 1

// Names for our tables, so you can use them in config.h.
// Table numbering starts at 0.
#define THERMISTOR_BED   0

/*
   You may be able to improve the accuracy of this table in various ways.

   1. Measure the actual resistance of the resistor. It's "nominally" 4.7K,
      but that's ± 5%.
   2. Measure the actual beta of your thermistor:
      http://reprap.org/wiki/MeasuringThermistorBeta
   3. Generate more table entries than you need, then trim down the ones
      in uninteresting ranges.

   In either case you'll have to regenerate this table with
   createTemperatureLookup.py, which requires python, which is difficult to
   install on windows. Since you'll have to do some testing to determine the
   correct temperature for your application anyway, you may decide that the
   effort isn't worth it. Who cares if it's reporting the "right" temperature
   as long as it's keeping the temperature steady enough to print, right?
*/

/*
    T,°С        R/R1    R,килоОм        U,В     I,мкА   P,мВт   U/Uref  ADC     E,°С
    0       3.5563  35.563  2.57573 72.427  0.187   0.7805237       3197
    5       2.7119  27.119  2.41097 88.903  0.214   0.7305962       2993    0.1241
    10      2.086   20.86   2.23065 106.935 0.239   0.6759559       2769    0.074
    15      1.6204  16.204  2.04065 125.935 0.257   0.6183789       2533    0.042
    20      1.2683  12.683  1.84517 145.483 0.268   0.5591412       2290    0.0097
    25      1       10      1.65    165     0.272   0.5     2048    0.0436
    30      0.7942  7.942   1.46074 183.926 0.269   0.4426485       1813    0.0556
    35      0.63268 6.3268  1.27878 202.122 0.258   0.3875101       1587    0.1084
    40      0.5074  5.074   1.1108  218.92  0.243   0.3366061       1379    0.1378
    45      0.41026 4.1026  0.96001 233.999 0.225   0.2909109       1192    0.1442
    50      0.33363 3.3363  0.82555 247.445 0.204   0.2501668       1025    0.1552
    55      0.27243 2.7243  0.70654 259.346 0.183   0.2141022       877     0.1854
    60      0.2237  2.237   0.60326 269.674 0.163   0.1828062       749     0.1909
    65      0.18459 1.8459  0.51423 278.577 0.143   0.1558261       638     0.2128
    70      0.15305 1.5305  0.43803 286.197 0.125   0.1327349       544     0.2088
    75      0.12755 1.2755  0.3733  292.67  0.109   0.1131214       463     0.2326
    80      0.10677 1.0677  0.31835 298.165 0.095   0.0964699       395     0.2452
    85      0.089928        0.89928 0.27228 302.772 0.082   0.0825082       338     0.2294
    90      0.076068        0.76068 0.23328 306.672 0.072   0.0706907       290     0.2014
    95      0.064524        0.64524 0.20002 309.998 0.062   0.060613        248     0.258
    100     0.054941        0.54941 0.17186 312.814 0.054   0.0520797       213     0.2777
    105     0.047003        0.47003 0.14815 315.185 0.047   0.0448929       184     0.2394
    110     0.040358        0.40358 0.12801 317.199 0.041   0.0387924       159     0.2379
    115     0.034743        0.34743 0.1108  318.92  0.035   0.0335765       138     0.2036
    120     0.030007        0.30007 0.09614 320.386 0.031   0.0291328       119     0.3226
    125     0.026006        0.26006 0.08364 321.636 0.027   0.0253468       104     0.2509
    130     0.022609        0.22609 0.07296 322.704 0.024   0.0221091       91      0.2064
    135     0.01972 0.1972  0.06382 323.618 0.021   0.0193386       79      0.358
    140     0.017251        0.17251 0.05596 324.404 0.018   0.0169584       69      0.4545
    145     0.015139        0.15139 0.04921 325.079 0.016   0.0149132       61      0.3694
    150     0.013321        0.13321 0.04338 325.662 0.014   0.0131459       54
*/

// The number of value pairs in our table.
// Must be the same for all tables.
#define NUMTEMPS 31
#define TEMP_MULTIPLIER 4
#define TEMP(x) ((x) * TEMP_MULTIPLIER)

const uint16_t temptable[NUMTABLES][NUMTEMPS][2] PROGMEM = {
{
   {56,   TEMP(150)},
   {64,   TEMP(145)},
   {72,   TEMP(140)},
   {82,   TEMP(135)},
   {94,   TEMP(130)},
   {108,  TEMP(125)},
   {124,  TEMP(120)},
   {143,  TEMP(115)},
   {165,  TEMP(110)},
   {191,  TEMP(105)},
   {222,  TEMP(100)},
   {258,  TEMP(95)},
   {301,  TEMP(90)},
   {351,  TEMP(85)},
   {410,  TEMP(80)},
   {480,  TEMP(75)},
   {563,  TEMP(70)},
   {661,  TEMP(65)},
   {774,  TEMP(60)},
   {905,  TEMP(55)},
   {1056, TEMP(50)},
   {1226, TEMP(45)},
   {1416, TEMP(40)},
   {1627, TEMP(35)},
   {1854, TEMP(30)},
   {2090, TEMP(25)},
   {2331, TEMP(20)},
   {2572, TEMP(15)},
   {2805, TEMP(10)},
   {3025, TEMP(5)},
   {3225, TEMP(0)},
}
};
