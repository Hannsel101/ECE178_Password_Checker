#include "sys/alt_stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include <unistd.h>
#include <io.h>
#include <alt_types.h>
#include "sys/alt_irq.h"

//void interrupt_handler();
void initHexDisplays();//clear all the hex displays
void timerSetup(alt_u32 period);//Setup high res timer
void startDelay();//Runs the timer for a set amount of time
void key_isr(void);
void handle_key_interrupt(void* context);//Handler for Key pushbutton interrupts
static void pio_init();//Initialize parallel input/output interrupts
void randomPattern(alt_u32 segSelect[], alt_u32* garbage);//Random pattern for Hex Displays
void LEDpattern();//Pattern for the red leds on the De2-115 board
void LEDGpattern();//Pattern for the green leds on the De2-115 board

volatile int edge_capture;


int main()
{
	//Setup Timer and Hexdisplays
	timerSetup(12500000);//Initialize the period
	initHexDisplays();//Set all the hex displays to low

	//Setup interrupts
	pio_init();

	while (1);

	return 0;
}
//--------------------------------------------------------------//
//-----------------BEGIN FUNCTION DEFINITIONS--------------------------//
//--------------------------------------------------------------//
static void pio_init()
{
	void* edge_capture_ptr = (void*)&edge_capture;

	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(KEY_0_BASE, 0x0F);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_0_BASE, 0x0);

	alt_irq_register(KEY_0_IRQ, edge_capture_ptr, handle_key_interrupt);

}
//--------------------------------------------------------------//
void handle_key_interrupt(void* context)
{
	volatile int *edge_capture_ptr = (volatile int*) context;

	*edge_capture_ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_0_BASE);
	if(*edge_capture_ptr & 0xF){
		key_isr();
	}
	return;
}
//--------------------------------------------------------------//
void key_isr(void)
{

	//Setup variables
	alt_u32* garbage = (alt_u32*) 0x01020;//Address to start reading for the random pattern
	alt_u8 counter = 20;//used to keep track of which led to light up.
	alt_u8 hexSelector = 6;//used to choose from segSelect list.
	alt_u8 KEYS = 0x0F;//Initialize the keys to their non-pressed state
	alt_u32 period = 3175000;//62.5ms delay
	alt_u32 segSelect [] = {HEX_0_BASE, HEX_1_BASE, HEX_2_BASE, HEX_3_BASE, HEX_4_BASE, HEX_5_BASE, HEX_6_BASE, HEX_7_BASE};//used to select the different segments
	alt_u8 outputPattern = 0b11110111; //Light up only the top segment of the seven segment display


	alt_u8 edgeCap = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_0_BASE);

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY_0_BASE, 0);
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY_0_BASE);

	if((edgeCap & 0x8) == 8)//If key3 is pressed run Hex display pattern
	{
		alt_putstr("KEY 3 has been pressed\n");
		for(int i = 0; i < 15; ++i)
		{
			randomPattern(segSelect, garbage);
			garbage += 0x10;
			startDelay();
		}
		initHexDisplays();//Turn the displays off

	}
	else if((edgeCap & 0x4) == 4)//If key2 is pressed run LEDG pattern
	{
		alt_putstr("KEY 2 has been pressed\n");
		LEDGpattern();
	}
	else if((edgeCap & 0x2) == 2)
	{
		alt_putstr("KEY 1 has been pressed\n");
		LEDpattern();
	}
	else
	{
		alt_putstr("KEY 0 has been pressed\n");
	}

	return;
}
//------------------------------------------------------------------//
void randomPattern(alt_u32 segSelect[], alt_u32* garbage)
{
	//Display garbage values to give the sense of a random pattern
	IOWR(segSelect[0], 0, *garbage);
	IOWR(segSelect[1], 0, *(garbage+1));
	IOWR(segSelect[2], 0, *(garbage+2));
	IOWR(segSelect[3], 0, *(garbage+3));
	IOWR(segSelect[4], 0, *(garbage+4));
	IOWR(segSelect[5], 0, *(garbage+5));
	IOWR(segSelect[6], 0, *(garbage+6));
	IOWR(segSelect[7], 0, *(garbage+7));
}
//------------------------------------------------------------------//
void timerSetup(alt_u32 period)
{
	//HIGH_RES_TIMER_BASE
	IOWR(HIGH_RES_TIMER_BASE, 1, 8);//Set stop on control bit of timer

	alt_u16 periodIn = period & 0x0FFFF;
	IOWR(HIGH_RES_TIMER_BASE, 2, periodIn);//Set period low

	periodIn = period >> 16;
	IOWR(HIGH_RES_TIMER_BASE, 3, periodIn);//Set period high
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
void LEDGpattern()
{
	alt_u8 sequence = 0b10000001;
	alt_u8 origSeq = sequence;

	IOWR(LEDG_BASE, 0, sequence);
	startDelay();

	for(alt_u8 i = 1; i < 8; ++i)
	{
		if(i < 4)//LEDs turning on two at a time
		{
			sequence += (origSeq << i) + (origSeq >> i);
			IOWR(LEDG_BASE, 0, sequence);

		}
		else if(i < 7)//LEDs turning off two at a time
		{
			sequence -= (origSeq << (7-i)) + (origSeq >> (7-i));
			IOWR(LEDG_BASE, 0, sequence);
		}
		else//Final pattern clears the LEDs
		{
			IOWR(LEDG_BASE, 0 , 0);//Clear the LEDs after the pattern finishes
		}
		startDelay();
	}
}
//------------------------------------------------------------------//
void LEDpattern()
{
	alt_u32 sequence = 0x20555;
	alt_u32 leftSeq = 0x20000;
	alt_u32 rightSeq = 0x01;
	IOWR(LEDS_BASE, 0, sequence);
	startDelay();

	for(int k = 0; k < 5; ++k)
	{
		alt_u8 rightCount = 9-k;//Counter to track how many places are needed to shift the LSB LEDs
		alt_u8 endCondition = 13 + k*2;//Condition for the following for loop

		for(alt_u16  i = 1; i < endCondition; ++i)
		{
			if(i < (7+k))//Shifts to the right until it reaches another lit LED
			{
				sequence -= leftSeq >> i;//Shift lone LED to the right
				IOWR(LEDS_BASE, 0, sequence);//output results
			}
			else//Shifts to the left while all other lit LEDs are shoved to the right
			{
				sequence += leftSeq >> (endCondition-i);//Shift the lone LED to the left

				if(rightCount > k)//Shift the right leds over if true
				{
					sequence -= rightSeq << (rightCount);//Shift an led right through subraction without affecting other LEDs
					rightCount -= 2;//Move over two places to shift the next LED
				}
				IOWR(LEDS_BASE, 0, sequence);//Output results
			}
			startDelay();//Timed Delay
		}
	}
}
