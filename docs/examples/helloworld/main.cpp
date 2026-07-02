#include "test.h"

TEST_CASE( A, B ) {
    ASSERT_EQUALS( 1, 1, )
}

#include <xutest/xutest.h>

int main() {
    RUN_ALL_TEST_CASES();
    return 0;     
}