#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <bits/stdc++.h>

class ThreadPool {
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;
public:
    ThreadPool(size_t T);
    void enqueue(std::function<void()> task);
    // void wait();
    ~ThreadPool();
};

#endif