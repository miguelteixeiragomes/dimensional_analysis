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

* `SKIP_DIMENSIONAL_ANALYSIS` - if this directive is defined the dimensional analysis is skipped entirely guaranteeing removing any of the library's overhead and speeding the up the compilation.
* EXPLICIT_CONSTRUCTOR - if this directive is defined the constructor of the library's primitive types is made explicit.
* INT8 <name> - this directive defaults to defines <name> as the 