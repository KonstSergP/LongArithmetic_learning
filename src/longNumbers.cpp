#include "../include/longNumbers.hpp"
#include "longArithmetic/longArithmetic.hpp"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <sstream>


LongNumber::LongNumber(const LongNumber& ln)
{
    digits = ln.digits;
    is_negative = ln.is_negative;
    precision = ln.precision;
}

LongNumber::LongNumber(std::string literal)
{
    is_negative = false;
    precision = 0;
        int sz = literal.size();
        for (int i=sz-1;i >= 0; i--)
    {
        if (literal[i] == '.')
        {
            precision = sz - 1 - i;
        }
        else if (literal[i] == '-')
        {
            is_negative = true;
        }
        else
        {
            digits.push_back(literal[i] - '0');
        }
    }
}

LongNumber::LongNumber(const char* lit): LongNumber(std::string(lit)) {}

LongNumber::LongNumber(long long int num): LongNumber(std::__cxx11::to_string(num)) {}


bool LongNumber::operator ==(const LongNumber& ln) const
{
    return (modules_compare(digits, ln.digits, precision, ln.precision) == 0) && (is_negative == ln.is_negative);
}

bool LongNumber::operator !=(const LongNumber& ln) const
{
    return (modules_compare(digits, ln.digits, precision, ln.precision) != 0) || (is_negative != ln.is_negative);
}

bool LongNumber::operator >(const LongNumber& ln) const
{   
    if (is_negative != ln.is_negative) {return not is_negative;}
    return (modules_compare(digits, ln.digits, precision, ln.precision) == 1) ^ is_negative;
}

bool LongNumber::operator <(const LongNumber& ln) const
{
    if (is_negative != ln.is_negative) {return is_negative;}
    return (modules_compare(digits, ln.digits, precision, ln.precision) == -1) ^ is_negative;
}

bool LongNumber::operator <=(const LongNumber& ln) const
{
    if (is_negative != ln.is_negative) {return is_negative;}
    int res = modules_compare(digits, ln.digits, precision, ln.precision);
    if (is_negative) {return res != -1;}
    return (res != 1);
}

bool LongNumber::operator >=(const LongNumber& ln) const
{
    if (is_negative != ln.is_negative) {return not is_negative;}
    int res = modules_compare(digits, ln.digits, precision, ln.precision);
    if (is_negative) {return res != 1;}
    return (res != -1);
}

LongNumber& LongNumber::operator +=(const LongNumber& ln)
{
    if (is_negative == ln.is_negative)
    {
        modules_summ(digits, ln.digits, precision, ln.precision);
    }
    else
    {
        int cmp = modules_compare(digits, ln.digits, precision, ln.precision);
        if (cmp != -1)
        {
            modules_sub(digits, ln.digits, precision, ln.precision);
        }
        else
        {
            std::vector<char> copy = ln.digits;
            int prec_copy = ln.precision;
            modules_sub(copy, digits, prec_copy, precision);
            swap(digits, copy);
            precision = prec_copy;
            is_negative = not is_negative;
        }
    }
    return *this;
}

LongNumber& LongNumber::operator -=(const LongNumber& ln)
{
    if (is_negative != ln.is_negative)
    {
        modules_summ(digits, ln.digits, precision, ln.precision);
    }
    else
    {
        int cmp = modules_compare(digits, ln.digits, precision, ln.precision);
        if (cmp != -1)
        {
            modules_sub(digits, ln.digits, precision, ln.precision);
        }
        else
        {
            std::vector<char> copy = ln.digits;
            int prec_copy = ln.precision;
            modules_sub(copy, digits, prec_copy, precision);
            swap(digits, copy);
            std::swap(prec_copy, precision);
            is_negative = not is_negative;
        }
    }
    return *this;
}

LongNumber& LongNumber::operator *=(const LongNumber& ln)
{
    modules_mult(digits, ln.digits, precision, ln.precision);
    is_negative = (is_negative != ln.is_negative);
    return *this;
}

LongNumber& LongNumber::operator /=(const LongNumber& ln)
{
    modules_div(digits, ln.digits, precision, ln.precision);
    is_negative = (is_negative != ln.is_negative);
    return *this;
}

LongNumber& LongNumber::operator =(const LongNumber& ln)
{
    digits = ln.digits;
    is_negative = ln.is_negative;
    precision = ln.precision;
    return *this; 
}

LongNumber LongNumber::operator +(const LongNumber& ln) const
{
    LongNumber copy = *this;
    copy += ln;
    return copy;
}

LongNumber LongNumber::operator -(const LongNumber& ln) const
{
    LongNumber copy = *this;
    copy -= ln;
    return copy; 
}

LongNumber LongNumber::operator *(const LongNumber& ln) const
{
    LongNumber copy = *this;
    copy *= ln;
    return copy;
}

LongNumber LongNumber::operator /(const LongNumber& ln) const
{
    LongNumber copy = *this;
    copy /= ln;
    return copy;
}

LongNumber LongNumber::operator +()
{
    LongNumber copy = *this;
    return copy; 
}

LongNumber LongNumber::operator -()
{
    LongNumber copy = *this;
    copy.is_negative = not copy.is_negative;
    return copy; 
}


std::ostream& operator <<(std::ostream& os, const LongNumber& ln)
{
    os << to_string(ln);
    return os;
}


LongNumber operator ""_LN(long double num)
{
    std::string str = std::__cxx11::to_string(num); 
    LongNumber nm = LongNumber(str);
    return nm;
}

LongNumber operator ""_LN(unsigned long long int num)
{
    std::string str = std::__cxx11::to_string(num); 
    LongNumber nm = LongNumber(str);
    return nm;
}

LongNumber operator ""_LN(const char* lit, size_t)
{
    std::string str = lit;
    return LongNumber(str);
}

LongNumber& LongNumber::operator++()       // Prefix 
{
    LongNumber nm = 1.0_LN;
    *this += nm;
    return *this;
}


LongNumber  LongNumber::operator++(int)    // Postfix
{
    LongNumber temp = *this;
    ++*this;
    return temp;
}

LongNumber& LongNumber::operator--()       // Prefix 
{
    LongNumber nm = 1.0_LN;
    *this -= nm;
    return *this;
}


LongNumber  LongNumber::operator--(int)    // Postfix
{
    LongNumber temp = *this;
    --*this;
    return temp;
}

std::string to_string(const LongNumber& value)
{
    std::ostringstream os;
    if (value.is_negative)
    {
        os << "-";
    }
    for (int i=value.digits.size() - 1; i>=0; i--)
    {
        os << static_cast<int>(value.digits[i]);
        if (value.precision && i == value.precision) {os << ".";}
    }
    return os.str();
}

//WORK IN PROGRESS
LongNumber square_root(const LongNumber& num)
{
    int prec = num.precision;
    LongNumber number = num;

    set_precision(number, prec + 10);

    LongNumber two = "2";

    LongNumber x = number / two;

    LongNumber s_div_x = x, next_x = x;

    int cnt = 0;
    int lng = number.digits.size() + 20;
    while (lng) { cnt++; lng /= 2;}
    cnt *= 4;

    for (int i = 0; i < cnt; i++)
    {
        s_div_x = number / x;

        next_x = (x + s_div_x) / two;

        x = next_x;

        set_precision(x, prec + 10);

    }

    return x;
}


void set_precision(LongNumber& ln, int prec)
{
    set_precision(ln.digits, ln.precision, prec);
}


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