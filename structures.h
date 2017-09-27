//
//  structures.h
//  testts
//
//  Created by Vartan Avny on 12/09/2017.
//  Copyright © 2017 Vartan Avny. All rights reserved.
//

#ifndef structures_h
#define structures_h

typedef struct nodes
{
    int  x;
    int  y;
    int  force;
    int  parentx;
    int  parenty;
    bool closedSet;
    //stop auto padding warnings
    char manualMemAligment1;
    char manualMemAligment2;
    char manualMemAligment3;
} node;

typedef struct cords
{
    int  x;
    int  y;
    int  force;
    bool closedSet;
    //stop auto padding warnings
    //char manualMemAligment1;
    //char manualMemAligment2;
    //char manualMemAligment3;
} cord;

typedef enum
{
    nullPointer,
    noInput,
    noLineScan,
    closeFail,
    badInput
}errors;

typedef struct errordesc
{
    int    messageNum;
    char * message;
} errordescs;

static errordescs errordesc[] =
{
    { nullPointer, "NULL pointer error" },
    { noInput, "Couldn't read File" },
    { noLineScan, "Couldn't read the line from the file" },
    { closeFail, "Couldn't close file"},
    { badInput, "The format of the input file is wrong, \
        IT must beggin with an itteration over the X and the the Y"}
};


#endif /* structures_h */
