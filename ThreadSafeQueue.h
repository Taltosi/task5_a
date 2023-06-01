#pragma once
#include <pthread.h>
#include <stdio.h>

typedef struct ThreadSafeQueue
{
    void **items;
    int capacity;
    int size;
    int head;
    int tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}ThreadSafeQueue;

void initializeQueue(ThreadSafeQueue* queue, int capacity);
void enqueue(ThreadSafeQueue *queue , void *item);
void* dequeue(ThreadSafeQueue* queue);