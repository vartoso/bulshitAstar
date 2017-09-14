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
#include "preset.h"
//only then
#include "structures.h"
//and only then
#include "functions.h"




int main()
{
    cord *map;
    cord start;
    cord end;
    
    start.x=7;
    start.y=8;
    end.x=0;
    end.y=0;
    
    map =  (cord *) malloc(sizeof( cord) * 100);
    if ( ((void *)map == NULL) || ( sizeof map == 0) ){
        error(0);
        return 1;
    }
    input(map,"input.txt");
     cord *ret = aStar(start,end,map);//,nodes);
    for (int i = sizeof(ret); i>0 ; i--){
        printf("%d\tx : %d \ty : %d\n", i, ret[i].x , ret[i].y);
    }
    return 0;
}

