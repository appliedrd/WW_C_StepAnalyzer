//
// Created by ted on 2022-03-17.
//

#ifndef WW_C_STEPANALYZER_MAIN_H
#define WW_C_STEPANALYZER_MAIN_H
#define LAG 5
#define THRESHOLD 2
#define INFLUENCE 0.1
#define MIN_DEGREES_SEC_FOR_PEAK 20.0
#define MIN_NUM_PEAKS_FOR_HEEL_STRIKE  3
#define SKIP_FLAT_FOOT_SAMPLES  15
#define SKIP_HEEL_OFF_SAMPLES  5
#define HEEL_STRIKE_VALLEY_INDICATOR -109.0
#define SAMPLE_LENGTH 1000
#define ROWS 50000
#define COLS 14
#define GYRO_Z_COLUMN 5
#define FOOT_SWING_THRESHOLD 100.0
#define GOOD_SWING_THRESHOLD -250.0
#define FILTER_DIV 3
#define DEBUG 0
#define PLOTTING_ARRAYS 0
#define INTERNAL_JENNIFER_ARRAY 1
#endif //WW_C_STEPANALYZER_MAIN_H

