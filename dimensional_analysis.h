#pragma once

#include <boost\cstdfloat.hpp>
#include <boost\mpl\set.hpp>
#include <boost\mpl\assert.hpp>
#include <boost\multiprecision\cpp_dec_float.hpp>
#include <boost\static_assert.hpp>
#include <boost\variant.hpp>
#include "dimensions.h"

//#define SKIP_ALL
#define INT8 int8
#define INT16 int16
#define INT32 int32
#define INT64 int64
#define UINT8 uint8
#define UINT16 uint16
#define UINT32 uint32
#define UINT64 uint64
#define FLOAT32 float32
#define FLOAT64 float64


#ifndef SKIP_ALL

	typedef boost::variant<std::int8_t, 
						   std::int16_t, 
						   std::int32_t, 
						   std::int64_t, 
						   std::uint8_t, 
						   std::uint16_t, 
						   std::uint32_t, 
						   std::uint64_t, 
						   boost::float32_t, 
						   boost::float64_t> AllowedPrimitiveTypes;

	typedef boost::variant<std::int8_t, 
						   std::int16_t, 
						   std::int32_t, 
						   std::int64_t, 
						   std::uint8_t, 
						   std::uint16_t, 
						   std::uint32_t, 
						   std::uint64_t> AllowedPrimitiveIntegers;

	template<typename NumT> struct NumericValue {
		static const NumT value;
	};

	template<typename NumT, typename Dims = Adimensional> class PrimitiveType {
		static_assert(boost::mpl::contains<AllowedPrimitiveTypes::types, NumT>::type::value, "Only primitive numeric types are allowed.");

		public:
			NumT value;

			inline PrimitiveType() {}

			inline PrimitiveType(NumT value) : value(value) {}

			template<typename NumT2> inline PrimitiveType(PrimitiveType<NumT2, Dims> x) {
				this->value = x.value;
			}

			inline friend std::ostream &operator<<(std::ostream &os, PrimitiveType<NumT, Dims> &rhs) {
					return os << rhs.value;
			}

			#define UNARY_PLUS_MINUS(OPERATOR)\
				inline PrimitiveType<decltype( ## OPERATOR ## NumericValue<NumT>::value), Dims> operator OPERATOR () {\
					return PrimitiveType<decltype( ## OPERATOR ## NumericValue<NumT>::value), Dims>( ## OPERATOR ## value);\
				}

			#define	UNARY_INCREMENT_DECREMENT(OPERATOR)\
				inline PrimitiveType<NumT, Dims>& operator ## OPERATOR ## () {\
					value ## OPERATOR ##;\
					return *this;\
				}\
				inline PrimitiveType<NumT, Dims>& operator ## OPERATOR ## (int) {\
					PrimitiveType<NumT, Dims> temp = *this;\
					value ## OPERATOR ##;\
					return temp;\
				}

			#define SAME_UNITS_COMPOUND_ASSIGNMENT(OPERATOR, ERROR_MESSAGE)\
				template<typename NumT_rhs> inline PrimitiveType<NumT, Dims> operator OPERATOR (PrimitiveType<NumT_rhs, Dims> rhs){\
					this->value OPERATOR rhs.value;\
					return *this;\
				}\
				\
				template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs> struct ERROR_MESSAGE;\
				\
				template<typename NumT_rhs, typename DimsRhs>\
					ERROR_MESSAGE<NumT, Dims, NumT_rhs, DimsRhs> operator OPERATOR (PrimitiveType<NumT_rhs, DimsRhs> rhs);

			#define MUL_DIV_COMPOUND_ASSIGNMENT(OPERATOR, ERROR_MESSAGE)\
				inline PrimitiveType<NumT, Dims> operator OPERATOR (PrimitiveType<NumT, Adimensional> rhs){\
					this->value OPERATOR rhs.value;\
					return *this;\
				}\
				\
				template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs> struct ERROR_MESSAGE;\
				\
				template<typename NumT_lhs, typename NumT_rhs, typename DimsRhs>\
					ERROR_MESSAGE<NumT, Dims, NumT_rhs, DimsRhs> operator OPERATOR (PrimitiveType<NumT_rhs, DimsRhs> rhs);


			UNARY_PLUS_MINUS(+)
			UNARY_PLUS_MINUS(-)

			UNARY_INCREMENT_DECREMENT(++)
			UNARY_INCREMENT_DECREMENT(--)

			SAME_UNITS_COMPOUND_ASSIGNMENT(+=, Unmatched_dimensions_in_compound_addition_between)
			SAME_UNITS_COMPOUND_ASSIGNMENT(-=, Unmatched_dimensions_in_compound_addition_between)


			template<typename NumT_alt = NumT, typename Dims_alt = Dims>
				/*inline typename std::enable_if<boost::mpl::contains<AllowedPrimitiveIntegers::types, NumT_alt>::type::value,*/ PrimitiveType<decltype(~NumericType<NumT_alt>::value), Dims_alt> /*>::type*/
					operator~() {
						return PrimitiveType<decltype(~NumericType<NumT_alt>::value), Dims_alt>(~(this->value));
			}
			
			/*struct Bitwise_negation_is_only_available_for_adimensional_integers;

			template<typename NumT_alt = NumT, typename Dims_alt = Dims>
				inline typename std::enable_if<!boost::mpl::contains<AllowedPrimitiveIntegers::types, NumT_alt>::type::value, Bitwise_negation_is_only_available_for_adimensional_integers_not>::type
					operator~() {
						return PrimitiveType<decltype(~PrimitiveType<NumT_alt, Dims_alt>::value), Dims_alt>(~(this->value));
			}*/
	};

	#define SAME_UNITS_OPERATOR(OPERATOR, ERROR_MESSAGE)\
		template<typename NumT_lhs, typename NumT_rhs, typename Dims>\
			inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Dims>\
				operator OPERATOR (PrimitiveType<NumT_lhs, Dims> lhs, PrimitiveType<NumT_rhs, Dims> rhs) {\
					return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Dims>(lhs.value OPERATOR rhs.value);\
				}\
		\
		template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs> struct ERROR_MESSAGE;\
		\
		template<typename NumT_lhs, typename NumT_rhs, typename DimsLhs, typename DimsRhs>\
			ERROR_MESSAGE<NumT_lhs, DimsLhs, NumT_rhs, DimsRhs> operator OPERATOR (PrimitiveType<NumT_lhs, DimsLhs> lhs, PrimitiveType<NumT_rhs, DimsRhs> rhs);

	#define COMPARATOR(OPERATOR, ERROR_MESSAGE)\
		template<typename NumT_lhs, typename NumT_rhs, typename Dims>\
			inline bool operator OPERATOR (PrimitiveType<NumT_lhs, Dims> lhs, PrimitiveType<NumT_rhs, Dims> rhs) {\
					return lhs.value OPERATOR rhs.value;\
				}\
		\
		template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs> struct ERROR_MESSAGE;\
		\
		template<typename NumT_lhs, typename NumT_rhs, typename DimsLhs, typename DimsRhs>\
			ERROR_MESSAGE<NumT_lhs, DimsLhs, NumT_rhs, DimsRhs> operator OPERATOR (PrimitiveType<NumT_lhs, DimsLhs> lhs, PrimitiveType<NumT_rhs, DimsRhs> rhs);

	#define MUL_OR_DIV(OPERATOR, CT_FUNC)\
		template<typename NumT_lhs, typename NumT_rhs, typename DimsLhs, typename DimsRhs>\
			inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), typename CT_FUNC ## <DimsLhs, DimsRhs>::result>\
				operator OPERATOR (PrimitiveType<NumT_lhs, DimsLhs> lhs, PrimitiveType<NumT_rhs, DimsRhs> rhs) {\
					return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), typename CT_FUNC ## <DimsLhs, DimsRhs>::result>(lhs.value OPERATOR rhs.value);\
				}

	#define BITWISE_BINARY_OPERATOR(OPERATOR, ERROR_MESSAGE)\
		template<typename NumT_lhs, typename NumT_rhs>\
			inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>\
				operator OPERATOR (PrimitiveType<NumT_lhs, Adimensional> lhs, PrimitiveType<NumT_rhs, Adimensional> rhs) {\
					return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>(lhs.value OPERATOR rhs.value);\
				}\
		\
		template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs> struct ERROR_MESSAGE;\
		\
		template<typename NumT_lhs, typename NumT_rhs, typename DimsLhs, typename DimsRhs>\
			ERROR_MESSAGE<NumT_lhs, DimsLhs, NumT_rhs, DimsRhs> operator OPERATOR (PrimitiveType<NumT_lhs, DimsLhs> lhs, PrimitiveType<NumT_rhs, DimsRhs> rhs);


	SAME_UNITS_OPERATOR(+, Unmatched_dimensions_in_addition_between)
	SAME_UNITS_OPERATOR(-, Unmatched_dimensions_in_subtraction_between)

	MUL_OR_DIV(*, __ADD_DIMENSIONS__)
	MUL_OR_DIV(/, __SUB_DIMENSIONS__)

	COMPARATOR(==, Unmatched_dimensions_in_comparison_operator_equal_between)
	COMPARATOR(!=, Unmatched_dimensions_in_comparison_operator_unequal_between)
	COMPARATOR(> , Unmatched_dimensions_in_comparison_operator_greater_than_between)
	COMPARATOR(< , Unmatched_dimensions_in_comparison_operator_less_than_between)
	COMPARATOR(>=, Unmatched_dimensions_in_comparison_operator_greater_than_or_equal_to_between)
	COMPARATOR(<=, Unmatched_dimensions_in_comparison_operator_less_than_or_equal_to_between)

	BITWISE_BINARY_OPERATOR(| , Bitwise_or_is_only_available_between_adimensional_numbers_and_not_for)
	BITWISE_BINARY_OPERATOR(& , Bitwise_and_is_only_available_between_adimensional_numbers_and_not_for)
	BITWISE_BINARY_OPERATOR(^ , Bitwise_exclusive_or_is_only_available_between_adimensional_numbers_and_not_for)
	BITWISE_BINARY_OPERATOR(<<, Bitwise_left_shift_is_only_available_between_adimensional_numbers_and_not_for)
	BITWISE_BINARY_OPERATOR(>>, Bitwise_right_shift_is_only_available_between_adimensional_numbers_and_not_for)


	template<typename Dims> using INT8  = PrimitiveType<std::int8_t , Dims>;
	template<typename Dims> using INT16 = PrimitiveType<std::int16_t, Dims>;
	template<typename Dims> using INT32 = PrimitiveType<std::int32_t, Dims>;
	template<typename Dims> using INT64 = PrimitiveType<std::int64_t, Dims>;

	template<typename Dims> using UINT8  = PrimitiveType<std::uint8_t , Dims>;
	template<typename Dims> using UINT16 = PrimitiveType<std::uint16_t, Dims>;
	template<typename Dims> using UINT32 = PrimitiveType<std::uint32_t, Dims>;
	template<typename Dims> using UINT64 = PrimitiveType<std::uint64_t, Dims>;

	template<typename Dims> using FLOAT32 = PrimitiveType<boost::float32_t, Dims>;
	template<typename Dims> using FLOAT64 = PrimitiveType<boost::float64_t, Dims>;


	/*using INT8  = INT8<Adimensional>;
	using INT16 = INT16<Adimensional>;
	using INT32 = INT32<Adimensional>;
	using INT64 = INT64<Adimensional>;

	using UINT8  = UINT8<Adimensional>;
	using UINT16 = UINT16<Adimensional>;
	using UINT32 = UINT32<Adimensional>;
	using UINT64 = UINT64<Adimensional>;

	using FLOAT32 = FLOAT32<Adimensional>;
	using FLOAT64 = FLOAT64<Adimensional>;*/

#else

	template<typename Dims> using INT8  = std::int8_t;
	template<typename Dims> using INT16 = std::int16_t;
	template<typename Dims> using INT32 = std::int32_t;
	template<typename Dims> using INT64 = std::int64_t;

	template<typename Dims> using UINT8  = std::uint8_t;
	template<typename Dims> using UINT16 = std::uint16_t;
	template<typename Dims> using UINT32 = std::uint32_t;
	template<typename Dims> using UINT64 = std::uint64_t;

	template<typename Dims> using FLOAT32 = boost::float32_t;
	template<typename Dims> using FLOAT64 = boost::float64_t;

#endif