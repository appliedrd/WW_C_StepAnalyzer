//
// Created by ted on 2022-03-17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../inc/main.h"

void clear_data(int rows, int cols, double data[][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            data[i][j] = 0;
}

void matrixColtoArray(double data[][COLS], double a[], int col, int size) {
    for (int i = 0; i < size; i++) {
        a[i] = data[i][col];
    }
}

int read_csv(char *filename, double data[][COLS], bool debug) {
    FILE *file;
    file = fopen(filename, "r");
    int i = 0;
    char line[4098];
    fgets(line, 4098, file); // read header
    while (fgets(line, 4098, file) && (i < ROWS)) {
        int j = 0;
        char *token = strtok(line, ",");
        while (token != NULL) {
            if (debug) {
                printf("%s\t", token);
            }
            if (j < COLS) {
                data[i][j++] = atof(token);
            }
            token = strtok(NULL, ",");
        }
        if (debug) {
            printf("\n");
        }
        i++;
    }
    return i;
}


