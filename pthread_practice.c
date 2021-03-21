#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>
#include <assert.h>

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

void *child(void *v)
{
    sleep(3);
	for (int i=0; i<3; i++) {
		pthread_mutex_lock(&mutex);
		int tmp = cnt;
		cnt = tmp + 1;
		pthread_mutex_unlock(&mutex);
		printf("cnt = %d\n", cnt);
	}
	pthread_exit(v);
}
int main(void)
{
	pthread_t t1, t2;
	void *v1;
	void *v2;
	pthread_create(&t1, NULL, child, v1);
    pthread_cancel(t1);
	pthread_create(&t2, NULL, child, v2);

    int v = pthread_join(t1, &v1);
	// if (!v) assert(v);
	if (v1 == PTHREAD_CANCELED) {
	    printf("Thread1 was canceled!\n");
	} else {
	    printf("No!\n");
	}
    v = pthread_join(t2, &v2);
	// if (!v) assert(v);
	if (v2 == PTHREAD_CANCELED) {
	    printf("No! thread2 was canceled\n");
	} else {
	    printf("Ok\n");
	}
	return 0;
}
