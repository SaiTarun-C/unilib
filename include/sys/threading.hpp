#ifndef UNILIB_SYS_THREADING_HPP
#define UNILIB_SYS_THREADING_HPP

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <vector>
#include <queue>
#include <stdexcept>

namespace unilib::sys {

// Simple thread wrapper
class Thread {
public:
    Thread() = default;

    template <typename Function, typename... Args>
    explicit Thread(Function&& func, Args&&... args) {
        start(std::forward<Function>(func), std::forward<Args>(args)...);
    }

    template <typename Function, typename... Args>
    void start(Function&& func, Args&&... args) {
        if (worker_.joinable())
            throw std::runtime_error("Thread already running");
        worker_ = std::thread(std::forward<Function>(func), std::forward<Args>(args)...);
    }

    void join() {
        if (worker_.joinable()) {
            worker_.join();
        }
    }

    void detach() {
        if (worker_.joinable()) {
            worker_.detach();
        }
    }

    bool joinable() const {
        return worker_.joinable();
    }

    ~Thread() {
        if (worker_.joinable()) {
            worker_.detach();  // Avoid std::terminate
        }
    }

private:
    std::thread worker_;
};

// Thread-safe queue
template<typename T>
class ThreadSafeQueue {
public:
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(value);
        cond_.notify_one();
    }

    bool try_pop(T& out) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty())
            return false;
        out = std::move(queue_.front());
        queue_.pop();
        return true;
    }

    T wait_and_pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [&] { return !queue_.empty(); });
        T value = std::move(queue_.front());
        queue_.pop();
        return value;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::queue<T> queue_;
    std::condition_variable cond_;
};

// Thread pool
class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency()) {
        start(num_threads);
    }

    ~ThreadPool() {
        stop();
    }

    template<typename Func>
    void enqueue(Func&& func) {
        tasks_.push(std::function<void()>(func));
    }

private:
    std::vector<std::thread> workers_;
    ThreadSafeQueue<std::function<void()>> tasks_;
    std::atomic<bool> running_{true};

    void start(size_t num_threads) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers_.emplace_back([this]() {
                while (running_) {
                    std::function<void()> task;
                    if (tasks_.try_pop(task)) {
                        task();
                    } else {
                        std::this_thread::yield();
                    }
                }
            });
        }
    }

    void stop() {
        running_ = false;
        for (auto& thread : workers_) {
            if (thread.joinable()) thread.join();
        }
    }
};

} // namespace unilib::sys

#endif // UNILIB_SYS_THREADING_HPP
