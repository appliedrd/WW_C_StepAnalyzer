cmake_minimum_required(VERSION 3.21)
project(WW_C_StepAnalyzer C)

set(CMAKE_C_STANDARD 99)

add_executable(WW_C_StepAnalyzer main.c src/Signal.c inc/Signal.h inc/main.h src/FileProcess.c inc/FileProcess.h src/ZscoreSignalDetector.c inc/ZscoreSignalDetector.h)
target_link_libraries(WW_C_StepAnalyzer m)