//Interface program that communicates with user

#include <stdio.h>
#include "serverFunctions.h"

int main() {
    int err;
    int Status = 0;
    int writeError, readError;
    int pipeToServ[2];  //Array that holds the read and write pipe to the server
    int pipeToInter[2];  //Array that holds the read and write pipe to the interface
    char args1[50];
    char args2[50];
    char ReadBuffer[BUFFER_SIZE + 1];//Input
    char WriteBuffer[BUFFER_SIZE + 1];
    int ServerPID;

    //Create Pipes
    pipe(pipeToServ);
    pipe(pipeToInter);
    //fork child process
    ServerPID = fork();

    errcheck(ServerPID);

    if (ServerPID == 0) {
        //in child process
        //Close unused pipe ends
        close(pipeToServ[1]);
        close(pipeToInter[0]);
        //Assign args
        sprintf(args1, "%d", pipeToServ[0]);
        sprintf(args2, "%d", pipeToInter[1]);
        //Execute Server Program
        err = execl("./server", args1, args2, NULL);

        errcheck(err);

        //DB is initialized.

    } else { // in Parent process
        //Close unused pipe ends
        close(pipeToServ[0]);
        close(pipeToInter[1]);

        //Pipes are established
        //Expecting message from DB with a success.
        printf("Reading from Server\n\n");
        readError = read(pipeToInter[0], ReadBuffer, 99);
        printf("Response: %s", ReadBuffer);
        clearBuffer(ReadBuffer);
        errcheck(readError);

        //Begin menu loop
        int Done = 0;
        while (Done == 0) {

            printf("Please supply a command( mpg,<id>| list,<id> | exit )\n:");

            //recieve input from user, send to Server.
            clearBuffer(WriteBuffer);
            scanf("%s", WriteBuffer);
            writeError = write(pipeToServ[1], WriteBuffer, BUFFER_SIZE);
            errcheck(writeError);

            //Read Response from DB
            readError = read(pipeToInter[0], ReadBuffer, BUFFER_SIZE);
            errcheck(readError);

            //Check for exit return by Server
            if (atoi(ReadBuffer) == 1) {
                Done = 1;
                clearBuffer(ReadBuffer);
                sprintf(ReadBuffer, "%s", "Server complete.\n");
                printf("Response: %s", ReadBuffer);
                printf("Interface:  child process (%d) completed.\n", ServerPID);
                break;
            }

            printf("Response: \n%s\n", ReadBuffer);



            clearBuffer(ReadBuffer);
        }
        //Wait for child process to finish;
        err = waitpid(-1, &Status, 0);
        errcheck(err);

        printf("Interface:  child process exit status = %d.\n", Status);
        printf("Interface:  Complete.\n");

    }//End of Parent Instructions

    return 0; //Exit
}
