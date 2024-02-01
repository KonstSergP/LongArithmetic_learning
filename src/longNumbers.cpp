#include "../include/longNumbers.hpp"
#include "../include/longArithmetics.hpp"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <sstream>


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


bool LongNumber::operator ==(LongNumber& ln)
{
    return (modules_compare(digits, ln.digits, precision, ln.precision) == 0);
}

bool LongNumber::operator !=(LongNumber& ln)
{
    return (modules_compare(digits, ln.digits, precision, ln.precision) != 0);
}

bool LongNumber::operator >(LongNumber& ln)
{
    return (modules_compare(digits, ln.digits, precision, ln.precision) == 1);
}

bool LongNumber::operator <(LongNumber& ln)
{
    return (modules_compare(digits, ln.digits, precision, ln.precision) == -1);
}

bool LongNumber::operator <=(LongNumber& ln)
{
    return (modules_compare(digits, ln.digits, precision, ln.precision) != 1);
}

bool LongNumber::operator >=(LongNumber& ln)
{
    return (modules_compare(digits, ln.digits, precision, ln.precision) != -1);
}

LongNumber& LongNumber::operator +=(LongNumber& ln)
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
            modules_sub(copy, digits, ln.precision, precision);
            swap(digits, copy);
            is_negative = ~is_negative;
        }
    }
    return *this;
}

LongNumber& LongNumber::operator -=(LongNumber& ln)
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
            is_negative = ~is_negative;
        }
    }
    return *this;
}

LongNumber& LongNumber::operator *=(LongNumber& ln)
{
    modules_mult(digits, ln.digits, precision, ln.precision);
    is_negative = not (is_negative == ln.is_negative);
    return *this;
}

LongNumber& LongNumber::operator /=(LongNumber& ln)
{
    modules_div(digits, ln.digits, precision, ln.precision);
    is_negative = not (is_negative == ln.is_negative);
    return *this;
}

LongNumber LongNumber::operator =(LongNumber& ln)
{
    LongNumber copy;
    copy.digits = ln.digits;
    copy.is_negative = ln.is_negative;
    copy.precision = ln.precision;
    return copy; 
}

LongNumber LongNumber::operator +(LongNumber& ln)
{
    LongNumber copy = *this;
    copy += ln;
    return copy; 
}

LongNumber LongNumber::operator -(LongNumber& ln)
{
    LongNumber copy = *this;
    copy -= ln;
    return copy; 
}

LongNumber LongNumber::operator *(LongNumber& ln)
{
    LongNumber copy = *this;
    copy *= ln;
    return copy;
}

LongNumber LongNumber::operator /(LongNumber& ln)
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
    copy.is_negative = ~copy.is_negative;
    return copy; 
}


std::ostream& operator <<(std::ostream& os, LongNumber ln)
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

std::string to_string(LongNumber& value)
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