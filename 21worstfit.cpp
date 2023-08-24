#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define LEFT(i) ((i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS)
#define RIGHT(i) ((i + 1) % NUM_PHILOSOPHERS)

enum state_t { THINKING, HUNGRY, EATING };
char* state_names[] = { "THINKING", "HUNGRY", "EATING" };

enum state_t state[NUM_PHILOSOPHERS] = { THINKING, THINKING, THINKING, THINKING, THINKING };
sem_t forks[NUM_PHILOSOPHERS];
sem_t mutex;

void print_states() {
    printf("[");
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        printf("%s", state_names[state[i]]);
        if (i < NUM_PHILOSOPHERS - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT(i)] != EATING && state[RIGHT(i)] != EATING) {
        state[i] = EATING;
        sem_post(&forks[i]);
    }
}

void pickup(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    print_states();
    test(i);
    sem_post(&mutex);
    sem_wait(&forks[i]);
}

void putdown(int i) {
    sem_wait(&mutex);
    state[i] = THINKING;
    print_states();
    test(LEFT(i));
    test(RIGHT(i));
    sem_post(&mutex);
}

void* philosopher(void* arg) {
    int i = *(int*) arg;
    while (1) {
        printf("Philosopher %d is thinking\n", i);
        sleep(rand() % 5);
        pickup(i);
        printf("Philosopher %d is eating\n", i);
        sleep(rand() % 5);
        putdown(i);
    }
}

int main() {
    srand(time(NULL));
    pthread_t threads[NUM_PHILOSOPHERS];
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }
    int ids[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}

