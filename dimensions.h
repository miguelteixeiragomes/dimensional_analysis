#pragma once


template<typename length, 
         typename time, 
         typename mass, 
         typename charge,
         typename temperature> 
	struct Dimensions {
		using LENGTH      = length     ;
		using TIME        = time       ;
		using MASS        = mass       ;
		using CHARGE      = charge     ;
		using TEMPERATURE = temperature;
	};

typedef Dimensions< std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0> > Adimensional;



namespace INTERNAL_NAMESPACE {

	#define DIMENSION_OPERATOR(OPERATION_NAME, FRACTION_FUNCTION)\
		template<typename DimsLhs, typename DimsRhs> struct OPERATION_NAME {\
			using result = Dimensions<FRACTION_FUNCTION<typename DimsLhs::LENGTH     , typename DimsRhs::LENGTH     >,\
			                          FRACTION_FUNCTION<typename DimsLhs::TIME       , typename DimsRhs::TIME       >,\
			                          FRACTION_FUNCTION<typename DimsLhs::MASS       , typename DimsRhs::MASS       >,\
			                          FRACTION_FUNCTION<typename DimsLhs::CHARGE     , typename DimsRhs::CHARGE     >,\
			                          FRACTION_FUNCTION<typename DimsLhs::TEMPERATURE, typename DimsRhs::TEMPERATURE> > ;\
		};

	DIMENSION_OPERATOR(__ADD_DIMENSIONS__, std::ratio_add)
	DIMENSION_OPERATOR(__SUB_DIMENSIONS__, std::ratio_subtract)
	#undef DIMENSION_OPERATOR


	template<typename scalar_ratio, typename DimsRhs> struct __MUL_DIMENSIONS_BY_SCALAR__ {
		using result = Dimensions<std::ratio_multiply<scalar_ratio, typename DimsRhs::LENGTH     >,
		                          std::ratio_multiply<scalar_ratio, typename DimsRhs::TIME       >,
		                          std::ratio_multiply<scalar_ratio, typename DimsRhs::MASS       >,
		                          std::ratio_multiply<scalar_ratio, typename DimsRhs::CHARGE     >,
		                          std::ratio_multiply<scalar_ratio, typename DimsRhs::TEMPERATURE> >;
	};

}


template<typename D0, typename ... Dn> struct MUL_DIMS {
	using value = typename INTERNAL_NAMESPACE::__ADD_DIMENSIONS__<D0, typename MUL_DIMS<Dn...>::value>::result;
};

template<typename D0> struct MUL_DIMS<D0> {
	using value = D0;
};