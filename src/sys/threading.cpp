#include "sys/threading.hpp"

#include <iostream>

namespace unilib::sys {

Thread::Thread(std::function<void()> func)
    : thread_(std::move(func)) {}

Thread::~Thread() {
    if (thread_.joinable()) {
        thread_.join(); // Ensures proper cleanup
    }
}

void Thread::join() {
    if (thread_.joinable()) {
        thread_.join();
    }
}

bool Thread::joinable() const {
    return thread_.joinable();
}

void Mutex::lock() {
    mutex_.lock();
}

bool Mutex::try_lock() {
    return mutex_.try_lock();
}

void Mutex::unlock() {
    mutex_.unlock();
}

void LockGuard::lock() {
    if (!locked_) {
        guard_ = std::make_unique<std::lock_guard<std::mutex>>(mutex_);
        locked_ = true;
    }
}

void LockGuard::unlock() {
    if (locked_) {
        guard_.reset(); // unlocks the lock_guard
        locked_ = false;
    }
}

bool LockGuard::isLocked() const {
    return locked_;
}

} // namespace unilib::sys
