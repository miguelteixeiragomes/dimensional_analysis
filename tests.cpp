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
	float f32;
	double f64;
	bool b8;

	//auto c = ~i8;

	int32<Time> a = 5;
	int32<Time> b = 2;
	int64<> c = 7;
	int64<> d = 11;

	std::cout << "+:  " << a + b << "\n";
	std::cout << "-:  " << a - b << "\n";
	std::cout << "*:  " << a * b << "\n";
	std::cout << "/:  " << a / b << "\n";
	std::cout << "%:  " << a % b << "\n";
	std::cout << "==: " << (a == b) << "\n";
	std::cout << "!=: " << (a != b) << "\n";
	std::cout << ">:  " << (a > b) << "\n";
	std::cout << "<:  " << (a < b) << "\n";
	std::cout << ">=: " << (a >= b) << "\n";
	std::cout << "<=: " << (a <= b) << "\n";
	std::cout << "~:  " << (~c) << '\n';
	std::cout << "|:  " << (c | d) << "\n";
	std::cout << "&:  " << (c & d) << "\n";
	std::cout << "^:  " << (c ^ d) << "\n";
	std::cout << "<<: " << (c << d) << "\n";
	std::cout << ">>: " << (c >> d) << "\n";
}


int main(int argc, char* argv[]) {
	test1();

	system("pause");
	return 0;
}