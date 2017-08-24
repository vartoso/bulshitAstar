#include <stdio.h>

#define xy 100
#define sizeofAS sizeof a /sizeof a[0]

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
};



 
struct cord aStar(struct cord *start,struct cord *end, struct node nodes[100]){
    int minForce = 1000; //start with the lowest being the highest value
    int endcord;
    struct cord openSet[xy];
    //struct cord closedSet[xy];
    struct node current;
    int co,cc ; 
    co = 0;
    openSet[0].x = end->x;
    openSet[0].y = end->y;
    struct node current[xy];
    //initialize
    for(int x=0; x<100; x++){ 
        if (nodes[x].x < end->x){
            //swap X if negative
            nodes[x].H = ( nodes[x].x - end->x ) + ( end->y - nodes[x].y ) ;
        }
        if (nodes[x].y < end->y){
            //swap Y if negative
            nodes[x].H = ( nodes[x].x - end->x ) + ( nodes[x].y - end->y ) ;
        }    
        nodes[x].H = end->x - nodes[x].x + end->y - nodes[x].y;

        //map the xy
        if (!((nodes[x].x > 10) | (nodes[x].y>10))){
            current[nodes[x].x][nodes[x].y]=nodes[x];    
        }
        //fix not given force
        if ( nodes[x].force >1000 | nodes[x].force<0 ) nodes[x].force =  minForce;
        
        
    }
    cc=0;
    //lets run over each node:
    //while there is something in the open list
    while ( co >= 0 ){
        struct node list[];
        //need to make current equal to end atleast for the first time
        struct node temp;
        int X,Y;
        X=end->x;
        Y=end->y;
        //first run the target is end
        temp = *end;
        AGAIN:
        current[cc] = temp;
        //if we made it to the start node then stop,we're done...
        if ((start->x == current.x ) & (start->y == current.y )) break;
        if(current.closedSet != true){
            //generate 8 direction options
            co++;
            list[co].x = current.x+1;
            list[co].y = current.y;
            list[co].F = current.f*1.4;
            list[co].closedSet = false;
            //cross
            co++;
            list[co].x = current.x-1;
            list[co].y = current.y;
            list[co].F = current.f*1.4;
            list[co].closedSet = false;
            //cros
            co++;
            list[co].closedSet = false;
            list[co].x = current.x+1;
            list[co].y = current.y+1;
            co++;
            list[co].closedSet = false;
            list[co].x = current.x-1;
            list[co].y = current.y-1;
            //cros
            co++;
            list[co].closedSet = false;
            list[co].x = current.x;
            list[co].y = current.y+1;
            list[co].F = current.f*1.4;        
            co++;
            list[co].closedSet = false;
            list[co].x = current.x+1;
            list[co].y = current.y-1;
            co++;
            list[co].closedSet = false;
            list[co].x = current.x-1;
            list[co].y = current.y+1;
            //cross
            co++;
            list[co].closedSet = false;
            list[co].x = current->x;
            list[co].y = current->y-1;
            list[co].F = current->f*1.4;
            //run over the list and find the smallert F.
            for (int i = co; i>0 ; i--){
                if (temp.F>list[i]) temp =list[i] ;
                if ( list[i].F > list[i+1].F ){
                    temp  = list[i+1];
                    temp.parentx = list[i+1].x;
                    temp.parenty = list[i+1].y;
                    temp.closedSet = true;
                } 
            }
            cc++
            //we check everything from current
            goto AGAIN;
        }
        
    }
    //when the list has been cleaned i.e all checked
    //build the path
    for (int i =cc; i>0  ;i--) { //condition is if the node is not the start
            openSet[i].x=current[i].parentx;             
            openSet[i].y=current[i].parenty;             
        }
    openSet[cc].x = start->x; 
    openSet[cc].y = start->y;
    return *openSet;
}

int main()
{
    //struct cord ret[1];
    struct cord start[10];
    struct cord end[10];
    //this is static now but suppose to be dynamic
    start[0].x=70;
    start[0].y=80;
    end[0].x=0;
    end[0].y=0;
    //need a function to receive some kind of format to a 100 nodes map
    struct cord ret = aStar(start,end);//,nodes);
    printf("%d\n", ret[0].x);
    printf("%d\n", ret[0].y);
}

