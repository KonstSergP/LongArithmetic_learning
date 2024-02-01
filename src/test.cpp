#include <iostream>
#include <stdlib.h>
#include <vector>

#include "../include/longNumbers.hpp"
#include "../include/longArithmetics.hpp"


int main()
{
    LongNumber ln1 = 7.0_LN;
    LongNumber ln2 = "7"_LN;

    std::cout << ln1 << " " << ln2 << "\n";

    LongNumber ln3 = ln1 / ln2;

    std::string ln4 = to_string(ln3);

    std::cout << ln1 << " " << ln2 <<  " " << ln3 << "\n" << ln4;

	return 0;
}
