#ifndef TEST_H
#define TEST_H

#include <xutest/xutest.h>

TEST_CASE( helloWorldTest, HelloWorldTests ) {
    ASSERT_EQUALS( 1, 1, )
}

#endif