#pragma once
#include <cmath>
#include <ratio>


#define INTERNAL_NAMESPACE dim//ensional_analysis_viscera

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

#ifndef FLOAT32_T
	#define FLOAT32_T float
#endif
#ifndef FLOAT64_T
	#define FLOAT64_T double
#endif
#ifndef FLOAT128_T
	#define FLOAT128_T long double
#endif


////////////////////////////
#include "dimensions.h"
#include "primitive_types.h"
////////////////////////////


#ifdef SKIP_DIMENSIONAL_ANALYSIS
	#undef SKIP_DIMENSIONAL_ANALYSIS
#endif
#ifdef EXPLICIT_CONSTRUCTOR
	#undef EXPLICIT_CONSTRUCTOR
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
#undef FLOAT32_T
#undef FLOAT64_T
#undef FLOAT128_T
#undef INTERNAL_NAMESPACE