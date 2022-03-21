//
// Created by ted on 2022-03-11.
//

#ifndef WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
#define WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H

#endif //WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
void init_signals(int *signals, double *y);
double lowpass_filter(int filter_div, int i, double point, double filtered);
void printSignal(int l, int i, double p, int s);
void doSignal(double y, int i, int *signals);
void doSignalOLD(double y[], int *signals, int lag, double threshold, double influence);

