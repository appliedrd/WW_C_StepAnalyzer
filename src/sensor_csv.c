//
// Created by tedhi on 5/27/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include "../inc/sensor_csv.h"

int read_sensor_csv(char * fname, imu_vector_t * records, int * total_records ) {
    FILE *fp;
    size_t count = 0;
//    imu_vector_t records[NUMRECORDS];
    fp = fopen(fname, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }

    char buf[200];
    char left[200];
    int sample;
    int times;
    double num;
    fgets(buf, sizeof buf, fp);
    while (fgets(buf, sizeof buf, fp) != NULL) {
        char tokens[12][15];
        int result = sscanf(buf,
                            "%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%s",
                            tokens[0], tokens[1],
                            tokens[2], tokens[3], tokens[4],
                            tokens[5], tokens[6], tokens[7],
                            tokens[8], tokens[9], tokens[10],
                            tokens[11]

        );
        records[count].sample = atoi(tokens[0]);
        records[count].timestamp = atoi(tokens[1]);
        records[count].GyroscopeX_ds = atof(tokens[2]);
        records[count].GyroscopeY_ds = atof(tokens[3]);
        records[count].GyroscopeZ_ds = atof(tokens[4]);
        records[count].AccelerometerX_ms2 = atof(tokens[5]);
        records[count].AccelerometerY_ms2 = atof(tokens[6]);
        records[count].AccelerometerZ_ms2 = atof(tokens[7]);
        records[count].MagX = atof(tokens[8]);
        records[count].MagY = atof(tokens[9]);
        records[count].MagZ = atof(tokens[10]);
        records[count].foot = tokens[11][0];
        if (count == NUMRECORDS) {
            *total_records = count;
            return -1;
        }
        count++;
    }
    *total_records = count;
    return 0;
}
