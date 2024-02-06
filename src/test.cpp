#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include "../include/longNumbers.hpp"
#include "../include/longArithmetics.hpp"


void binary_split(int a, int b, LongNumber& Pab, LongNumber& Qab, LongNumber& Rab)
{
    LongNumber Pam = "0", Qam = "0", Ram = "0";
    LongNumber Pmb = "0", Qmb = "0", Rmb = "0";
    std::cout << a << " " << b << "\n";
    if (b == a + 1)
    {   
        LongNumber six = "6", five = "5", two = "2", one = "1", la = LongNumber(a);
        Pab = -(six*la - five)*(two*la - one)*(six*la - one);
        Qab = "10939058860032000"_LN * (a * a * a);
        Rab = Pab * ("545140134"_LN*a + "13591409"_LN);
    }
    else
    {
        int m = (a + b) / 2;
        binary_split(a, m, Pam, Qam, Ram);
        binary_split(m, b, Pmb, Qmb, Rmb);
        
        Pab = Pam * Pmb;
        Qab = Qam * Qmb;
        Rab = Qmb * Ram + Pam * Rmb;
    }
}


LongNumber chudnovsky(int n)
{
    LongNumber P1n = "0", Q1n = "0", R1n = "0";
    binary_split(1, n, P1n, Q1n, R1n);
    LongNumber rt = "10005";
    set_precision(rt, 500);
    rt = square_root(rt);

    LongNumber num1 = "426880", num2 = "13591409";

    return (num1 * rt * Q1n) / (num2*Q1n + R1n);
}



int main()
{
    clock_t t1 = clock();

    LongNumber res = chudnovsky(35);

    set_precision(res, 500);

    std::cout << res << "\n";

    clock_t t2 = clock();

    double tm = (double)(t2 - t1) / CLOCKS_PER_SEC;

    std::cout << tm << "\n";

	return 0;
}
