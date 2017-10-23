#include <iostream>
#include "dimensional_analysis.h"

class A {};

void test1() {
	std::cout << std::boolalpha;

	std::int8_t i8 = 1;
	std::int16_t i16 = 1;
	std::int32_t i32 = 1;
	std::int64_t i64 = 1;
	std::uint8_t u8 = 1;
	std::uint16_t u16 = 1;
	std::uint32_t u32 = 1;
	std::uint64_t u64 = 1;
	float f32 = 1;
	double f64 = 1;
	bool b8 = 1;
	std::cout << b8 << '\n';
	/*#define OP -
	std::cout << typeid(decltype(OP NumericValue<std::int8_t>::value)).name() << '\n';
	std::cout << typeid(decltype(OP NumericValue<std::int16_t>::value)).name() << '\n';
	std::cout << typeid(decltype(OP NumericValue<std::int32_t>::value)).name() << '\n';
	std::cout << typeid(decltype(OP NumericValue<std::int64_t>::value)).name() << "\n\n";

	std::cout << typeid(decltype(OP NumericValue<std::uint8_t>::value)).name() << '\n';
	std::cout << typeid(decltype(OP NumericValue<std::uint16_t>::value)).name() << '\n';
	std::cout << typeid(decltype(OP NumericValue<std::uint32_t>::value)).name() << '\n';
	std::cout << typeid(decltype(OP NumericValue<std::uint64_t>::value)).name() << "\n\n";

	std::cout << typeid(decltype(OP NumericValue<float>::value)).name() << '\n';
	std::cout << typeid(decltype(OP NumericValue<double>::value)).name() << "\n\n\n";

	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<std::int8_t>::value)) << '\n';
	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<std::int16_t>::value)) << '\n';
	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<std::int32_t>::value)) << '\n';
	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<std::int64_t>::value)) << "\n\n";

	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<std::uint8_t>::value)) << '\n';
	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<std::uint16_t>::value)) << '\n';
	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<std::uint32_t>::value)) << '\n';
	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<std::uint64_t>::value)) << "\n\n";

	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<float>::value)) << '\n';
	std::cout << IS_NUMERIC_TYPE(decltype(OP NumericValue<double>::value)) << "\n\n";*/

	//int t = int32<>(1);

	int32<Time> a = 5;
	int32<Time> b = a;
	int32<> e = 2;
	int64<> c = 7;
	int64<> d = c;
	/*
	auto yo = +b8;
	std::cout << "u+:  " << +a << "\n";
	std::cout << "u-:  " << -a << "\n";
	std::cout << "+:   " << a + b << "\n";
	std::cout << "-:   " << a - b << "\n";
	std::cout << "*:   " << a * b << "\n";
	std::cout << "/:   " << a / b << "\n";
	std::cout << "%:   " << a % b << "\n";
	std::cout << "++:  " << a++ << "\n";
	std::cout << "--:  " << a-- << "\n";
	std::cout << "+=:  " << (a += b) << "\n";
	std::cout << "-=:  " << (a -= b) << "\n";
	std::cout << "*=:  " << (a *= e) << "\n";
	std::cout << "/=:  " << (a /= e) << "\n";
	std::cout << "==:  " << (a == b) << "\n";
	std::cout << "!=:  " << (a != b) << "\n";
	std::cout << ">:   " << (a > b) << "\n";
	std::cout << "<:   " << (a < b) << "\n";
	std::cout << ">=:  " << (a >= b) << "\n";
	std::cout << "<=:  " << (a <= b) << "\n";
	std::cout << "~:   " << (~c) << '\n';
	std::cout << "|:   " << (c | d) << "\n";
	std::cout << "&:   " << (c & d) << "\n";
	std::cout << "^:   " << (c ^ d) << "\n";
	std::cout << "<<:  " << (c << d) << "\n";
	std::cout << ">>:  " << (c >> d) << "\n";
	std::cout << "|=:  " << (c |= d) << "\n";
	std::cout << "&=:  " << (c &= d) << "\n";
	std::cout << "^=:  " << (c ^= d) << "\n";
	std::cout << "<<=: " << (c <<= d) << "\n";
	std::cout << ">>=: " << (c >>= d) << "\n";*/
}


int main(int argc, char* argv[]) {
	test1();

	//system("pause");
	return 0;
}