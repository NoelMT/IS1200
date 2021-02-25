//
//  main.c
//  time4io.c
//
//  Created by Parosh on 2021-02-11.
//

#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw (void)
{

int swish = (PORTD >> 8) & 0xF;


return swish;

}

int getbtns(void){

int butt = (PORTD >> 5) & 0x7;

return butt;
}
