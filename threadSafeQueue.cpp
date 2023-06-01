#include "threadSafeQueue.hpp"

using namespace std;

template <typename T>
void ThreadSafeQueue<T>::enqueue(T elem)
{
    lock_guard<mutex> lock(_mutex);
    _queue.push(elem);
}

template <typename T>
T ThreadSafeQueue<T>::dequeue()
{
    unique_lock<mutex> lock(_mutex);
    while (_queue.empty())
        _cv.wait(lock);
    T elem = _queue.front();
    _queue.pop();
    return elem;
}

template class ThreadSafeQueue<int>;
