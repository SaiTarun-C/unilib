#pragma once

#include <type_traits>

namespace unilib::meta {

// Type trait to check if a type is a smart pointer
template <typename T>
struct is_smart_pointer : std::false_type {};

template <typename T>
struct is_smart_pointer<std::unique_ptr<T>> : std::true_type {};

template <typename T>
struct is_smart_pointer<std::shared_ptr<T>> : std::true_type {};

template <typename T>
inline constexpr bool is_smart_pointer_v = is_smart_pointer<T>::value;

// Type trait to check if a type is an iterable container (vector, list, etc.)
template <typename T, typename = void>
struct is_iterable : std::false_type {};

template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>())), decltype(std::end(std::declval<T>()))>> : std::true_type {};

template <typename T>
inline constexpr bool is_iterable_v = is_iterable<T>::value;

// Type trait to check if a type is callable (function pointer, functor, lambda, etc.)
template <typename T>
struct is_callable : std::false_type {};

template <typename R, typename... Args>
struct is_callable<R(Args...)> : std::true_type {};

template <typename T>
inline constexpr bool is_callable_v = is_callable<T>::value;

// Type trait to get the underlying type of a smart pointer
template <typename T>
struct smart_pointer_underlying_type {
    using type = void; // Default to void for non-smart pointers
};

template <typename T>
struct smart_pointer_underlying_type<std::unique_ptr<T>> {
    using type = T;
};

template <typename T>
struct smart_pointer_underlying_type<std::shared_ptr<T>> {
    using type = T;
};

template <typename T>
using smart_pointer_underlying_type_t = typename smart_pointer_underlying_type<T>::type;

// Type trait to conditionally add const to a type based on a boolean condition
template <typename T, bool AddConst>
struct conditional_const {
    using type = T;
};

template <typename T>
struct conditional_const<T, true> {
    using type = const T;
};

template <typename T, bool AddConst>
using conditional_const_t = typename conditional_const<T, AddConst>::type;

// Type trait to check if a type is integral (int, short, long, etc.)
template <typename T>
struct is_integral : std::is_integral<T> {};

template <typename T>
inline constexpr bool is_integral_v = is_integral<T>::value;

} // namespace unilib::meta
