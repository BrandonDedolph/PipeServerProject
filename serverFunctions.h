

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUMBER_OF_GAS_DATA 12   //Number of cars in the file to be read
#define BUFFER_SIZE 2048        //Max buffer size
#define PIPE_SIZE 2             //Pipe size

typedef enum { false, true } bool;
typedef enum { PipeRead, PipeWrite } PipeDirection;

//Structure declaration for the car information.
typedef struct
{
    char id[8];    //id of vehicle
    int odometer;  //number of miles on odometer
    float gallons; //gallons
}carInfo;

void errcheck(int err)  //Used to check if an error occurred with reading or writing from buffers.
{

    if(err == -1)
    {
        printf("It looks like there was an issue...");
        printf("Error Number :%d\n", errno);
        exit(-1);
    }
}

void clearBuffer(char *input)  //Clears the buffer after use.
{
    int i = 0;
    for(i; i < BUFFER_SIZE; i++)
    {
        *(input+i) = '\0';
    }
}

float getAvg(char *account, const carInfo *recs){
    float totalOd = 0.0;
    float totalGal = 0.0;
    float lastOd;

    for (int i = 0; i < NUMBER_OF_GAS_DATA;  i++){

        if(strcmp(recs[i].id, account) == 0){

            if (recs[i].gallons == 0.0)
                lastOd = recs[i].odometer;
            else {
                totalOd += (recs[i].odometer - lastOd);
                totalGal += recs[i].gallons;
                lastOd = recs[i].odometer;
            }
        }
    }

    return totalOd/totalGal;

}


void sort(carInfo *car)  //Sorts the array of car structures. using bubble sort
{
    int i, j;

    for (i = 0; i < NUMBER_OF_GAS_DATA - 1; i++) {
        for (j = 0; j < NUMBER_OF_GAS_DATA - i - 1; j++) {
            if (car[j].odometer > car[j + 1].odometer) {
                carInfo temp;
                temp = car[j];
                car[j] = car[j + 1];
                car[j + 1] = temp;
            }
        }
    }
}

#endif //FUNCTIONS_H