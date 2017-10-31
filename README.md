# Dimensional Analysis Library

This library implements compile time dimensional analysis in C++ through template meta-programming. The library defines template classes matching C++'s arithmetic built-in types whose template argument is the dimensions.

## Getting started

### Prerequisites

The library is composed only of header files. To use it, simply include the file 'dimensional_analysis.h'. The compilers tested were

* MS Visual C++ 14;
* GCC - 6.3.0/7.2.0

However, the library should work with any C++11 compliant compiler.

### Compile options

This library supports a number of compilation options through macro definitions:

* `SKIP_DIMENSIONAL_ANALYSIS` - if this directive is defined the dimensional analysis is skipped entirely guaranteeing removing any of the library's overhead and speeding the up the compilation;
* `EXPLICIT_CONSTRUCTOR` - if this directive is defined the constructor of the library's primitive types is made explicit;
* `INT8 <name>` - this directive defaults to `int8` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `char`;
* `INT16 <name>` - this directive defaults to `int16` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `short`;
* `INT32 <name>` - this directive defaults to `int32` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `int`;
* `INT64 <name>` - this directive defaults to `int64` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `long long`;
* `UINT8 <name>` - this directive defaults to `uint8` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `unsigned char`;
* `UINT16 <name>` - this directive defaults to `uint16` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `unsigned short`;
* `UINT32 <name>` - this directive defaults to `uint32` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `unsigned int`;
* `UINT64 <name>` - this directive defaults to `uint64` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `unsigned long long`;
* `FLOAT32 <name>` - this directive defaults to `float32` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `FLOAT32_T`;
* `FLOAT64 <name>` - this directive defaults to `float64` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `FLOAT64_T`;
* `FLOAT128 <name>` - this directive defaults to `float128` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `FLOAT128_T`;
* `FLOAT32_T <name>` - this directive defaults to `loat` and defines `<name>` as the name of the dimensioned quantity that encapsulates the built-in type `FLOAT32_T`;