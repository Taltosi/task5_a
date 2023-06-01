#pragma once

#include "threadSafeQueue.hpp"

#include <functional>

class ActiveObject
{
    ThreadSafeQueue<int> *queue;
    std::function<void(int)> taskFunc;
    std::thread activeThread;
    bool isActive;

    void activeLoop();

public:
    ActiveObject();

    void CreateActiveObject(std::function<void(int)> func);
    ThreadSafeQueue<int> *getQueue();
    void stop();
    void setNextQueue(ThreadSafeQueue<int> *next);
};
