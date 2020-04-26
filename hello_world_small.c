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
volatile unsigned char buffer[64];//Buffer for input
alt_u8 numChars = 0;//Number of characters currently stored in buffer
unsigned char *bufferIndex;//determines what location the user is attempting to change
volatile short int sdcardStorage;

//Hardware Functions
void initHexDisplays();//clear all the hex displays
void initLEDs();//Clear green and red leds
void timerSetup(alt_u32 period);//Setup high res timer in milliseconds
void startDelay();//Runs the timer for a set amount of time



void keyInput();
void printBuffer();

//LCD Functions
void displayWelcome();
void promptUsername();
void promptPassword();
void selectionMenu();

//SDCard Functions
bool sdcardTest();//Checks if card can access a file and returns true if it can, otherwise false

//State Machine that gives time slices to each state before switching to the next
void scheduler(alt_u8 *state);

int i = 0;//For testing scheduler during development LEDR
int k = 0;//For testing scheduler during development LEDG
alt_up_character_lcd_dev * char_lcd_dev;//LCD pointer
alt_up_sd_card_dev *device_reference = NULL;//SDCARD Pointer

int main()
{

	int connected = 0;
	device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");

	//alt_up_character_lcd_dev * char_lcd_dev;
	// open the Character LCD port
	char_lcd_dev = alt_up_character_lcd_open_dev ("/dev/character_lcd_0");

	if ( char_lcd_dev == NULL)
		alt_printf ("Error: could not open character LCD device\n");
	else
		alt_printf ("Opened character LCD device\n");

	/* Initialize the character display */
	alt_up_character_lcd_init (char_lcd_dev);

	//Initialize PIOs
	initHexDisplays();
	initLEDs();

	timerSetup(2000);//2 seconds for the welcome message
	IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start timer

	//Control Variables
	alt_u8 state = 0;
	alt_u8 displayState = 0;
	alt_u8 sdState = 0;
	bool fileOpened = false;
	bool readOnce = false;

	//Buffers
	volatile unsigned char readBuffer[4][16];//Holds up to four rows of values to output to lcd

	//main event loop
	while (1)
	{
		  scheduler(&state);

		  switch(state)
		  {
		  	  case(0)://SD Card Operations
		  			  switch(sdState)//Current operation to be handled by SDcard
		  			  {
						  case (0)://Check for SDCard
								if ((connected == 0) && (alt_up_sd_card_is_Present()))
								{
								   printf("Card connected.\n");
								   if (alt_up_sd_card_is_FAT16())
								   {
									   printf("FAT16 file system detected.\n");
									   sdState += 1;//Everything checks out move on to next state
								   } else
								   {
									   printf("Unknown file system.\n");
								   }
								   connected = 1;
								}
								else if ((connected == 1) && (alt_up_sd_card_is_Present() == false))
								{
								   printf("Card disconnected.\n");
								   connected = 0;
								}
						  	    break;
						  case(1)://Read from SDcard
								//for(int i=0; (i<16) && (readBuffer[i] != '\n'); ++i)
						  			//printf("readBuffer: %c", readBuffer[0][i]);
						  	  	//printf("\n");
							    break;
		  			  }
		  			  break;
			  case(1):
			  	  	  switch(displayState)
			  	  	  {
			  	  	  	  case(0)://Welcome Screen
			  	  	  			  displayWelcome();
			  	  	  	  	  	  startDelay();
			  	  	  	  	  	  displayState += 1;
			  	  	  	  	  	  break;
			  	  	  	  case(1)://Selection Menu
			  	  	  			  selectionMenu();
			  	  	  	  	  	  break;
			  	  	  	  default:
			  	  	  		  	  break;
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
				  	  if(fileOpened && !readOnce)
				  	  {
				  		printf("readBuffer: ");
				  		for(int i2=0; (i2<64) && (buffer[i2] != -1); ++i2)
				  		{
				  			buffer[i2] = alt_up_sd_card_read(sdcardStorage);
				  		}

				  		for (int i2=0; i2<64 && buffer[i2] != 0xff; ++i2)//buffer[i2] >= 30 && buffer[i2] <= 0x7a ; ++i2)
				  			printf("%c", buffer[i2]);

				  		//for(int i2 = 0; i2 < 16; ++i2)
				  			//printf("%c", alt_up_sd_card_read(sdcardStorage));
				  		printf("\n");
				  		  //printf("%c", alt_up_sd_card_read(sdcardStorage));
				  		//for(int i=0; (i<16) && (buffer[i] != '\n'); ++i)
				  			//readBuffer[0][i] = buffer[i];
				  		readOnce = true;
				  	  }
				  	  else if(!readOnce)
				  	  {
				  		fileOpened = sdcardTest();
				  	  }
				      break;
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
void initLEDs()
{
	IOWR(LEDS_BASE, 0, 0);
	IOWR(LEDG_BASE, 0, 0);
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
					timerSetup(4);//Timer set to 400ns
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
					break;
				case 1://display contents on screen
					timerSetup(4);//Timer set to 400ns
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
					break;
				case 2://Poll User input
					timerSetup(100);//Timer set to 10ms
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
					break;
				case 3://Check valid input from user
					timerSetup(20);//Timer set to 2ms
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
					break;
				default:
					timerSetup(500);//Timer set to 50ms
					IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start the timer in control register
			}
	}
	else
	{
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
	alt_up_character_lcd_init (char_lcd_dev);
}
//------------------------------------------------------------------//
bool sdcardTest()
{
	//alt_up_sd_card_fclose("Testing1.txt");//release contents of file accessed in previous runs
	sdcardStorage = alt_up_sd_card_fopen("Testing.txt", false);
	if(sdcardStorage < 0)
	{
		printf("Failed to access Testing.txt file\n");
		return false;
	}
	else
	{
		printf("Successfully accessed Testing.txt file\n");
		return true;
	}
}
//------------------------------------------------------------------//

//------------------------------------------------------------------//
