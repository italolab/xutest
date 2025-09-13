#include <xutest/xutest.h>

TEST_CASE( primeiroTeste, Testes ) {
    ASSERT_EQUALS( 1, 1, )

    int a = 1;
    int b = 1;
    string c = "teste";
    string d = "teste";

    ASSERT_EQUALS( a, b, )
    ASSERT_EQUALS( c, d, As strings não são iguais! )
}

int main() {
    RUN_ALL_TEST_CASES();
    return 0;
}