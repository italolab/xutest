#include "test/cbtest.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class X {

};

TEST_CASE( test1, classes ) {
	ASSERT_EQUALS( 1, 1 );
	ASSERT_EQUALS( 2, 2 );

	ASSERT_TRUE( true );
	ASSERT_FALSE( false );

	ASSERT_NULL( nullptr );
	ASSERT_NOT_NULL( new string );

	int a1[] = { 1, 2, 3 };
	int a2[] = { 1, 2, 3 };
	int a3[] = { 1, 2, 3, 4 };

	vector<X*> v1 = { new X, new X, new X };
	vector<X*> v2 = { new X, new X, new X };
	vector<X*> v3 = { new X, new X, new X, new X };

	ASSERT_EQUALS_ARRAYS( a1, a2, 3, "abc" );
	ASSERT_NOT_EQUALS_ARRAYS( a1, a3, 3 );

    /*

	ASSERT_EQUALS_VECTORS( v1, v3, "abc" );
	ASSERT_NOT_EQUALS_VECTORS( v1, v3 );

	ASSERT_EQUALS_ARRAYS( a1, a3, 3, "Arrays diferentes." );
	ASSERT_NOT_EQUALS_ARRAYS( a1, a3, 3 );

	ASSERT_EQUALS_VECTORS( v1, v2 );
	ASSERT_NOT_EQUALS_VECTORS( v1, v3 );
    */
}

int main() {
	ADD_TEST_CASE( test1, classes );

	RUN_ALL_TEST_CASES();
}
