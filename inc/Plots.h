//
// Created by ted on 2022-03-22.
//

#ifndef WW_C_STEPANALYZER_PLOTS_H
#define WW_C_STEPANALYZER_PLOTS_H

#endif //WW_C_STEPANALYZER_PLOTS_H
void testPlot();
void plotXY(double y[], int start, int stop);
void plotXYint(int y[], int start, int stop);
void create_csv(char *filename, double z[], int signal[],int start,int stop);
void create_multi_csv(char *filename, double z[], double hs[], double beep[], int signal[],int start,int stop);