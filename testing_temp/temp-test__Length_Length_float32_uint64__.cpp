
        #include <iostream>
        #include "../dimensional_analysis.h"
        

        class A {};

        int main(int argc, char* argv[]) {
            std::cout << (float32<Length>(16) + uint64<Length>(32)) << std::endl;;std::cout << (float32<Length>(32) - uint64<Length>(16));;
            return 0;
        }
        