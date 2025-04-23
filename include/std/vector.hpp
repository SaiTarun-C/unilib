#ifndef UNILIB_STD_VECTOR_HPP
#define UNILIB_STD_VECTOR_HPP

#include <vector>
#include <stdexcept>
#include <iostream>
#include <type_traits>
#include <utility>

namespace unilib::std_ext {

template<typename T>
class SafeVector {
public:
    using container_type = std::vector<T>;
    using iterator = typename container_type::iterator;
    using const_iterator = typename container_type::const_iterator;

    SafeVector() = default;
    explicit SafeVector(std::size_t size, const T& default_value = T{}) : data_(size, default_value) {}

    // Safe access with bounds checking
    T& at(std::size_t index) {
        if (index >= data_.size())
            throw std::out_of_range("SafeVector: Index out of range");
        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= data_.size())
            throw std::out_of_range("SafeVector: Index out of range");
        return data_[index];
    }

    void push(const T& value) { data_.push_back(value); }
    void pop() { if (!data_.empty()) data_.pop_back(); }

    std::size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }
    void clear() { data_.clear(); }

    iterator begin() { return data_.begin(); }
    iterator end() { return data_.end(); }
    const_iterator begin() const { return data_.begin(); }
    const_iterator end() const { return data_.end(); }

    T& operator[](std::size_t index) { return data_[index]; }
    const T& operator[](std::size_t index) const { return data_[index]; }

private:
    container_type data_;
};

} // namespace unilib::std_ext

#endif // UNILIB_STD_VECTOR_HPP
