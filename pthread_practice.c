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

void *child(void *v)
{
    int s = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	if (s != 0) assert(s == 0);
	printf("thread_func(): Thread start, cancellation disabled\n");
	sleep(3);
	printf("thread_func(): About to enable cancellation\n");
	s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	if (s != 0) assert(s == 0);
	sleep(1000); /* Should get canceled while we sleep */
	/* Should never get here */
	printf("therad not canceled!\n");
	pthread_exit(v);
}
int main(void)
{
	pthread_t t1;
	void *v1;
	pthread_create(&t1, NULL, child, v1);
    sleep(5); /* Give thread a chance to get started */
	pthread_cancel(t1);

    int v = pthread_join(t1, &v1);
	if (v != 0) assert(v==0);
	if (v1 == PTHREAD_CANCELED) {
	    printf("Thread1 was canceled!\n");
	} else {
	    printf("No!\n");
	}
	return 0;
}
