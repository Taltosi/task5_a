#include "activeObject.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <chrono>
#include <random>

int seed;
ActiveObject ao1;
ActiveObject ao2;
ActiveObject ao3;
ActiveObject ao4;

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

// Function to be executed by the first ActiveObject
void processNumbersAO1(int N)
{
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(100000, 999999);
    for (int i = 0; i < N; ++i)
    {
        int num = dist(rng);
        std::cout << num << " was generated\n";
        ao2.getQueue()->enqueue(num);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

// Function to be executed by the second ActiveObject
void processNumbersAO2(int number)
{
    std::cout << "ao2 func\n";
    std::cout << "Number: " << number << std::endl;
    std::cout << "Is Prime: " << (isPrime(number) ? "true" : "false") << std::endl;
    number += 11;
    ao3.getQueue()->enqueue(number);
}

// Function to be executed by the third ActiveObject
void processNumbersAO3(int number)
{
    std::cout << "ao3 func\n";
    std::cout << "Number: " << number << std::endl;
    std::cout << "Is Prime: " << (isPrime(number) ? "true" : "false") << std::endl;
    number -= 13;
    ao4.getQueue()->enqueue(number);
}

// Function to be executed by the fourth ActiveObject
void processNumbersAO4(int number)
{
    std::cout << "ao4 func\n";
    std::cout << "Number: " << number << std::endl;
    number += 2;
    std::cout << "Modified Number: " << number << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        std::cerr << "Usage: ./st_pipline N [seed]\n";
        return 1;
    }
    int N = 0;
    seed = 0;
    if (argc >= 2)
        N = atoi(argv[1]);
    if (argc >= 3)
        seed = atoi(argv[2]);
    else
    {
        std::mt19937 rng(static_cast<unsigned int>(time(NULL)));
        std::uniform_int_distribution<int> dist(1, 100);
        seed = dist(rng);
    }

    std::cout << "creating AOs\n";

    ao1.CreateActiveObject(processNumbersAO1);
    ao1.getQueue()->enqueue(N);
    ao2.CreateActiveObject(processNumbersAO2);
    ao3.CreateActiveObject(processNumbersAO3);
    ao4.CreateActiveObject(processNumbersAO4);

    // sleep(N);

    ao1.stop();
    ao2.stop();
    ao3.stop();
    ao4.stop();

    return 0;
}
