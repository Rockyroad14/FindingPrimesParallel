// 
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <thread>
#include <vector>
#include <future>

using namespace std;

const int THREAD_COUNT = 8;  // Total threads to be used is 8

void markNonPrimes(bool* num, int size, int start, int step)
{
    for (int i = start; i <= size; i += step)
    {
        if (num[i] == true)
        {
            int index = i + i;
            while (index <= size)
            {
                num[index] = false;
                index += i;
            }
        }
    }
}


int main(void)
{
    // Initialize variables and arrays
    int size = 100000000;
    long long sumprime = 0; 
    int* top = new int[10];
    bool* num = new bool[size + 1];
    std::fill(num, num + size + 1, true);
    int count = 0;

    // Initialzing Future variable to collect output from threads
    vector<future<void>> futures;

    clock_t begin = clock();
    // Async takes a function object as its argument and launches asyncronous threads.
    for (int t = 0; t < THREAD_COUNT; ++t)
    {
        futures.emplace_back(async(launch::async, markNonPrimes, num, size, t + 2, THREAD_COUNT));
    }

    for (auto& future : futures)
    {
        future.wait();
    }
    clock_t end = clock();
    
    int indexTen = 9;
    for (int i = size; i >= 2; i--)
    {
        if (num[i] == true)
        {
            count++;
            sumprime += i;

            if(indexTen >= 0)
            {
                top[indexTen] = i;
                indexTen--;
            }

        }
    }
    
    double parallel_time = (double) (end - begin) / CLOCKS_PER_SEC;

    ofstream Outputfile;
    Outputfile.open("primes.txt");
    Outputfile << "Elapsed Time: " << parallel_time << " " << count << " " << sumprime << " ";
    for(int i = 0; i < 10; i++)
    {
        Outputfile << top[i] << " ";
    }

    Outputfile.close();
    delete[] num; // Release memory
    delete[] top;


    return 0;
}
