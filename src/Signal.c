//
// Created by ted on 2022-03-11.
//
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "../inc/main.h"

double stddev(double data[], int len);

double mean(double data[], int len);

double avgFilter[ROWS];
double stdFilter[ROWS];
double filteredData[ROWS];

void init_signals(int *signals, double *y) {
    for (int i = 0; i++; i < ROWS) {
        signals[i] = 0;
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
    printf("i: %d  p: %.3f s: %d \n", i, p , s);
    printf("filt:" );
    for (int j=i-l; j <=i; j++) {
        printf(" %.3f", filteredData[j]);
    }
    printf("\n");
    printf("avg :" );
    for (int j=i-l; j <=i; j++) {
        printf(" %.3f", avgFilter[j]);
    }
    printf("\n");
    printf("std :" );
    for (int j=i-l; j <=i; j++) {
        printf(" %.3f", stdFilter[j]);
    }
    printf("\n");
}

double lowpass_filter(int filter_div, int i, double point, double filtered) {
    if ((i % filter_div) == 0) {
        filtered = point;
    }
    return(filtered);
}


int doSignal(double point, int i, int *signals) {
    if (point == 0) {
        signals[i] = 0;
        return 0;
    }
    // if the distance between the current value and average is enough standard
    // deviations (threshold) away
    if (fabs(point) > MIN_DEGREES_SEC_FOR_PEAK &&
       fabs(point - avgFilter[i - 1]) > THRESHOLD * stdFilter[i - 1]) {

        // this is a signal (i.e. peak), determine if it is a positive or negative
        // signal
        if (point > avgFilter[i - 1]) {
            signals[i] = (int) FOOT_SWING_THRESHOLD;
        } else {
            signals[i] =  (int) GOOD_SWING_THRESHOLD;
        }

        // filter this signal out using influence
        filteredData[i] = INFLUENCE * point + (1 - INFLUENCE) * filteredData[i - 1];
    } else {
        // ensure this signal remains a zero
        signals[i] = 0;
        // ensure this value is not filtered
        filteredData[i] = point;
    }
    avgFilter[i] = mean(filteredData + i - LAG, LAG);
    stdFilter[i] = stddev(filteredData + i - LAG, LAG);

    // fix from ahmed data June 8, 2020
    if ((point > MIN_DEGREES_SEC_FOR_PEAK) && (signals[i - 1] == (int) FOOT_SWING_THRESHOLD)) {
        signals[i] = (int) FOOT_SWING_THRESHOLD;
    }
    printSignal(LAG, i, point, signals[i]);
    return signals[i];
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

double stddev(double data[], int len) {
    double the_mean = mean(data, len);
    double standardDeviation = 0.0;

    int i;
    for (i = 0; i < len; ++i) {
        standardDeviation += pow(data[i] - the_mean, 2);
    }

    return sqrt(standardDeviation / len);
}
