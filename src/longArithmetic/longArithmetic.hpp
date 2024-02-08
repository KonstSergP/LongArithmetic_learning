#pragma once

#include <vector>
#include "../../include/longNumbers.hpp"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))


// True if number equals zero, False in other cases
bool is_zero(const std::vector<char>& array);

// Delete leading zeros from integer part, except last (0,...)
void delete_first_zeros(std::vector<char>& array, int prec);

// Change the precision of number prec2 > prec1: add zeros, prec1 >= prec2: remove extra digits
void set_precision(std::vector<char>& left, int& prec1, int prec2);

// 1 - bigger, 0 - equal, -1 - smaller
int modules_compare(const std::vector<char>& left, const std::vector<char>& right, const int prec1, const int prec2);

// Adding right to left
void modules_summ  (std::vector<char>& left, const std::vector<char>& right, int& prec1, const int& prec2);

// Substract right from left
void modules_sub   (std::vector<char>& left, const std::vector<char>& right, int& prec1, const int& prec2);

// Multyply left by right
void modules_mult  (std::vector<char>& left, const std::vector<char>& right, int& prec1, const int& prec2);

// Divide left by right
void modules_div   (std::vector<char>& left, const std::vector<char>& right, int& prec1, const int& prec2);
// WORK IN PROGRESS
// 1)Presicion of result
// 2)Less code