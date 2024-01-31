#include <iostream>
#include <stdlib.h>
#include <vector>

#include "../include/longNumbers.hpp"
#include "../include/longArithmetics.hpp"


int main()
{
    LongNumber ln1 = 10.0005_LN;
    LongNumber ln2 = "0.001224355645"_LN;

    std::cout << ln1 << " " << ln2 << "\n";

    ln1--;

    std::cout << ln1 << " " << ln2 << "\n";

	return 0;
}
