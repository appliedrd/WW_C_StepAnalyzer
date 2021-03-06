#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "inc/IMU_Signal.h"
#include "inc/IMU_ZscoreSignalDetector.h"
#include "inc/FileProcess.h"
#include "inc/main.h"
#include "inc/Plots.h"
#include "inc/sensor_csv.h"
#include "inc/foot_detect.h"
#include <sys/time.h>
#include "inc/read_allStepAnalytics.h"

extern int nSteps, ngood;
extern double accY_avg;
extern double accZ_avg;

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
all_steps_t stepRecords[2000];
imu_vector_t records[NUMRECORDS];

int main(int argc, char const *argv[]) {
    int idle_counter = 0;
    bool valid = false;
    int total_step_records;
   // char *allSteps = "Q:\\data\\Heel2toe\\allStepAnalytics.csv";
    char *allSteps = "Q:\\data\\test\\allStepAnalytics.csv";

    printf("C version of Step Analyzer\n");
    read_allStepAnalytics(allSteps, stepRecords, &total_step_records);

    for (int s = 0; s < total_step_records; s++) {
        int total_records;
        char fullpath[200];
//        strcpy(fullpath, "Q:\\data\\Heel2toe\\csv-processed\\");
        strcpy(fullpath, "Q:\\data\\test\\");
        strcat(fullpath, stepRecords[s].fname);
        strcat(fullpath, ".csv");
        printf("READING AN IMU DATA FILE %s\n", fullpath);

//        char *fname = "Q:\\data\\Heel2toe\\csv-processed\\H2T-PhysioBioMetrics-htt26-Heel2toe2021-07-22-15-00-30.csv";
//    char * fname = "C:\\Users\\tedhi\\Downloads\\android_5-26\\H2T-PhysioBioMetrics-ted-Heel2toe2022-05-26-08-21-08.csv";
        read_sensor_csv(fullpath, records, &total_records);
//        printf("Total records = %d\n", total_records);


        IMU_init_signals();
        initStepDetector();
        initFootDetector();
        StepState thisStepState = LOOKING_FOR_STEP;
        double filtered = 0.0;
        beepIt = 0;
        lastSignal = 0;
        Foot_Detect_State footDetectState;

        for (int i = LAG; i < total_records; i++) {
            filtered = lowpass_filter(FILTER_DIV, i + 1,
                                      records[i].GyroscopeZ_ds, filtered);
#if PLOTTING_ARRAYS
            signals[i] = IMU_doSignal(filtered, i, signals[i-1]);
            thisStepState = IMU_doStepDetect(z[i], i, signals[i], thisStepState, DEBUG);
#else
            signal = IMU_doSignal(filtered, i, lastSignal);
            thisStepState = IMU_doStepDetect(records[i].GyroscopeZ_ds, i,
                                             signal, thisStepState, DEBUG);
            lastSignal = signal;
            if (thisStepState == LOOKING_FOR_STEP) {
                footDetectState = footDetect(records[i].AccelerometerZ_ms2,
                                             records[i].AccelerometerY_ms2);
                if (footDetectState == LEFT_FOOT || footDetectState == RIGHT_FOOT) {
                    printf("%0.3f,  %0.3f, %d, %s, %c \n",
                           accZ_avg, accY_avg, idle_counter, stepRecords[s].foot, footDetectState);
                    initFootDetector();
                }
            }

#endif
            if (beepIt) {
                //printf("%d BEEEP\n", i);
            }
            if (i == 2000) {
                int here = 0;
            }
        }
//        printf("steps = %d good steps = %d\n", nSteps, ngood);
#if PLOTTING_ARRAYS
        create_multi_csv("/home/ted/temp/multi1.csv", z, HeelStrikeValley, beep, signals,650,950);
#endif
        fflush(stdout);
    }
    return 0;
}
