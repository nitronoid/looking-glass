#ifndef GLASS_TESTS_HPP
#define GLASS_TESTS_HPP
#pragma once

namespace GLASS_NAMESPACE
{
namespace detail
{
namespace test
{
struct Test0
{
};
static_assert(member_count<Test0> == 0, "glass unit test failed.");
static_assert(std::is_same_v<tuple<Test0>, std::tuple<>>, "glass unit test failed.");

struct Test1
{
    uint32_t a;
};
static_assert(member_count<Test1> == 1, "glass unit test failed.");
static_assert(std::is_same_v<tuple<Test1>, std::tuple<uint32_t>>, "glass unit test failed.");

struct Test2
{
    uint32_t a, b;
};
static_assert(member_count<Test2> == 2, "glass unit test failed.");
static_assert(std::is_same_v<tuple<Test2>, std::tuple<uint32_t, uint32_t>>, "glass unit test failed.");

struct Test3
{
    uint32_t a, b;
    uint64_t c;
};
static_assert(member_count<Test3> == 3, "glass unit test failed.");
static_assert(std::is_same_v<tuple<Test3>, std::tuple<uint32_t, uint32_t, uint64_t>>, "glass unit test failed.");

struct Test10
{
    uint32_t x1, x2, x3, x4, x5, x6, x7, x8, x9, x10;
};
static_assert(member_count<Test10> == 10, "glass unit test failed.");
static_assert(
    std::is_same_v<tuple<Test10>, std::tuple<uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t>>,
    "glass unit test failed."
);

template <typename T>
struct Template
{
    T x;
    T y;
};
static_assert(member_count<Template<int>> == 2, "glass unit test failed.");
static_assert(std::is_same_v<tuple<Template<int>>, std::tuple<int, int>>, "glass unit test failed.");

struct Nested
{
    struct
    {
        uint32_t a, b, c;
    } inner;
};
static_assert(member_count<Nested> == 1, "glass unit test failed.");
static_assert(std::is_same_v<tuple<Nested>, std::tuple<decltype(Nested::inner)>>, "glass unit test failed.");

struct TestSimpleUnion
{
    union
    {
        float f;
        uint32_t i;
    };
};
static_assert(member_count<TestSimpleUnion> == 1, "glass unit test failed.");

struct TestComplexUnion
{
    uint32_t x;
    union
    {
        struct
        {
            uint32_t a, b;
        };
        uint64_t c;
        double d;
    };
    uint32_t y;
};
static_assert(member_count<TestComplexUnion> == 3, "glass unit test failed.");

struct TestNamedNestedStruct
{
    struct S
    {
        uint64_t u;
        double d;
    };
    S a, b;
};
static_assert(member_count<TestNamedNestedStruct> == 2, "glass unit test failed.");
static_assert(std::is_same_v<tuple<TestNamedNestedStruct>, std::tuple<TestNamedNestedStruct::S, TestNamedNestedStruct::S>>, "glass unit test failed.");

struct TestNamedNestedUnion
{
    union U
    {
        uint64_t u;
        double d;
    };
    U a, b;
};
static_assert(member_count<TestNamedNestedUnion> == 2, "glass unit test failed.");
static_assert(std::is_same_v<tuple<TestNamedNestedUnion>, std::tuple<TestNamedNestedUnion::U, TestNamedNestedUnion::U>>, "glass unit test failed.");
}  // namespace test
}  // namespace detail
}  // namespace GLASS_NAMESPACE
#endif  // GLASS_TESTS_HPP
