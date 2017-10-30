
        #include <iostream>
        #include "../dimensional_analysis.h"
        

        class A {};

        int main(int argc, char* argv[]) {
            std::cout << (uint32<Time>(16) + float32<Length>(32)) << std::endl;;std::cout << (uint32<Time>(32) - float32<Length>(16));;
            return 0;
        }
        