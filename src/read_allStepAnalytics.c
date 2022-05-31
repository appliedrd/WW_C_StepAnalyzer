//
// Created by tedhi on 5/27/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../inc/read_allStepAnalytics.h"

#define MANUAL_MERGE 1

int read_allStepAnalytics(char * fname, all_steps_t * step_records, int * total_records ) {
    FILE *fp;
    size_t count = 0;
//    imu_vector_t records[NUMRECORDS];
    fp = fopen(fname, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error reading file\n");
        return 1;
    }

    char buf[1000];
    fgets(buf, sizeof buf, fp);
    fgets(buf, sizeof buf, fp);
    while (fgets(buf, sizeof buf, fp) != NULL) {
        char tokens[12][200];
        int result = sscanf(buf,
                            "%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%[^','],%s",
                            tokens[0], tokens[1],
                            tokens[2], tokens[3], tokens[4],
                            tokens[5],  tokens[6], tokens[7],
                            tokens[8],  tokens[9], tokens[10]
        );
        char * foot = "UNKNOWN";
        bool useFile = false;
        if (strcmp(tokens[5], "L") == 0)  {
            foot = "LEFT";
            useFile = true;
        } else if (strcmp(tokens[5], "R") == 0)  {
            foot = "RIGHT";
            useFile = true;
        }
        if (useFile) {
            if (MANUAL_MERGE) {
                printf("%s client: %s foot: %s fname: %s \n", foot, tokens[3], tokens[5], tokens[1]);
                strcpy(step_records[count].client, tokens[3]);
                strcpy(step_records[count].foot, tokens[5]);
                strcpy(step_records[count].fname, tokens[1]);
            } else {
                printf("%s client: %s foot: %s fname: %s \n", foot, tokens[3], tokens[5], tokens[8]);
                strcpy(step_records[count].client, tokens[3]);
                strcpy(step_records[count].foot, tokens[5]);
                strcpy(step_records[count].fname, tokens[8]);
        }
            count++;
        }
    }
    *total_records = count;
    return 0;
}
