#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include "../include/longNumbers.hpp"
#include "../src/longArithmetic/longArithmetic.hpp"
#include "../src/test_system/test_system.hpp"

#define CHECK(x) if (not (x)) {return FAIL;}


bool test_ok()
{
	return OK;
}

bool test_fail()
{
	return FAIL;
}

bool test_timeout()
{
	long long int cnt = 0;
	while (true) {cnt++;}
}

bool test_exception()
{
	throw std::bad_exception();
}

bool test_error()
{
	abort();
}

bool test_testsystem()
{
	CHECK(run_test("test_ok", test_ok, 0) == OK);
	CHECK(run_test("test_fail", test_fail, 0) == FAIL);
	CHECK(run_test("test_timeout", test_timeout, 0) == TIMEOUT);
	CHECK(run_test("test_exception", test_exception, 0) == EXCEPTION);
	CHECK(run_test("test_error", test_error, 0) == ERROR);
	return OK;
}


bool test_constructors()
{
	LongNumber n1 = LongNumber(0e0);
	LongNumber n2 = -0_LN;
	CHECK(n1 == n2);

	LongNumber n3 = LongNumber(n2);
	CHECK(n2 == n3);

	LongNumber n4 = "-0.00125", n5 = "-0.00125"_LN;
	CHECK(n4 == n5);

	LongNumber n6  = -0.00125_LN, n7 = n5;
	CHECK(n6 == n7);

	return OK;
}

bool test_addition()
{
	CHECK("0"_LN + "-0"_LN == "0"_LN);
	CHECK("999.999"_LN + "0.001"_LN == "1000"_LN);
	LongNumber a = "1234567898765432";
	CHECK(a + a == "2469135797530864"_LN);
	CHECK("1000.0001"_LN + "-1000.0001"_LN == "0"_LN);

	return OK;
}

bool test_substraction()
{
	CHECK("0"_LN - "-0"_LN == "0"_LN);
	CHECK("1000"_LN - "0.001"_LN == "999.999"_LN);
	LongNumber a = "1234567898765432";
	CHECK(a - a == "0"_LN);
	CHECK("1000.0001"_LN - "-1000.0001"_LN == "2000.0002"_LN);

	return OK;
}

bool test_multyplying()
{
	CHECK("0"_LN * "-0"_LN == "0"_LN);
	CHECK("999.999"_LN * "0.001"_LN == "0.999999"_LN);
	LongNumber a = "1111111111";
	CHECK(a * a == "1234567900987654321"_LN);
	CHECK("1000"_LN * "-1000.001"_LN == "-1000001"_LN);

	return OK;
}

bool test_division()
{
	CHECK("0"_LN / "-1234567890987654"_LN == "0"_LN);
	CHECK("999.999"_LN / "0.001"_LN == "999999"_LN);
	LongNumber a = "1111111111";
	CHECK(a / a == "1"_LN);
	CHECK("9009.009"_LN / "-1001.001"_LN == "-9"_LN);

	return OK;
}


bool test_compare()
{
	CHECK(("0"_LN == "-0"_LN) && ("123456789987654321"_LN != -"123456789987654321"_LN));
	CHECK(("1000"_LN < "1000.001"_LN) && ("1000"_LN <= "1001.001"_LN));
	CHECK(("-1000"_LN > "-1000.001"_LN) && ("-1000"_LN >= "-1001.001"_LN));
	CHECK("930572458374"_LN != "6537846237.9768"_LN);
	CHECK("1000000"_LN != "1000000.0000001"_LN);

	return OK;
}

bool test_conversion()
{
	CHECK(to_string("123456789.123456789"_LN) == "123456789.123456789");
	CHECK(to_string("-123456789.123456789"_LN) == "-123456789.123456789");
	CHECK(to_string("-0"_LN) == "0");
	CHECK(to_string("-0.0000000001"_LN) == "-0.0000000001");
	return OK;
}


int main()
{	
	run_test("Testing system", test_testsystem, 1, 2000);
    run_test("Constructors", test_constructors);
    run_test("Addition",     test_addition);
    run_test("Substraction", test_substraction);
    run_test("Multyplying",  test_multyplying);
    run_test("Division",     test_division);
    run_test("Compare",      test_compare);
    run_test("Conversion to str",   test_conversion);

	return 0;
}
