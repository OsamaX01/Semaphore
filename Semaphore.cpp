#include <iostream>
#include <thread>
#include <mutex>
#include <syncstream>
#include <condition_variable>

class semaphore {
public:
    semaphore(int value = 0);
    void wait();
    void signal();

private:
    int value;
    std::mutex m;
    std::condition_variable_any cv;
};

semaphore::semaphore(int value) : value(value) {}

void semaphore::wait() {
    lock_guard<mutex> lg(m);
    cv.wait(m, [this]{ return value > 0; });
    value--;
}

void semaphore::signal() {
    lock_guard<mutex> lg(m);
    value++;
    if (value == 1) cv.notify_all();
}