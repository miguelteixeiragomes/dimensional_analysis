
        #include <iostream>
        #include "../dimensional_analysis.h"
        

        class A {};

        int main(int argc, char* argv[]) {
            std::cout << (float128<Adimensional>(16) + float64<Adimensional>(32)) << std::endl;;std::cout << (float128<Adimensional>(32) - float64<Adimensional>(16));;
            return 0;
        }
        