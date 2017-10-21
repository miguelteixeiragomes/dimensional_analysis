#include <iostream>
#include "dimensional_analysis.h"
#include <vector>

class A {};

void test1() {
	std::vector<int> aux = { 1, 2 };
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

	auto C = +u8;
	int t = int32<>(1);

	int32<Time> a = 5;
	int32<Time> b = a;
	int64<> c = 7;
	int64<> d = c;

	auto yo = +b8;
	std::cout << "u+: " << +a << "\n";
	std::cout << "u-: " << -a << "\n";
	std::cout << "+:  " << a + b << "\n";
	std::cout << "-:  " << a - b << "\n";
	std::cout << "*:  " << a * b << "\n";
	std::cout << "/:  " << a / b << "\n";
	std::cout << "%:  " << a % b << "\n";
	std::cout << "++: " << a++ << "\n";
	std::cout << "--: " << a-- << "\n";
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

	//system("pause");
	return 0;
}