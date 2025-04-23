#ifndef UNILIB_STD_ALGORITHM_HPP
#define UNILIB_STD_ALGORITHM_HPP

#include <algorithm>
#include <iterator>
#include <functional>
#include <vector>
#include <numeric>
#include <execution> // For parallel execution (C++17+)

namespace unilib::std_ext::algo {

// Safe sort with fallback to sequential if parallel not supported
template <typename Iterator, typename Compare = std::less<>>
void sort(Iterator begin, Iterator end, Compare comp = Compare{}) {
#if __cpp_lib_execution
    std::sort(std::execution::par_unseq, begin, end, comp);
#else
    std::sort(begin, end, comp);
#endif
}

// Deduplicate a sorted container
template <typename Container>
void unique_erase(Container& c) {
    c.erase(std::unique(c.begin(), c.end()), c.end());
}

// Generalized reduce
template <typename Container, typename T = typename Container::value_type>
T reduce(const Container& c, T init = T{}) {
#if __cpp_lib_execution
    return std::reduce(std::execution::par, c.begin(), c.end(), init);
#else
    return std::accumulate(c.begin(), c.end(), init);
#endif
}

} // namespace unilib::std_ext::algo

#endif // UNILIB_STD_ALGORITHM_HPP
