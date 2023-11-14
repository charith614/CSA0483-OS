#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

sem_t empty;   // Semaphore to track empty slots in the buffer
sem_t full;    // Semaphore to track filled slots in the buffer
pthread_mutex_t mutex;  // Mutex for mutual exclusion
int buffer[BUFFER_SIZE]; // Shared buffer

int in = 0; // Index for the producer to insert an item
int out = 0; // Index for the consumer to remove an item

void *producer(void *arg) {
    int item;
    while (1) {
        // Produce item
        item = rand() % 100;

        // Wait for an empty slot in the buffer
        sem_wait(&empty);

        // Acquire mutex for mutual exclusion
        pthread_mutex_lock(&mutex);

        // Insert item into the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced item: %d\n", item);

        // Release mutex
        pthread_mutex_unlock(&mutex);

        // Signal that a slot in the buffer is now full
        sem_post(&full);

        // Sleep to simulate variable production time
        sleep(rand() % 3 + 1);
    }
}

void *consumer(void *arg) {
    int item;
    while (1) {
        // Wait for a filled slot in the buffer
        sem_wait(&full);

        // Acquire mutex for mutual exclusion
        pthread_mutex_lock(&mutex);

        // Remove item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed item: %d\n", item);

        // Release mutex
        pthread_mutex_unlock(&mutex);

        // Signal that a slot in the buffer is now empty
        sem_post(&empty);

        // Sleep to simulate variable consumption time
        sleep(rand() % 3 + 1);
    }
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Join threads (this will never be reached in this simple example)
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Clean up
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

