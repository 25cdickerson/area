// Import Statments
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

// Global Variables
double area;
double count = 32;

pthread_mutex_t my_lock;

// Function Prototypes
void *compute(void *idnum);


// Main
int main(int argc, char *argv[]){
	// Get Number of Threads
	int SIZE = atoi(argv[1]);

	// Create Array
	pthread_t *threads;
	
	// Calculate count (calculates the amount of times a single thread has to loop)
	count = count / SIZE;

	// Allocate space for the array
	threads = (pthread_t*)malloc(SIZE * sizeof(pthread_t));

	// Create Threads
	for(long i = 0; i < SIZE; i++){
		pthread_create(&threads[i], NULL, compute, (void *)i);
	}

	// Join Threads
	for(int i = 0; i < SIZE; i++){
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&my_lock);

	// Print
	printf("Area under the line: %f\n", area);
	
	// Exit
	free(threads);
	threads = NULL;
	pthread_exit(NULL);
	return 0;
}

// Function Definitions
void *compute(void *idnum){
	long id = (long) idnum;
	double f = 0;

	double x = id * count;

	for(int i = 0; i < count * 5; i++){
		pthread_mutex_lock(&my_lock);
		f = ((2 * x) + 3) * 0.2;
		area = area + f;
		x = x + 0.2;
		pthread_mutex_unlock(&my_lock);
	}
}
