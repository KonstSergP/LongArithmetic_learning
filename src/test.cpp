#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include "../include/longNumbers.hpp"
#include "../include/longArithmetics.hpp"


int main()
{
    LongNumber res = 0_LN;
    set_precision(res, 100);


    LongNumber x = 0.2_LN;
    set_precision(x, 100);

    for (int i = 0; i < 10; i++)
    {
        x *= x;
        set_precision(x, 100);
        std::cout << x << "\n";
    }

	return 0;
}
