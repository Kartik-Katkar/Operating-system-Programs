#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *test()
{
	
	printf("I am in test function \n");
	return NULL;
}

int main()
{
	pthread_t th;
	int ret;
	printf("Before Thread\n");
	ret=pthread_create(&th, NULL, test, NULL);
	if(ret==0){
	    printf("Thread Created Succesfully\n");
	}
	else{
	    printf("Not Created\n");
	}
	pthread_join(th, NULL);
	exit(0);
}