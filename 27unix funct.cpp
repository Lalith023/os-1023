#include <stdio.h>27. Write a program for semaphore signaling mechanism where a process can signal a process that is waiting on a semaphore.
Test Case:
number of instances: 4
Number of Processes: 4 (P1, P2, P3, P4) all are calling wait operation on S
Show the response when another process P5 wants the same resource.
sol:

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 5
#define NUM_SEMAPHORES 1

// Define the semaphores
sem_t semaphores[NUM_SEMAPHORES];

// Define the threads
pthread_t threads[NUM_THREADS];

void* threadFunction(void* threadID) {
    int id = *(int*)threadID;
    
    printf("Thread %d waiting on semaphore...\n", id);
    
    // Wait on the semaphore
    sem_wait(&semaphores[0]);
    
    printf("Thread %d got the semaphore!\n", id);
    
    // Release the semaphore
    sem_post(&semaphores[0]);
    
    pthread_exit(NULL);
}

int main() {
    int threadIDs[NUM_THREADS];
    int i;
    
    // Initialize the semaphore
    sem_init(&semaphores[0], 0, 4);
    
    // Create the threads
    for (i = 0; i < NUM_THREADS; i++) {
        threadIDs[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, (void*)&threadIDs[i]);
    }
    
    // Wait for the threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Destroy the semaphore
    sem_destroy(&semaphores[0]);
    
    return 0;
}
