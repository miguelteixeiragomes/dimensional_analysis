
        #include <iostream>
        
        
        #include "../dimensional_analysis.h"


        class A {};

        int main(int argc, char* argv[]) {
            std::uint16_t bi_a = 7;long double bi_b = 2;auto bi_c = bi_a != bi_b;uint16<Length> lt_a(7);float128<Time> lt_b(2);auto lt_c = lt_a + lt_b;std::cout << bi_c == lt_c.value << std::endl;std::cout << std::is_same<decltype(bi_c), decltype(lt_c.value)>::result;
            return 0;
        }
        