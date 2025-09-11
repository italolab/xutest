
#include "calc/calc.h"

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    cout << "  Calculadora de areas" << endl;
    cout << endl;
    cout << "  (1) Area do quadrado" << endl;
    cout << "  (2) Area do retangulo" << endl;
    cout << "  (3) Area do triangulo" << endl;
    cout << "  (4) Area do circulo" << endl;
    cout << endl;

    int op;
    cout << "Informe a opcao >> " << std::flush;
    cin >> op;

    cout << endl;

    double side;
    double base;
    double height;
    double radius;
    double area;

    cout << std::fixed << std::setprecision( 4 );

    switch ( op ) {
        case 1:
            cout << "Informe o lado do quadrado: " << std::flush;
            cin >> side;
            
            area = calc::square_area( side );

            cout << endl;
            cout << "A area do quadrado eh: " << area << endl;
            break;
        case 2:
            cout << "Informe a base do retangulo: " << std::flush;
            cin >> base;
            cout << "Informe a altura do retangulo: " << std::flush;
            cin >> height;

            area = calc::rectangle_area( base, height );

            cout << endl;
            cout << "A area do retangulo eh: " << area << endl;
            break;
        case 3:
            cout << "Informe a base do triangulo: " << std::flush;
            cin >> base;
            cout << "Informe a altura do triangulo: " << std::flush;
            cin >> height;

            area = calc::triangle_area( base, height );

            cout << endl;
            cout << "A area do triangulo eh: " << area << endl;
            break;
        case 4:
            cout << "Informe o raio do circulo: " << std::flush;
            cin >> radius;
            
            area = calc::circle_area( radius );

            cout << endl;
            cout << "A area do circulo eh: " << area << endl;
            break;
        default:
            cout << "Voce informou uma opcao invalida." << endl;
    }

    cout << endl;
    cout << "Fim do calculo de area..." << endl;
}