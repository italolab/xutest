#include "tests.h"
#include "strutiltests.h"

TEST_CASE( abcTest, abc ) {
	ASSERT_NULL( NULL, );
	ASSERT_NULL( nullptr, );
	ASSERT_NOT_NULL( new string( "" ), );
}

#include <cbtest/cbtest.h>

int main() {
	RUN_TEST_CASES_MENU();
}