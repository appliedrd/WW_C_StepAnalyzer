//
// Created by ted on 2022-03-11.
//

#ifndef WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
#define WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H

#endif //WW_C_STEPANALYZER_ZSCORESIGNALDETECTOR_H
void IMU_init_signals();
double lowpass_filter(int filter_div, int i, double point, double filtered);
void printSignal(int l, int i, double p, int s);
int IMU_doSignal(double y, int i,  int last_signal);

