#pragma once


#ifndef SKIP_DIMENSIONAL_ANALYSIS

	namespace INTERNAL_NAMESPACE {

		#ifdef EXPLICIT_CONSTRUCTOR
			#define EXPLICIT explicit
		#else
			#define EXPLICIT
		#endif

		template<typename NumT> struct NumericValue {
			static const NumT value;
		};

		template<typename NumT, typename Dims, bool only_built_ins = true> class PrimitiveType;

		template<typename NumT, typename Dims> class PrimitiveTypeBase {
			public:
				NumT value;

				inline PrimitiveTypeBase() {}

				inline PrimitiveTypeBase(NumT value) : value(value) {}
		};

		template<typename NumT> class PrimitiveTypeBase<NumT, Adimensional> {
			public:
				NumT value;

				inline PrimitiveTypeBase() {}

				inline PrimitiveTypeBase(NumT value) : value(value) {}
				
				inline PrimitiveTypeBase(PrimitiveType<NumT, Adimensional> x) : value(x.value) {}

				inline PrimitiveTypeBase<NumT, Adimensional> operator=(PrimitiveType<NumT, Adimensional> rhs) {
					this->value = rhs.value;
					return *this;
				}

				inline operator NumT() {
					return this->value;
				}
		};

		template<typename NumT, typename Dims, bool only_built_ins> class PrimitiveType : public PrimitiveTypeBase<NumT, Dims> {
			//static_assert((std::is_arithmetic<NumT>::value & !std::is_same<NumT, bool>::value) | !only_built_ins, "Only C++ primitive numeric types are allowed as first template specialization of class 'PrimitiveType'.");
		
			public:
				inline PrimitiveType() {}

				EXPLICIT inline PrimitiveType(NumT value) : PrimitiveTypeBase<NumT, Dims>(value) {}

				//EXPLICIT template<typename ...Args> inline PrimitiveType(Args... args) : PrimitiveTypeBase<T, Dims, false>(T(args...)) {}

				inline PrimitiveType<NumT, Dims> operator=(NumT rhs) {
					this->value = rhs;
					return *this;
				}

				template<typename NumT2> inline PrimitiveType(PrimitiveType<NumT2, Dims> x) {
					this->value = x.value;
				}
			
				#define UNARY_PLUS_MINUS(OPERATOR)\
					inline PrimitiveType<decltype( OPERATOR NumericValue<NumT>::value), Dims> operator OPERATOR () {\
						return PrimitiveType<decltype( OPERATOR NumericValue<NumT>::value), Dims>( OPERATOR this->value);\
					}
			
				#define	UNARY_INCREMENT_DECREMENT(OPERATOR)\
					inline PrimitiveType<NumT, Dims>& operator OPERATOR () {\
						(this->value) OPERATOR;\
						return *this;\
					}\
					inline PrimitiveType<NumT, Dims> operator OPERATOR (int) {\
						PrimitiveType<NumT, Dims> temp = *this;\
						(this->value) OPERATOR;\
						return temp;\
					}


				UNARY_PLUS_MINUS(+)
				UNARY_PLUS_MINUS(-)
			
				UNARY_INCREMENT_DECREMENT(++)
				UNARY_INCREMENT_DECREMENT(--)
		};

		template<typename NumT, typename Dims> inline std::ostream &operator<<(std::ostream &os, PrimitiveType<NumT, Dims> rhs) {
			return os << rhs.value;
		}


		// Operator overloads between the library's primitive types
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

		#define SAME_UNITS_COMPOUND_ASSIGNMENT(OPERATOR, ERROR_MESSAGE)\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims>\
				inline PrimitiveType<NumT_lhs, Dims> operator OPERATOR (PrimitiveType<NumT_lhs, Dims>& lhs, PrimitiveType<NumT_rhs, Dims> rhs){\
					lhs.value OPERATOR rhs.value;\
					return lhs;\
				}\
			\
			template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs> struct ERROR_MESSAGE;\
			\
			template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs>\
				ERROR_MESSAGE<NumT_lhs, DimsLhs, NumT_rhs, DimsRhs> operator OPERATOR (PrimitiveType<NumT_lhs, DimsLhs> lhs, PrimitiveType<NumT_rhs, DimsRhs> rhs);

		#define MUL_DIV_COMPOUND_ASSIGNMENT(OPERATOR, ERROR_MESSAGE)\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims>\
				inline PrimitiveType<NumT_lhs, Dims> operator OPERATOR (PrimitiveType<NumT_lhs, Dims>& lhs, PrimitiveType<NumT_rhs, Adimensional> rhs){\
					lhs.value OPERATOR rhs.value;\
					return lhs;\
				}\
			\
			template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs> struct ERROR_MESSAGE;\
			\
			template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs>\
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
				inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), typename CT_FUNC<DimsLhs, DimsRhs>::result>\
					operator OPERATOR (PrimitiveType<NumT_lhs, DimsLhs> lhs, PrimitiveType<NumT_rhs, DimsRhs> rhs) {\
						return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), typename CT_FUNC<DimsLhs, DimsRhs>::result>(lhs.value OPERATOR rhs.value);\
					}

		#define BITWISE_BINARY_OPERATOR(OPERATOR, ERROR_MESSAGE)\
			template<typename NumT_lhs, typename NumT_rhs, typename Constraint = typename std::enable_if<std::is_integral<NumT_lhs>::value & std::is_integral<NumT_rhs>::value, void>::type>\
				inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>\
					operator OPERATOR (PrimitiveType<NumT_lhs, Adimensional> lhs, PrimitiveType<NumT_rhs, Adimensional> rhs) {\
						return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>(lhs.value OPERATOR rhs.value);\
					}\
			\
			template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs> struct ERROR_MESSAGE;\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename DimsLhs, typename DimsRhs, typename Constraint = typename std::enable_if<std::is_integral<NumT_lhs>::value & std::is_integral<NumT_rhs>::value, void>::type>\
				ERROR_MESSAGE<NumT_lhs, DimsLhs, NumT_rhs, DimsRhs> operator OPERATOR (PrimitiveType<NumT_lhs, DimsLhs> lhs, PrimitiveType<NumT_rhs, DimsRhs> rhs);
	
		#define BITWISE_COMPOUND_ASSIGNMENT(OPERATOR, ERROR_MESSAGE)\
			template<typename NumT_lhs, typename NumT_rhs, typename Constraint = typename std::enable_if<std::is_integral<NumT_lhs>::value & std::is_integral<NumT_rhs>::value, void>::type>\
				inline PrimitiveType<NumT_lhs, Adimensional>\
					operator OPERATOR (PrimitiveType<NumT_lhs, Adimensional>& lhs, PrimitiveType<NumT_rhs, Adimensional> rhs) {\
						return PrimitiveType<NumT_lhs, Adimensional>(lhs.value OPERATOR rhs.value);\
					}\
			\
			template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs> struct ERROR_MESSAGE;\
			\
			template<typename NumT_lhs, typename DimsLhs, typename NumT_rhs, typename DimsRhs, typename Constraint = typename std::enable_if<std::is_integral<NumT_lhs>::value & std::is_integral<NumT_rhs>::value, void>::type>\
				inline ERROR_MESSAGE<NumT_lhs, DimsLhs, NumT_rhs, DimsRhs>\
					operator OPERATOR (PrimitiveType<NumT_lhs, DimsLhs> lhs, PrimitiveType<NumT_rhs, DimsRhs> rhs);

		SAME_UNITS_OPERATOR(+, Unmatched_dimensions_in_addition_between)
		SAME_UNITS_OPERATOR(-, Unmatched_dimensions_in_subtraction_between)

		MUL_OR_DIV(*, __ADD_DIMENSIONS__)
		MUL_OR_DIV(/, __SUB_DIMENSIONS__)

		SAME_UNITS_COMPOUND_ASSIGNMENT(+=, Unmatched_dimensions_in_compound_addition_between)
		SAME_UNITS_COMPOUND_ASSIGNMENT(-=, Unmatched_dimensions_in_compound_subtraction_between)

		MUL_DIV_COMPOUND_ASSIGNMENT(*=, Compound_assignment_multiplication_is_only_possible_with_an_adimensional_right_hand_side)
		MUL_DIV_COMPOUND_ASSIGNMENT(/=, Compound_assignment_division_is_only_possible_with_an_adimensional_right_hand_side)

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

		BITWISE_COMPOUND_ASSIGNMENT(|= , Compound_assignment_bitwise_or_is_only_possible_between_adimensional_quantities)
		BITWISE_COMPOUND_ASSIGNMENT(^= , Compound_assignment_bitwise_exclusive_or_is_only_possible_between_adimensional_quantities)
		BITWISE_COMPOUND_ASSIGNMENT(&= , Compound_assignment_bitwise_and_is_only_possible_between_adimensional_quantities)
		BITWISE_COMPOUND_ASSIGNMENT(<<=, Compound_assignment_bitwise_left_shift_is_only_possible_between_adimensional_quantities)
		BITWISE_COMPOUND_ASSIGNMENT(>>=, Compound_assignment_bitwise_right_shift_is_only_possible_between_adimensional_quantities)

	
		// Operator overloads between the library's adimensional primitive types and C++ primitive types (including 'bool')
		#define SAME_UNITS_OPERATOR_WITH_C_PRIM(OPERATOR, ERROR_MESSAGE)\
			template<typename NumT_lhs, typename NumT_rhs/*, typename Constraint = typename std::enable_if<std::is_arithmetic<NumT_lhs>::value, void>::type*/>\
				inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>\
					operator OPERATOR (NumT_lhs lhs, PrimitiveType<NumT_rhs, Adimensional> rhs) {\
						return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>(lhs OPERATOR rhs.value);\
					}\
			\
			template<typename NumT_lhs, typename NumT_rhs/*, typename Constraint = typename std::enable_if<std::is_arithmetic<NumT_rhs>::value, void>::type*/>\
				inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>\
					operator OPERATOR (PrimitiveType<NumT_lhs, Adimensional> lhs, NumT_rhs rhs) {\
						return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>(lhs.value OPERATOR rhs);\
					}\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims> struct ERROR_MESSAGE;\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims, typename Constraint = typename std::enable_if<std::is_arithmetic<NumT_lhs>::value, void>::type>\
				ERROR_MESSAGE<NumT_lhs, NumT_rhs, Dims> operator OPERATOR (NumT_lhs lhs, PrimitiveType<NumT_rhs, Dims> rhs);\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims/*, typename Constraint = typename std::enable_if<std::is_arithmetic<NumT_rhs>::value, void>::type*/>\
				ERROR_MESSAGE<NumT_lhs, NumT_rhs, Dims> operator OPERATOR (PrimitiveType<NumT_lhs, Dims> lhs, NumT_rhs rhs);

		#define MUL_OR_DIV_C_PRIM(OPERATOR, CT_FUNC)\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims>\
				inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), typename CT_FUNC<Adimensional, Dims>::result>\
					operator OPERATOR (NumT_lhs lhs, PrimitiveType<NumT_rhs, Dims> rhs) {\
						return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), typename CT_FUNC<Adimensional, Dims>::result>(lhs OPERATOR rhs.value);\
					}\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims>\
				inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), typename CT_FUNC<Dims, Adimensional>::result>\
					operator OPERATOR (PrimitiveType<NumT_lhs, Dims> lhs, NumT_rhs rhs) {\
						return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), typename CT_FUNC<Dims, Adimensional>::result>(lhs.value OPERATOR rhs);\
					}

		#define COMPARATOR_C_PRIM(OPERATOR, ERROR_MESSAGE)\
			template<typename NumT_lhs, typename NumT_rhs>\
				inline bool operator OPERATOR (NumT_lhs lhs, PrimitiveType<NumT_rhs, Adimensional> rhs) {\
						return lhs OPERATOR rhs.value;\
					}\
			\
			template<typename NumT_lhs, typename NumT_rhs>\
				inline bool operator OPERATOR (PrimitiveType<NumT_lhs, Adimensional> lhs, NumT_rhs rhs) {\
						return lhs.value OPERATOR rhs;\
					}\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims> struct ERROR_MESSAGE;\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims>\
				ERROR_MESSAGE<NumT_lhs, NumT_rhs, Dims> operator OPERATOR (NumT_lhs lhs, PrimitiveType<NumT_rhs, Dims> rhs);\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims>\
				ERROR_MESSAGE<NumT_lhs, NumT_rhs, Dims> operator OPERATOR (PrimitiveType<NumT_lhs, Dims> lhs, NumT_rhs rhs);

		#define BITWISE_BINARY_OPERATOR_C_PRIM(OPERATOR, ERROR_MESSAGE)\
			template<typename NumT_lhs, typename NumT_rhs, typename Constraint = typename std::enable_if<std::is_integral<NumT_lhs>::value & std::is_integral<NumT_rhs>::value, void>::type>\
				inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>\
					operator OPERATOR (NumT_lhs lhs, PrimitiveType<NumT_rhs, Adimensional> rhs) {\
						return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>(lhs OPERATOR rhs.value);\
					}\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Constraint = typename std::enable_if<std::is_integral<NumT_lhs>::value & std::is_integral<NumT_rhs>::value, void>::type>\
				inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>\
					operator OPERATOR (PrimitiveType<NumT_lhs, Adimensional> lhs, NumT_rhs rhs) {\
						return PrimitiveType<decltype(NumericValue<NumT_lhs>::value OPERATOR NumericValue<NumT_rhs>::value), Adimensional>(lhs.value OPERATOR rhs);\
					}\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims> struct ERROR_MESSAGE;\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims, typename Constraint = typename std::enable_if<std::is_integral<NumT_lhs>::value & std::is_integral<NumT_rhs>::value, void>::type>\
				ERROR_MESSAGE<NumT_lhs, NumT_rhs, Dims> operator OPERATOR (NumT_lhs lhs, PrimitiveType<NumT_rhs, Dims> rhs);\
			\
			template<typename NumT_lhs, typename NumT_rhs, typename Dims, typename Constraint = typename std::enable_if<std::is_integral<NumT_lhs>::value & std::is_integral<NumT_rhs>::value, void>::type>\
				ERROR_MESSAGE<NumT_lhs, NumT_rhs, Dims> operator OPERATOR (PrimitiveType<NumT_lhs, Dims> lhs, NumT_rhs rhs);
	
		
		SAME_UNITS_OPERATOR_WITH_C_PRIM(+, Addition_is_not_possible_between_Cpp_primitive_types_and_dimensioned_quantities)
		SAME_UNITS_OPERATOR_WITH_C_PRIM(-, Addition_is_not_possible_between_Cpp_primitive_types_and_dimensioned_quantities)
	
		MUL_OR_DIV_C_PRIM(*, __ADD_DIMENSIONS__)
		MUL_OR_DIV_C_PRIM(/, __SUB_DIMENSIONS__)

		COMPARATOR_C_PRIM(==, Comparison_operator_equal_is_not_available_between_Cpp_primitives_and_dimensioned_quantities)
		COMPARATOR_C_PRIM(!=, Comparison_operator_unequal_is_not_available_between_Cpp_primitives_and_dimensioned_quantities)
		COMPARATOR_C_PRIM(> , Comparison_operator_greater_than_is_not_available_between_Cpp_primitives_and_dimensioned_quantities)
		COMPARATOR_C_PRIM(< , Comparison_operator_less_than_is_not_available_between_Cpp_primitives_and_dimensioned_quantities)
		COMPARATOR_C_PRIM(>=, Comparison_operator_greater_than_or_equal_to_is_not_available_between_Cpp_primitives_and_dimensioned_quantities)
		COMPARATOR_C_PRIM(<=, Comparison_operator_less_than_or_equal_to_is_not_available_between_Cpp_primitives_and_dimensioned_quantities)

		BITWISE_BINARY_OPERATOR_C_PRIM(| , Bitwise_or_is_not_available_between_Cpp_primitive_types_and_dimensioned_quantities)
		BITWISE_BINARY_OPERATOR_C_PRIM(& , Bitwise_and_is_not_available_between_Cpp_primitive_types_and_dimensioned_quantities)
		BITWISE_BINARY_OPERATOR_C_PRIM(^ , Bitwise_exclusive_or_is_not_available_between_Cpp_primitive_types_and_dimensioned_quantities)
		BITWISE_BINARY_OPERATOR_C_PRIM(<<, Bitwise_left_shift_is_not_available_between_Cpp_primitive_types_and_dimensioned_quantities)
		BITWISE_BINARY_OPERATOR_C_PRIM(>>, Bitwise_right_shift_is_not_available_between_Cpp_primitive_types_and_dimensioned_quantities)
		
		
	
		template<typename NumT> struct Bitwise_negation_is_only_available_for_integers_and_not;
		Bitwise_negation_is_only_available_for_integers_and_not<FLOAT32_T> operator~(PrimitiveType<FLOAT32_T, Adimensional> x);
		Bitwise_negation_is_only_available_for_integers_and_not<FLOAT64_T> operator~(PrimitiveType<FLOAT64_T, Adimensional> x);
		template<typename NumT> PrimitiveType<NumT, Adimensional> operator~(PrimitiveType<NumT, Adimensional> x) {
			return PrimitiveType<NumT, Adimensional>(~x.value);
		}
		template<typename NumT, typename Dims> struct Bitwise_negation_is_only_available_for_adimensional_quantities_and_not;
		template<typename NumT, typename Dims> Bitwise_negation_is_only_available_for_adimensional_quantities_and_not<NumT, Dims> operator~(PrimitiveType<NumT, Dims> x);
	

		template<typename NumT_lhs, typename NumT_rhs, typename DimsLhs, typename DimsRhs>
			inline PrimitiveType<decltype(NumericValue<NumT_lhs>::value % NumericValue<NumT_rhs>::value), DimsLhs>
				operator%(PrimitiveType<NumT_lhs, DimsLhs> lhs, PrimitiveType<NumT_rhs, DimsRhs> rhs) {
					return PrimitiveType<decltype(NumericValue<NumT_lhs>::value % NumericValue<NumT_rhs>::value), DimsLhs>(lhs.value % rhs.value);
		}

	}


	// cmath adapted functions
	#define NUM_RET_TYPE typename std::conditional<std::is_floating_point<NumT>::value, NumT, double>::type
	#define RET_DIMS typename INTERNAL_NAMESPACE::__MUL_DIMENSIONS_BY_SCALAR__<std::ratio<exp_num, exp_den>, Dims>::result
	template<std::int64_t exp_num, std::int64_t exp_den = 1, typename NumT, typename Dims>
		inline INTERNAL_NAMESPACE::PrimitiveType<NUM_RET_TYPE, RET_DIMS>
			pow(INTERNAL_NAMESPACE::PrimitiveType<NumT, Dims> x) {
				return 
					INTERNAL_NAMESPACE::PrimitiveType<NUM_RET_TYPE, RET_DIMS>(
						std::pow(x.value, NUM_RET_TYPE(exp_num) / NUM_RET_TYPE(exp_den)));
			}
	#undef NUM_RET_TYPE
	#undef RET_DIMS

	#define NUM_RET_TYPE typename std::conditional<std::is_floating_point<NumT>::value, NumT, double>::type
	#define RET_DIMS typename INTERNAL_NAMESPACE::__MUL_DIMENSIONS_BY_SCALAR__<std::ratio<1, 2>, Dims>::result
	template<typename NumT, typename Dims>
		inline INTERNAL_NAMESPACE::PrimitiveType<NUM_RET_TYPE, RET_DIMS>
			sqrt(INTERNAL_NAMESPACE::PrimitiveType<NumT, Dims> x) {
				return INTERNAL_NAMESPACE::PrimitiveType<NUM_RET_TYPE, RET_DIMS>( std::sqrt(x.value) );
			}
	#undef NUM_RET_TYPE
	#undef RET_DIMS

	#define NUM_RET_TYPE typename std::conditional<std::is_floating_point<NumT>::value, NumT, double>::type
	#define RET_DIMS typename INTERNAL_NAMESPACE::__MUL_DIMENSIONS_BY_SCALAR__<std::ratio<1, 3>, Dims>::result
	template<typename NumT, typename Dims>
		inline INTERNAL_NAMESPACE::PrimitiveType<NUM_RET_TYPE, RET_DIMS>
			cbrt(INTERNAL_NAMESPACE::PrimitiveType<NumT, Dims> x) {
				return INTERNAL_NAMESPACE::PrimitiveType<NUM_RET_TYPE, RET_DIMS>( std::cbrt(x.value) );
			}
	#undef NUM_RET_TYPE
	#undef RET_DIMS


	// typedefing the primitive types
	template<typename Dims = Adimensional> using INT8  = INTERNAL_NAMESPACE::PrimitiveType<std::int8_t , Dims>;
	template<typename Dims = Adimensional> using INT16 = INTERNAL_NAMESPACE::PrimitiveType<std::int16_t, Dims>;
	template<typename Dims = Adimensional> using INT32 = INTERNAL_NAMESPACE::PrimitiveType<std::int32_t, Dims>;
	template<typename Dims = Adimensional> using INT64 = INTERNAL_NAMESPACE::PrimitiveType<std::int64_t, Dims>;

	template<typename Dims = Adimensional> using UINT8  = INTERNAL_NAMESPACE::PrimitiveType<std::uint8_t , Dims>;
	template<typename Dims = Adimensional> using UINT16 = INTERNAL_NAMESPACE::PrimitiveType<std::uint16_t, Dims>;
	template<typename Dims = Adimensional> using UINT32 = INTERNAL_NAMESPACE::PrimitiveType<std::uint32_t, Dims>;
	template<typename Dims = Adimensional> using UINT64 = INTERNAL_NAMESPACE::PrimitiveType<std::uint64_t, Dims>;

	template<typename Dims = Adimensional> using FLOAT32  = INTERNAL_NAMESPACE::PrimitiveType<FLOAT32_T , Dims>;
	template<typename Dims = Adimensional> using FLOAT64  = INTERNAL_NAMESPACE::PrimitiveType<FLOAT64_T , Dims>;
	template<typename Dims = Adimensional> using FLOAT128 = INTERNAL_NAMESPACE::PrimitiveType<FLOAT128_T, Dims>;


	#undef UNARY_PLUS_MINUS
	#undef UNARY_INCREMENT_DECREMENT
	#undef SAME_UNITS_COMPOUND_ASSIGNMENT
	#undef MUL_DIV_COMPOUND_ASSIGNMENT
	#undef SAME_UNITS_OPERATOR
	#undef COMPARATOR
	#undef MUL_OR_DIV
	#undef BITWISE_BINARY_OPERATOR
	#undef BITWISE_COMPOUND_ASSIGNMENT
	#undef SAME_UNITS_OPERATOR_WITH_C_PRIM
	#undef MUL_OR_DIV_C_PRIM
	#undef COMPARATOR_C_PRIM
	#undef BITWISE_BINARY_OPERATOR_C_PRIM
	#undef EXPLICIT

	#define remove_dims(X) PrimitiveTypes<decltype(X.value), Adimensional>(X.value)


	// generic dimensioned place-holder
	template<typename T, typename Dims = Adimensional> class Quantity : public INTERNAL_NAMESPACE::PrimitiveType<T, Dims> {
		public:
			inline Quantity() {}

			template<typename ...Args> inline Quantity(Args... args) : INTERNAL_NAMESPACE::PrimitiveType<T, Dims>(T(args...)) {}
	};
	//template<typename T, typename Dims = Adimensional> using Quantity = INTERNAL_NAMESPACE::PrimitiveType<T, Dims>;

#else

	template<typename Dims = Adimensional> using INT8  = std::int8_t;
	template<typename Dims = Adimensional> using INT16 = std::int16_t;
	template<typename Dims = Adimensional> using INT32 = std::int32_t;
	template<typename Dims = Adimensional> using INT64 = std::int64_t;

	template<typename Dims = Adimensional> using UINT8  = std::uint8_t;
	template<typename Dims = Adimensional> using UINT16 = std::uint16_t;
	template<typename Dims = Adimensional> using UINT32 = std::uint32_t;
	template<typename Dims = Adimensional> using UINT64 = std::uint64_t;

	template<typename Dims = Adimensional> using FLOAT32  = FLOAT32_T;
	template<typename Dims = Adimensional> using FLOAT64  = FLOAT64_T;
	template<typename Dims = Adimensional> using FLOAT128 = FLOAT128_T;


	#define NUM_RET_TYPE typename std::conditional<std::is_floating_point<NumT>::value, NumT, double>::type
	template<std::int64_t exp_num, std::int64_t exp_den = 1, typename NumT> 
		inline NUM_RET_TYPE pow(NumT base) {
			return std::pow(base, NUM_RET_TYPE(exp_num) / NUM_RET_TYPE(exp_den));
		}
	#undef NUM_RET_TYPE


	#define remove_dims(X) X


	// generic dimensioned place-holder
	template<typename T, typename Dims> using Quantity = T;

#endif