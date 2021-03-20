#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int cnt = 0;
void *child()
{
	for (int i=0; i<1000000; i++) {
	    /*int tmp = cnt;
		sleep(1);
		cnt = tmp + 1;*/
		cnt = cnt + 1;
		printf("cnt = %d\n", cnt);
	}
	pthread_exit(NULL);
}
/* Expexcted 2*1000000 but not really */
int main(void)
{
    pthread_t t1, t2;
	pthread_create(&t1, NULL, child, "NULL");
	pthread_create(&t2, NULL, child, "NULL");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
	return 0;
}
