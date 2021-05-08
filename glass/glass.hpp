#ifndef GLASS_HPP
#define GLASS_HPP
#pragma once

#include <cstdint>
#include <tuple>
#include <utility>

static_assert(__cplusplus >= 201703L, "Requires at least C++17");

#if defined(__GNUC__) && !defined(__clang__)
static_assert(__GNUC__ > 8, "member_count requires GCC version 9 or above.");
// GCC emits a warning for the lookup function, but it's intentionally not templated
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-template-friend"
#endif

#ifndef GLASS_NAMESPACE
#define GLASS_NAMESPACE glass
#endif

namespace GLASS_NAMESPACE
{
namespace detail
{
/// A type and index pair identifying a struct member.
template <typename T, std::size_t N>
struct Key
{
    // Declare at instantiation, return type is unknown at this point, required for ADL
    friend auto lookup(Key<T, N>);
};

template <typename T, typename U, std::size_t N>
struct GenerateLookup
{
    // Define the lookup friend
    friend auto lookup(Key<T, N>) { return U{}; }
};

template <typename T, std::size_t N>
struct CvtToAny
{
    // Don't need to define this as it should never be used in an evaluated context.
    // Trigger the generation of a lookup function for this member
    template <typename U, int = sizeof(GenerateLookup<T, U, N>)>
    constexpr operator U() noexcept;
};

// Second choice since an exact match exists for the int parameter
template <typename T, std::size_t... I, typename U>
constexpr std::size_t member_count_impl(U) noexcept
{
    // We know that with N args, the type constructor fails but N - 1 worked.
    return sizeof...(I) - 1;
}

// Picked via overload resolution if the constructor compiles
template <typename T, std::size_t... I>
constexpr auto member_count_impl(int) -> decltype(T{CvtToAny<T, I>{}...}, 0)
{
    // Recurse until SFINAE picks the other overload, passing another larger index each time
    return member_count_impl<T, I..., sizeof...(I)>(0);
}

template <typename T, typename U>
struct type_list;

template <typename T, std::size_t... I>
struct type_list<T, std::index_sequence<I...>>
{
    using type = std::tuple<decltype(lookup(detail::Key<T, I>{}))...>;
};
}  // namespace detail

// Determine the number of members within type T
template <typename T, std::enable_if_t<std::is_aggregate_v<T>, int>...>
constexpr std::size_t member_count = detail::member_count_impl<T>(0);

template <typename T, std::enable_if_t<std::is_aggregate_v<T>, int>...>
using tuple = typename detail::type_list<T, std::make_index_sequence<member_count<T>>>::type;
}  // namespace GLASS_NAMESPACE

// Compile time tests
#ifndef GLASS_DISABLE_TESTS
#include "test/glass_tests.hpp"
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif

#endif  // GLASS_HPP
