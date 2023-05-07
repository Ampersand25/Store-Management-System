#include "TestingUtils.h"

#include <cassert> // #include <assert.h>

void TestingUtils::runTestsUtilsCompareStr() const
{
	assert(utils.compareStr("abc", "") == false);
	assert(utils.compareStr("", "abc") == false);
	assert(utils.compareStr("abcde", "abc") == false);
	assert(utils.compareStr("abc", "abcde") == false);
	assert(utils.compareStr("abd", "Abc") == false);
	assert(utils.compareStr("AbC", "abD") == false);
	assert(utils.compareStr("Abc", "cbc") == false);
	assert(utils.compareStr("abC", "aDc") == false);
	assert(utils.compareStr("abcde", "abced") == false);
	assert(utils.compareStr("abcfs", "abcft") == false);

	assert(utils.compareStr("123", "124") == false);
	assert(utils.compareStr("0", "3") == false);
	assert(utils.compareStr("349.1", "349.123") == false);
	assert(utils.compareStr("./,.fsa", "gf./,.") == false);
	assert(utils.compareStr("./,.asf43207.23sf", "./,.aSF43207.23sa") == false);

	assert(utils.compareStr("", "") == true);
	assert(utils.compareStr("abc", "abc") == true);
	assert(utils.compareStr("aBc", "abc") == true);
	assert(utils.compareStr("abc", "Abc") == true);
	assert(utils.compareStr("AbC", "abc") == true);
	assert(utils.compareStr("AbC", "aBc") == true);
	assert(utils.compareStr("ABc", "aBC") == true);
	assert(utils.compareStr("ABC", "abc") == true);
	assert(utils.compareStr("abc", "ABC") == true);

	assert(utils.compareStr("123", "123") == true);
	assert(utils.compareStr("0", "0") == true);
	assert(utils.compareStr("349.123", "349.123") == true);
	assert(utils.compareStr("./,.", "./,.") == true);
	assert(utils.compareStr("./,.asf43207.23", "./,.aSF43207.23") == true);
}

void TestingUtils::runTestsUtilsIsDouble() const
{
	assert(utils.isDouble("") == false);
	assert(utils.isDouble("+") == false);
	assert(utils.isDouble("-") == false);
	assert(utils.isDouble("+-") == false);
	assert(utils.isDouble("-+") == false);
	assert(utils.isDouble("+.") == false);
	assert(utils.isDouble("-.") == false);
	assert(utils.isDouble(".+") == false);
	assert(utils.isDouble(".-") == false);
	assert(utils.isDouble("4287.") == false);
	assert(utils.isDouble(".34") == false);
	assert(utils.isDouble(".") == false);
	assert(utils.isDouble("..") == false);
	assert(utils.isDouble("4289asf324908.34") == false);
	assert(utils.isDouble("34.541754.65") == false);
	assert(utils.isDouble("4389.124.675.213") == false);
	assert(utils.isDouble("24..451") == false);
	assert(utils.isDouble("324f") == false);
	assert(utils.isDouble("a34") == false);
	assert(utils.isDouble("234/325891") == false);
	assert(utils.isDouble("34.98-") == false);
	assert(utils.isDouble("3-4.98") == false);
	assert(utils.isDouble("34.98+") == false);
	assert(utils.isDouble("34.+98") == false);

	assert(utils.isDouble("12421") == true);
	assert(utils.isDouble("45.46") == true);
	assert(utils.isDouble("3.054") == true);
	assert(utils.isDouble("231.5623") == true);
	assert(utils.isDouble("123.56") == true);
	assert(utils.isDouble("123534.5") == true);
	assert(utils.isDouble("234.0") == true);
	assert(utils.isDouble("0.234") == true);
	assert(utils.isDouble("1248.543") == true);
	assert(utils.isDouble("1320.2356") == true);
	assert(utils.isDouble("43") == true);
	assert(utils.isDouble("3.001") == true);
	assert(utils.isDouble("+43.76") == true);
	assert(utils.isDouble("+316") == true);
	assert(utils.isDouble("-0.56") == true);
	assert(utils.isDouble("-43.013") == true);
	assert(utils.isDouble("6") == true);
	assert(utils.isDouble("-9") == true);
	assert(utils.isDouble("+3") == true);
	assert(utils.isDouble("0") == true);
	assert(utils.isDouble("-0.589") == true);
	assert(utils.isDouble("+0.45") == true);
}

void TestingUtils::runTestsUtilsIsInteger() const
{
	assert(utils.isInteger("") == false);
	assert(utils.isInteger(".") == false);
	assert(utils.isInteger("+") == false);
	assert(utils.isInteger("-") == false);
	assert(utils.isInteger("++") == false);
	assert(utils.isInteger("--") == false);
	assert(utils.isInteger("+-") == false);
	assert(utils.isInteger("-+") == false);
	assert(utils.isInteger("dsg24asf") == false);
	assert(utils.isInteger("abc") == false);
	assert(utils.isInteger("48dsgoj") == false);
	assert(utils.isInteger("5698.dg31gf") == false);
	assert(utils.isInteger("6.21") == false);
	assert(utils.isInteger("+539-") == false);
	assert(utils.isInteger("-539+") == false);
	assert(utils.isInteger("-8361+48129-4") == false);
	assert(utils.isInteger("+836-1+48-129+4") == false);
	assert(utils.isInteger("+489dsg591db") == false);
	assert(utils.isInteger("-aiooji371985") == false);

	assert(utils.isInteger("35") == true);
	assert(utils.isInteger("0") == true);
	assert(utils.isInteger("+9") == true);
	assert(utils.isInteger("-24") == true);
	assert(utils.isInteger("-0") == true);
	assert(utils.isInteger("+0") == true);
	assert(utils.isInteger("-4871") == true);
	assert(utils.isInteger("+43") == true);
	assert(utils.isInteger("+913631") == true);
	assert(utils.isInteger("-8") == true);
	assert(utils.isInteger("3") == true);
	assert(utils.isInteger("8914") == true);
	assert(utils.isInteger("26") == true);
	assert(utils.isInteger("983") == true);
	assert(utils.isInteger("-581") == true);
	assert(utils.isInteger("-79") == true);
}

void TestingUtils::runTestsUtils() const
{
	runTestsUtilsCompareStr();
	runTestsUtilsIsDouble();
	runTestsUtilsIsInteger();
}