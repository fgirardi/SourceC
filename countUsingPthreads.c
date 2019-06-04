#include<stdio.h>
#include<pthread.h>

#define MAX_LOOPS 2000000
long long sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* count (void *args) {

	int offset = *(int *) args;
	
	for (int i = 0; i < MAX_LOOPS; i++) {

		//Start critical section
		pthread_mutex_lock(&mutex);
		sum += offset;
		pthread_mutex_unlock(&mutex);
		//End critical section
	}
	pthread_exit(NULL);
}

int  main (void) {

	pthread_t tid1;
	pthread_t tid2;

	int offset1 = 1;
	//Spawn Threads
	pthread_create(&tid1, NULL, count, &offset1);

	int offset2 = -1;
	pthread_create(&tid2, NULL, count, &offset2);

	//Wait for threads to finish
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("sum = %lld\n", sum);
	return 0;
}
