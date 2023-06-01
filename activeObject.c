#include "activeObject.h"
#include <stdlib.h>
#include <pthread.h>

void* activeObjectThread(void *object)
{
    activeObject* ao = (activeObject*)(object);

    void *task;
    while((task = dequeue(ao->queue)))
    {
        ao->func(ao->next,task);
    }

    return NULL;
}

activeObject * createActiveObject(activeObject * next, void (*otherFunc)(activeObject * ao ,  void* item))
{
    activeObject* ao = (activeObject*)(malloc(sizeof(activeObject)));
    if (ao == NULL)
    {
        return NULL;
    }
    ao->func = otherFunc;
    ao->next = next;
    ThreadSafeQueue* q = (ThreadSafeQueue*)malloc(sizeof(ThreadSafeQueue));
    initializeQueue(q,10);
    ao->queue=q;
    pthread_create(&(ao->thread) , NULL , activeObjectThread , (void*)ao);
    return ao;
 
}

void stop(activeObject* ao)
{
    pthread_cancel(ao->thread);

    free(ao->queue);       
    free(ao);
}