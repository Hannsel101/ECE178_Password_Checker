//PasswordCheckerV2
//By: Hannselthill Camacho
//April 23, 2020

#include "sys/alt_stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include <unistd.h>
#include <io.h>
#include <alt_types.h>
#include "sys/alt_irq.h"
#include "altera_up_avalon_character_lcd.h"
#include <altera_up_sd_card_avalon_interface.h>

//Hardware Constant Defines
#define SDCARD 0x800
#define READ_BLOCK 0x11
#define SECTOR 480

//State Scheduler Defines
#define NUM_STATES 4

//Global Variables
unsigned char buffer[16];//Buffer for input
alt_u8 numChars = 0;//Number of characters currently stored in buffer
unsigned char *bufferIndex;//determines what location the user is attempting to change

void initHexDisplays();//clear all the hex displays
void timerSetup(alt_u32 period);//Setup high res timer in milliseconds
void startDelay();//Runs the timer for a set amount of time



void keyInput();
void printBuffer();

//LCD Functions
void displayWelcome();
void promptUsername();
void promptPassword();
void selectionMenu();


//State Machine that gives time slices to each state before switching to the next
void scheduler(alt_u8 *state);

int i = 0;//For testing scheduler during development LEDR
int k = 0;//For testing scheduler during development LEDG
alt_up_character_lcd_dev * char_lcd_dev;//LCD pointer

int main()
{
	//alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");

	if ( char_lcd_dev == NULL)
		alt_printf ("Error: could not open character LCD device\n");
	else
		alt_printf ("Opened character LCD device\n");

	/* Initialize the character display */
	alt_up_character_lcd_init (char_lcd_dev);

	initHexDisplays();
	timerSetup(20);//2ms
	IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start timer

	//Control Variables
	alt_u8 state = 0;
	alt_u8 displayState = 0;

	//main event loop
	while (1)
	{
		  printf("State: %i\n", state);
		  scheduler(&state);

		  switch(state)
		  {
		  	  case(0)://Check for SD Card

			  case(1):
			  	  	  switch(displayState)
			  	  	  {
			  	  	  	  case(0)://Welcome Screen
			  	  	  			  displayWelcome();
			  	  	  	  	  	  break;
			  	  	  	  case(1)://Selection Menu
			  	  	  			  selectionMenu();
			  	  	  	  	  	  break;
			  	  	  	  default:
			  	  	  		  	  printf("Display State Default\n");
			  	  	  }

					  break;
			  case(2):
					  // Initialize the character display
					  //alt_up_character_lcd_init (char_lcd_dev);
					  if(k < 1024)
					    IOWR(LEDS_BASE, 0 , k);
					  else
					    k = 0;
					  ++k;
					  break;
			  case(3):
					  if(i < 256)
					    IOWR(LEDG_BASE, 0, i);
					  else
					    i = 0;
					  ++i;
					  break;
			  default://FOR TESTING NOT ACTUAL CODE TO GO IN THIS STATE
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
	period *= 5000;//Convert from 100ns to cc

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
void scheduler(alt_u8 *state)
{
	if(IORD(HIGH_RES_TIMER_BASE, 0) & 1)
	{
		if(*state <= NUM_STATES)
		{
			*state += 1;//Go to next state
			IOWR(HIGH_RES_TIMER_BASE, 0, 1);//Reset Time out bit
		}
		else
		{
			*state = 0;//Reset the state machine
			IOWR(HIGH_RES_TIMER_BASE, 0, 1);//Reset Time out bit
		}

		switch(*state)
			{
				case 0://Check if SD card is still inserted
					timerSetup(4);//Timer set to 500ns
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
					//printf("Checking SDCARD\n");
					break;
				case 1://display current cursor position and contents on screen
					timerSetup(4);//Timer set to 500ns
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
					//printf("Display Contents on LCD\n");
					break;
				case 2://Poll User input
					timerSetup(100);//Timer set to 10ms
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
					//printf("Polling User Input\n");
					break;
				case 3://Check valid input from user
					timerSetup(20);//Timer set to 2ms
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
					//printf("Checking Input for edge cases\n");
					break;
				default:
					timerSetup(500);//Timer set to 50ms
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
					//printf("In Default for scheduler\n");
			}
	}
	else
	{
		printf("Normal Operation: No context switch.\n");
	}
}
//------------------------------------------------------------------//
void displayWelcome()
{
	//Display the welcome boot up screen
	alt_up_character_lcd_init(char_lcd_dev);
	alt_up_character_lcd_string(char_lcd_dev, "////Password\\\\\\\\");

	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, "\\\\\\\\ Checker ////");
}
//------------------------------------------------------------------//
void promptUsername()
{
	// Write "Enter Username:" in the first row
	alt_up_character_lcd_init (char_lcd_dev);
	alt_up_character_lcd_string(char_lcd_dev, "Enter Username:");
}
//------------------------------------------------------------------//
void promptPassword()
{
	// Write "Enter Password:" in the first row
	alt_up_character_lcd_init (char_lcd_dev);
	alt_up_character_lcd_string(char_lcd_dev, "Enter Password:");
}
//------------------------------------------------------------------//
void selectionMenu()
{

}
//------------------------------------------------------------------//

//------------------------------------------------------------------//

//------------------------------------------------------------------//
