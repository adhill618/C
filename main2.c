#include <stdio.h>
#include <math.h>


double original_function(double x) {
    return sqrt(1 - sqrt(1 - x * x));
}


double stable_function(double x) {
    return fabs(x) / sqrt(1 + sqrt(1 - x * x));
}

int main() {
    double x = 1e-8;

    
    double result_original = original_function(x);
    double result_stable = stable_function(x);

    
    printf("Original function result: %.16e\n", result_original);
    printf("Stable function result:    %.16e\n", result_stable);

    return 0;
}