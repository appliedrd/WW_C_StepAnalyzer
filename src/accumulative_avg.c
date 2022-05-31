//
// Created by tedhi on 5/27/2022.
//
#include <stdio.h>
#include "../inc/accumulative_avg.h"

#define IDLE_WINDOW 100
#define MIN_ACC_DIFF 0.500
#define MIN_ACC 0.750
double accY_accumulator = 0;
double accY_avg = 0;
double accZ_accumulator = 0;
double accZ_avg = 0;
int idle_counter = 0;

double accumulative_avg(double *accumulator, int len, double nextNum)
{
    *accumulator += nextNum;
    len++;
    //return the average
    return *accumulator / len;
}

void initFootDetector() {
    accY_accumulator = 0;
    accY_avg = 0;
    accZ_accumulator = 0;
    accZ_avg = 0;
    idle_counter = 0;
}

Foot_Detect_State footDetect(double accZ, double accY) {
        idle_counter++;
        Foot_Detect_State footDetectState;
        accY_avg = accumulative_avg(&accY_accumulator,
                                    idle_counter,accY);
        accZ_avg = accumulative_avg(&accZ_accumulator,
                                    idle_counter,accZ);

        if (idle_counter > IDLE_WINDOW) {
            // todo decide if left or right foot
            // todo set leftright mult factor (1 or -1)
            if (accY_avg > MIN_ACC && accY_avg - accZ_avg > MIN_ACC_DIFF) {
                return RIGHT_FOOT;
            } else if (accZ_avg > MIN_ACC && accZ_avg - accY_avg > MIN_ACC_DIFF) {
                return LEFT_FOOT;
            }
            initFootDetector();
        }
        return ACCUMULATING;
}

