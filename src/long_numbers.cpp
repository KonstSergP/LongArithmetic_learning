#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int modules_compare(std::vector<char>& left, std::vector<char>& right, int prec1, int prec2)
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
        for (int i = MAX(delta_prec1, delta_prec2) - 1; i >= 0; i--)
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

void set_precision(std::vector<char>& left, int& prec1, int prec2)
{
    int delta_prec = prec2 - prec1;
    std::vector<char> new_left(left.size() + delta_prec, 0);
    if (delta_prec >= 0)
    {
        for (int i=delta_prec; i<new_left.size(); i++)
        {
            new_left[i] = left[i - delta_prec];
        } 
    }
    else
    {
        for (int i=-delta_prec; i < left.size(); i++)
        {
            new_left[i + delta_prec] = left[i];
        }
    }
    prec1 = prec2;
    swap(left, new_left);
}

void modules_summ(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2)
{
    int rt_size = right.size();
    int lt_size = left.size();

    if (prec1 < prec2)
    {
        set_precision(left, prec1, prec2);
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
        set_precision(left, prec1, prec2);
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


void modules_div(std::vector<char>& left, std::vector<char>& right, int& prec1, int& prec2)
{
    std::vector<char> inter_res;
    
    int x = prec1;
    int y = prec2;
    
    int right_zeros = 0;

    delete_first_zeros(left, 0);
    while (right[right.size()-1] == 0) {right.pop_back(); right_zeros++;}

    int lt_sz = left.size();
    int rt_sz = right.size();

    int bigger = modules_compare(left, right, 0, 0);

    set_precision(left, prec1, prec1+rt_sz);

    if (bigger >= 0)
    {
        for (int new_rt_prec = -lt_sz; new_rt_prec <= 0; new_rt_prec++)
        {
            int new_lt_prec = 0;
            inter_res.push_back(0);
            while (modules_compare(left, right, new_lt_prec, new_rt_prec) >= 0)
            {
                modules_sub(left, right, new_lt_prec, new_rt_prec);
                inter_res[inter_res.size()-1] += 1;

            }
        }
        std::reverse(inter_res.begin(), inter_res.end());

        int new_prec = inter_res.size() - (lt_sz - rt_sz) - 1;
        new_prec += x - y;

        if (new_prec < 0) {set_precision(inter_res, new_prec, 0);}
        while (new_prec > inter_res.size() - 1)
        {
            inter_res.push_back(0);
        }

        delete_first_zeros(inter_res, new_prec);

        prec1 = new_prec;
        swap(left, inter_res);

    }
    else
    {
        for (int i=0;i<rt_sz-lt_sz;i++) {inter_res.push_back(0);}

        for (int new_rt_prec = -lt_sz; new_rt_prec <= 0; new_rt_prec++)
        {
            int new_lt_prec = 0;
            inter_res.push_back(0);
            while (modules_compare(left, right, new_lt_prec, new_rt_prec) >= 0)
            {
                modules_sub(left, right, new_lt_prec, new_rt_prec);
                inter_res[inter_res.size()-1] += 1;

            }
        }
        std::reverse(inter_res.begin(), inter_res.end());

        int new_prec = inter_res.size() - 1;
        new_prec += x - y;

        if (new_prec < 0) {set_precision(inter_res, new_prec, 0);}
        while (new_prec > inter_res.size() - 1)
        {
            inter_res.push_back(0);
        }

        delete_first_zeros(inter_res, new_prec);

        prec1 = new_prec;
        swap(left, inter_res);

        for (int i=0;i<right_zeros;i++) {right.push_back(0);}

    }

}











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
                digits.push_back(literal[i] - '0');
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

    LongNumber& operator /=(LongNumber& ln)
    {
        modules_div(digits, ln.digits, precision, ln.precision);
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

    LongNumber operator /(LongNumber& ln)
    {
        LongNumber copy = *this;
        copy /= ln;
        return copy;
    }

};

std::ostream& operator <<(std::ostream& os, const LongNumber& ln)
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

    LongNumber ln1 = LongNumber("355.0000000");
    LongNumber ln2 = LongNumber("113");

    LongNumber ln3 = ln1 / ln2;

    std::cout << ln1 << " " << ln2 << " " << ln3;

	return 0;
}