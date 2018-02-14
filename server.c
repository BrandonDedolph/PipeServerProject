//Server program that handles all the operations.

#include "serverFunctions.h"

int main(int argc, char **argv)
{
    char writeBuffer[BUFFER_SIZE];  //Buffer to transfer the written strings through the pipes
    char readBuffer[BUFFER_SIZE];  //Buffer to transfer the read strings through the pipes
    carInfo carList[NUMBER_OF_GAS_DATA+1];  //Array of carInfo objects
    int pipeToServ[2];  //Array that holds the read and write pipe to the server
    int pipeToInter[2];  //Array that holds the read and write pipe to the interface
    int writeError;  //Variable to check for errors in written strings
    int readError;  //Variable to check for errors in read strings

    FILE *inFile;  //Input file variable

    sscanf(argv[0], "%d", &pipeToServ[0]);  //Creates pipe that communicates to server.
    sscanf(argv[1], "%d", &pipeToInter[1]);  //Creates pipe that communicates to interface.

    inFile = fopen("gasData","r");  //Opens file "gasData" for reading

    int numOfCars = 0;  //Total number of cars being read in the loop
    int err;  //Error variable while reading the file

    for(int i = 0; !feof(inFile) && i < NUMBER_OF_GAS_DATA; i++)  //Loop to read the carInfo from the file
    {
        err = fscanf(inFile, "%7s %i %f \n", carList[i].id, &carList[i].odometer, &carList[i].gallons);
        errcheck(err);
        printf("[%d]:%7s %i %f \n", i, carList[i].id, carList[i].odometer, carList[i].gallons);  //Prints each car instance
        numOfCars++;
    }

    sort(carList);  //Sorts the records for when list command is called
    clearBuffer(writeBuffer);  //Clear write buffer for future input

    sprintf(writeBuffer,"The file was added successfully.\n Server can now accept commands.\n");  //String loaded into write buffer
    writeError = write(pipeToInter[1], writeBuffer, 99);  //write above string to interface
    errcheck(writeError);  //Error check to make sure string was successfully printed

    int Done = 0;
    while(Done == 0)
    {

        readError = read(pipeToServ[0], readBuffer, BUFFER_SIZE);
        clearBuffer(writeBuffer);
        errcheck(readError);
        if(strncmp(readBuffer, "\0", 1) == 0)
        {
            wait(10);
        }
            // mpg,<id>
        else if(strncmp(readBuffer, "mpg,", 4)== 0 ) // computer avg  for <id>
        {

            char id[8];
            float amount;

            int i;
            int j = 0;

            for (i = 4; i < 16; i++){
                id[j++] = readBuffer[i];
            }


            clearBuffer(readBuffer);

            amount = getAvg(id, carList);


            clearBuffer(readBuffer);

            //Write account amount to the buffer in the formatted string.
            clearBuffer(writeBuffer);
            sprintf(writeBuffer,"Average MPG for %s = %f.\n", id, amount);
            writeError = write(pipeToInter[1], writeBuffer, 99);
            errcheck(writeError);
        }




        else if (strncmp(readBuffer, "list,", 5) == 0 )
        {

            char id[8];
            int i;
            int j = 0;
            for (i = 5; i < 16; i++){
                id[j++] = readBuffer[i];
            }


            clearBuffer(readBuffer);

            int done = 0;

            if(numOfCars == 0)
            {
                done = 1;
            }
            i=0;
            int offset = 0;
            //loop through records each to buffer
            clearBuffer(writeBuffer);
            for(i = 0; (i < numOfCars) && (done != 1); i++)
            {
                if(strcmp(carList[i].id, id) == 0) {
                    offset += sprintf(writeBuffer + offset, "[%d]:%7s %i %f\n", i, carList[i].id, carList[i].odometer,
                                      carList[i].gallons);
                }
            }
            //Write entire buffer
            writeError = write(pipeToInter[1], writeBuffer, BUFFER_SIZE);
            errcheck(writeError);
        }

        else if(strncmp(readBuffer, "exit",4) == 0)
        {
            //Command from interface is exit.

            //send 1 down the pipe to terminate parent loop.
            clearBuffer(writeBuffer);
            sprintf(writeBuffer, "%d", 1);
            writeError = write(pipeToInter[1], writeBuffer, 99);
            errcheck(writeError);
            Done = 1;
        }
        else
        {
            //Unknown command
            clearBuffer(writeBuffer);
            sprintf(writeBuffer,"Server did not understand the command... \n");
            writeError = write(pipeToInter[1], writeBuffer, 99);
            errcheck(writeError);
        }
        clearBuffer(readBuffer);
    }

    return 0;
}
