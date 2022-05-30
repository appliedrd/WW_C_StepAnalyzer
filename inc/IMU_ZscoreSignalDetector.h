//
// Created by ted on 2022-03-21.
//

#ifndef WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
#define WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
#endif //WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
typedef enum {
    LOOKING_FOR_STEP = 1,
    FOOT_SWING = 2,
    POTENTIAL_HEEL_STRIKE = 3,
    HEEL_STRIKE = 4,
    FLAT_FOOT = 5,
    HEEL_OFF = 6,
} StepState;
void initStepDetector();
StepState IMU_doStepDetect(double point, int i, int signal, StepState stepState, bool debug);



