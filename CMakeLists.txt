cmake_minimum_required(VERSION 3.21)
project(WW_C_StepAnalyzer C)

set(CMAKE_C_STANDARD 99)

add_executable(WW_C_StepAnalyzer main.c src/IMU_Signal.c inc/IMU_Signal.h inc/main.h
        src/FileProcess.c inc/FileProcess.h
        src/sensor_csv.c inc/sensor_csv.h
        src/IMU_ZscoreSignalDetector.c inc/IMU_ZscoreSignalDetector.h
        src/Plots.c inc/Plots.h src/jenniferZ.c
        src/foot_detect.c inc/foot_detect.h
        src/read_allStepAnalytics.c inc/read_allStepAnalytics.h)
target_link_libraries(WW_C_StepAnalyzer m)