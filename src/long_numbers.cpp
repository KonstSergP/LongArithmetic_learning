#include <iostream>
#include <stdlib.h>
#include <vector>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int modules_compare(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2)
{
    if (left.size()-prec1 > right.size()-prec2)
    {
        return 1;
    }
    else if (right.size()-prec2 > left.size()-prec1)
    {
        return -1;
    }
    else
    {
        int delta_prec1 = MAX(prec1-prec2, 0);
        int delta_prec2 = MAX(prec2-prec1, 0);
        for (int i = MIN(left.size(), right.size()) - 1; i >= 0; i--)
        {
            if (left[i + delta_prec1] > right[i + delta_prec2])
            {
                return 1;
            }
            else if (right[i + delta_prec2] > left[i + delta_prec1])
            {
                return -1;
            }
        }
        if (left.size() == right.size()) {return 0;}
        std::vector<char>& longer = (left.size() > right.size()) ? (left) : (right);
        for (int i = MAX(delta_prec1, delta_prec2); i >= 0; i--)
        {
            if (longer[i] != 0)
            {
                return (left.size() > right.size()) ? 1 : -1;
            }
        }
    }
    return 0;
}

void delete_first_zeros(std::vector<char>& array, int prec)
{
    while (array[array.size()-1] == 0 && array.size() > prec + 1)
    {
        array.pop_back();
    }
}

void modules_summ(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2)
{
    int rt_size = right.size();
    int lt_size = left.size();
    if (prec1 < prec2)
    {
        int delta_prec = prec2 - prec1;
        std::vector<char> new_left(left.size() + delta_prec, 0);
        for (int i=delta_prec; i<new_left.size(); i++)
        {
            new_left[i] = left[i - delta_prec];
        }
        prec1 = prec2;

        swap(left, new_left);

    }
    if (left.capacity() - prec1 <= rt_size - prec2)
    {
        left.resize(prec1 + (rt_size-  prec2) + 1);
    }
    lt_size = left.size();

    for (int i = 0; i < rt_size; i++)
    {
        left[i + prec1 - prec2] += right[i];
    }


    for (int i = 0; i < lt_size; i++)
    {
        if (left[i] > 9 && i == lt_size - 1)
        {
            left.push_back(left[i] / 10);
        }
        else
        {
            left[i + 1] += left[i] / 10;
        }
        left[i] %= 10;
    }

    delete_first_zeros(left, prec1);
}


void modules_sub(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2)
{
    int rt_size = right.size();
    int lt_size = left.size();
    if (prec1 < prec2)
    {
        int delta_prec = prec2 - prec1;
        std::vector<char> new_left(left.size() + delta_prec, 0);
        for (int i=delta_prec; i<new_left.size(); i++)
        {
            new_left[i] = left[i - delta_prec];
        }
        prec1 = prec2;

        swap(left, new_left);

    }
    lt_size = left.size();

    for (int i = 0; i < rt_size; i++)
    {
        left[i + prec1 - prec2] -= right[i];
    }
    for (int i = 0; i < lt_size; i++)
    {
        if (left[i] < 0)
        {
            left[i] += 10;
            left[i + 1] -= 1;
        }
    }

    delete_first_zeros(left, prec1);
}


void modules_mult(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2)
{
    int left_sz = left.size();
    int right_sz = right.size();
    int max_sz = left_sz+right_sz;

    std::vector<int> res(max_sz, 0);

    for (int i = 0; i < left_sz; i++)
    {
        for (int j = 0; j < right_sz; j++)
        {
            res[i + j] += left[i] * right[j];
        }
    }

    for (int i = 0; i < (max_sz); i++)
    {
        res[i + 1] += (res[i] / 10);
        res[i] %= 10;
    }

    left.resize(max_sz);
    for (int i = 0; i < max_sz; i++)
    {
        left[i] = static_cast<char>(res[i]);
    }
    
    prec1 += prec2;

    delete_first_zeros(left, prec1);
}


/*

void modules_div(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2)
{
    int max_len = MAX(left_len - right_len + 1, 1);
    char* inter_res = calloc(max_len, sizeof(char));
    char* left_copy = malloc(left_len * sizeof(char));
    CHECK_CONTRACT(inter_res != NULL, "Not enough memory\n");
    CHECK_CONTRACT(left_copy != NULL, "Not enough memory\n");
    memccpy(left_copy, left, '?', left_len);

    int left_copy_len = right_len;

    for (int shift = left_len - right_len; shift >= 0; shift--)
    {
        while (left_copy[shift + left_copy_len - 1] == 0 && left_copy_len > 0)
        {
            left_copy_len--;
        }
        while (arrays_compare(left_copy + shift, right, left_copy_len, right_len) >= 0)
        {
            modules_sub(left_copy + shift, left_copy + shift, right, left_copy_len, right_len);
            inter_res[shift] += 1;
            while (left_copy[shift + left_copy_len - 1] == 0 && left_copy_len > 0)
            {
                left_copy_len--;
            }
        }
        left_copy_len++;
    }

    for (int i = 0; i < max_len; i++)
    {
        result[i] = inter_res[i];
    }
    free(inter_res);
    free(left_copy);
}


*/






















struct LongNumber
{
	bool is_negative;
	std::vector<char> digits;
	int precision;

    LongNumber(std::string literal)
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
                digits.push_back(literal[i] - '1' + 1);
            }
        }
    }

    LongNumber() {}

    bool operator ==(LongNumber& ln)
    {
        return (modules_compare(digits, ln.digits, precision, ln.precision) == 0);
    }

    bool operator !=(LongNumber& ln)
    {
        return (modules_compare(digits, ln.digits, precision, ln.precision) != 0);
    }

    bool operator >(LongNumber& ln)
    {
        return (modules_compare(digits, ln.digits, precision, ln.precision) == 1);
    }

    bool operator <(LongNumber& ln)
    {
        return (modules_compare(digits, ln.digits, precision, ln.precision) == -1);
    }

    LongNumber& operator +=(LongNumber& ln)
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

    LongNumber& operator -=(LongNumber& ln)
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

    LongNumber& operator *=(LongNumber& ln)
    {
        modules_mult(digits, ln.digits, precision, ln.precision);
        is_negative = not (is_negative == ln.is_negative);
        return *this;
    }

    LongNumber operator =(LongNumber& ln)
    {
        LongNumber copy;
        copy.digits = ln.digits;
        copy.is_negative = ln.is_negative;
        copy.precision = ln.precision;
        return copy; 
    }

    LongNumber operator +(LongNumber& ln)
    {
        LongNumber copy = *this;
        copy += ln;
        return copy; 
    }

    LongNumber operator -(LongNumber& ln)
    {
        LongNumber copy = *this;
        copy -= ln;
        return copy; 
    }

    LongNumber operator *(LongNumber& ln)
    {
        LongNumber copy = *this;
        copy *= ln;
        return copy;
    }

};

std::ostream& operator<<(std::ostream& os, const LongNumber& ln)
{
    if (ln.is_negative)
    {
        os << "-";
    }
    for (int i=ln.digits.size() - 1; i>=0; i--)
    {
        os << static_cast<int>(ln.digits[i]);
        if (ln.precision && i == ln.precision) {std::cout << ".";}
    }
    return os;
}



int main()
{

    LongNumber ln1 = LongNumber("1.4");
    LongNumber ln2 = LongNumber("1.4");


    LongNumber ln3 = ln1 * ln2;

    std::cout << ln1 << "\n" << ln2 << "\n" << ln3;
	return 0;
}