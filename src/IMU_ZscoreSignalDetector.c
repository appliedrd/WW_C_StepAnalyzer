//
// Created by ted on 2022-03-21.
//

#include <stdbool.h>
#include <stdio.h>
#include "../inc/IMU_ZscoreSignalDetector.h"
#include "../inc/main.h"

//extern double goodStepFilter[ROWS];
//double stepFilter[ROWS];
//double heelOffPower[ROWS];
//double startSwing[ROWS];
//double stopSwing[ROWS];
//double maxFootSwings[ROWS];
extern double HeelStrikeValley[ROWS];
extern double beep[ROWS];
extern int beepIt;

double lastPeakStatus;
double footSwingThreshold;
double goodStepThreshold;
double maxFootSwing;
double minHeelValley;
double heelOffPowerMin;
int lastSignal;
int stateCount;
int inStepTimeout;

int nSteps, ngood;

bool foundStepStart;
bool lookForNextStep;
bool foundToeDown;
bool inToeDown;
bool inStep;
bool firstBelow;
bool firstBeep;
bool unknownData;

enum StepState thisStepState;

void initStepDetector() {
    thisStepState = LOOKING_FOR_STEP;
    inStepTimeout = 0;

    foundStepStart = false;
    foundToeDown = false;
    lookForNextStep = true;
    inStep = false;
    inToeDown = false;
    maxFootSwing = 0.0;
    minHeelValley = 0.0;
    heelOffPowerMin = 0.0;
    nSteps = 0;
    ngood = 0;
}

//double footSwingMeasurements(double point, int i, double maxFootSwing) {
//    if ((stopSwing[i - 1] == 0) && (stopSwing[i - 2] == 0)) {
//        stopSwing[i] =  point;
//    }
//    maxFootSwings[i] = maxFootSwing;
//    maxFootSwing = 0.0;
//    return maxFootSwing;
//}

const char* getStepStateName(enum StepState stepState)
{
    switch (stepState)
    {
        case LOOKING_FOR_STEP: return "LOOKING_FOR_STEP";
        case FOOT_SWING: return "FOOT_SWING";
        case POTENTIAL_HEEL_STRIKE: return "POTENTIAL_HEEL_STRIKE";
        case FLAT_FOOT: return "FLAT_FOOT";
        case HEEL_OFF: return "HEEL_OFF";
    }
}


enum StepState IMU_doStepDetect(double point, int i, int signal, enum StepState stepState, bool debug) {

    if (debug)  {
        printf("stepState %s  t: %d signal: %d point: %.3f \n",
               getStepStateName(stepState), i, signal, point);
    }
    beepIt = 0;

    switch (stepState) {
        case LOOKING_FOR_STEP:
            if (debug) printf("LOOKING_FOR_STEP\n");
            firstBelow = true;
            firstBeep = true;

            // we need to capture the 1st 0 crossing
//            if ((signal > 0) && (point >= 0) && (startSwing[i - 1] == 0) && (startSwing[i - 2] == 0)
//                && (startSwing[i - 3] == 0)) {
//                startSwing[i] = point;
//                if (debug)  {
//                    printf("startSwing : %d\n", i);
//                }
//
//            }

            if (signal > 0 && point > FOOT_SWING_THRESHOLD) {
                //stepFilter[i] =  FOOT_SWING_THRESHOLD;
                maxFootSwing = point;
                stepState = FOOT_SWING;
            }
            break;

        case FOOT_SWING:
            // do we still have a PEAK?
            if (signal > 0) {
                if (point > maxFootSwing) {
                    maxFootSwing = point;
                }
                // Potential valley. we may have a HEEL_STRIKE
            } else {
                if (point < 0) {
                    if (signal < 0) {
                        stepState = HEEL_STRIKE;
                    }
//					} else {
//						stepState = StepState.POTENTIAL_HEEL_STRIKE;
//					}
                }
            }
            break;

            // is this real or a false peak?
        case POTENTIAL_HEEL_STRIKE:
            // if false peak, return to FOOT_SWING
            if (signal >= 0 && point > 0) {
                stepState = FOOT_SWING;
            } else {
                stepState = HEEL_STRIKE;
                minHeelValley = point;
                //goodStepFilter[i] =  HEEL_STRIKE_VALLEY_INDICATOR;
            }
            break;

        case HEEL_STRIKE:
            if (debug) {
                printf(" FOOT SWING timestamp: %d maxFootSwing: %.3f\n",
                       i, maxFootSwing);
            }
            if (firstBelow) {
                nSteps++;
                firstBelow = false;
               // maxFootSwing = footSwingMeasurements(point, i, maxFootSwing);
            }
            // do we still have a HEEL STRIKE?
            if (signal < 0) {
                if (debug) {
                    printf("t: %d signal: %.3f  point: %.3f\n", i, point, goodStepThreshold);
                }

                if (point < minHeelValley) {
                    //goodStepFilter[i] =  HEEL_STRIKE_VALLEY_INDICATOR;
                    minHeelValley = point;
                }
                if (point < GOOD_SWING_THRESHOLD && firstBeep) {
                    ngood++;
                    if (PLOTTING_ARRAYS) {
                        beep[i] = GOOD_SWING_THRESHOLD;
                    }
                    firstBeep = false;
                    /*
                     * uncomment for android if (beepSound > 0) soundMgr.playSound(beepSound);
                     */
                    beepIt = 1;
                    if (debug) {
                        printf("BEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEP\n");
                    }
                }
                // no. then go back and look for a step
                // TODO transition the reset of gait
            } else {
                if (PLOTTING_ARRAYS) {
                    HeelStrikeValley[i] =  minHeelValley;
                }
                stepState = FLAT_FOOT;
                stateCount = SKIP_FLAT_FOOT_SAMPLES;
                if (debug) {
                    printf("HEEL STRIKE timestamp: %d minHeelValley: %.3f\n",
                            i, minHeelValley);
                }
                minHeelValley = 0.0;
            }
            break;

        case FLAT_FOOT:
            if (debug) printf("FLAT_FOOT s: %d\n", signal);
            stateCount--;
            if (signal < 0) {
                stepState = HEEL_OFF;
                stateCount = SKIP_HEEL_OFF_SAMPLES;
            }
            break;

        case HEEL_OFF:
            stateCount--;
            if (point < heelOffPowerMin) {
                heelOffPowerMin = point;
            }
            if (signal > 0) {
                //heelOffPower[i] =  heelOffPowerMin;
                heelOffPowerMin = 0.0;
                stepState = LOOKING_FOR_STEP;
            }
            break;
    }

    return stepState;
}