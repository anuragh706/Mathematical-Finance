#include "ExoticOption.h"

double Phi(double x)
{
	const double SQRT_TWO = 1.4142135623730950488016887242097;
	return 1.0 - 0.5 * erfc(x / SQRT_TWO);
}

int factorial(int n) {
	if (n == 1 || n == 0) return 1;

	int fact=1;
	while (n > 1) {
		
		fact *= n;
		n--;
	}
	
	return fact;
}