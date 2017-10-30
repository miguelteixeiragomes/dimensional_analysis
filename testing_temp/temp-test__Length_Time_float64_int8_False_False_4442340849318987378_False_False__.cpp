
        #include <iostream>
        
        
        #include "../dimensional_analysis.h"


        class A {};

        int main(int argc, char* argv[]) {
            double bi_a = 7;std::int8_t bi_b = 2;auto bi_c = bi_a <<= bi_b;float64<Length> lt_a(7);int8<Time> lt_b(2);auto lt_c = lt_a + lt_b;std::cout << bi_c == lt_c.value << std::endl;std::cout << std::is_same<decltype(bi_c), decltype(lt_c.value)>::result;
            return 0;
        }
        