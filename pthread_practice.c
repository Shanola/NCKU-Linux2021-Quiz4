#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
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
sem_t semaphore;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *child()
{
	for (int i=0; i<3; i++) {
	    sem_wait(&semaphore);
		pthread_mutex_lock(&mutex);
		int tmp = cnt;
		cnt = tmp + 1;
		pthread_mutex_unlock(&mutex);
		//cnt = cnt + 1;
		printf("cnt = %d\n", cnt);
	}
	pthread_exit(NULL);
}
int main(void)
{
	// double t11 = tvgetf();
    sem_init(&semaphore, 0, 0);
	pthread_t t1, t2;
	pthread_create(&t1, NULL, child, "NULL");
	pthread_create(&t2, NULL, child, "NULL");

	for(int i=0; i<6; i++) {
	    sem_post(&semaphore);
	}
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
	// double t22 = tvgetf();
	// printf("%.6f\n", (t22 - t11) * 1000);
	return 0;
}
