/**
 * @file: serverFunctions.h
 * @author: Brandon Dedolph
 * @date: February 14, 2017
 * CSCI2 Account: cs311118
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 2048        //Max buffer size
#define PIPE_SIZE 2             //Pipe size

#define PIPE_READ 0             //Added for readability when using pipes


#define PIPE_WRITE 1            //Added for readability when using pipes


#define INFILE "gasData"        //File to have the gas data read in from

typedef enum { false, true } bool;

typedef struct //To contain the information for each car
{
    char id[8];
    int odometer;
    float gallons;
}carInfo;

void errcheck(int err)  //checks if -1 has been returned when reading or writing through pipes
{

    if(err == -1)
    {
        printf("It looks like there was an issue...");
        printf("Error Number :%d\n", errno);
        exit(-1);
    }
}

void clearBuffer(char *input)  //Clears the buffer
{
    int i = 0;
    for(i; i < BUFFER_SIZE; i++)
    {
        *(input+i) = '\0';
    }
}
#endif //FUNCTIONS_H
