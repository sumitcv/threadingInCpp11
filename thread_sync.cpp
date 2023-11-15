#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

mutex mymutex;

int globalData = 0;
std::shared_ptr<int> sptr_globalData = std::make_shared<int>(globalData);

void myThreadFn()
{
    thread::id threadId = this_thread::get_id();
    this_thread::sleep_for(std::chrono::milliseconds(5000));
    for(int i = 0 ; i < 5000 ; i++)
    {
        // mymutex.lock();
        (*sptr_globalData)++;
        // mymutex.unlock();
    }
    shared_ptr<int> sprt_tmp = sptr_globalData;
    cout << threadId <<" |"<<*sptr_globalData << "| " << endl;
    cout << threadId << "| sptr_globalData use count :" << sptr_globalData.use_count() << endl;
}

int main()
{
    vector<thread> threadList;
    for(int i = 0 ; i<5; ++i)
    {
        threadList.push_back(thread(myThreadFn));
    }
    this_thread::sleep_for(std::chrono::milliseconds(5000));
    for(auto & thread:threadList)
    {
        thread.join();
    }
    cout << "finally sptr_globalData value: " << *sptr_globalData << endl;
    return 0;
}

