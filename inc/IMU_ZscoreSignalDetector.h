//
// Created by ted on 2022-03-21.
//

#ifndef WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
#define WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
#endif //WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
enum StepState {
    LOOKING_FOR_STEP, FOOT_SWING, POTENTIAL_HEEL_STRIKE, HEEL_STRIKE, FLAT_FOOT, HEEL_OFF,
};
void initStepDetector();
enum StepState IMU_doStepDetect(double point, int i, int signal, enum StepState stepState, bool debug);



