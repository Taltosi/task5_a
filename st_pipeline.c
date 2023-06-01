#include "activeObject.h"
#include "ThreadSafeQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


// check if prime num
int isPrime(unsigned int n) {                       
    if (n == 2) {
        return 1;
    }
    if (n < 2 || n % 2 == 0) {
        return 0;
    }
    for (unsigned int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

// The task for Ao1
void generateNumbers(activeObject *next, void *otherSeed)
{
    int maxNum = 900000;
    int minNum = 100000;
    int randomNum;
    randomNum = (rand() % (maxNum - minNum + 1)) + minNum;
    void *task = &randomNum;
    sleep(1);
    enqueue(next->queue, task);
}

// The task for Ao2
void checkPrimeAndAdd11(activeObject *next, void *item)
{
    int num = *(int *)(item);
    printf("%d\n", num);
    if (isPrime(num))
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }
    num += 11;
    int* numP = malloc(sizeof(int));
    *numP = num;
    enqueue(next->queue, numP);
}

// The task for Ao3
void checkPrimeAndSubtract13(activeObject *next, void *item)
{
    int num = *(int *)(item);
    printf("%d\n", num);
    if (isPrime(num))
    {
        printf("True\n");
    }
    else
    {
        printf("False\n");
    }
    num -= 13;
    int* numP = malloc(sizeof(int));
    *numP = num;
    enqueue(next->queue, numP);       
    free(item);
}

// The task for Ao4
void printAndAdd2(activeObject *next, void *item)
{
    int num = *(int *)(item);
    printf("%d\n", num);
    num += 2;
    printf("%d\n", num);
    free(item);
}

int main(int argc, char *argv[])
{
    int randomSeed = 0;
    if (argc > 3)
    {
        printf("Too many arguments\n");
        exit(0);
    }

    else if (argc == 2)
    {
        srand(time(NULL));
        randomSeed = (rand() % (10));
    }
    else if(argc == 3)
    {
        randomSeed = atoi(argv[2]);
    }

    activeObject *Ao4 = createActiveObject(NULL, printAndAdd2);
    activeObject *Ao3 = createActiveObject(Ao4, checkPrimeAndSubtract13);
    activeObject *Ao2 = createActiveObject(Ao3, checkPrimeAndAdd11);
    activeObject *Ao1 = createActiveObject(Ao2, generateNumbers);


    void *task = &randomSeed;

    for (int i = 0; i <= atoi(argv[1]); i++)
    {
        int randomSeed = *(int *)task;
        enqueue(Ao1->queue, &randomSeed);       
    }

    while (Ao1->queue->size > 0) {}
    sleep(1);
    stop(Ao1);

    while (Ao2->queue->size > 0) {}
    stop(Ao2);

    while (Ao3->queue->size > 0) {}
    stop(Ao3);

    while (Ao4->queue->size > 0) {}
    stop(Ao4);

    return 0;
}

