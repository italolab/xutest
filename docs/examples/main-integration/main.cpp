#include "libmath/libmath.h"
#include "test/libmathtest.h"

#include <xutest/xutest.h>
#include <cstring>

#include <iostream>

using namespace std;

int main( int argc, char* argv[] ) {
    if ( argc == 2 ) {
        if ( strcmp( argv[ 1 ], "test" ) == 0 ) {
            RUN_ALL_TEST_CASES();
            return 0;
        }
    }

    int n;
    cout << "Informe um número para calcular o fatorial: ";
    cin >> n;

    int fat = fatorial( n );
    cout << "Fatorial de " << n << " é: " << fat << endl;

    return 0;
}