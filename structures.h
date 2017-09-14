//
//  structures.h
//  testts
//
//  Created by Vartan Avny on 12/09/2017.
//  Copyright © 2017 Vartan Avny. All rights reserved.
//

#ifndef structures_h
#define structures_h

typedef struct  nodes {
    int x;
    int y;
    int force;
    int parentx;
    int parenty;
    bool closedSet;
} node;

typedef struct cords {
    int x;
    int y;
    int force;
    bool closedSet;
} cord;

typedef enum {
    nullPointer,
    noInput,
    noLineScan,
    closeFail
}errors;

struct errordesc{
    int  code;
    char *message;
} errordesc[] = {
    { nullPointer, "NULL pointer error" },
    { noInput, "Couldn't read File" },
    { noLineScan, "Couldn't read the line from the file" },
    { closeFail, "Couldn't close file"}
};

#endif /* structures_h */
