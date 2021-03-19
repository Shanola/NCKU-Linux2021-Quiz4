#include <stdio.h>
#include <stdlib.h>
double compute_pi_leibniz(size_t N)
{
    double val = 0.0;
	for (size_t i=0; i<N; i++) {
	    double tmp = (i & 1) ? (-1):(1);
	    val += tmp / (2 * i + 1);
	}
	return val * 4.0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("You should input a number\n");
		return EXIT_FAILURE;
	}
	int n = strtol(argv[1], NULL, 10);
	printf("n = %d\n", n);
    printf("%f\n", compute_pi_leibniz(n));
	return EXIT_SUCCESS;
}
