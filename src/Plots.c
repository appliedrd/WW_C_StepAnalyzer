//
// Created by ted on 2022-03-22.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void testPlot() {
    int x[] = { 2015, 2016, 2017, 2018, 2019, 2020 };
    int y[] = { 344, 543, 433, 232, 212, 343 };

    FILE *gnuplot = popen("gnuplot", "w");
    if (!gnuplot) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    fprintf(gnuplot, "plot '-' u 1:2 t 'Price' w lp\n");
    for (int i = 0; i < 6; ++i) {
        fprintf(gnuplot,"%d %d\n", i, y[i]);
    }
    fprintf(gnuplot, "e\n");
    fprintf(stdout, "Click Ctrl+d to quit...\n");
    fflush(gnuplot);
    getchar();

    pclose(gnuplot);
}

void plotXY(double y[], int start, int stop) {
    FILE *gnuplot = popen("gnuplot", "w");
    if (!gnuplot) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    fprintf(gnuplot, "plot '-' u 1:2 t 'Angular Velocity' w l\n");
    for (int i = start; i < stop; ++i) {
        fprintf(gnuplot,"%d %f\n", i, y[i]);
    }
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);
    getchar();

    pclose(gnuplot);
}

void plotXYint(int y[], int start, int stop) {
    FILE *gnuplot = popen("gnuplot", "w");
    if (!gnuplot) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    fprintf(gnuplot, "plot '-' u 1:2 t 'Angular Velocity' w l\n");
    for (int i = start; i < stop; ++i) {
        fprintf(gnuplot,"%d %d\n", i, y[i]);
    }
    fprintf(gnuplot, "e\n");
    fflush(gnuplot);
    getchar();

    pclose(gnuplot);
}

void create_csv(char *filename, double z[], int signal[],int start,int stop) {
    printf("\n Creating %s.csv file",filename);
    FILE *fp;
    int i;
    fp=fopen(filename,"w+");
    for(i=start;i<=stop;i++){
        fprintf(fp,"%d, %0.3f, %d\n",i, z[i], signal[i]);
    }
    fclose(fp);
    printf("\n %s file created",filename);
}

void create_multi_csv(char *filename, double z[], double hs[], double beep[], int signal[],int start,int stop) {
    printf("\n Creating %s.csv file",filename);
    FILE *fp;
    int i;
    fp=fopen(filename,"w+");
    for(i=start;i<=stop;i++){
        fprintf(fp,"%d, %0.3f, %0.3f,  %0.3f,  %d\n",i, z[i], hs[i], beep[i], signal[i]);
    }
    fclose(fp);
    printf("\n %s file created",filename);
}



