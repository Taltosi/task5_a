#include "ThreadSafeQueue.h"

typedef struct activeObject
{
    void(*func)(struct activeObject * ao, void* item); 
    ThreadSafeQueue *queue;                 
    pthread_t thread; 
    struct activeObject * next;
}activeObject;

void* activeObjectThread(void *object);
activeObject * createActiveObject(activeObject * next, void (*otherFunc)(activeObject * ao ,  void* item));
void stop(activeObject *ao);