/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */
#include <stdio.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
//#define  period ((80000000 )) //klock frekvensen kittet är 80 Mhz och vi vill ha en tiondels sekund vilket get 8 mil perioder

#define  period ((80000000 / 256) / 10); // 80 mil ger ut en sekund, så talet divideras med 10 så vi får en period på 0,1 sekunder
											//	prescale med 256 eftersom vi bara har 16 bitar så tal större än 2^16 måste delas upp i mindre bitar sedan köras igenom loop

int mytime = 0x0000;
int timecount = 0;
char textstring[] = "text, more text, and even more text!";
volatile int* eport = (volatile int*) 0xbf886110;
 volatile int* led = (volatile int*) 0xbf886100;
 int riktning = 0; //0 är boll går mot <- och 1 är boll går mot -> 

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}
void test( void ){
	if (riktning) {
		*eport = *eport / 2;
	} else {
		*eport = *eport * 2;	
	}
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	
	
	
	*led = *led & 0xff00; //ledsen till 1
	
 
    TRISDSET = 0x0FE0; //SÄTTER KNAPPARNA OCH SWTICHES TILL INPUTS
	
	//TIMER START VÄRDEN 
	PR2 = period;  // timern kommer köra tills den nått perioden vilket e lika med en tiondels  sekund
	T2CONSET = 0x70; // prescale till 1:256
	T2CONSET = 0x8000; // STARTAR TIMERN
	   *eport =  2;
	
	
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
	int swish = getsw();
	int btn = getbtns();
		
	while((*eport <= 128) && (*eport >= 0 ){
	if((IFS(0) & 0x100) ){
	  
	  TMR2 = 0; // startar om timern
	  IFSCLR(0) = 0x100; // CLR på bit 8 av IFS alltså sätter flaggan till 0
	  if( (*eport == 128) && (btn == 4)){
		  riktning = 1;
	  }
	  else if ((*eport == 1) && (btn == 4)){
		  riktning = 0;
	  }
	  test();
	
    //*eport = *eport + 0x1; //ökar portE med 1
		}
	}
	
	 
	
	
	
	/*
	if((IFS(0) & 0x100) && (*eport < 128) ){
		TMR2 = 0; // startar om timern
	  IFSCLR(0) = 0x100; // CLR på bit 8 av IFS alltså sätter flaggan till 0
		*eport =  *eport * 0x2;
	}
	if((IFS(0) & 0x100) && (*eport > 128) ){
		TMR2 = 0; // startar om timern
		IFSCLR(0) = 0x100; // CLR på bit 8 av IFS alltså sätter flaggan till 0
		*eport =  *eport / 0x2;
	}
	*/

	 


}


/*
   volatile int* eport = (volatile int*) 0xbf886110;
   // *eport = 0x0;
	
	
	
    int butt = getbtns();
    int swish = getsw();
    
 
   
    //btn 3
    if (butt == 1 || butt == 3 || butt == 5 || butt == 7){
        mytime = mytime & 0xFF0F;
        mytime = (swish << 4) | mytime;
        
    }
        //btn 3
    if (butt == 2 || butt == 3 || butt == 6 || butt == 7){
        mytime = mytime & 0xF0FF;
        mytime = (swish << 8) | mytime;
        
    }
    // btn 4
    if (butt == 4 || butt == 5 || butt == 6 || butt == 7){
        mytime = mytime & 0x0FFF;
        mytime = (swish << 12) | mytime;
    }
	
    
     // delay( 1000 );


while (timecount != 10){
	
  if((IFS(0) & 0x100) ){
	  
	  TMR2 = 0; // startar om timern
	  IFSCLR(0) = 0x100; // CLR på bit 8 av IFS alltså sätter flaggan till 0
	  timecount++; // ökar på counten med 1
	  /*
	   display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
    *eport = *eport + 0x1; //ökar portE med 1
	}
  }
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
    *eport = *eport + 0x1; //ökar portE med 1
*/