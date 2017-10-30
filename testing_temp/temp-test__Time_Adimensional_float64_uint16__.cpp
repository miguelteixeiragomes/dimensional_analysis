
        #include <iostream>
        #include "../dimensional_analysis.h"
        

        class A {};

        int main(int argc, char* argv[]) {
            std::cout << (float64<Time>(16) + uint16<Adimensional>(32)) << std::endl;;std::cout << (float64<Time>(32) - uint16<Adimensional>(16));;
            return 0;
        }
        