
//
//  functions.h
//  testts
//
//  Created by Vartan Avny on 12/09/2017.
//  Copyright © 2017 Vartan Avny. All rights reserved.
//

#ifndef functions_h
#define functions_h

//printing errors



void error(int err) __attribute__ ((noreturn));
int * input( cord * map, char *inputFile, int *  xy);
void initIt( cord * nodes, cord start, cord ** current , int * xy);
node * findf( int X, int  Y, cord ** current, int * xy);
cord * aStar( cord start, cord end, cord * nodes, int * xy);

void error(int err){
    switch (err)
    {
        case 0:
            printf("I got %s from allocation: ", errordesc[err].message);
            break;
            
        case 1:
            printf("I got %s from fgets: ", errordesc[err].message);
            break;
            
        case 2:
            printf("I got %s from Sscanf: ", errordesc[err].message);
        
        case 3:
            printf("I got %s from fclose: ", errordesc[err].message);
        
        case 4:
            printf("I got %s from fclose: ", errordesc[err].message);
    
        default:
            break;
    }
    perror("Failed because: ");
    exit(1);
}


int * input( cord * map, char * inputFile, int * xy){
    char * err;
    char line[20];
    int inc=0;
    int x=0;
    int y=0;
    //static int xy[2];
    FILE * pf = NULL;
    
    if (( pf = fopen(inputFile, "r")) == NULL)
    {
        printf( "No input file\n");
        exit(0);
    }
    while (( err = fgets( line, sizeof line, pf)))
    {
        if ( err == NULL )
        {
            error(1);
        }
        else if ((sscanf( line, "%d %d %d", &map[inc].x, &map[inc].y, &map[inc].force)) != EOF)
        {
            testPrint ( "map[inc].x : %d , map[inc].y : %d , map[inc].force : %d\n", map[inc].x, map[inc].y, map[inc].force);
            if( map[inc].x == 0 )
            {
                if( map[inc].x < 1 )
                {
                    y++;
                }else{
                    error(4);
                }
            }else if( map[inc].x == inc/y )
            {
                x = map[inc].x + 1;
            }
            inc++;
        }
        else {
            error(2);
        }
    }
    if ( fclose (pf) == EOF )
    {
        error(3);
    }
    xy[0] = x;
    xy[1] = y;
    return  xy;
}



void initIt( cord * nodes, cord start, cord ** current , int * xy)
{
    int minForce = 1000; //start with the lowest being the highest value
    for(int x=0; x < (((int)xy[0] * (int)xy[1])); x++)
    {
        //fix not given force
        if ( nodes[x].force > 1000 | nodes[x].force < 0 ) nodes[x].force =  minForce;
        if ( nodes[x].x > start.x )
        {
            //swap X if negative  it suppose to be start x - end x but we need to replace it to current - start ...
            nodes[x].force = nodes[x].force + ( abs((( nodes[x].x - start.x ) + ( start.y - nodes[x].y ))) * 100 );
        }
        if ( nodes[x].y > start.y )
        {
            //swap Y if negative  it suppose to be start y - end y but we need to replace it to current - end ...
            nodes[x].force = nodes[x].force + ( abs((( start.x  - nodes[x].x ) + ( nodes[x].y - start.y ))) * 100 );
        }
        else
        {
            nodes[x].force = nodes[x].force + ( abs(((start.x - nodes[x].x) + (start.y - nodes[x].y))) * 100 );
        }
        //map the xy
        if ( !((nodes[x].x > xy[0]) | (nodes[x].y > xy[1])) )
        {
            current[nodes[x].x][nodes[x].y] = nodes[x];
            testPrint ( "current[%d][%d] :  %d\n", nodes[x].x, nodes[x].y, current[nodes[x].x][nodes[x].y].force);
        }
    }
    
}


node *findf(int X, int  Y, cord ** current, int * xy){
    
    node list[xy[0] * xy[1]];
    int co = 0;
    node * temp;
    temp = malloc( sizeof(node));
    
    if ( X < 9 )
    {
        co++;
        list[co].x          = current[X][Y].x + 1;
        list[co].y          = current[X][Y].y;
        list[co].force      = (int )( current[X][Y].force * 1.4);
        list[co].closedSet  = false;
    }
    //cross
    if( X > 0 )
    {
        co++;
        list[co].x          = current[X][Y].x - 1;
        list[co].y          = current[X][Y].y;
        list[co].force      = (int )( current[X][Y].force * 1.4);
        list[co].closedSet  = false;
    }
    //cros
    if( (X<9) & (Y<9) )
    {
        co++;
        list[co].closedSet  = false;
        list[co].x          = current[X][Y].x + 1;
        list[co].y          = current[X][Y].y + 1;
        list[co].force      = (int )( current[X][Y].force);
    }
    if( (X>0) & (Y>0) )
    {
        co++;
        list[co].closedSet  = false;
        list[co].x          = current[X][Y].x - 1;
        list[co].y          = current[X][Y].y - 1;
        list[co].force      = (int )( current[X][Y].force);
    }
    //cros
    if( X < 9 )
    {
        co++;
        list[co].closedSet  = false;
        list[co].x          = current[X][Y].x;
        list[co].y          = current[X][Y].y + 1;
        list[co].force      = (int )( current[X][Y].force * 1.4);
    }
    if( (Y>0) & (X<9) )
    {
        co++;
        list[co].closedSet  = false;
        list[co].x          = current[X][Y].x + 1;
        list[co].y          = current[X][Y].y - 1;
        list[co].force      = (int )( current[X][Y].force);
    }
    if( (X>0) & (Y<9) )
    {
        co++;
        list[co].closedSet  = false;
        list[co].x          = current[X][Y].x - 1;
        list[co].y          = current[X][Y].y + 1;
        list[co].force      = (int )( current[X][Y].force);
        //cross
    }
    if( Y > 0 )
    {
        co++;
        list[co].closedSet  = false;
        list[co].x          = current[X][Y].x;
        list[co].y          = current[X][Y].y-1;
        list[co].force      = (int )(current[X][Y].force * 1.4);
    }
    temp->force = 65000;
    for ( int i = co; i > 1; i-- )
    {
        if ( temp->force > list[i].force )
        {
            *temp           = list[i];
            temp->closedSet = true;
        }
        if ( list[i].force > list[i-1].force)
        {
            *temp           = list[i-1];
            temp->closedSet = true;
        }
        
        testPrint("%d %d %d \n " ,list[i].x,list[i].y,list[i].force);
    }
    
    return temp;
    
    
}




cord *aStar( cord start, cord end,  cord * nodes , int * xy){
    cord * closedSet = malloc( sizeof( cord)*(xy[0]*xy[1]));
    if (closedSet == NULL) error(0);
    int co;
    co = 0;
    closedSet[0].x = start.x;
    closedSet[0].y = start.y;
    cord  ** current = malloc( xy[0] * (sizeof (cord * )) );
    for ( int i = 0; i < xy[0]; i++)
    {
        current[i] = malloc( xy[1] * (sizeof(cord)) );
    }
    //  initialize values
    initIt( nodes, start, current, xy);
    /*  
        takes an end point on the map (a pointer to a 2D array) and a current location
        finds the best route, then returns a pointer to the  of best    
    */
    co++;
    node *best      = findf( start.x, start.y, current, xy);
    closedSet[co].x = best->x;
    closedSet[co].y = best->y;
    while ( ( co >= 0 ) & ( co < (xy[0] * xy[1]) ) )
    {
        if ( (best->x != end.x) & (best->y != end.y) )
        {
            best = findf( best->x, best->y, current,xy);
        }else if( (best->x = end.x) & (best->y = end.y) )
        {
            break;
        }
        co++;
        closedSet[co].x = best->x;
        closedSet[co].y = best->y;
    }



    //if we find the best F we still need to check that the last path is better then other availbe paths before it... maybe later
    return closedSet;
}
#endif /* functions_h */
