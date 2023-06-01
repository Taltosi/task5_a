#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

template <typename T>
class ThreadSafeQueue
{
    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _cv;

public:
    void enqueue(T elem);
    T dequeue();
};