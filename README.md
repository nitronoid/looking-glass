## `looking-glass`
---
`constexpr` utilities to determine the number of member fields in an aggregate `struct`, and produce a `std::tuple` with the same list of types.

<p align="center">
<img src="https://github.com/nitronoid/looking-glass/raw/main/.github/images/looking-glass.jpg" width="900">
</p>

### Example usage
---
```cpp
// Struct with three member variables
struct S
{
    char a, b, c;
};

// Check that S has three members at compile time
static_assert(glass::member_count<S> == 3, "S does not have 3 members.");
static_assert(std::is_same_v<glass::tuple<S>, std::tuple<char, char, char>>);
```

### Requirements
---
This lib requires GCC version 9 or above due to a bug fix provided for uniform aggregate initialisation of `unions`.
I haven't traced back the minimum MSVC version yet, but it does work with v19.14 and above.
* GCC >= 9.0.0
* Clang >= 4
* MSVC >= 19.14 (probably lower?)
* C++17

### Build
---
The utility is header only, simply include `"glass.hpp"` to use.  
There are a couple of customisation options for the header:
* Define `REFLEX_NAMESPACE` if you want the utilities to live in a namespace other than `glass`.
* Disable the compile-time unit tests by defining `REFLEX_DISABLE_TESTS`

### Tests
---
The unit tests have been added as `static_asserts` (because why not?) and are included at the end of the main header so they are always checked.
A dummy translation unit has been provided for easy of checking the compilation:

```
$(CXX) test/test.cpp
```

### TODO
---
- [x] Support for anonymous `unions` and unnamed `structs`.
- [x] Portable across GCC and Clang.
- [x] Basic unit tests.
- [x] Configurable `namespace`.
- [ ] Trace minimum MSVC version.
- [ ] Unit test tuple types with anonymous unions?
- [ ] Continuous integration.
