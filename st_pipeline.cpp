// #include "activeObject.hpp"
// #include "threadSafeQueue.hpp"
// #include <cmath>
// #include <cstdlib>
// #include <ctime>
// #include <iostream>
// #include <unistd.h>
// #include <chrono>
// #include <random>

// int seed;
// ActiveObject ao1;
// ActiveObject ao2;
// ActiveObject ao3;
// ActiveObject ao4;

// // Function to check if a number is prime
// int isPrime(unsigned int num)
// {
//     if (num == 2)
//     {
//         return 1;
//     }
//     if (num < 2 || num % 2 == 0)
//     {
//         return 0;
//     }
//     for (unsigned int i = 3; i <= sqrt(num); i += 2)
//     {
//         if (num % i == 0)
//         {
//             return 0;
//         }
//     }
//     return 1;
// }

// // Function to be executed by the first ActiveObject
// void processNumbersAO1(int N)
// {
//     std::mt19937 rng(seed);
//     std::uniform_int_distribution<int> dist(100000, 999999);
//     for (int i = 0; i < N; ++i)
//     {
//         int num = dist(rng);
//         std::cout << num << " was generated\n";
//         ao2.getQueue()->enqueue(num);
//         std::this_thread::sleep_for(std::chrono::milliseconds(1));
//     }
// }

// // Function to be executed by the second ActiveObject
// void processNumbersAO2(int number)
// {
//     std::cout << "ao2 func\n";
//     std::cout << "Number: " << number << std::endl;
//     std::cout << "Is Prime: " << (isPrime(number) ? "true" : "false") << std::endl;
//     number += 11;
//     ao3.getQueue()->enqueue(number);
// }

// // Function to be executed by the third ActiveObject
// void processNumbersAO3(int number)
// {
//     std::cout << "ao3 func\n";
//     std::cout << "Number: " << number << std::endl;
//     std::cout << "Is Prime: " << (isPrime(number) ? "true" : "false") << std::endl;
//     number -= 13;
//     ao4.getQueue()->enqueue(number);
// }

// // Function to be executed by the fourth ActiveObject
// void processNumbersAO4(int number)
// {
//     std::cout << "ao4 func\n";
//     std::cout << "Number: " << number << std::endl;
//     number += 2;
//     std::cout << "Modified Number: " << number << std::endl;
// }

// int main(int argc, char *argv[])
// {
//     if (argc < 2 || argc > 3)
//     {
//         std::cerr << "Usage: ./st_pipline N [seed]\n";
//         return 1;
//     }
//     int N = 0;
//     seed = 0;
//     if (argc >= 2)
//         N = atoi(argv[1]);
//     if (argc >= 3)
//         seed = atoi(argv[2]);
//     else
//     {
//         std::mt19937 rng(static_cast<unsigned int>(time(NULL)));
//         std::uniform_int_distribution<int> dist(1, 100);
//         seed = dist(rng);
//     }

//     std::cout << "creating AOs\n";

//     ao1.CreateActiveObject(processNumbersAO1);
//     ao1.getQueue()->enqueue(N);
//     ao2.CreateActiveObject(processNumbersAO2);
//     ao3.CreateActiveObject(processNumbersAO3);
//     ao4.CreateActiveObject(processNumbersAO4);

//     // sleep(N);

//     ao1.stop();
//     ao2.stop();
//     ao3.stop();
//     ao4.stop();

//     return 0;
// }

#include "activeObject.hpp"
#include <iostream>
#include <random>
#include <chrono>

// Function to check if a number is prime
int isPrime(unsigned int num)
{
    if (num == 2)
    {
        return 1;
    }
    if (num < 2 || num % 2 == 0)
    {
        return 0;
    }
    for (unsigned int i = 3; i <= sqrt(num); i += 2)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}


// Generates N random numbers and enqueues them in the given queue
void generateNumbers(ThreadSafeQueue<void *> *queue, int N, unsigned int seed)
{
    std::mt19937 rng(seed == 0 ? std::chrono::steady_clock::now().time_since_epoch().count() : seed);
    std::uniform_int_distribution<int> dist(100000, 999999);
    for (int i = 0; i < N; i++)
    {
        int num = dist(rng);
        queue->enqueue(new int(num));
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

// Prints the number, checks if it's prime, and enqueues it in the next queue
void checkPrime(ThreadSafeQueue<void *> *inQueue, ThreadSafeQueue<void *> *outQueue)
{
    while (true)
    {
        int *num = static_cast<int *>(inQueue->dequeue());
        if (num == nullptr)
            break;
        std::cout << *num << std::endl;
        bool isPrimeNum = isPrime(*num);
        std::cout << std::boolalpha << isPrimeNum << std::endl;
        outQueue->enqueue(new int(*num + 11));
        delete num;
    }
}

// Prints the number, checks if it's prime, and enqueues it in the next queue
void checkPrime2(ThreadSafeQueue<void *> *inQueue, ThreadSafeQueue<void *> *outQueue)
{
    while (true)
    {
        int *num = static_cast<int *>(inQueue->dequeue());
        if (num == nullptr)
            break;
        std::cout << *num << std::endl;
        bool isPrimeNum = isPrime(*num);
        std::cout << std::boolalpha << isPrimeNum << std::endl;
        outQueue->enqueue(new int(*num - 13));
        delete num;
    }
}

// Prints the number, adds 2, and prints the new number
void printNumber(ThreadSafeQueue<void *> *inQueue)
{
    while (true)
    {
        int *num = static_cast<int *>(inQueue->dequeue());
        if (num == nullptr)
            break;
        std::cout << *num << std::endl;
        *num += 2;
        std::cout << *num << std::endl;
        delete num;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cerr << "Usage: " << argv[0] << " N [seed]" << std::endl;
        return 1;
    }

    int N = std::stoi(argv[1]);
    unsigned int seed = argc == 3 ? std::stoi(argv[2]) : 0;

    ThreadSafeQueue<void *> q1, q2, q3, q4;

    ActiveObject ao1, ao2, ao3, ao4;

    ao1.CreateActiveObject(&q1, std::bind(generateNumbers, &q1, N, seed));
    ao2.CreateActiveObject(&q1, [&q2](void *arg) {
        checkPrime(static_cast<ThreadSafeQueue<void *> *>(arg), &q2);
    });

    ao3.CreateActiveObject(&q2, [&q3](void *arg) {
        checkPrime2(static_cast<ThreadSafeQueue<void *> *>(arg), &q3);
    });    
    ao4.CreateActiveObject(&q3, [](void *arg) {
        printNumber(static_cast<ThreadSafeQueue<void *> *>(arg));
    });
    ao2.getQueue()->enqueue(nullptr);
    ao3.getQueue()->enqueue(nullptr);
    ao4.getQueue()->enqueue(nullptr);

    ao1.stop();
    ao2.stop();
    ao3.stop();
    ao4.stop();

    return 0;
}
