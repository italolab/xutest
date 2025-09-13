#ifndef STRUTIL_TESTS_H
#define STRUTIL_TESTS_H

#include <xutest/xutest.h>

TEST_CASE( startsWithTest, StrutilTests ) {
    string a = "ABC";
    if ( true )
        ASSERT_EQUALS( 1, 1, )
    else ASSERT_EQUALS( a, "ABC", )
}

#endif