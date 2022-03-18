#include <stdio.h>
#include "inc/Signal.h"
#include "inc/main.h"

int main() {
    printf("Hello, World!\n");
    int lag = 5;
    float threshold = 3;
    float influence = 0.5;
    float y[]=  {1,1,1.1,1,0.9,1,1,1.1,1,0.9,1,1.1,1,1,0.9,1,1,1.1,1,1,1,1,1.1,0.9,1,1.1,1,1,0.9,
            1,1.1,1,1,1.1,1,0.8,0.9,1,1.2,0.9,1,1,1.1,1.2,1,1.5,1,3,2,5,3,2,1,1,1,0.9,1,1,3,       2.6,4,3,3.2,2,1,1,0.8,4,4,2,2.5,1,1,1,1.2,1,1.5,1,3,2,5,3,2,1,1,1,0.9,1,1,3,
            2.6,4,3,3.2,2,1,1,0.8,4,4,2,2.5,1,1,1};

    int signals[SAMPLE_LENGTH];

    init_signals(signals, y);

    for (int i = LAG; i < SAMPLE_LENGTH; i++) {
        doSignal(y[i], i, signals);
    }
    return 0;
}
