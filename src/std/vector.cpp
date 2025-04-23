#include "std/vector.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>

namespace unilib::std_utils {

// Function to safely add an element to a vector, with resizing if necessary
template <typename T>
void SafeAdd(std::vector<T>& vec, const T& element) {
    try {
        vec.push_back(element);
    } catch (const std::bad_alloc& e) {
        std::cerr << "Failed to allocate memory for the vector: " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}

// Function to reverse the elements in a vector
template <typename T>
void Reverse(std::vector<T>& vec) {
    std::reverse(vec.begin(), vec.end());
}

// Function to transform elements in the vector based on a lambda or function
template <typename T, typename Func>
void Transform(std::vector<T>& vec, Func func) {
    std::transform(vec.begin(), vec.end(), vec.begin(), func);
}

// Function to safely get an element at a specified index, checking bounds
template <typename T>
T SafeGet(const std::vector<T>& vec, size_t index) {
    if (index >= vec.size()) {
        throw std::out_of_range("Index is out of range");
    }
    return vec[index];
}

} // namespace unilib::std_utils
