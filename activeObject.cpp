// #include "activeObject.hpp"

// ActiveObject::ActiveObject() : queue(nullptr), isActive(false)
// {
// }

// void ActiveObject::CreateActiveObject(std::function<void(int)> func)
// {
//     if (!isActive)
//     {
//         queue = new ThreadSafeQueue<int>();
//         taskFunc = func;
//         isActive = true;
//         activeThread = std::thread(&ActiveObject::activeLoop, this);
//     }
// }

// ThreadSafeQueue<int> *ActiveObject::getQueue()
// {
//     return queue;
// }

// void ActiveObject::stop()
// {
//     // if (isActive)
//     // {
//     //     isActive = false;
//     //     activeThread.join();
//     //     delete queue;
//     //     queue = nullptr;
//     // }
//       isActive = true;
//         if (activeThread.joinable())
//             activeThread.join();
// }

// void ActiveObject::activeLoop()
// {
//     while (isActive)
//     {
//         int task = queue->dequeue();
//         taskFunc(task);
//     }
// }

#include "activeObject.hpp"

void ActiveObject::CreateActiveObject(ThreadSafeQueue<void *> *queue, std::function<void(void *)> func)
{
    m_queue = queue;
    m_func = func;
    m_stop = false;

    m_thread = std::thread([this]() {
        while (!m_stop)
        {
            void *task = m_queue->dequeue();
            if (task != nullptr)
            {
                m_func(task);
            }
        }
    });
}

void ActiveObject::stop()
{
    m_stop = true;
    if (m_thread.joinable())
    {
        m_thread.join();
    }
    delete m_queue;
    m_queue = nullptr;
}