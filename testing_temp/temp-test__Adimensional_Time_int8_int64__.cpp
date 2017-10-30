
        #include <iostream>
        #include "../dimensional_analysis.h"
        

        class A {};

        int main(int argc, char* argv[]) {
            std::cout << (int8<Adimensional>(16) + int64<Time>(32)) << std::endl;;std::cout << (int8<Adimensional>(32) - int64<Time>(16));;
            return 0;
        }
        