/*
 Getting and Modifying Scheduling Policy: Write a program to obtain the scheduling policy 
and modify it (e.g., SCHED_FIFO, SCHED_RR).
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main() 
{
    int policy;
    struct sched_param param;
    // Get the current scheduling policy
    policy = sched_getscheduler(0);
    if (policy == -1) 
    {
        perror("Error getting scheduling policy");
        return 1;
    }
    printf("Current scheduling policy: ");
    switch (policy) 
    {
        case SCHED_FIFO:
            printf("FIFO\n");
            break;
        case SCHED_RR:
            printf("Round Robin\n");
            break;
        case SCHED_OTHER:
            printf("Other (default)\n");
            break;
        default:
            printf("Unknown\n");
            break;
    }
    param.sched_priority = sched_get_priority_max(SCHED_RR);// Modify the scheduling policy to SCHED_RR
    if (sched_setscheduler(0, SCHED_RR, &param) == -1)
    {
        perror("Error setting scheduling policy");
        return 1;
    }
    printf("Scheduling policy modified to RR\n");
    return 0;
}
