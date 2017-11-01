#pragma once


template<typename length, 
		 typename time, 
		 typename mass, 
		 typename charge,
		 typename temperature> 
	struct Dimensions {
		typedef length      LENGTH;
		typedef time        TIME;
		typedef mass        MASS;
		typedef charge      CHARGE;
		typedef temperature TEMPERATURE;
	};

typedef Dimensions< std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Adimensional;
typedef Dimensions< std::ratio< 1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Length;
typedef Dimensions< std::ratio< 2>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Area;
typedef Dimensions< std::ratio< 3>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Volume;
typedef Dimensions< std::ratio< 0>, std::ratio< 1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Time;
typedef Dimensions< std::ratio< 0>, std::ratio< 0>, std::ratio< 1>, std::ratio< 0>, std::ratio< 0> > Mass;
typedef Dimensions< std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 1>, std::ratio< 0> > Charge;
typedef Dimensions< std::ratio< 0>, std::ratio<-1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Frequency;
typedef Dimensions< std::ratio< 0>, std::ratio<-1>, std::ratio< 0>, std::ratio< 1>, std::ratio< 0> > Current;
typedef Dimensions< std::ratio< 1>, std::ratio<-1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Velocity;
typedef Dimensions< std::ratio< 1>, std::ratio<-2>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Acceleration;


namespace INTERNAL_NAMESPACE {

	#define DIMENSION_OPERATOR(OPERATION_NAME, FRACTION_FUNCTION)\
		template<typename DimsLhs, typename DimsRhs> struct OPERATION_NAME {\
			typedef Dimensions<FRACTION_FUNCTION<typename DimsLhs::LENGTH     , typename DimsRhs::LENGTH     >,\
							   FRACTION_FUNCTION<typename DimsLhs::TIME       , typename DimsRhs::TIME       >,\
							   FRACTION_FUNCTION<typename DimsLhs::MASS       , typename DimsRhs::MASS       >,\
							   FRACTION_FUNCTION<typename DimsLhs::CHARGE     , typename DimsRhs::CHARGE     >,\
							   FRACTION_FUNCTION<typename DimsLhs::TEMPERATURE, typename DimsRhs::TEMPERATURE> > result;\
		};

	DIMENSION_OPERATOR(__ADD_DIMENSIONS__, std::ratio_add)
	DIMENSION_OPERATOR(__SUB_DIMENSIONS__, std::ratio_subtract)
	#undef DIMENSION_OPERATOR


	template<typename scalar_ratio, typename DimsRhs> struct __MUL_DIMENSIONS_BY_SCALAR__ {\
		typedef Dimensions<std::ratio_multiply<scalar_ratio, typename DimsRhs::LENGTH     >,\
						   std::ratio_multiply<scalar_ratio, typename DimsRhs::TIME       >,\
						   std::ratio_multiply<scalar_ratio, typename DimsRhs::MASS       >,\
						   std::ratio_multiply<scalar_ratio, typename DimsRhs::CHARGE     >,\
						   std::ratio_multiply<scalar_ratio, typename DimsRhs::TEMPERATURE> > result;\
	};

}