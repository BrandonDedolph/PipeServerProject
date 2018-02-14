/**
 * @file: interface.c
 * @author: Brandon Dedolph
 * @date: February 14, 2017
 * CSCI2 Account: cs311118
 */

#include <stdio.h>
#include "serverFunctions.h"

int main() {
    int error;
    int Status = 0;
    int writeError, readError;
    int serverPipe[PIPE_SIZE];  //Array that holds the read and write pipe to the server
    int interfacePipe[PIPE_SIZE];  //Array that holds the read and write pipe to the interface
    char argument1[20];
    char argument2[20];
    char ReadBuffer[BUFFER_SIZE];//Input
    char WriteBuffer[BUFFER_SIZE];
    int processID;

    //Create Pipes
    pipe(serverPipe);
    pipe(interfacePipe);
    //fork child process
    processID = fork();

    errcheck(processID);

    if (processID == 0) {
        //in child process
        //Close unused pipe ends
        close(serverPipe[PIPE_WRITE]);
        close(interfacePipe[PIPE_READ]);
        //Assign args
        sprintf(argument1, "%d", serverPipe[PIPE_READ]);
        sprintf(argument2, "%d", interfacePipe[PIPE_WRITE]);
        //Execute Server Program
        error = execl("./server", argument1, argument2, NULL);

        errcheck(error);

        //DB is initialized.

    } else { // in Parent process
        //Close unused pipe ends
        close(serverPipe[PIPE_READ]);
        close(interfacePipe[PIPE_WRITE]);

        //Reading from the Server
        readError = read(interfacePipe[PIPE_READ], ReadBuffer, 99);
        printf("Response: %s", ReadBuffer);
        clearBuffer(ReadBuffer);
        errcheck(readError);

        //Begin menu loop
        bool done = false;
        while (done == false) {

            printf("\n:");

            //receive input from user, send to Server.
            clearBuffer(WriteBuffer);
            scanf("%s", WriteBuffer);
            writeError = write(serverPipe[PIPE_WRITE], WriteBuffer, BUFFER_SIZE);
            errcheck(writeError);

            //Read Response from DB
            readError = read(interfacePipe[PIPE_READ], ReadBuffer, BUFFER_SIZE);
            errcheck(readError);

            //Check for exit return by Server
            if (atoi(ReadBuffer) == 1) {
                done = true;
                clearBuffer(ReadBuffer);
                sprintf(ReadBuffer, "%s", "Server complete.\n");
                printf("Response: %s", ReadBuffer);
                printf("Interface:  child process (%d) completed.\n", processID);
                break;
            }

            printf("Response: \n%s ", ReadBuffer);



            clearBuffer(ReadBuffer);
        }
        //Wait for child process to finish;
        error = waitpid(-1, &Status, 0);
        errcheck(error);

        printf("Interface:  child process exit status = %d.\n", Status);
        printf("Interface:  Complete.\n");

    }//End of Parent Instructions

    return 0; //Exit
}
