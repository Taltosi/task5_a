#include "activeObject.hpp"

ActiveObject::ActiveObject() : queue(nullptr), isActive(false)
{
}

void ActiveObject::CreateActiveObject(std::function<void(int)> func)
{
    if (!isActive)
    {
        queue = new ThreadSafeQueue<int>();
        taskFunc = func;
        isActive = true;
        activeThread = std::thread(&ActiveObject::activeLoop, this);
    }
}

ThreadSafeQueue<int> *ActiveObject::getQueue()
{
    return queue;
}

void ActiveObject::stop()
{
    if (isActive)
    {
        isActive = false;
        activeThread.join();
        delete queue;
        queue = nullptr;
    }
}

void ActiveObject::activeLoop()
{
    while (isActive)
    {
        int task = queue->dequeue();
        taskFunc(task);
    }
}
