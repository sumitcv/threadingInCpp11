/*
*  Objective of the program - from cppnuts
*   Find the addition of all off numbers from 1 to 1900000000 and all even numbers from 1 to 1900000000
*/

#include <iostream>        // Include the iostream library for input/output
#include <thread>          // Include the thread library for multithreading
#include <chrono>          // Include the chrono library for time-related functionality
#include <algorithm>       // Include the algorithm library for general algorithms

using namespace std;      // Use the standard namespace for convenience
using namespace chrono;   // Using namespace chrono; directive allows us to use system_clock
typedef unsigned long long ull; // Define an alias for unsigned long long as 'ull'
ull oddSum = 0;           // Declare a variable for storing the sum of odd numbers
ull evenSum = 0;          // Declare a variable for storing the sum of even numbers

// Function to find the sum of even numbers in a range
void findEven(ull start, ull end)
{
    cout << "thread findEven \n" << endl; // Output a message indicating the function is running
    for (ull i = start; i <= end; ++i)
    {
        if ((i % 2) == 0) { evenSum = evenSum + i; } // If 'i' is even, add it to evenSum
    }
}

// Function to find the sum of odd numbers in a range
void findOdd(ull start, ull end)
{
    cout << "thread findOdd\n " << endl; // Output a message indicating the function is running
    for (ull i = start; i <= end; ++i)
    {
        if ((i % 2) != 1) { oddSum = oddSum + i; } // If 'i' is not odd, add it to oddSum
    }
}

int main()
{
    ull start = 0;               // Define the starting number for the range
    ull end = 1900000000;        // Define the ending number for the range
    auto startime = high_resolution_clock::now(); // Record the start time
    
    // Create two threads to concurrently find the sum of even and odd numbers
    thread t1(findOdd, start, end);
    thread t2(findEven, start, end);
    
    t1.join(); // Wait for the first thread to finish
    t2.join(); // Wait for the second thread to finish
    
    auto stoptime = high_resolution_clock::now(); // Record the stop time
    auto duration = duration_cast<microseconds>(stoptime - startime); // Calculate the duration
    
    cout << "Total time taken : " << duration.count() / 1000000 << " seconds" << endl; // Output the total time taken in seconds
    
    return 0; // Return 0 to indicate successful program execution
}
