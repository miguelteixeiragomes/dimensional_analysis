#pragma once
#include <cmath>
#include <ratio>


#define INTERNAL_NAMESPACE dimensional_analysis_viscera

#ifndef INT8
	#define INT8  int8
#endif
#ifndef INT16
	#define INT16 int16
#endif
#ifndef INT32
	#define INT32 int32
#endif
#ifndef INT64
	#define INT64 int64
#endif
#ifndef UINT8
	#define UINT8  uint8
#endif
#ifndef UINT16
	#define UINT16 uint16
#endif
#ifndef UINT32
	#define UINT32 uint32
#endif
#ifndef UINT64
	#define UINT64 uint64
#endif
#ifndef FLOAT32
	#define FLOAT32 float32
#endif
#ifndef FLOAT64
	#define FLOAT64 float64
#endif
#ifndef FLOAT128
	#define FLOAT128 float128
#endif

#ifndef INT8_T
	#ifdef __CUDACC__
		#define INT8_T signed char
	#else
		#define INT8_T std::int8_t
	#endif
#endif
#ifndef INT16_T
	#ifdef __CUDACC__
		#define INT16_T signed short
	#else
		#define INT16_T std::int16_t
	#endif
#endif
#ifndef INT32_T
	#ifdef __CUDACC__
		#define INT32_T signed int
	#else
		#define INT32_T std::int32_t
	#endif
#endif
#ifndef INT64_T
	#ifdef __CUDACC__
		#define INT64_T signed long long
	#else
		#define INT64_T std::int64_t
	#endif
#endif
#ifndef UINT8_T
	#ifdef __CUDACC__
		#define UINT8_T unsigned char
	#else
		#define UINT8_T std::uint8_t
	#endif
#endif
#ifndef UINT16_T
	#ifdef __CUDACC__
		#define UINT16_T unsigned short
	#else
		#define UINT16_T std::uint16_t
	#endif
#endif
#ifndef UINT32_T
	#ifdef __CUDACC__
		#define UINT32_T unsigned int
	#else
		#define UINT32_T std::uint32_t
	#endif
#endif
#ifndef UINT64_T
	#ifdef __CUDACC__
		#define UINT64_T unsigned long long
	#else
		#define UINT64_T std::uint64_t
	#endif
#endif
#ifndef FLOAT32_T
	#define FLOAT32_T float
#endif
#ifndef FLOAT64_T
	#define FLOAT64_T double
#endif
#ifndef FLOAT128_T
	#define FLOAT128_T long double
#endif

#ifdef __CUDACC__
	#define CUDA_CALLABLE_MEMBER __host__ __device__
#else
	#define CUDA_CALLABLE_MEMBER
#endif

////////////////////////////////////////////////////////
#include "dimensions.h"
#include "primitive_types.h"
////////////////////////////////////////////////////////


#ifdef SKIP_DIMENSIONAL_ANALYSIS
	#undef SKIP_DIMENSIONAL_ANALYSIS
#endif
#undef INT8
#undef INT16
#undef INT32
#undef INT64
#undef UINT8
#undef UINT16
#undef UINT32
#undef UINT64
#undef FLOAT32
#undef FLOAT64
#undef FLOAT128

#undef INT8_T
#undef INT16_T
#undef INT32_T
#undef INT64_T
#undef UINT8_T
#undef UINT16_T
#undef UINT32_T
#undef UINT64_T
#undef FLOAT32_T
#undef FLOAT64_T
#undef FLOAT128_T

#undef INTERNAL_NAMESPACE
#undef CUDA_CALLABLE_MEMBER