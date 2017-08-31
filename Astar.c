//
//  main.c
//  testts
//
//  Created by Vartan Avny on 31/08/2017.
//  Copyright © 2017 Vartan Avny. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define xy 100
#define sizeofAS sizeof a /sizeof a[0]

#define bool int
#define true 1
#define false 0


struct  node {
    int x,y,force;
    long G,H,F;
    int parentx;
    int parenty;
    bool closedSet;
};

struct cord{
    int x;
    int y;
    int force;
    bool closedSet;
};

//receive a file with cordinates
void input(struct cord * map,char *inputFile){
    char line[20];
    int inc=0;
    FILE *pf = NULL;
    
    if ( ( pf = fopen (inputFile, "r")) == NULL) {
        printf ( "No input file\n");
    }
    while ( ( fgets ( line, sizeof line, pf))) {
        if ( ( sscanf ( line, "%d %d %d"
                       , &map[inc].x,&map[inc].y,&map[inc].force)) != EOF ) {
            printf ( "map[inc].x : %d , map[inc].y : %d , map[inc].force : %d\n", map[inc].x, map[inc].y, map[inc].force);
            inc++;
        }
    }
    fclose (pf);
}


//threw the init to another function just for the order of things
void initit(struct cord * nodes, struct cord end, struct cord **current)
{
    int minForce = 1000; //start with the lowest being the highest value
    //struct cord current[10][10];
    for(int x=0; x<100; x++){
        if (nodes[x].x < end.x){
            //swap X if negative
            nodes[x].force = nodes[x].force + ((( nodes[x].x - end.x ) + ( end.y - nodes[x].y ))*10);
        }
        if (nodes[x].y < end.y){
            //swap Y if negative
            nodes[x].force = nodes[x].force + ((( nodes[x].x - end.x ) + ( nodes[x].y - end.y ))*10);
        }
        nodes[x].force = nodes[x].force + (((end.x - nodes[x].x) + (end.y - nodes[x].y))*10);
        
        //map the xy
        if (!((nodes[x].x > 10) | (nodes[x].y>10))){
            current[nodes[x].x][nodes[x].y]=nodes[x];
        }
        //fix not given force
        if ( nodes[x].force >1000 | nodes[x].force<0 ) nodes[x].force =  minForce;
        
    }

}


struct cord *aStar(struct cord start,struct cord end, struct cord nodes[100]){
//    int minForce = 1000; //start with the lowest being the highest value
    struct cord openSet[xy];
    struct cord * closedSet = malloc(sizeof(struct cord)*100);
    int co,cc ;
    co = 0;
    openSet[0].x = end.x;
    openSet[0].y = end.y;
    struct cord current[10][10];
    struct cord * cur;
    cur = current[0];
    
    //initialize values
    initit(nodes, end, &cur);
    
    
    cc=0;
    //lets run over each node:
    //while there is something in the open list
    while ( co >= 0 ){
        struct node list[100];
        //need to make current equal to end atleast for the first time
        struct node temp;
        int X,Y;
        X=end.x;
        Y=end.y;
        //first run the target is end
        temp.x = end.x;
        temp.y = end.y;
        temp.force = end.force;
        
    AGAIN:
        current[X][Y].x = temp.x;
        current[X][Y].y = temp.y;
        current[X][Y].force = temp.force;
        
        //if we made it to the start node then stop,we're done...
        if ((start.x == current[X][Y].x ) & (start.y == current[X][Y].y )) break;
        if(current[X][Y].closedSet != true){
            //generate 8 direction options
            co++;
            list[co].x = current[X][Y].x+1;
            list[co].y = current[X][Y].y;
            list[co].force = current[X][Y].force*1.4;
            list[co].closedSet = false;
            //cross
            co++;
            list[co].x = current[X][Y].x-1;
            list[co].y = current[X][Y].y;
            list[co].force = current[X][Y].force*1.4;
            list[co].closedSet = false;
            //cros
            co++;
            list[co].closedSet = false;
            list[co].x = current[X][Y].x+1;
            list[co].y = current[X][Y].y+1;
            co++;
            list[co].closedSet = false;
            list[co].x = current[X][Y].x-1;
            list[co].y = current[X][Y].y-1;
            //cros
            co++;
            list[co].closedSet = false;
            list[co].x = current[X][Y].x;
            list[co].y = current[X][Y].y+1;
            list[co].force = current[X][Y].force*1.4;
            co++;
            list[co].closedSet = false;
            list[co].x = current[X][Y].x+1;
            list[co].y = current[X][Y].y-1;
            co++;
            list[co].closedSet = false;
            list[co].x = current[X][Y].x-1;
            list[co].y = current[X][Y].y+1;
            //cross
            co++;
            list[co].closedSet = false;
            list[co].x = current[X][Y].x;
            list[co].y = current[X][Y].y-1;
            list[co].force = current[X][Y].force*1.4;
            //run over the list and find the smallert F.
            for (int i = co; i>0 ; i--){
                if (temp.force>list[i].force){
                    temp =list[i];
                    temp.parentx = list[i].x;
                    temp.parenty = list[i].y;
                    temp.closedSet = true;
                }
                if ( list[i].force > list[i+1].force ){
                    temp  = list[i+1];
                    temp.parentx = list[i+1].x;
                    temp.parenty = list[i+1].y;
                    temp.closedSet = true;
                }
            }
            closedSet[cc].x=temp.x;
            closedSet[cc].y=temp.y;
            X=temp.x;
            Y=temp.y;
            cc++;
            //we check everything from current
            goto AGAIN;
        }
        
    }
    return closedSet;
}

int main()
{
    struct cord *map;
    struct cord start;
    struct cord end;
    
    
    //this is static now but suppose to be dynamic
    start.x=70;
    start.y=80;
    end.x=0;
    end.y=0;
    
    map = (struct cord *)malloc(sizeof(struct cord) * 100);
    input(map,"input.txt");
    struct cord *ret = aStar(start,end,map);//,nodes);
    printf("%d\n", ret[0].x);
    printf("%d\n", ret[0].y);
}

