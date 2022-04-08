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
double z[ROWS];
int signals[ROWS];
double goodStepFilter[ROWS];
double HeelStrikeValley[ROWS];
double beep[ROWS];
int beepIt;

int main(int argc, char const *argv[]) {

    printf("C version of Step Analyzer\n");
    /* code */
    if (argc < 1){
        printf("Please specify the CSV file as an input.\n");
        exit(0);
    }
    char fname[256];	strcpy(fname, argv[1]);
    clear_data(ROWS, COLS, data);
    int num_rows = read_csv(fname, data, DEBUG);
    printf("%d\n", num_rows);
    matrixColtoArray(data, z, GYRO_Z_COLUMN, num_rows);
    IMU_init_signals();
    initStepDetector();
    enum StepState thisStepState = LOOKING_FOR_STEP;
    double filtered = 0.0;
    beepIt = 0;
    for (int i = LAG; i < num_rows; i++) {
        filtered = lowpass_filter(FILTER_DIV, i+1, z[i], filtered);
        signals[i] = IMU_doSignal(filtered, i, signals[i-1]);
        thisStepState = IMU_doStepDetect(z[i], i, signals[i], thisStepState, DEBUG);
        if (beepIt) {
            printf("%d BEEEP\n", i);
        }
        if ( i == 2000) {
            int here = 0;
        }
    }
    printf("steps = %d good steps = %d\n", nSteps, ngood);
    if (PLOTTING_ARRAYS) {
        create_multi_csv("/home/ted/temp/multi1.csv", z, HeelStrikeValley, beep, signals,650,950);
    }
    return 0;
}
