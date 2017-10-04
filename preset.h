//
//  preset.h
//  testts
//
//  Created by Vartan Avny on 12/09/2017.
//  Copyright © 2017 Vartan Avny. All rights reserved.
//

#ifndef preset_h
#define preset_h




#ifdef DEBUG
#define testPrint(x,...) printf(x,__VA_ARGS__)
#else
#define testPrint(x,...) ;
#endif
#define noError 10

#endif /* preset_h */
