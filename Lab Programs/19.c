/*
Process States: Develop a program to initiate a process in distinct states: 
a. running
b. sleeping
c. stopped
Confirm the current state of the process using the relevant commands.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Process running...\n");
    
    // Infinite loop to simulate the process running
    while (1) {
        // Sleeping state
        printf("Process sleeping...\n");
        sleep(5); // Sleep for 5 seconds
        
        // Stopped state
        printf("Process stopped. Press Enter to resume...\n");
        getchar(); // Wait for user input
        
        // Back to running state
        printf("Process resumed...\n");
    }

    return 0;
}
