//
// Created by Raihan on 10/19/2025.
//
#include <ThreadPool.h>

// void ThreadPool::wait() {
//     std::unique_lock<std::mutex> lock(mtx);
//     cv.wait(lock, [this]() { return tasks.empty(); });
// }

ThreadPool::ThreadPool(size_t T) {
    for (size_t i = 0; i < T; i++) {
        threads.emplace_back([this]() {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this]() {return stop || !tasks.empty();});
                    if (stop && tasks.empty()) {
                        return;
                    }
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                task();
            }
        });
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.emplace(std::move(task));
    }
    cv.notify_one();
}

ThreadPool::~ThreadPool() {
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();
    for (std::thread &t : threads) if (t.joinable()) t.join();
}


