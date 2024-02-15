#include "../include/longNumbers.hpp"
#include <iostream>
#include <stdlib.h>

#include <time.h>
#include <chrono>

void calc_split(int a, int b, LongNumber& Pab, LongNumber& Qab, LongNumber& Rab)
{
    LongNumber Pam = "0", Qam = "0", Ram = "0";
    LongNumber Pmb = "0", Qmb = "0", Rmb = "0";
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
        calc_split(a, m, Pam, Qam, Ram);
        calc_split(m, b, Pmb, Qmb, Rmb);
        
        Pab = Pam * Pmb;
        Qab = Qam * Qmb;
        Rab = Qmb * Ram + Pam * Rmb;
    }
}


LongNumber calculate_pi(int precision)
{
    LongNumber P1n = "0", Q1n = "0", R1n = "0";
    calc_split(1, precision / 10 + 2, P1n, Q1n, R1n);
    LongNumber rt = "10005";
    set_precision(rt, precision + 10);
    rt = square_root(rt);

    LongNumber num1 = "426880", num2 = "13591409";

    LongNumber pi = (num1 * rt * Q1n) / (num2*Q1n + R1n);
    set_precision(pi, precision);

    return pi;
}



int main(int argc, char **argv)
{
	int d;
    if (argc == 1)
    {
        std::cout << "Количество знаков: ";
        std::cin >> d;
    }
    else if (argc == 2)
    {
        d = strtol(argv[1], argv, 10);
    }

    auto begin = std::chrono::steady_clock::now(); // auto -> std::chrono:steady_clock::time_point
    clock_t t1 = clock();

    LongNumber res = calculate_pi(d);

    std::cout << res << "\n";

    auto end = std::chrono::steady_clock::now();
    clock_t t2 = clock();


    double tm = (double)(t2 - t1) / CLOCKS_PER_SEC;
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "Time: " << tm << "\n";
    std::cout << elapsed_ms.count() << " ms\n";

    return 0;
}
