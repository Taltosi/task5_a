#include "ThreadSafeQueue.h"
#include <stdlib.h>

// Initialize the queue
void initializeQueue(ThreadSafeQueue* queue, int capacity)
{
    queue->items = (void**)malloc(capacity * sizeof(void*));
    queue->capacity = capacity;
    queue->size = 0;
    queue->head = 0;
    queue->tail = -1;
    pthread_mutex_init(&(queue->mutex), NULL);
    pthread_cond_init(&(queue->cond), NULL);
}

// Enqueue an element into the queue
void enqueue(ThreadSafeQueue *queue , void *item)
{
       pthread_mutex_lock(&queue->mutex); // Acquire the mutex lock if isn't locked
    while (queue->size >= queue->capacity) { // Wait as long as the queue is full
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->items[queue->tail] = item;
    queue->size++;

    pthread_cond_signal(&queue->cond); // Signal waiting threads
    pthread_mutex_unlock(&queue->mutex); // Release
}

// Dequeue an element from the queue
void* dequeue(ThreadSafeQueue* queue)
{
    pthread_mutex_lock(&(queue->mutex));

    while (queue->size == 0)    // while the queue is empty
    {
        pthread_cond_wait(&(queue->cond), &(queue->mutex));
    }

    void* item = queue->items[queue->head];
    queue->head = (queue->head + 1) % queue->capacity;
    queue->size--;

    pthread_cond_signal(&(queue->cond));       // Signal waiting threads
    pthread_mutex_unlock(&(queue->mutex));    //Release

    return item;
}