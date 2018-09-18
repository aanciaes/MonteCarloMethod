#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>

#define RADIUS 1

pthread_mutex_t lock;
int totalShots;
int shotsInTarget;

/* generate a random floating point number from min to max */
double fRand()
{
    double f = (double)rand() / RAND_MAX;
    return f * RADIUS;
}

double calculateDistanceToPoint (double x, double y) {
    return sqrt((x * x) + (y * y));
}

void setTotal (int localTotal, int localInTarget) {

    pthread_mutex_lock(&lock); // Locks mutex

    totalShots += localTotal;
    shotsInTarget += localInTarget;

    pthread_mutex_unlock(&lock); // Unlock mutex
}

void* approxPi (void *args) {

    int numberOfTries = *(int*) args;
    int localTotal = 0;
    int localInTarget = 0;

    srand(getpid());

    int i;
    for (i = 0; i < numberOfTries; i++) {
        double xCoor = fRand();
        double yCoor = fRand();

        double distance = calculateDistanceToPoint(xCoor, yCoor);
        localTotal++;

        if (distance <= 1.0) {
            localInTarget++;
        }
    }

    setTotal(localTotal, localInTarget);

    return NULL;
}

int main(int argc, char **argv) {

    int numberOfTries;
    int numberOfThreads;

    if(argc != 3) {
        printf("Usage: $ ApproxPi numberOfShots numberOfThreads\n");
        return 1;
    }

    numberOfTries = strtol(argv[1], NULL, 0);
    numberOfThreads = strtol(argv[2], NULL, 0);

    totalShots = 0;
    shotsInTarget = 0;
    int shotsByThread = numberOfTries / numberOfThreads;
    printf("Shots by thread: %d\n", shotsByThread);

    pthread_t tid[numberOfThreads];
    for (int i = 0; i < numberOfThreads; i++) {
        int *arg = malloc(sizeof(*arg));
        *arg = shotsByThread;
        pthread_create(&tid[i], NULL, approxPi, arg);
    }
    for (int i = 0; i < numberOfThreads; i++)
        pthread_join(tid[i], NULL);

    double pi = ((double)shotsInTarget/(double)totalShots)*4;
    printf("Approximation of Pi: %f\n", pi);

    return 0;
}