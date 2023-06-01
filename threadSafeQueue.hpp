// #pragma once

// #include <iostream>
// #include <queue>
// #include <mutex>
// #include <condition_variable>
// #include <thread>

// template <typename T>
// class ThreadSafeQueue
// {
//     std::queue<T> _queue;
//     std::mutex _mutex;
//     std::condition_variable _cv;

// public:
//     void enqueue(T elem);
//     T dequeue();
// };
#ifndef THREADSAFEQUEUE_HPP
#define THREADSAFEQUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue() {}

    // Adds an item to the back of the queue
    void enqueue(const T &item)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(item);
        lock.unlock();
        m_condition.notify_one();
    }

    // Removes and returns an item from the front of the queue
    // If the queue is empty, waits until an item is available
    T dequeue()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_queue.empty())
        {
            m_condition.wait(lock);
        }
        T item = m_queue.front();
        m_queue.pop();
        return item;
    }

    // Returns true if the queue is empty
    bool empty() const
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

private:
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_condition;
};

#endif // THREADSAFEQUEUE_HPP