#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_TICKETS 100
#define NUM_THREADS 10

// Shared data
int ticket_number = 0;
int shared_memory = 0;
int pseudo_resource1 = 0;
int pseudo_resource2 = 0;

// Semaphores
sem_t ticket_semaphore;
sem_t shared_memory_semaphore;
sem_t pseudo_resource_semaphore;

// Function to generate ticket number
void *generate_ticket(void *thread_id) {
    int id = *((int *)thread_id);
    while (1) {
        sem_wait(&ticket_semaphore); // Wait for access to ticket_number
        if (ticket_number < NUM_TICKETS) {
            printf("Thread %d: Ticket Number %d\n", id, ++ticket_number);
        } else {
            sem_post(&ticket_semaphore); // Release semaphore before exiting
            pthread_exit(NULL);
        }
        sem_post(&ticket_semaphore); // Release semaphore after ticket generation
    }
}

// Function to access shared memory
void *access_shared_memory(void *thread_id) {
    int id = *((int *)thread_id);
    int data = id + 1;
    while (1) {
        sem_wait(&shared_memory_semaphore); // Wait for access to shared_memory
        shared_memory += data;
        printf("Thread %d: Shared Memory Value: %d\n", id, shared_memory);
        sem_post(&shared_memory_semaphore); // Release semaphore after accessing shared_memory
        sleep(1);
    }
}

// Function to access pseudo resources
void *access_pseudo_resources(void *thread_id) {
    int id = *((int *)thread_id);
    int resource = id % 2 == 0 ? 1 : -1; // Alternating resource usage
    while (1) {
        sem_wait(&pseudo_resource_semaphore); // Wait for access to pseudo resources
        if ((resource == 1 && pseudo_resource1 < NUM_THREADS / 2) ||
            (resource == -1 && pseudo_resource2 < NUM_THREADS / 2)) {
            if (resource == 1)
                pseudo_resource1++;
            else
                pseudo_resource2++;
            printf("Thread %d: Pseudo Resource %d used\n", id, resource);
        }
        sem_post(&pseudo_resource_semaphore); // Release semaphore after accessing pseudo resources
        sleep(1);
    }
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;

    // Initialize semaphores
    sem_init(&ticket_semaphore, 0, 1); // Binary semaphore for ticket_number
    sem_init(&shared_memory_semaphore, 0, 1); // Binary semaphore for shared_memory
    sem_init(&pseudo_resource_semaphore, 0, 1); // Counting semaphore for pseudo resources

    // Create threads for generating ticket numbers
    for (i = 0; i < NUM_THREADS / 2; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, generate_ticket, (void *)&thread_ids[i]);
    }

    // Create threads for accessing shared memory
    for (i = NUM_THREADS / 2; i < NUM_THREADS * 3 / 4; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, access_shared_memory, (void *)&thread_ids[i]);
    }

    // Create threads for accessing pseudo resources
    for (i = NUM_THREADS * 3 / 4; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, access_pseudo_resources, (void *)&thread_ids[i]);
    }

    // Join threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&ticket_semaphore);
    sem_destroy(&shared_memory_semaphore);
    sem_destroy(&pseudo_resource_semaphore);

    return 0;
}
