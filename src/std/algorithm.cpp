#include "std/algorithm.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>

namespace unilib::std_utils {

// Extended algorithm for finding the maximum in a range (including empty check)
template <typename Iterator>
Iterator FindMax(Iterator begin, Iterator end) {
    if (begin == end) {
        throw std::invalid_argument("Range cannot be empty");
    }
    return std::max_element(begin, end);
}

// Extended algorithm for finding the minimum in a range (including empty check)
template <typename Iterator>
Iterator FindMin(Iterator begin, Iterator end) {
    if (begin == end) {
        throw std::invalid_argument("Range cannot be empty");
    }
    return std::min_element(begin, end);
}

// Algorithm to calculate the mean of a numeric range
template <typename Iterator>
double CalculateMean(Iterator begin, Iterator end) {
    if (begin == end) {
        throw std::invalid_argument("Range cannot be empty");
    }
    double sum = std::accumulate(begin, end, 0.0);
    return sum / std::distance(begin, end);
}

// Algorithm to partition a range based on a predicate
template <typename Iterator, typename Predicate>
Iterator Partition(Iterator begin, Iterator end, Predicate pred) {
    return std::partition(begin, end, pred);
}

// Sorting utility that also accepts a custom comparison function
template <typename Iterator, typename Compare>
void Sort(Iterator begin, Iterator end, Compare comp) {
    std::sort(begin, end, comp);
}

} // namespace unilib::std_utils
