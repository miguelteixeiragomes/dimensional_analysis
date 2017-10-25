#pragma once

#include <ratio>


template<typename length, 
		 typename time, 
		 typename mass, 
		 typename charge,
		 typename temperature, 
		 typename amount, 
		 typename intensity> 
	struct Dimensions {
		typedef length      LENGTH;
		typedef time        TIME;
		typedef mass        MASS;
		typedef charge      CHARGE;
		typedef temperature TEMPERATURE;
		typedef amount      AMOUNT;
		typedef intensity   INTENSITY;
	};


typedef Dimensions< std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Adimensional;
typedef Dimensions< std::ratio< 1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Length;
typedef Dimensions< std::ratio< 0>, std::ratio< 1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Time;
typedef Dimensions< std::ratio< 0>, std::ratio< 0>, std::ratio< 1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Mass;
typedef Dimensions< std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Charge;
typedef Dimensions< std::ratio< 0>, std::ratio<-1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Frequency;
typedef Dimensions< std::ratio< 0>, std::ratio<-1>, std::ratio< 0>, std::ratio< 1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Current;
typedef Dimensions< std::ratio< 1>, std::ratio<-1>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0>, std::ratio< 0> > Velocity;


#define DIMENSION_OPERATOR(OPERATION_NAME, FRACTION_FUNCTION)\
	template<typename DimsLhs, typename DimsRhs> struct OPERATION_NAME {\
		typedef Dimensions<FRACTION_FUNCTION<typename DimsLhs::LENGTH     , typename DimsRhs::LENGTH     >,\
						   FRACTION_FUNCTION<typename DimsLhs::TIME       , typename DimsRhs::TIME       >,\
						   FRACTION_FUNCTION<typename DimsLhs::MASS       , typename DimsRhs::MASS       >,\
						   FRACTION_FUNCTION<typename DimsLhs::CHARGE     , typename DimsRhs::CHARGE     >,\
						   FRACTION_FUNCTION<typename DimsLhs::TEMPERATURE, typename DimsRhs::TEMPERATURE>,\
						   FRACTION_FUNCTION<typename DimsLhs::AMOUNT     , typename DimsRhs::AMOUNT     >,\
						   FRACTION_FUNCTION<typename DimsLhs::INTENSITY  , typename DimsRhs::INTENSITY  > > result;\
	};

DIMENSION_OPERATOR(__ADD_DIMENSIONS__, std::ratio_add)
DIMENSION_OPERATOR(__SUB_DIMENSIONS__, std::ratio_subtract)
#undef DIMENSION_OPERATOR


template<typename scalar_ratio, typename DimsRhs> struct __MUL_DIMENSIONS_BY_SCALAR__ {\
	typedef Dimensions<std::ratio_multiply<scalar_ratio, typename DimsRhs::LENGTH     >,\
					   std::ratio_multiply<scalar_ratio, typename DimsRhs::TIME       >,\
					   std::ratio_multiply<scalar_ratio, typename DimsRhs::MASS       >,\
					   std::ratio_multiply<scalar_ratio, typename DimsRhs::CHARGE     >,\
					   std::ratio_multiply<scalar_ratio, typename DimsRhs::TEMPERATURE>,\
					   std::ratio_multiply<scalar_ratio, typename DimsRhs::AMOUNT     >,\
					   std::ratio_multiply<scalar_ratio, typename DimsRhs::INTENSITY  > > result;\
};


/*template<typename ValueType, typename DimsType = Adimensional> class Quantity {
	private:
		ValueType m_value;

	public:
		Quantity(ValueType value) : m_value(value) {}

		inline ValueType value() {
			return m_value;
		}
	};

	template<typename T, typename D> inline Quantity<T, D> operator+(Quantity<T, D> lhs, Quantity<T, D> rhs) {
		return Quantity<T, D>(lhs.value() + rhs.value());
	}

	template<typename T, typename D> inline Quantity<T, D> operator-(Quantity<T, D> lhs, Quantity<T, D> rhs) {
		return Quantity<T, D>(lhs.value() - rhs.value());
	}

	template<typename T, typename DimsTypeLhs, typename DimsTypeRhs> inline Quantity<T, typename __MUL__<DimsTypeLhs, DimsTypeRhs>::result> operator*(Quantity<T, DimsTypeLhs> lhs, Quantity<T, DimsTypeRhs> rhs) {
		return lhs.value() * rhs.value();
	}

	template<typename T, typename DimsTypeLhs, typename DimsTypeRhs> inline Quantity<T, typename __DIV__<DimsTypeLhs, DimsTypeRhs>::result> operator/(Quantity<T, DimsTypeLhs> lhs, Quantity<T, DimsTypeRhs> rhs) {
		return lhs.value() / rhs.value();
	}*/