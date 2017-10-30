#include <iostream>
#include <limits>
//#define EXPLICIT_CONSTRUCTOR
#define SKIP_DIMENSIONAL_ANALYSIS
#include "dimensional_analysis.h"

class A { public: int val; };

void func(int a) {}
void func2(int64<Adimensional> a) {}

class B : public A { public: B() {} };

void test1() {
	std::cout << std::boolalpha;

	int32<Time> a(5);
	int32<Time> b(a);
	int64<> c(7);
	int64<> d = c;
	float32<> e(3.14f);
	float64<> f(2.7);
	
	std::cout << "Operations with library types\n";
		std::cout << "\t" << "a:   " << a << "\n";
		std::cout << "\t" << "u+:  " << +a << "\n";
		std::cout << "\t" << "u-:  " << -a << "\n";
		std::cout << "\t" << "+:   " << a + b << "\n";
		std::cout << "\t" << "-:   " << a - b << "\n";
		std::cout << "\t" << "*:   " << a * b << "\n";
		std::cout << "\t" << "/:   " << a / b << "\n";
		std::cout << "\t" << "%:   " << a % b << "\n";
		std::cout << "\t" << "s++: " << a++ << "\n";
		std::cout << "\t" << "s--: " << a-- << "\n";
		std::cout << "\t" << "p++: " << ++a << "\n";
		std::cout << "\t" << "p--: " << --a << "\n";
		std::cout << "\t" << "+=:  " << (a += b) << "\n";
		std::cout << "\t" << "-=:  " << (a -= b) << "\n";
		std::cout << "\t" << "*=:  " << (a *= c) << "\n";
		std::cout << "\t" << "/=:  " << (a /= d) << "\n";
		std::cout << "\t" << "==:  " << (a == b) << "\n";
		std::cout << "\t" << "!=:  " << (a != b) << "\n";
		std::cout << "\t" << ">:   " << (a > b) << "\n";
		std::cout << "\t" << "<:   " << (a < b) << "\n";
		std::cout << "\t" << ">=:  " << (a >= b) << "\n";
		std::cout << "\t" << "<=:  " << (a <= b) << "\n";
		std::cout << "\t" << "~:   " << (~c) << '\n';
		std::cout << "\t" << "|:   " << (c | d) << "\n";
		std::cout << "\t" << "^:   " << (c ^ d) << "\n";
		std::cout << "\t" << "&:   " << (c & d) << "\n";
		std::cout << "\t" << "<<:  " << (c << d) << "\n";
		std::cout << "\t" << ">>:  " << (c >> d) << "\n";
		std::cout << "\t" << "|=:  " << (c |= d) << "\n";
		std::cout << "\t" << "&=:  " << (c &= d) << "\n";
		std::cout << "\t" << "^=:  " << (c ^= d) << "\n";
		std::cout << "\t" << "<<=: " << (c <<= d) << "\n";
		std::cout << "\t" << ">>=: " << (c >>= d) << "\n";

	std::cout << "\nOperation with built-ins\n";
		std::cout << "\t" << "+:   " << (c + 7) << "\n";
		std::cout << "\t" << "-:   " << (7 - d) << "\n";
		std::cout << "\t" << "*:   " << (c * 7) << "\n";
		std::cout << "\t" << "/:   " << (7 / d) << "\n";
		std::cout << "\t" << "==:  " << (c == 7) << "\n";
		std::cout << "\t" << "!=:  " << (7 != c) << "\n";
		std::cout << "\t" << ">:   " << (c > 7) << "\n";
		std::cout << "\t" << "<:   " << (7 < d) << "\n";
		std::cout << "\t" << ">=:  " << (c >= 7) << "\n";
		std::cout << "\t" << "<=:  " << (7 <= d) << "\n";
		std::cout << "\t" << "|:   " << (c | 7) << "\n";
		std::cout << "\t" << "^:   " << (7 ^ d) << "\n";
		std::cout << "\t" << "&:   " << (c & 7) << "\n";
		std::cout << "\t" << "<<:  " << (7 << d) << "\n";
		std::cout << "\t" << ">>:  " << (c >> 7) << "\n";

	//std::cout << pow<7>(pow<1, 7>(a)) << '\n';
	std::cout << float64<Length>(5) + cbrt(float64<Volume>(125)) << '\n';
}


int main(int argc, char* argv[]) {
	test1();

	//system("pause");
	return 0;
}