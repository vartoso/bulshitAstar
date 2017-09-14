//
//  preset.h
//  testts
//
//  Created by Vartan Avny on 12/09/2017.
//  Copyright © 2017 Vartan Avny. All rights reserved.
//

#ifndef preset_h
#define preset_h

#ifndef MAPSIZE
#define MAPSIZE 100
#endif

#ifdef DEBUG
#define testPrint(x,...) printf(x,__VA_ARGS__)
#else
#define testPrint(x,...) ;
#endif


#endif /* preset_h */

