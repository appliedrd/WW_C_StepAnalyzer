//
// Created by tedhi on 5/28/2022.
//

#ifndef READ_ALLSTEPANALYTICS_H
typedef struct {
    char client[100];
    char foot[2];
    char fname[200];
    char detected_foot[10];
    int matched; //1 yes, -1 no, 0 unknown
} all_steps_t;

int read_allStepAnalytics(char * fname, all_steps_t * step_records, int * total_records ) ;
#define READ_ALLSTEPANALYTICS_H

#endif //UNTITLED_READ_ALLSTEPANALYTICS_H
