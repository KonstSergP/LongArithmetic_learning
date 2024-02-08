#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include "../include/longNumbers.hpp"
#include "longArithmetic/longArithmetic.hpp"



int main()
{
    clock_t t1 = clock();

    LongNumber res = calculate_pi(100);

    std::cout << res << "\n";

    clock_t t2 = clock();

    double tm = (double)(t2 - t1) / CLOCKS_PER_SEC;

    std::cout << tm << "\n";


	return 0;
}
