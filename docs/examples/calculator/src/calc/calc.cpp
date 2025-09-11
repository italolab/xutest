
#include "calc.h"

#include <cmath>

namespace calc {
    
    double square_area( double side ) {
        return side * side;
    }

    double rectangle_area( double base, double height ) {
        return base * height;
    }

    double triangle_area( double base, double height ) {
        return ( base * height ) / 2.0f;
    }

    double circle_area( double radius ) {
        return M_PI * pow( radius, 2.0f );
    }

}