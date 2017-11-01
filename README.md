# Dimensional Analysis Library

This library implements compile time dimensional analysis in C++ through template meta-programming. The library defines template classes matching C++'s arithmetic built-in types whose template argument is the dimensions.

## Getting started

### Prerequisites

The library is composed only of header files. To use it, simply include the file 'dimensional_analysis.h'. The compilers tested were

* MS Visual C++ 19.00.24215.1;
* GCC - 6.3.0/7.2.0

However, the library should work with any C++11 compliant compiler.

### Compile options

This library supports a number of compilation options through macro definitions:

* `#define SKIP_DIMENSIONAL_ANALYSIS` - if defined the dimensional analysis is skipped entirely removing any of the library's overhead and speeding the up the compilation;
* `#define EXPLICIT_CONSTRUCTOR` - if defined the constructor of the library's primitive types is made explicit;

* `#define <TYPE-NAME> <type-name>` - these directives allow changing the names of the library's primitive types:
  - `#define INT8 <name>` - defaults to `int8` and encapsulates the built-in type `std::int8_t`;
  - `#define INT16 <name>` - defaults to `int16` and encapsulates the built-in type `std::int16_t`;
  - `#define INT32 <name>` - defaults to `int32` and encapsulates the built-in type `std::int32_t`;
  - `#define INT64 <name>` - defaults to `int64` and encapsulates the built-in type `std::int64_t`;
  - `#define UINT8 <name>` - defaults to `uint8` and encapsulates the built-in type `std::uint8_t`;
  - `#define UINT16 <name>` - defaults to `uint16` and encapsulates the built-in type `std::uint16_t`;
  - `#define UINT32 <name>` - defaults to `uint32` and encapsulates the built-in type `std::uint32_t`;
  - `#define UINT64 <name>` - defaults to `uint64` and encapsulates the built-in type `std::uint64_t`;
  - `#define FLOAT32 <name>` - defaults to `float32` and encapsulates the built-in type `FLOAT32_T` (see ahead);
  - `#define FLOAT64 <name>` - defaults to `float64` and encapsulates the built-in type `FLOAT64_T` (see ahead);
  - `#define FLOAT128 <name>` - defaults to `float128` and encapsulates the built-in type `FLOAT128_T` (see ahead);

* `#define FLOAT32_T <name>` - defaults to `float`;
* `#define FLOAT64_T <name>` - defaults to `double`;
* `#define FLOAT128_T <name>` - defaults to `long double`;


## Usage

The primitive types in the library are template classes that can be used to replace C++'s arithmetic built-in types. The template argument serves as the dimension.

```
int32<Adimensional> b(42); // 'a' is adimensional
uint64<> b(42); // 'b' is also adimensional
float32<Time> c(3.14); // 'c' as time dimensions
```

All the operations available for the built-in types are also available for the library's types. Compilation will fail with an undefined `struct`, that acts as an error message, whenever the operations do not have the correct units

```
float32<Time> a = float32<Time>(3.14) + float32<Time>(2.7); // compiles
float32<Time> b = float32<Length>(3.14) + float32<Time>(2.7); // does not compile
float64<Acceleration> ac = (float64<Velocity>(3e8) - float64<Length>(3.14) / float32<Time>(2.7)) / float64<Time>(1.0); // compiles
```

The C++ arithmetic built-in types can be operated with the library's types and are interpreted as `Adimensional`.
The operators +, -, *, /, and % are implemented between types with any dimensions. The bitwise operators ~, |, ^, &, <<, and >> are only defined for adimensional quantities.