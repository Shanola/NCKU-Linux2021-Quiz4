#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double tvgetf()
{
    struct timespec ts;
    double sec;

    clock_gettime(CLOCK_REALTIME, &ts);
    sec = ts.tv_nsec;
    sec /= 1e9;
    sec += ts.tv_sec;

    return sec;
}

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
    FILE *fp = fopen("1.txt", "w");
    if (argc != 2) {
        printf("You should input a number >= 1000\n");
		return EXIT_FAILURE;
	}
	int n = strtol(argv[1], NULL, 10);
	printf("Press enter to start...\n");
	scanf("%d");
	for (int i=1000; i<=n; i++) {
	    double t1 = tvgetf();
		compute_pi_leibniz(i);
		double t2 = tvgetf();
		fprintf(fp, "%d %.6f\n", i, (t2 - t1) * 1000); // msec
	}
    // printf("%f\n", compute_pi_leibniz(n));
	fclose(fp);
	return EXIT_SUCCESS;
}
