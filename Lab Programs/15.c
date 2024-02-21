#include<stdio.h>
#include<stdlib.h>

/*
Displaying User Environmental Variables: Create a program to display the environmental 
variables of the user, utilizing the environ variable.
*/

extern char ** environ;

int main() {
    int i = 0;
    while (environ[i])
    {
        printf("%s\n", environ[i]);
        i++;
    }
}