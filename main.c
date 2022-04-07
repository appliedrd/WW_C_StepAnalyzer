#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/Signal.h"
#include "inc/ZscoreSignalDetector.h"
#include "inc/FileProcess.h"
#include "inc/main.h"
#include "inc/Plots.h"

extern int nSteps, ngood;

double data[ROWS][COLS];
double z[ROWS];
int signals[ROWS];
double goodStepFilter[ROWS];
double HeelStrikeValley[ROWS];
double beep[ROWS];

float y[]=  {1,1,1.1,1,0.9,1,1,1.1,1,0.9,1,1.1,1,1,0.9,1,1,1.1,1,1,1,1,1.1,0.9,1,1.1,1,1,0.9,
             1,1.1,1,1,1.1,1,0.8,0.9,1,1.2,0.9,1,1,1.1,1.2,1,1.5,1,3,2,5,3,2,1,1,1,0.9,1,1,3,       2.6,4,3,3.2,2,1,1,0.8,4,4,2,2.5,1,1,1,1.2,1,1.5,1,3,2,5,3,2,1,1,1,0.9,1,1,3,
             2.6,4,3,3.2,2,1,1,0.8,4,4,2,2.5,1,1,1};


int main(int argc, char const *argv[]) {

    printf("C version of Step Analyzer\n");
    /* code */
    if (argc < 1){
        printf("Please specify the CSV file as an input.\n");
        exit(0);
    }
    char fname[256];	strcpy(fname, argv[1]);
    clear_data(ROWS, COLS, data);
    int num_rows = read_csv(fname, data);
    printf("%d\n", num_rows);
    matrixColtoArray(data, z, GYRO_Z_COLUMN, num_rows);
    init_signals(signals, z);
    initStepDetector();
    enum StepState thisStepState = LOOKING_FOR_STEP;
    double filtered = 0.0;
    for (int i = LAG; i < num_rows; i++) {
        filtered = lowpass_filter(FILTER_DIV, i+1, z[i], filtered);
        doSignal(filtered, i, signals);
        thisStepState = doStepDetect(z[i], i, signals[i], thisStepState, true,
                                     HeelStrikeValley, beep);
        if ( i == 2000) {
            int here = 0;
        }
    }
    printf("steps = %d good steps = %d\n", nSteps, ngood);
//    plotXY(signals, 1000, 1500);
 //   plotXY(z, 1000, 1500);
 //   plotXYint(signals, 1000, 1200);
 //   plotXY(goodStepFilter, 1000, 1500);
    //create_csv("/home/ted/temp/plot2.csv", z, signals,1000,1200);
    create_multi_csv("/home/ted/temp/multi1.csv", z, HeelStrikeValley, beep, signals,650,950);
    return 0;
}
