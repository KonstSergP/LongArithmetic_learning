#pragma once

#include <vector>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

bool is_zero(std::vector<char>& array);

void delete_first_zeros(std::vector<char>& array, int prec);


void set_precision(std::vector<char>& left, int& prec1, int prec2);
void set_precision(LongNumber& ln, int prec);


int modules_compare(std::vector<char>& left, std::vector<char>& right, int  prec1, int  prec2);


void modules_summ  (std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2);


void modules_sub   (std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2);


void modules_mult  (std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2);


// WORK IN PROGRESS
// 1)Division by itself
// 2)Presicion of result
// 3)Less code
void modules_div   (std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2);
// WORK IN PROGRESS