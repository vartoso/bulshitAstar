//
//  main.c
//  testts
//
//  Created by Vartan Avny on 31/08/2017.
//  Copyright © 2017 Vartan Avny. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "preset.h"
#include "structures.h"
#include "functions.c"




int main()
{
    int globalError = noError;
    int matrix[2]; //0 is X and 1 is Y
    cord *map;
    cord start;
    cord end;
    
    start.x = 7;
    start.y = 8;
    end.x   = 0;
    end.y   = 0;
    
    //I'm limiting the input matrix to a 1000 on 1000
    map = malloc( sizeof(cord) * 1000000);
    if ( ((void * )map == NULL) || (sizeof map == 0) )
    {
        error(nullPointer);
    }
    input( map, "input.txt", matrix);
    cord *ret = aStar( start, end, map, matrix, &globalError); //map is map that consists from nodes);
    if ( globalError != noError )
    {
        printf("This program had a memmory management problem and did not run the way it should have ran, please run it again to get the correct results.");
        return globalError;
    }
    for ( int i = sizeof(ret); i > 0; i-- )
    {
        printf("%d\tx : %d \ty : %d\n", i, ret[i].x , ret[i].y);
    }
    if ( globalError == noError )
    {
        return 0;
    }else
    {
        return 1;
    }
}

