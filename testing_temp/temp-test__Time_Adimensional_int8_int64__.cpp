
        #include <iostream>
        #include "../dimensional_analysis.h"
        

        class A {};

        int main(int argc, char* argv[]) {
            std::cout << (int8<Time>(16) + int64<Adimensional>(32)) << std::endl;;std::cout << (int8<Time>(32) - int64<Adimensional>(16));;
            return 0;
        }
        