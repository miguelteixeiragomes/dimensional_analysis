# Dimensional Analysis Library

This is a header-only library that implements compile time dimensional and [orientational](https://en.wikipedia.org/wiki/Dimensional_analysis#Siano.27s_extension:_orientational_analysis) analysis in C++ through template meta-programming. The library defines template classes matching C++'s arithmetic built-in types whose template argument is the dimensions. It also provides a generic container for adding dimensions to other types.

## Getting started

### Prerequisites

The library is composed only of header files. To use it, simply include the file 'dimensional_analysis.h'. The compilers tested were

* MS Visual C++ 19.00.24215.1;
* GCC - 7.2.0;
* NVCC - 8.0.60.

However, the library should work with any C++11 compliant compiler.

### Compile options

This library supports a number of compilation options through macro definitions:

* `#define SKIP_DIMENSIONAL_ANALYSIS` - if defined the dimensional analysis is skipped entirely removing any of the library's overhead and speeding the up the compilation;

* `#define <LIB-TYPE-NAME> <lib-type-name>` - these directives allow changing the names of the library's primitive types:
  - `#define INT8 <name>` - defaults to `int8` and encapsulates the built-in type `INT8_T`;
  - `#define INT16 <name>` - defaults to `int16` and encapsulates the built-in type `INT16_T`;
  - `#define INT32 <name>` - defaults to `int32` and encapsulates the built-in type `INT32_T`;
  - `#define INT64 <name>` - defaults to `int64` and encapsulates the built-in type `INT64_T`;
  - `#define UINT8 <name>` - defaults to `uint8` and encapsulates the built-in type `UINT8_T`;
  - `#define UINT16 <name>` - defaults to `uint16` and encapsulates the built-in type `UINT16_T`;
  - `#define UINT32 <name>` - defaults to `uint32` and encapsulates the built-in type `UINT32_T`;
  - `#define UINT64 <name>` - defaults to `uint64` and encapsulates the built-in type `UINT64_T`;
  - `#define FLOAT32 <name>` - defaults to `float32` and encapsulates the built-in type `FLOAT32_T`;
  - `#define FLOAT64 <name>` - defaults to `float64` and encapsulates the built-in type `FLOAT64_T`;
  - `#define FLOAT128 <name>` - defaults to `float128` and encapsulates the built-in type `FLOAT128_T`;

* `#define <ACTUAL-TYPE-NAME> <actual-type-name>`
  - `#define INT8_T <name>` - defaults to `std::int8_t` or `signed char` in CUDA;
  - `#define INT16_T <name>` - defaults to `std::int16_t` or `signed short` in CUDA;
  - `#define INT32_T <name>` - defaults to `std::int32_t` or `signed int` in CUDA;
  - `#define INT64_T <name>` - defaults to `std::int64_t` or `signed long long` in CUDA;
  - `#define UINT8_T <name>` - defaults to `std::uint8_t` or `unsigned char` in CUDA;
  - `#define UINT16_T <name>` - defaults to `std::uint16_t` or `unsigned short` in CUDA;
  - `#define UINT32_T <name>` - defaults to `std::uint32_t` or `unsigned int` in CUDA;
  - `#define UINT64_T <name>` - defaults to `std::uint64_t` or `unsigned long long` in CUDA;
  - `#define FLOAT32_T <name>` - defaults to `float`;
  - `#define FLOAT64_T <name>` - defaults to `double`;
  - `#define FLOAT128_T <name>` - defaults to `long double`.


## Usage

### Simple examples

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

The C++ arithmetic built-in types can be operated with the library's types and are interpreted as `Adimensional`. The operators `+`, `-`, `*`, `/`, and `%` are implemented between types with any dimensions. The bitwise operators `~`, `|`, `^`, `&`, `<<`, and `>>` are only defined for adimensional quantities.

### Literals

The library defines literals for declaring dimensioned quantities. The names coincide with the names given to the dimensions (listed below). Before the name of the dimension a suffix can be added to define the arithmetic type:

* `_s8_ ## <dim-name>` - declares a `INT8_T`;
* `_s16_ ## <dim-name>` - declares a `INT16_T`;
* `_s32_ ## <dim-name>` or just `_ ## <dim-name>` - declares a `INT32_T`;
* `_s64_ ## <dim-name>` - declares a `INT64_T`;
* `_u8_ ## <dim-name>` - declares a `UINT8_T`;
* `_u16_ ## <dim-name>` - declares a `UINT16_T`;
* `_u32_ ## <dim-name>` - declares a `UINT32_T`;
* `_u64_ ## <dim-name>` - declares a `UINT64_T`;
* `_f32_ ## <dim-name>` - declares a `FLOAT32_T`;
* `_f64_ ## <dim-name>` or just `_ ## <dim-name>` - declares a `FLOAT32_T`;
* `_f128_ ## <dim-name>` - declares a `FLOAT128_T`.

The missing `<dim-name>` can be from the following list of dimensions:

| `Acceleration`              | `LengthX`          |
| `Area`                      | `LengthY`          |
| `Capacitance`               | `LengthZ`          |
| `Charge`                    | `Mass`             |
| `Current`                   | `Permeability`     |
| `ElectricDisplacementField` | `Permittivity`     |
| `ElectricField`             | `SpatialFrequency` |
| `Energy`                    | `Temperature`      |
| `Force`                     | `Time`             |
| `Frequency`                 | `Velocity`         |
| `Inductance`                | `Volume`           |
| `Length`                    |                    |

For example:

```
float64<Length>(8.0) + 7.0_f64_Length; // compiles
float64<Time>(8.0) + 7.0_Length; // doesn't compiles (the literal is the same as the line above)
```

### Functions

Most mathematical functions can only take adimensional arguments, however functions like `sqrt`, `cbrt`, and `pow` can take dimensioned quantities and alter their dimensions. The library defines `sqrt`, `sqrtf`, `cbrt`, and `cbrtf` which can be used directly, and map to the corresponding functions in the `std` library or in CUDA.
For the function `pow` (or `powf`) the exponent (2nd argument) must be known at compile-time and so the library defines both functions with template arguments for numerator and denominator:

```
std::cout << pow<7>(pow<1, 7>(a)) << '\n'; // the first 'pow' is has exponent 7 while the second has exponent 1/7
std::cout << float64<Length>(5) + sqrt(float64<Area>(25)) << '\n';
std::cout << float64<Length>(5) + cbrt(float64<Volume>(125)) << '\n';
float64<Velocity> lightspeed = 1.0 / sqrt(float64<Permittivity>(8.85418781762039e-12)*float64<Permeability>(1.256637061435917e-6));
```

### Declaring new dimensions

To declare new dimensions the base dimensions - 'Length', 'Time', 'Mass', 'Charge', 'Temperature' - can be used in conjunction with the `struct` `MUl_DIMS` and `DIMS_POW`:

```
using Force = MUL_DIMS<Mass, Length, DIMS_POW<Time, -2>::value>::value; // note: 'Force' is already defined in the library
```

### Orientational analysis

The implementation of Siano's orientational analysis is still in an experimental phase since several adaptations add to me made to accommodate the fractional powers. The types can already be defined from the base units. Since `Length` is the only base unit to have orientation the extra units `LengthX`, `LengthY`, and `LengthZ` are defined to allow the construction of any dimension and orientation.
