//
// Created by ted on 2022-03-17.
//

#ifndef WW_C_STEPANALYZER_FILEPROCESS_H
#define WW_C_STEPANALYZER_FILEPROCESS_H
#include "../inc/main.h"
void clear_data(int rows, int cols, double data[][COLS]);
int read_csv(char *filename, double data[ROWS][COLS], bool debug);
void matrixColtoArray(double data[][COLS], double a[], int col, int size);
#endif //WW_C_STEPANALYZER_FILEPROCESS_H
