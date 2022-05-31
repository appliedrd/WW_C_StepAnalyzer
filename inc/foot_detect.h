//
// Created by tedhi on 5/27/2022.
//

#ifndef WW_C_STEPANALYZER_ACCUMULATIVE_AVG_H
#define IDLE_WINDOW 100
#define MIN_ACC_DIFF 0.500
#define MIN_ACC 0.750

typedef enum {
    ACCUMULATING = 'a',
    LEFT_FOOT = 'L',
    RIGHT_FOOT = 'R',
} Foot_Detect_State;


void initFootDetector();
double accumulative_avg(double *accumulator, int len, double nextNum);
Foot_Detect_State footDetect(double accZ, double accY);

#define WW_C_STEPANALYZER_ACCUMULATIVE_AVG_H

#endif //WW_C_STEPANALYZER_ACCUMULATIVE_AVG_H
