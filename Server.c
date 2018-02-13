//It loads a list of account records, sorts and
//writes data to Interface.

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "MPGHeader.h"

//Functions
void clearBuffer(char *input);
//void sort(carInfo *recs, int count);
//void printRecords(carInfo *records, int count);
void errcheck(int err);
float totalMPG(long int account, const carInfo *recs, int count);
//float getDateTotal(char * date, const record * recs, int count );

//Expects 2 integers for program execution.
int main(int argc,char **argv){

    //Initializations for communication
    char writeBuffer[2048];
    char readBuffer[2048];
    char Cmd[100];
    int toDB[2];
    int toInterface[2];
    int writeError;
    int readError;

    //Initialize for file read.
    FILE *fd;

    //assign pipe values from start;
    sscanf(argv[0],"%d",&toDB[0]);
    sscanf(argv[1],"%d",&toInterface[1]);

    //Open the gasData file.
    fd = fopen("gasData","r");
    //Initialize array to hold the car info.
    carInfo carList[MAX_CARS+1];

    int i =0;
    int numRecords;
    int err;

    //read records from file.
    for(i=0; !feof(fd) && i < MAX_CARS; i++)
    {
        err = fscanf(fd,"%7s %i %f \n", carList[i].id, &carList[i].odometer, &carList[i].gallons);
        if(err ==-1){
            printf("Error in processing file... Error:%d \n",errno);
            exit(-1);
        }
        printf("[%d]:%7s %i %f \n", i, carList[i].id, carList[i].odometer, carList[i].gallons);
        numRecords++;
    }
    //write records to buffer


    //records have been read in, sort them for further displays

    sprintf(writeBuffer,"All records added successfully.\n - DB Initialized - \n");
    writeError = write(toInterface[1],writeBuffer,99);
    errcheck(writeError);

    //ready to receive input from interface.
    //Create call structure for different calls from interface.
    int Done = 0;
    while(Done == 0){

        readError = read(toDB[0],readBuffer, BUFFER_SIZE);
        clearBuffer(writeBuffer);
        errcheck(readError);
        if(strncmp(readBuffer,"\0",1) == 0){wait(10);}

        else if(strncmp(readBuffer,"id",2)== 0 ){
            long int account;
            float amount;
            char accountch[12];
            int i;
            int j = 0;
            //extract account number
            for (i = 8; i < 20; i++){
                accountch[j++] = readBuffer[i];
            }
            sscanf(accountch,"%ld",&account);
            clearBuffer(readBuffer);

            //Total up the amount for the given account number.
            amount = totalMPG(account, carList, numRecords);

            //Write account amount to the buffer in the formatted string.
            clearBuffer(writeBuffer);
            sprintf(writeBuffer,"total for %ld = %.2f.\n",account,amount);
            writeError = write(toInterface[1],writeBuffer,99);
            errcheck(writeError);
        }
        else if(strncmp(readBuffer, "exit",4) == 0){
            //Command from interface is exit.

            //send 1 down the pipe to terminate parent loop.
            clearBuffer(writeBuffer);
            sprintf(writeBuffer,"%d",1);
            writeError = write(toInterface[1],writeBuffer,99);
            errcheck(writeError);
            Done = 1;
        }
        else{
            //Unknown command, clear buffer and try again to recieve input from the user.
            clearBuffer(writeBuffer);
            sprintf(writeBuffer,"DB did not understand the command... \n");
            writeError = write(toInterface[1],writeBuffer,99);
            errcheck(writeError);
        }
        clearBuffer(readBuffer);
    }


    return 0;
}
/////////////////////////FUNCTION LIST//////////////////////////////////////////
void clearBuffer(char *input){
    int i = 0;
    for(i; i < BUFFER_SIZE; i++){
        *(input+i) = '\0';
    }
}



void printRecords(carInfo *records, int count){

    int i = 0;
    for(i; i < count; i++){
        printf("%c %i %.8f \n",records[i].id, records[i].odometer, records[i].gallons);
    }
}
//Wrote function to minimize the space by this check.
void errcheck(int err){

    if(err == -1){
        printf("It looks like there was an issue...");
        printf("Error Number :%d\n", errno);
        exit(-1);
    }
}
//Takes and account number and accumulates the total for the give date.
float totalMPG(long int account, const carInfo * recs, int count ){
    float totalodom = 0;
    float totalgal = 0;
    float average = 0;
    int i;
    for(i=0; i< count;i++){

        if(recs[i].id == account){
            totalodom += recs[i].odometer;
            totalgal+=recs[i].gallons;
        }
    }

    average = totalodom/totalgal;

    return average;
}