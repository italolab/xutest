#include <cbtest/cbtest.h>

#include "calc/calc.h"
#include <cmath>

TEST_CASE( square_area_test, CalcTests ) {
    ASSERT_EQUALS( calc::square_area( 10 ), 100, );
    ASSERT_EQUALS( calc::square_area( -1 ), 1, );
    ASSERT_EQUALS( calc::square_area( 0 ), 0, );
    ASSERT_EQUALS( calc::square_area( 2.5 ), 6.25, );
}

TEST_CASE( rectangle_area_test, CalcTests ) {
    ASSERT_EQUALS( calc::rectangle_area( 10, 10 ), 100, );
    ASSERT_EQUALS( calc::rectangle_area( -1, 20 ), -20, );
    ASSERT_EQUALS( calc::rectangle_area( 0, 10 ), 0, );
    ASSERT_EQUALS( calc::rectangle_area( 2.5, 10 ), 25, );
}

TEST_CASE( triangle_area_test, CalcTests ) {
    ASSERT_EQUALS( calc::triangle_area( 10, 10 ), 50, );
    ASSERT_EQUALS( calc::triangle_area( -1, 20 ), -10, );
    ASSERT_EQUALS( calc::triangle_area( 0, 10 ), 0, );
    ASSERT_EQUALS( calc::triangle_area( 2.5, 10 ), 12.5, );
}

TEST_CASE( circle_area_test, CalcTests ) {
    ASSERT_EQUALS( calc::circle_area( 10 ), M_PI * 100, );
    ASSERT_EQUALS( calc::circle_area( -1 ), M_PI, );
    ASSERT_EQUALS( calc::circle_area( 0 ), 0, );
    ASSERT_EQUALS( calc::circle_area( 2.5 ), M_PI * 6.25, );
}