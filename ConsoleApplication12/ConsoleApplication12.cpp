#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
bool isEventOccurred = false;

void ProduceEvent()
{
    unique_lock<mutex> lock(mtx);
    isEventOccurred = true;
    cout << "Event produced" << endl;
    cv.notify_one();
}

void ConsumeEvent()
{
    unique_lock<mutex> lock(mtx);
    while (!isEventOccurred)
    {
        cout << "Waiting for event" << endl;
        cv.wait(lock);
    }

    cout << "Event handled" << endl;

    isEventOccurred = false;
    cv.notify_one();
}

int main()
{
    thread producer(ProduceEvent);
    thread consumer1(ConsumeEvent);
    thread consumer2(ConsumeEvent);

    producer.join();

    return 0;
}
