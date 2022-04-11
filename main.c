#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/IMU_Signal.h"
#include "inc/IMU_ZscoreSignalDetector.h"
#include "inc/FileProcess.h"
#include "inc/main.h"
#include "inc/Plots.h"
#include <sys/time.h>

extern int nSteps, ngood;

double data[ROWS][COLS];

#if PLOTTING_ARRAYS
int signals[ROWS];
double goodStepFilter[ROWS];
double HeelStrikeValley[ROWS];
double beep[ROWS];
#else
int signal;
int lastSignal;
#endif
int beepIt;

#if INTERNAL_JENNIFER_ARRAY
extern double z[];
#else
double z[ROWS];
#endif

int main(int argc, char const *argv[]) {

    printf("C version of Step Analyzer\n");
    /* code */
    if (argc < 2){
        printf("Please specify the CSV file as an input.\n");
        exit(0);
    }

#if INTERNAL_JENNIFER_ARRAY
    int num_rows = 6857;
    for (int n = 0; n < 100; n++) {
        printf("%f\r\n", z[n] );
        fflush(stdout);
    }
#else
    char fname[256];	strcpy(fname, argv[1]);
    clear_data(ROWS, COLS, data);
    int num_rows = read_csv(fname, data, DEBUG);
    printf("%d\n", num_rows);
    matrixColtoArray(data, z, GYRO_Z_COLUMN, num_rows);
#endif
    IMU_init_signals();
    initStepDetector();
    enum StepState thisStepState = LOOKING_FOR_STEP;
    double filtered = 0.0;
    beepIt = 0;
    lastSignal = 0;
    for (int i = LAG; i < num_rows; i++) {
        filtered = lowpass_filter(FILTER_DIV, i+1, z[i], filtered);
#if PLOTTING_ARRAYS
        signals[i] = IMU_doSignal(filtered, i, signals[i-1]);
        thisStepState = IMU_doStepDetect(z[i], i, signals[i], thisStepState, DEBUG);
#else
        signal = IMU_doSignal(filtered, i, lastSignal);
        thisStepState = IMU_doStepDetect(z[i], i, signal, thisStepState, DEBUG);
        lastSignal = signal;
#endif
        if (beepIt) {
            printf("%d BEEEP\n", i);
        }
        if ( i == 2000) {
            int here = 0;
        }
    }
    printf("steps = %d good steps = %d\n", nSteps, ngood);
#if PLOTTING_ARRAYS
        create_multi_csv("/home/ted/temp/multi1.csv", z, HeelStrikeValley, beep, signals,650,950);
#endif
    fflush(stdout);
    return 0;
}
