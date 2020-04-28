//PasswordCheckerV2
//By: Hannselthill Camacho and James Dols
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


//Global Variables
volatile short int sdcardStorage;

//Hardware Functions
void initHexDisplays();//clear all the hex displays
void initLEDs();//Clear green and red leds
void timerSetup(alt_u32 period);//Setup high res timer in milliseconds
void startDelay();//Runs the timer for a set amount of time
void displayfail();
void displaypass();


//LCD Functions
void displayWelcome();
void promptUsername();
void promptPassword();
void selectionMenu();

//SDCard Functions
bool sdcardTest();//Checks if card can access a file and returns true if it can, otherwise false

alt_up_character_lcd_dev * char_lcd_dev;//LCD pointer
alt_up_sd_card_dev *device_reference = NULL;//SDCARD Pointer

int main()
{
	//declare varialbes
	int key_input, release, navigator = 0; //handling inputs from pushbuttons.
	int connected = 0;
	char username [15]="";


	device_reference = alt_up_sd_card_open_dev("/dev/Altera_UP_SD_Card_Avalon_Interface_0");

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



	//Control Variables
	bool fileOpened = false;
	bool readOnce = false;

	//Buffers
	volatile unsigned char readBuffer[4][16];//Holds up to four rows of values to output to lcd


//Check for SD Card
	while (connected == 0){
	if ((connected == 0) && (alt_up_sd_card_is_Present()))
								{
								   printf("Card connected.\n");
								   if (alt_up_sd_card_is_FAT16())
								   {
									   printf("FAT16 file system detected.\n");
								   } else
								   {
									   printf("Unknown file system.\n");
								   }
								   connected = 1;
								}
								else if ((connected == 1) && (alt_up_sd_card_is_Present() == false))
								{
								   printf("Card disconnected.\n");
								   printf("Please insert an SD card\n");
								   connected = 0;
								}
	}


//Welcome Screen
displayWelcome();
timerSetup(4000);//2 seconds for the welcome message
IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start timer
startDelay();

//Selection Menu
selectionMenu();
//wait for input/poll keys
	while (navigator == 0)
	{ //until an option is picked
		key_input = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //wait for input
	if (key_input == 7 || key_input == 11) //if a valid key is pressed.
	{
	release = key_input;
	while(release != 15){ //wait for the key to be released
	release = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);} //wait for key release
	switch (key_input){
		case 11:{
			printf("You pressed Login\n");
			navigator = 2;
			break;
	}
		case 7:{
			printf("You pressed Register.\n");
			navigator = 1;
			break;
		}
		}
	} //end IF key_input == 8 or 4;

	}
	promptUsername();
	while (navigator == 1);{
		//until an option is picked
				key_input = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //wait for input
			if (key_input == 7 || key_input == 11) //if a valid key is pressed.
			{
			release = key_input;
			while(release != 15){ //wait for the key to be released
			release = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);} //wait for key release
				switch (key_input){
		case 11:{
			printf("You pressed a key\n");
			navigator = 0;
			break;
	}
		case 7:{
			printf("You pressed a key.\n");
			navigator = 0;
			break;
		}
		}
	}//end IF KEY
	}
	return 0;
}
///////////END MAIN ////////////////
/*************************************/
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
void displaypass()
{
	//Display SUCCESS

	IOWR_ALTERA_AVALON_PIO_DATA(HEX_6_BASE,0b00010010); //display the S
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_5_BASE,0b01000001); //display the U
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_4_BASE,0b01000110); //display the C
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_3_BASE,0b01000110); //display the C
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_2_BASE,0b00000110); //display the E
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_1_BASE,0b00010010); //display the S
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_0_BASE,0b00010010); //display the S
}
//------------------------------------------------------------------//
void displayfail()
{
	//Display FAIL
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_3_BASE,0b00001110); //display the F
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_2_BASE,0b00001000); //display the A
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_1_BASE,0b01001111); //display the I
	IOWR_ALTERA_AVALON_PIO_DATA(HEX_0_BASE,0b01000111); //display the L
}
//------------------------------------------------------------------//
void initLEDs()
{
	IOWR(LEDS_BASE, 0, 0);
	IOWR(LEDG_BASE, 0, 0);
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
//	char test[] = "James";
int	i,k,key_in, release = 0;

	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
	char username[16] = "";//temporary username
	username[k] = alphabet[i];
	int done = 0;
	printf("Use Key3 for next character.\nUse Key2 for previous character.\n");
	printf("Use Key2 for next input.\nUse Key1 to enter selection. \n");
	while (done == 0){
	// Write "Enter Username:" in the first row
	alt_up_character_lcd_init (char_lcd_dev);
	alt_up_character_lcd_string(char_lcd_dev, "Enter Username:");

	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, username);
	key_in = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //read pushbuttons
		while (key_in == 15){//wait for input
			key_in = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);//read pushbuttons
			release = key_in;
		}
		while(release != 15){ //wait for the key to be released
			release = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);} //wait for key release
		switch (key_in){
			case 7: {
				if (i<25)
					i = i+ 1;
				else
					i = 0;
				username[k] = alphabet[i];
				break;
			} //end case 0
			case 11:{
				if (i>0)
					i = i-1;
				else
					i = 25;
				username[k] = alphabet[i];
				break;
			}//end case 11
			case 13:{
				if (k <15){
					k = k+1;
					i = 0;
					username[k] = alphabet[i];
				}
				else
					printf("You have already entered the maximum number of characters.\n");
				break;
			}//end case 13
			case 14:{
				done = 1;
				break;
			}
		}//end switch key_in
	} //end while done == 0

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
	alt_up_character_lcd_string(char_lcd_dev, "1: Login");

	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, "2: Register");
}
//------------------------------------------------------------------//

//------------------------------------------------------------------//
bool sdcardTest()
{
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
