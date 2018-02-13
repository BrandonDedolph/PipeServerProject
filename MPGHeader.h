//
// Created by ajfoggia on 2/12/18.
//

#ifndef UNTITLED_MPGHEADER_H
#define UNTITLED_MPGHEADER_H

#define MAX_CARS 12  //Limit for the number of cars in the file
#define BUFFER_SIZE 2048  //Max buffer size

//Struct declaration for the car information.
typedef struct
{
    char id[8]; //id of vehicle
    int odometer; //number of miles on odometer
    float gallons; //gallons
}carInfo;

#endif //UNTITLED_MPGHEADER_H
