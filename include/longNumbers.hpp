#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "../src/longArithmetic/longArithmetic.hpp"


struct LongNumber
{
    friend std::string to_string(const LongNumber& value);
    friend LongNumber square_root(const LongNumber& num);
    friend void set_precision(LongNumber& ln, int prec);

private:
	bool is_negative;
	std::vector<char> digits;
	int precision;

public:
    LongNumber(const LongNumber& ln);

    LongNumber(std::string literal);

    LongNumber(const char* lit);

    LongNumber(long double num);

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

// Get a square root of a number
LongNumber square_root(const LongNumber& num);
//WORK IN PROGRESS
