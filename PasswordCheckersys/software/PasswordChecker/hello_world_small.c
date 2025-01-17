#include "sys/alt_stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include <unistd.h>
#include <io.h>
#include <alt_types.h>
#include "sys/alt_irq.h"

//Global Variables
unsigned char buffer[16];//Buffer for input
alt_u8 numChars = 0;//Number of characters currently stored in buffer
unsigned char *bufferIndex;//determines what location the user is attempting to change

void initHexDisplays();//clear all the hex displays
void timerSetup(alt_u32 period);//Setup high res timer in milliseconds
void startDelay();//Runs the timer for a set amount of time

void keyInput();
void printBuffer();

int main()
{ 
	initHexDisplays();
	timerSetup(10);//testing 1 second
	int i = 0;
	int k = 0;
	int state = 0;
  while (1)
  {
	  startDelay();

	  if(state) state = 0;
	  else state = 1;

	  switch(state)
	  {
	  case(0):
	  	  if(i < 256)
	  		  IOWR(LEDG_BASE, 0, i);
	  	  else
	  		  i = 0;
	  	  ++i;
	  	  break;
	  case(1):
		  if(k < 1024)
			  IOWR(LEDS_BASE, 0 , k);
		  else
			  k = 0;
	  	  ++k;
	  	  break;
	  default:
		  printf("In default case\n");
	  }
  }
  return 0;
}

void keyInput()
{

}
//------------------------------------------------------------------//
void timerSetup(alt_u32 period)
{
	if(period > 85889)
	{
		period = 85889;
	}
	period *= 50000;//Convert from ms to cc

	//HIGH_RES_TIMER_BASE
	IOWR(HIGH_RES_TIMER_BASE, 1, 8);//Set stop on control bit of timer

	alt_u16 periodIn = period & 0x0FFFF;
	IOWR(HIGH_RES_TIMER_BASE, 2, periodIn);//Set period low

	periodIn = period >> 16;
	IOWR(HIGH_RES_TIMER_BASE, 3, periodIn);//Set period high

	return;
}
//------------------------------------------------------------------//
void startDelay()
{
	IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Set Start on control register
	alt_u8 status;
	do{
		status = IORD(HIGH_RES_TIMER_BASE, 0) & 1;
	}while(!status);
	IOWR(HIGH_RES_TIMER_BASE, 0, 1);//Reset Time out bit
}
//------------------------------------------------------------------//
void initHexDisplays()
{
	//Clear all the displays
	IOWR(HEX_0_BASE, 0, 0xFF);
	IOWR(HEX_1_BASE, 0, 0xFF);
	IOWR(HEX_2_BASE, 0, 0xFF);
	IOWR(HEX_3_BASE, 0, 0xFF);
	IOWR(HEX_4_BASE, 0, 0xFF);
	IOWR(HEX_5_BASE, 0, 0xFF);
	IOWR(HEX_6_BASE, 0, 0xFF);
	IOWR(HEX_7_BASE, 0, 0xFF);
}
//------------------------------------------------------------------//
