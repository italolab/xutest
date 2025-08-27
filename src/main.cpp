#include "test/cbtest.h"

TEST_CASE( test1, classes ) {
	ASSERT_EQUAL( 1, 2 );
	ASSERT_EQUAL( 1, 1 );
}

int main() {
	ADD_TEST_CASE( test1, classes );

	RUN_ALL_TEST_CASES();
}
