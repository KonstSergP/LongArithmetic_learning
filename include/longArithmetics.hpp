#pragma once

#include "longNumbers.hpp"
#include <vector>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))



int modules_compare(std::vector<char>& left, std::vector<char>& right, int prec1, int prec2);


void delete_first_zeros(std::vector<char>& array, int prec);


void set_precision(std::vector<char>& left, int& prec1, int prec2);


void modules_summ(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2);


void modules_sub(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2);


void modules_mult(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2);


void modules_div(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2);