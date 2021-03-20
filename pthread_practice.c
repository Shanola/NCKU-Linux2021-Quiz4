#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
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

int cnt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *child()
{
	for (int i=0; i<1000000; i++) {
	    /*int tmp = cnt;
		sleep(1);
		cnt = tmp + 1;*/
		pthread_mutex_lock(&mutex);
		cnt = cnt + 1;
		pthread_mutex_unlock(&mutex);
		//printf("cnt = %d\n", cnt);
	}
	pthread_exit(NULL);
}
int main(void)
{
	double t11 = tvgetf();
    pthread_t t1, t2;
	pthread_create(&t1, NULL, child, "NULL");
	pthread_create(&t2, NULL, child, "NULL");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
	double t22 = tvgetf();
	printf("%.6f\n", (t22 - t11) * 1000);
	return 0;
}
