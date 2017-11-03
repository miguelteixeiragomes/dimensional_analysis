#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <complex>
//#define EXPLICIT_CONSTRUCTOR
//#define SKIP_DIMENSIONAL_ANALYSIS
#include "dimensional_analysis.h"


class CLASS {};
void adim_func(long long x) {}
void time_func(int64<Time> x) {}


void test1() {
	std::cout << std::boolalpha;

	int32<Time> a(5);
	int32<Time> b(6);
	int64<> c(7);
	int64<> d(8);
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
		std::cout << a << ", " << b << '\n';
		std::cout << "\t" << "+=:  " << (a += b) << "\n";
		std::cout << a << ", " << b << '\n';
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
		std::cout << c << ", " << d << '\n';
		std::cout << "\t" << "|=:  " << (c |= d) << "\n";
		std::cout << c << ", " << d << '\n';
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
		std::cout << "\t" << ">>:  " << (c >> 7) << "\n\n";

	std::cout << pow<7>(pow<1, 7>(a)) << '\n';
	std::cout << float64<Length>(5) + sqrt(float64<Area>(25)) << '\n';
	std::cout << float64<Length>(5) + cbrt(float64<Volume>(125)) << '\n';
	adim_func(c);
	time_func(a);
	float64<Velocity> lightspeed = 1.0 / sqrt(float64<Permittivity>(8.85418781762039e-12)*float64<Permeability>(1.256637061435917e-6));
	std::cout.precision(15);
	std::cout << lightspeed << '\n';

	Quantity<std::complex<double>, Time> comp1(1, 2);
	Quantity<std::complex<double>, Time> comp2(1, 2);
	std::complex<double> comp3;
	(comp1 + comp2) + comp3;
}


int main(int argc, char* argv[]) {
	test1();

	return 0;
}