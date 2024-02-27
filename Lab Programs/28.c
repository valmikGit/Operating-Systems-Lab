#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>

int main() 
{
    int my_Priority = getpriority(PRIO_PROCESS,getpid());
    if(my_Priority == -1) 
    {
        perror("Error getting priority");
        return 1;
    }
    printf("Current priority: %d\n", my_Priority);
    int my_Priority_increment = 6;
    nice(my_Priority_increment);//Modifying priority
    my_Priority = getpriority(PRIO_PROCESS,getpid());
    if(my_Priority == -1) 
    {
        perror("Error getting priority");
        return 1;
    }
    printf("Updated priority: %d\n",my_Priority);
    return 0;
}