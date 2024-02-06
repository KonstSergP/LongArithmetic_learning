#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>


struct LongNumber
{
	bool is_negative;
	std::vector<char> digits;
	int precision;

    LongNumber(const LongNumber& ln);

    LongNumber(std::string literal);

    LongNumber(const char* lit);

    LongNumber(long long int num);

    LongNumber() {}

    bool operator ==(const LongNumber& ln) const;

    bool operator !=(const LongNumber& ln) const;

    bool operator >(const LongNumber& ln) const;

    bool operator <(const LongNumber& ln) const;

    bool operator >=(const LongNumber& ln) const;

    bool operator <=(const LongNumber& ln) const;

    LongNumber& operator +=(const LongNumber& ln);

    LongNumber& operator -=(const LongNumber& ln);

    LongNumber& operator *=(const LongNumber& ln);

    LongNumber& operator /=(const LongNumber& ln);

    LongNumber& operator =(const LongNumber& ln);

    LongNumber operator +(const LongNumber& ln) const;

    LongNumber operator -(const LongNumber& ln) const;

    LongNumber operator *(const LongNumber& ln) const;

    LongNumber operator /(const LongNumber& ln) const;

    LongNumber operator +();

    LongNumber operator -();

    LongNumber& operator++();       // Prefix 
    LongNumber  operator++(int);    // Postfix

    LongNumber& operator--();       // Prefix 
    LongNumber  operator--(int);    // Postfix

};

LongNumber operator ""_LN(long double num);
LongNumber operator ""_LN(unsigned long long int num);
LongNumber operator ""_LN(const char* lit, size_t);


std::ostream& operator <<(std::ostream& os, const LongNumber& ln);
std::string to_string(const LongNumber& value);

LongNumber square_root(const LongNumber& num);
