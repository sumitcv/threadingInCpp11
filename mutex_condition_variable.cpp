/* 
this code explain how the condition variable works in C++
  */

#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::chrono ;

condition_variable cv;
mutex m;
int accountBalance = 0;

void add_amount(int id)
{
    
    cout << id  << ": mutex locking ..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    lock_guard<mutex> lg(m); // तुरंत लोकक होगा
    this_thread::sleep_for(chrono::seconds(1));
    cout << id << ":  in the cs" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    accountBalance = accountBalance + 500;
    cout << id << ": notifing" << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cv.notify_one();
}

void withdrawal_amount(int id)
{
    
    cout << id  << ": mutex lock" << endl;
    unique_lock<mutex> ul(m); 
    cout << id  << ": thread waiting for signal ... " << endl;
    cv.wait(ul, []() {return (accountBalance!= 0 )? true:false; } ); // lambda function 
    cout << id  << ": signal received " << endl;
    accountBalance = accountBalance - 500 ;
    cout << id << " amount withdrawal " << endl;
}
void monitorBalance()
{
    for(;;)
    {
        this_thread::sleep_for(chrono::seconds(1));
        cout << "account balance: " << accountBalance << endl;
    }
}
int main()
{
    thread t1(add_amount, 1);
    thread t2(withdrawal_amount, 2);
    thread t3(monitorBalance);
    t1.join();
    t2.join();
    t3.join();
    
    return 0;


/*
output-
1: mutex locking ...
2: mutex lock
2: thread waiting for signal ... 
account balance: 0
1:  in the cs
account balance: 0
account balance: 500
1: notifing
account balance: 500
2: signal received 
2 amount withdrawal 
account balance: 0
account balance: 0
  */
