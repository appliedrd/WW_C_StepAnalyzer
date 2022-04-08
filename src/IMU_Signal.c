//
// Created by ted on 2022-03-11.
//
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "../inc/main.h"

double stddev(double data[], int len);

double stdDevSampleVariance(double data[], int len);

double mean(double data[], int len);

double avgFilter[LAG];
double stdFilter[LAG];
double filteredData[LAG];

void IMU_init_signals() {
    for (int i = 0; i++; i < LAG) {
        filteredData[i] = 0;
        avgFilter[i] = 0;
        stdFilter[i] = 0;
    }
//    memset(signals, 0, sizeof(int) * ROWS);
//    memcpy(filteredData, 0, sizeof(double) * ROWS);
//
//    avgFilter[LAG - 1] = mean(y, LAG);
//    stdFilter[LAG - 1] = stddev(y, LAG);
}

void printSignal(int l, int i, double p, int s) {
    printf("i: %d  p: %.3f s: %d \n", i, p, s);
    printf("filt:");
    for (int j = i - l; j <= i; j++) {
        printf(" %.3f", filteredData[j % LAG]);
    }
    printf("\n");
    printf("avg :");
    for (int j = i - l; j <= i; j++) {
        printf(" %.3f", avgFilter[j % LAG]);
    }
    printf("\n");
    printf("std :");
    for (int j = i - l; j <= i; j++) {
        printf(" %.3f", stdFilter[j % LAG]);
    }
    printf("\n");
}

double lowpass_filter(int filter_div, int i, double point, double filtered) {
    if ((i % filter_div) == 0) {
        filtered = point;
    }
    return (filtered);
}


int IMU_doSignal(double point, int i, int last_signal) {
    int signal = 0;
    if (point == 0) {
        return 0;
    }
    // if the distance between the current value and average is enough standard
    // deviations (threshold) away
    if (fabs(point) > MIN_DEGREES_SEC_FOR_PEAK &&
        (fabs(point - avgFilter[(i - 1) % LAG]) > THRESHOLD * stdFilter[(i - 1) % LAG])) {

        // this is a signal (i.e. peak), determine if it is a positive or negative
        // signal
        if (point > avgFilter[(i - 1) % LAG]) {
            signal = (int) FOOT_SWING_THRESHOLD;
        } else {
            signal = (int) GOOD_SWING_THRESHOLD;
        }

        // filter this signal out using influence
        filteredData[i % LAG] = INFLUENCE * point + (1 - INFLUENCE) * filteredData[(i - 1) % LAG];
    } else {
        // ensure this signal remains a zero
        signal = 0;
        // ensure this value is not filtered
        filteredData[i % LAG] = point;
    }
    avgFilter[i % LAG] = mean(filteredData, LAG);
    stdFilter[i % LAG] = stdDevSampleVariance(filteredData, LAG);

    // fix from ahmed data June 8, 2020
    if ((point > MIN_DEGREES_SEC_FOR_PEAK) && (last_signal == (int) FOOT_SWING_THRESHOLD)) {
        signal = (int) FOOT_SWING_THRESHOLD;
    }
    //printSignal(LAG, i, point, signals[i]);
    return signal;
}

double mean(double data[], int len) {
    double sum = 0.0, mean = 0.0;

    int i;
    for (i = 0; i < len; ++i) {
        sum += data[i];
    }

    mean = sum / len;
    return mean;
}

double stdDevSampleVariance(double data[], int len) {
    double the_mean = mean(data, len);
    double var = 0;
    for (int i = 0; i < len; i++) {
        var += (data[i] - the_mean) * (data[i] - the_mean);
    }
    var /= (len - 1);
    return sqrt(var);
}
