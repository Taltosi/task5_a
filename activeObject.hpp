// #pragma once

// #include "threadSafeQueue.hpp"

// #include <functional>

// class ActiveObject
// {
//     ThreadSafeQueue<int> *queue;
//     std::function<void(int)> taskFunc;
//     std::thread activeThread;
//     bool isActive;

//     void activeLoop();

// public:
//     ActiveObject();

//     void CreateActiveObject(std::function<void(int)> func);
//     ThreadSafeQueue<int> *getQueue();
//     void stop();
//     void setNextQueue(ThreadSafeQueue<int> *next);
// };

#ifndef ACTIVEOBJECT_HPP
#define ACTIVEOBJECT_HPP

#include "threadSafeQueue.hpp"
#include <functional>
#include <thread>
#include <atomic>

class ActiveObject
{
public:
    ActiveObject() : m_stop(false) {}
    ~ActiveObject() { stop(); }

    // Creates and runs a thread for the active object
    void CreateActiveObject(ThreadSafeQueue<void *> *queue, std::function<void(void *)> func);

    // Returns a pointer to the active object's queue
    ThreadSafeQueue<void *> *getQueue() { return m_queue; }

    // Stops the active object and releases all memory structures
    void stop();

private:
    ThreadSafeQueue<void *> *m_queue;
    std::function<void(void *)> m_func;
    std::thread m_thread;
    std::atomic<bool> m_stop;
};

#endif // ACTIVEOBJECT_HPP