# FindingPrimesParallel

## Program Instruction:
To compile the program: `g++ main.cpp`

Run the command: `./a.exe`

Outputs a file named prime.txt with the desired output.

Expected output: 

`Elapsed Time: 0.902 5761455 279209790387276 99999787 99999821 99999827 99999839 99999847 99999931 99999941 99999959 99999971 99999989`

## Summary of Approach:

The approach I used to the problem of finding primes from 1-10^8 is The Sieve of Eratosthenes (at least a modified version of it.) The basic premise of the algorithm is to start with an array of boolean and set all of them to true.
Then, start at 2 and set multiples of it to false since a prime number cannot have composite numbers. This component can be parallelized, marking the non-primes in the array as false. I created a separate function outside of the main function so that the function can be placed as an argument in `std::async`.
The function is then called 8 times, corresponding to the number of threads needed in this assignment. Each time a new thread is instantiated in the loop, the starting index of the marking function is indexed 2 more than the previous call, to allow no deadlock with accessing the same resource. 
Then, use futures to wait for all threads to finish. Then use a loop inside of the main to count and sum all primes.

## Correctness and Efficiency of Design:

The program uses asynchronous threads (`std::async`) to parallelize the marking of non-prime numbers. The async is called 8 times, which corresponds to the number of threads defined in global space. Race conditions are avoided by assigning disjoint portions of the array to different threads. Since this is the case, nothing is shared and there is no need for a mutex to synchronize the threads. An error that could occur when implementing and finding the sum of all primes to 10^8 is getting buffer overflow when adding since the `int` primitive storage limit is 2,147,483,647, and adding the sums of all those primes can create overflow. The best course of action is to use `long long` which can store up to 9,223,372,036,854,775,807. Counting and summing all the primes happen in linear time.

### Calculated Speedup







