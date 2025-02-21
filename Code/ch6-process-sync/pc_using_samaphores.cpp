#include <iostream>
#include <queue>
#include <thread>
#include <semaphore.h>
#include <mutex>

using namespace std;

queue<int> buffer;
const int BUFFER_SIZE = 5;
sem_t emptySlots, fullSlots;
mutex mtx;

void producer() {
    for (int i = 1; i <= 10; ++i) {
        sem_wait(&emptySlots);
        unique_lock<mutex> lock(mtx);

        buffer.push(i);
        cout << "Produced: " << i << endl;

        sem_post(&fullSlots);
    }
}

void consumer() {
    for (int i = 1; i <= 10; ++i) {
        sem_wait(&fullSlots);
        unique_lock<mutex> lock(mtx);

        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << endl;

        sem_post(&emptySlots);
    }
}

int main() {
    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);

    thread t1(producer), t2(consumer);
    t1.join();
    t2.join();

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    return 0;
}
