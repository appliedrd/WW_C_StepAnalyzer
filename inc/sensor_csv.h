//
// Created by tedhi on 5/27/2022.
//

#ifndef SENSOR_CSV_H
#define NUMRECORDS 20000
typedef struct {
    int sample;
    int timestamp;
    double GyroscopeX_ds;
    double GyroscopeY_ds;
    double GyroscopeZ_ds;
    double AccelerometerX_ms2;
    double AccelerometerY_ms2;
    double AccelerometerZ_ms2;
    double MagX;
    double MagY;
    double MagZ;
    char foot;
} imu_vector_t;

int read_sensor_csv(char * fname, imu_vector_t * records, int * total_records );
#define SENSOR_CSV_H

#endif //UNTITLED_SENSOR_CSV_H
