#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

struct Result {
    int totalShots;
    int shotsInTarget;
};

struct Input {
    int numberOfShots;
    struct Result* resultPointer;
};

/* generate a random floating point number from min to max */
double fRand(unsigned int* state) {
    return (double)rand_r(state) / RAND_MAX;
}

double calculateDistanceToPoint (double x, double y) {
    return sqrt((x * x) + (y * y));
}

void writeTotal (int localTotalShots, int localShotsInTarget, struct Result* rst) {
    rst->totalShots = localTotalShots;
    rst->shotsInTarget = localShotsInTarget;
}

void* approxPi (void *args) {

    struct Input* input = (struct Input*) args;
    int numberOfShots = input->numberOfShots;

    int localTotal = 0;
    int localInTarget = 0;

    // XOR pid with time to create semi-unique state
    unsigned int state = time(NULL) ^ getpid();

    int i;
    for (i = 0; i < numberOfShots; i++) {

        double xCoor = fRand(&state);
        double yCoor = fRand(&state);

        double distance = calculateDistanceToPoint(xCoor, yCoor);
        localTotal++;

        if (distance <= 1.0) {
            localInTarget++;
        }
    }

    writeTotal(localTotal, localInTarget, input->resultPointer);

    return NULL;
}

int main(int argc, char **argv) {

    int numberOfTries;
    int numberOfThreads;
    int totalShots = 0;
    int shotsInTarget = 0;

    if(argc != 3) {
        printf("Usage: $ ApproxPi numberOfShots numberOfThreads\n");
        return 1;
    }

    numberOfTries = strtol(argv[1], NULL, 0);
    numberOfThreads = strtol(argv[2], NULL, 0);

    int shotsByThread = numberOfTries / numberOfThreads;

    struct Input inputs [numberOfThreads];

    // Place where each tread will write the results
    struct Result rst [numberOfThreads];

    pthread_t tid[numberOfThreads];

    for (int i = 0; i < numberOfThreads; i++) {
        inputs[i].numberOfShots = shotsByThread;
        inputs[i].resultPointer = &rst[i];

        void* args = (void*) &inputs[i];

        pthread_create(&tid[i], NULL, approxPi, args);
    }

    for (int i = 0; i < numberOfThreads; i++)
        pthread_join(tid[i], NULL);


    for (int i=0; i<numberOfThreads; i++) {
        totalShots += rst[i].totalShots;
        shotsInTarget += rst[i].shotsInTarget;
    };

    if(totalShots != numberOfTries){
        printf("The threads did not perform all of the shots\n");
    }

    double pi = ((double)shotsInTarget/(double)totalShots)*4;
    printf("Approximation of Pi: %f\n", pi);

    return 0;
}
