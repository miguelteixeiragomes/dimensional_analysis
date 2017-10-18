#include <iostream>
#include "dimensional_analysis.h"


void test1() {
	std::int8_t i8;
	std::int16_t i16;
	std::int32_t i32;
	std::int64_t i64;
	std::uint8_t u8;
	std::uint16_t u16;
	std::uint32_t u32;
	std::uint64_t u64;
	boost::float32_t f32;
	boost::float64_t f64;
	bool b8;

	auto c = i8;

	int32<Time> a = 5;
	int32<Adimensional> b = 2;

	//std::cout << (~b) << '\n';
	/*std::cout << a + b << "\n";
	std::cout << a - b << "\n";
	std::cout << a * b << "\n";
	std::cout << a / b << "\n";
	std::cout << (a == b) << "\n";
	std::cout << (a != b) << "\n";
	std::cout << (a > b) << "\n";
	std::cout << (a < b) << "\n";
	std::cout << (a >= b) << "\n";
	std::cout << (a <= b) << "\n";*/
}

/*#include <iostream>
#include <stdint.h>

//#define DEBUG
template<int lenght, int time, int mass, int charge, int temperature, int amount, int intensity> 
struct Dimensions {
	static const int64_t LENGHT = lenght;
	static const int64_t TIME = time;
	static const int64_t MASS = mass;
	static const int64_t CHARGE = charge;
	static const int64_t TEMPERATURE = temperature;
	static const int64_t AMOUNT = amount;
	static const int64_t INTENSITY = intensity;
};

typedef Dimensions<  0, 0, 0, 0, 0, 0, 0 > Adimensional;
typedef Dimensions<  1, 0, 0, 0, 0, 0, 0 > Length;
typedef Dimensions<  0, 1, 0, 0, 0, 0, 0 > Time;

#ifdef DEBUG
	template<typename Dims> class Int32 {
	private:
		int32_t m_value;

	public:
		inline Int32() : m_value(0) {}

		inline Int32(int32_t value) : m_value(value) {}

		inline int32_t value() {
			return m_value;
		}
	};

	template<typename Dims> 
	Int32<Dims> inline operator+(Int32<Dims> &lhs, Int32<Dims> &rhs) {
		return Int32<Dims>(lhs.value() + rhs.value());
	}

	template<typename Dims> inline std::ostream &operator<<(std::ostream &os, Int32<Dims> &m) {
			return os << m.value();
	}

	struct Unmatched_dimensions_between_operands;

	template<typename DimsLhs, typename DimsRhs>
	Unmatched_dimensions_between_operands inline operator+(Int32<DimsLhs> &lhs, Int32<DimsRhs> &rhs);
#else
	template<typename Dims> using Int32 = std::int32_t;
#endif

int main(int argc, char* argv[]) {
	Int32<Time> a = 2;
	Int32<Time> b = 5;

	std::cout << a + b << "\n";
	return 0;
}*/



int main(int argc, char* argv[]) {
	test1();

	system("pause");
	return 0;
}