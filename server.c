/**
 * @file: server.c
 * @author: Brandon Dedolph
 * @date: February 14, 2017
 * CSCI2 Account: cs311118
 */

#include "serverFunctions.h"

int NumCars = 12;         //To contain the number of cars found in the gas data file

float getAvg(char *, const carInfo *);
void sort(carInfo *);

int main(int argc, char **argv)
{
    char writeBuffer[BUFFER_SIZE];          //Buffer to transfer the written strings through the pipes
    char readBuffer[BUFFER_SIZE];           //Buffer to transfer the read strings through the pipes
    int serverPipe[PIPE_SIZE];              //Array that holds the read and write pipe to the server
    int interfacePipe[PIPE_SIZE];           //Array that holds the read and write pipe to the interface
    int error;                              //used to check for errors

    FILE *inFile;            //Input file variable

    sscanf(argv[PIPE_READ], "%d", &serverPipe[PIPE_READ]);       //Creates read pipes.
    sscanf(argv[PIPE_WRITE], "%d", &interfacePipe[PIPE_WRITE]);  //Creates write pipes.

    inFile = fopen(INFILE,"r");         //Opens file listed in the define function in the header

    carInfo temp;
    for(int i = 0; !feof(inFile); i++)  //Loop to read the carInfo from the file
    {
        error = fscanf(inFile, "%7s %i %f \n", temp.id, &temp.odometer, &temp.gallons);
        errcheck(error);
        //NumCars++;
    }

    close(inFile);

    carInfo carList[NumCars];    //Array of carInfo objects

    inFile = fopen(INFILE,"r");

    printf("Input command:\n");
    for(int i = 0; i < NumCars; i++)  //Loop to read the carInfo from the file
    {
        error = fscanf(inFile, "%7s %i %f \n",carList[i].id, &carList[i].odometer, &carList[i].gallons);
        errcheck(error);
        printf("element = %d:  id = %s, odometer = %i, gallons = %f \n", i, carList[i].id, carList[i].odometer, carList[i].gallons);
    }

    close(inFile);

    sort(carList);               //Sorts the records for when list command is called
    clearBuffer(writeBuffer);    //Clear write buffer for future input

    error = write(interfacePipe[PIPE_WRITE], writeBuffer, 99);  //write above string to interface
    errcheck(error);  //Error check to make sure string was successfully printed

    bool done = false;
    while(done == false)
    {

        error = read(serverPipe[PIPE_READ], readBuffer, BUFFER_SIZE);
        clearBuffer(writeBuffer);
        errcheck(error);
        if(strncmp(readBuffer, "\0", 1) == 0)
        {
            wait(10);
        }
            // mpg,<id>
        else if(strncmp(readBuffer, "mpg,", 4)== 0 ) // computer avg  for <id>
        {

            char id[7];
            float amount;

            int i;
            int j = 0;

            for (i = 4; i < 16; i++){
                id[j++] = readBuffer[i];
            }

            clearBuffer(readBuffer);

            amount = getAvg(id, carList);

            //Write account amount to the buffer in the formatted string.
            sprintf(writeBuffer,"Average MPG for %s = %f.\n", id, amount);
            error = write(interfacePipe[PIPE_WRITE], writeBuffer, 99);
            errcheck(error);
        }




        else if (strncmp(readBuffer, "list,", 5) == 0 )
        {

            char id[8];
            int j = 0;
            for (int i = 5; i < 16; i++){
                id[j++] = readBuffer[i];
            }


            clearBuffer(readBuffer);


            //loop through records each to buffer
            clearBuffer(writeBuffer);
            for(int i = 0, offset = 0; i < NumCars; i++)
            {
                if(strcmp(carList[i].id, id) == 0) {
                    offset += sprintf(writeBuffer + offset, "odometer = %i, gallons = %f\n", carList[i].odometer,
                                      carList[i].gallons);
                }
            }
            //Write entire buffer
            error = write(interfacePipe[PIPE_WRITE], writeBuffer, BUFFER_SIZE);
            errcheck(error);
        }

        else if(strncmp(readBuffer, "exit",4) == 0)
        {
            //Command from interface is exit.

            //send 1 down the pipe to terminate parent loop.
            clearBuffer(writeBuffer);
            sprintf(writeBuffer, "%d", 1);
            error = write(interfacePipe[PIPE_WRITE], writeBuffer, 99);
            errcheck(error);
            done = true;
        }
        else
        {
            //Unknown command
            clearBuffer(writeBuffer);
            sprintf(writeBuffer,"Server did not understand the command... \n");
            error = write(interfacePipe[PIPE_WRITE], writeBuffer, 99);
            errcheck(error);
        }
        clearBuffer(readBuffer);
    }

    return 0;
}

float getAvg(char *account, const carInfo *recs){
    float totalOd = 0.0;
    float totalGal = 0.0;
    float lastOd;

    for (int car = 0; car < NumCars;  car++){

        if(strcmp(recs[car].id, account) == 0){

            if (recs[car].gallons == 0.0)
                lastOd = recs[car].odometer;
            else {
                totalOd += (recs[car].odometer - lastOd);
                totalGal += recs[car].gallons;
                lastOd = recs[car].odometer;
            }
        }
    }

    return totalOd/totalGal;

}


void sort(carInfo *car)  //Sorts the array of car structures. using bubble sort
{
    for (int car1 = 0; car1 < NumCars; car1++) {
        for (int car2 = 0; car2 < NumCars - car1 - 1; car2++) {
            if (car[car2].odometer > car[car2 + 1].odometer) {
                carInfo temp;
                temp = car[car2];
                car[car2] = car[car2 + 1];
                car[car2 + 1] = temp;
            }
        }
    }
}
