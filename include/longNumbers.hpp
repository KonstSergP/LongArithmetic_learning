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

    LongNumber(std::string literal);

    LongNumber() {}

    bool operator ==(LongNumber& ln);

    bool operator !=(LongNumber& ln);

    bool operator >(LongNumber& ln);

    bool operator <(LongNumber& ln);

    bool operator >=(LongNumber& ln);

    bool operator <=(LongNumber& ln);

    LongNumber& operator +=(LongNumber& ln);

    LongNumber& operator -=(LongNumber& ln);

    LongNumber& operator *=(LongNumber& ln);

    LongNumber& operator /=(LongNumber& ln);

    LongNumber operator =(LongNumber& ln);

    LongNumber operator +(LongNumber& ln);

    LongNumber operator -(LongNumber& ln);

    LongNumber operator *(LongNumber& ln);

    LongNumber operator /(LongNumber& ln);

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


std::ostream& operator <<(std::ostream& os, LongNumber& ln);
std::string to_string(LongNumber& value);
