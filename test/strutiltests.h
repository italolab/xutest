#ifndef STRUTIL_TESTS_H
#define STRUTIL_TESTS_H

#include <test/cbtest.h>

TEST_CASE( startsWithTest, StrutilTests ) {
    string a = "ABC";
    ASSERT_EQUALS( a, "ABC", );
}

#endif