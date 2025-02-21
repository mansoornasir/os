#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

queue<int> buffer;
const int BUFFER_SIZE = 5;
mutex mtx;
condition_variable cv;

void producer() {
    for (int i = 1; i <= 10; ++i) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });

        buffer.push(i);
        cout << "Produced: " << i << endl;

        cv.notify_all();  // Notify consumer
    }
}

void consumer() {
    for (int i = 1; i <= 10; ++i) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty(); });

        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << endl;

        cv.notify_all();  // Notify producer
    }
}

int main() {
    thread t1(producer), t2(consumer);
    t1.join();
    t2.join();
    return 0;
}
