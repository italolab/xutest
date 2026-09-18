#include <xutest/xutest.h>

#include "../libmath/libmath.h"

TEST_CASE( fatorialTest, LibMathTests ) {
    int f0 = fatorial( 0 );
    int f1 = fatorial( 1 );
    int f2 = fatorial( 2 );
    int f3 = fatorial( 3 );
    int f4 = fatorial( 4 );
    int f5 = fatorial( 5 );
    ASSERT_EQUALS( f0, 1, );
    ASSERT_EQUALS( f1, 1, );
    ASSERT_EQUALS( f2, 2, );
    ASSERT_EQUALS( f3, 6, );
    ASSERT_EQUALS( f4, 24, );
    ASSERT_EQUALS( f5, 120, );
}