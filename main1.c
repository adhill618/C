#include <stdio.h>
#include <math.h>

int main() {
    long double a = 1.0;
    long double b = 1e8;
    long double c = 1.0;
    long double disc = (b + 2.0) * (b - 2.0);

    long double x1 = (2 * c)/(-b - sqrt(disc));
    long double x2 = c/x1;
    printf("%20.20Lf  and %20.20Lf\n", x1, x2);


}