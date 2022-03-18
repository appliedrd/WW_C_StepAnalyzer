//
// Created by ted on 2022-03-11.
//

#ifndef WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
#define WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H

#endif //WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
void init_signals(int *signals, float *y);
void doSignal(float y, int i, int *signals);
void doSignalOLD(float y[], int *signals, int lag, float threshold, float influence);

