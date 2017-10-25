#include <iostream>
#include <limits>
#include "dimensional_analysis.h"

class A { public: int val; };

class B : public A { public: B() {} };

void test1() {
	std::cout << std::boolalpha;

	int32<Time> a = 5;
	int32<Time> b = a;
	int64<> c = 7;
	int64<> d = c;
	/*float32<> e = 3.14;
	float64<> f = 2.7;*/

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
}


int main(int argc, char* argv[]) {
	test1();

	//system("pause");
	return 0;
}