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
#include <string.h>

//Global Variables
volatile short int sdcardStorage;
volatile short int usersdcardStorage;
volatile char username [17]="";//16 user inputs + '\0'
volatile char password [17]="";
alt_u8 userIndex = -1;

//Buffers for SD card interaction
volatile char sdBuffer[10][34];//Buffer for holding usernames and passwords
alt_8 numberOfUsers = -1;//Number of rows read from SD card


//Hardware Functions
void initHexDisplays();//clear all the hex displays
void initLEDs();//Clear green and red leds
void timerSetup(alt_u32 period);//Setup high res timer in milliseconds
void startDelay();//Runs the timer for a set amount of time
void displayfail();
void displaypass();




//LCD Functions
void displayWelcome();
void promptUsername(int operation);
void selectionMenu();
void userMenu(int page);


//SDCard Functions
bool checkForSDcard();//Checks if the SD card is inserted or removed.
bool sdcardTest();//Checks if card can access a file and returns true if it can, otherwise false
void writeToSD();
void initReadBuffer();
void readUsers();
bool checkUser();
bool checkPass();
void writefile();
void readfile();

alt_up_character_lcd_dev * char_lcd_dev;//LCD pointer
alt_up_sd_card_dev *device_reference = NULL;//SDCARD Pointer

int main()
{
	//declare variables
	int key_input, release, navigator, page; //handling inputs from pushbuttons.
	int connected = 0;

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

	//Initialize the SD read Buffer character array
	initReadBuffer();


	//Control Variables
	bool fileOpened = false;
	bool readOnce = false;

	//Check for SD Card
	while (connected == 0)
	{
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

	//Read contents from SDCard
	while(1)
	{
		if(fileOpened && !readOnce)
		{
			readUsers();
			readOnce = true;
			break;
		}
		else if(!readOnce)
		{
			fileOpened = sdcardTest();
		}
	}
	printUsers();

	writeToSD(); //testing writing to the SD
/////CLOSE THE OPEN SD CARD FILE
alt_up_sd_card_fclose(sdcardStorage); //close the file and write the data.

	//Welcome Screen
	displayWelcome();
	timerSetup(6000);// delay for the welcome message
	IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start timer
	startDelay();
	navigator = 0;
	page = 0;
	release = 0;
	key_input = 15;
	//Main Event Loop
	while(1)
	{
		//Selection Menu if not already logged in.
		if (navigator == 0)
			selectionMenu();

		while (navigator == 0)
		{ //until an option is picked
			key_input = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //wait for input

			if (key_input == 7 || key_input == 11) //if a valid key is pressed.
			{
				release = key_input;
				while(release != 15){ //wait for the key to be released
				release = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);} //wait for key release
				switch (key_input)
				{
					case 11:
					{
						printf("You pressed Register\n");
						navigator = 2;
						break;
					}
					case 7:
					{
						printf("You pressed Login.\n");
						navigator = 1;
						break;
					}
				}
			} //end IF key_input == 7 or 11;

		}

		while(navigator == 1)//Login Has been selected
		{
			promptUsername(0);//Enter username
			initHexDisplays();//Clear the fail or success when trying again.

			if(checkUser())
			{
				printf("\nValid Username, please enter password.\n");
				promptUsername(1);//Enter Password

				if(checkPass())
				{
					printf("\nSuccess\n");
					displaypass();
					navigator = 3; //display the user menu
					key_input = 15; //clear previous key inputs.
				}
				else
				{
					printf("\nFail! Incorrect Password.\n");
					username[0] = '\0';
					password[0] = '\0';
					displayfail();
					navigator = 0;
				}
			}
			else
			{
				printf("\n\nNot a valid user. Please try again\n");
				username[0] = '\0';
				password[0] = '\0';
				displayfail();
				navigator = 0;
			}

		}

		while (navigator == 2)//Register has been selected.
		{
			promptUsername(0);//Enter username
			if(checkUser())
			{
				printf("\nThat username is already taken. Please enter a different username.\n");
				username[0] = '\0'; //clear the username array
			}
			else
			{
				printf("\nValid Username, please enter a password.\n");
				promptUsername(1);//Enter Password
				navigator = 0;
			}


			//function call here to write username and password to the SD card.

		}

		while(navigator == 3)//User is logged in
		{
		if (!page)
		{
			userMenu(page); //displays page0 of the user menu
			key_input = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //wait for input
			while (key_input == 15)
			{
				key_input = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //wait for input
				release = key_input;
			}
			if (key_input == 7 || key_input == 11 || key_input == 13) //if a valid key is pressed.
			{
				while(release != 15){ //wait for the key to be released
				release = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);} //wait for key release
				switch (key_input)
				{
					case 7:
						{
							//sequence to write data to the sd card.
							printf("\nAsk for user data and write to SD\n");
							writefile();
							break;
						}
					case 11:
					{
						//read data from the SD card
						printf("\nThis should output data user has written to SD\n");
						readfile();
						//readfile();
						break;
					}
					case 13:
					{
						//go to next menu page
						page = 1;
						break;
					}
				}//end switch key_input
			}// end if key_input 7,11,13 page0
		}// if !Page
		if (page) //page 1
				{
					userMenu(page); //displays page1 of the user menu Reset Password/Logout
					key_input = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //wait for input
					while (key_input == 15)
					{
						key_input = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //wait for input
						release = key_input;
					}
					if (key_input == 7 || key_input == 11 || key_input == 13) //if a valid key is pressed.
					{
						while(release != 15){ //wait for the key to be released
						release = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);} //wait for key release
						switch (key_input)
						{
							case 7:
								{
									//Password reset.
									printf("\nPlease enter a new password\n");
									promptUsername(1); //prompts for a password entry
		//****************************//need to write the password to the Sd card.
									alt_up_character_lcd_init(char_lcd_dev);
									alt_up_character_lcd_string(char_lcd_dev, "PASSWORD");

									alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
									alt_up_character_lcd_string(char_lcd_dev, "CHANGED");
									timerSetup(6000);// delay for the logout message
									IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start timer
									startDelay();
									printf("\nPassword Changed Please login again.\n");
									navigator = 0; //reset navigator
									page = 0;	//reset page
									username[0] = '\0'; //clear username
									password[0] = '\0'; //clear password
									break;
								}
							case 11:
							{
								//Logout
								alt_up_character_lcd_init(char_lcd_dev);
								alt_up_character_lcd_string(char_lcd_dev, "LOGOUT");

								alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
								alt_up_character_lcd_string(char_lcd_dev, "SUCCESSFUL");
								timerSetup(6000);// delay for the logout message
								IOWR(HIGH_RES_TIMER_BASE, 1, 4);//Start timer
								startDelay();
								printf("\nYou have been logged out.\n");
								navigator = 0; //reset navigator
								page = 0;	//reset page
								username[0] = '\0'; //clear username
								password[0] = '\0'; //clear password

								break;
							}
							case 13:
							{
								//go to next menu page
								page = 0;
								break;
							}
						}//end switch key_input
					}// end if key_input 7,11,13 page0
				}// if !Page
		} //END while navigator = 3

	}//END MAIN EVENT LOOP

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
void promptUsername(int operation)
{
	//operation = 0 for enter username
	//operation = 1 for enter password


	//	char test[] = "James";
	int	i = 0;
	int k = 0;
	int key_in = 0;
	int release = 0;

	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";

	char userEntry[17] = "";
	userEntry[k] = alphabet[i];
	//username[k] = alphabet[i];

	int done = 0;
	printf("\nUse Key3 for next character.\nUse Key2 for previous character.\n");
	printf("Use Key1 for next input.\nUse Key0 to enter selection. \n\n");

	while (done == 0)
	{
		// Write "Enter Username:" in the first row
		alt_up_character_lcd_init (char_lcd_dev);

		if(!operation)
			alt_up_character_lcd_string(char_lcd_dev, "Enter Username:");
		else
			alt_up_character_lcd_string(char_lcd_dev, "Enter Password:");

		alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
		alt_up_character_lcd_string(char_lcd_dev, userEntry);
		key_in = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //read pushbuttons

		while (key_in == 15)
		{//wait for input
			key_in = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);//read pushbuttons
			release = key_in;
		}

		while(release != 15)
		{ //wait for the key to be released
			release = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);
		} //wait for key release

		switch (key_in)
		{
			case 7:
			{
				if (i<25)
					i = i+ 1;
				else
					i = 0;
				userEntry[k] = alphabet[i];
				break;
			} //end case 0
			case 11:
			{
				if (i>0)
					i = i-1;
				else
					i = 25;
				userEntry[k] = alphabet[i];
				break;
			}//end case 11
			case 13:
			{
				if (k <15)
				{
					k = k+1;
					i = 0;
					userEntry[k] = alphabet[i];
				}
				else
					printf("You have already entered the maximum number of characters.\n");
				break;
			}//end case 13
			case 14:
			{
				userEntry[k+1] = '\0';//Null Terminate the char array
				if(!operation)
				{
					for(int j=0; j<=k+1; ++j)
						username[j] = userEntry[j];
				}
				else
				{
					for(int j=0; j<=k+1; ++j)
						password[j] = userEntry[j];
				}
				done = 1;
				break;
			}
		}//end switch key_in
	} //end while done == 0
}
//------------------------------------------------------------------//

void selectionMenu()
{
	alt_up_character_lcd_init (char_lcd_dev);
	alt_up_character_lcd_string(char_lcd_dev, "3: Login");

	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
	alt_up_character_lcd_string(char_lcd_dev, "2: Register");
}
//------------------------------------------------------------------//
void userMenu(int page)
{
	if (!page)//page0
	{
		printf("Press Key 1 for more options\n");
		alt_up_character_lcd_init (char_lcd_dev);
		alt_up_character_lcd_string(char_lcd_dev, "3: Write file");

		alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
		alt_up_character_lcd_string(char_lcd_dev, "2: Read file");
	}
	else
	{
		printf("Press Key 1 for previous options\n");
		alt_up_character_lcd_init (char_lcd_dev);
		alt_up_character_lcd_string(char_lcd_dev, "3: Change Pswd");

		alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
		alt_up_character_lcd_string(char_lcd_dev, "2: Logout");
	}
}

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
void writeToSD()
{
	char buff[23] = "This is what i wrote\n";
	alt_up_sd_card_write(sdcardStorage, "\n");
	for(int i2=0; i2<22; ++i2)
	{
		alt_up_sd_card_write(sdcardStorage, buff[i2]);
	}
	alt_up_sd_card_fclose(sdcardStorage); //close the file and write the data.
}
//------------------------------------------------------------------//
void initReadBuffer()
{
	for(int i=0; i<10; ++i)
	{
		sdBuffer[i][0] = '\0';
	}
}
//------------------------------------------------------------------//
void readUsers()
{
	char extractChar;
	alt_u8 row = 0;
	alt_u8 col = 0;
	extractChar = alt_up_sd_card_read(sdcardStorage);//Read first character from sdcard

	while(extractChar > -1)//End of file has been reached
	{
		if((extractChar == 0x0d) || (col > 33))//Setup the next row of input
		{
			if(col == 0)
			{
				sdBuffer[row][col] = '\0';
			}
			else
			{
				numberOfUsers += 1;//Increment entries read from sdcard
				sdBuffer[row][col] = '\0';//Terminate the string
				row += 1;
				col = 0;
			}
		}
		else//Store char into buffer
		{
			sdBuffer[row][col] = extractChar;
			col += 1;
		}
		extractChar = alt_up_sd_card_read(sdcardStorage);//Read another character from sdcard
		if(extractChar == '\n')
			extractChar = 0x0d;
	}

}
//------------------------------------------------------------------//
bool checkUser()//verifies that a username exists
{

	for(int i = 0; i <=numberOfUsers; ++i)
	{
		for(int k=0; k<16; ++k)//sdBuffer[i][k] != '\0'; ++k)
		{
			if((username[k] == '\0') && (sdBuffer[i][k] == ' '))//if end of username reached and whitespace reached
			{
					userIndex = i;
					return true;//Found a match
			}
			else if(sdBuffer[i][k] != username[k])
				break;
		}
	}
	return false;
}
//------------------------------------------------------------------//
bool checkPass()
{
	for(int i=0; i<37; ++i)
	{

		sdBuffer[userIndex][i];

		if(sdBuffer[userIndex][i] == ' ')
		{
			++i;
			for(int k=0; k<16; ++k, ++i)
			{
				if(password[k] == '\0')
				{
					if(sdBuffer[userIndex][i] == '\n' || sdBuffer[userIndex][i] < 0x30 || sdBuffer[userIndex][i] > 0x7a)
					{
						return true;
					}
					return false;
				}
				else if(sdBuffer[userIndex][i] != password[k])
				{
					return false;
				}

			}
		}
	}
	return true;
}
//------------------------------------------------------------------//
void printUsers()
{

	printf("\n------SDCARD Contents-----\n");
	for(int i = 0; i<=numberOfUsers; ++i)
	{
		printf("User%i: ", i);
		for(int k = 0; sdBuffer[i][k] != '\0'; ++k)
		{
			printf("%c",sdBuffer[i][k]);
		}
		printf("\n");
	}
	printf("--------------------------\n");
}
//----------------------------------------------------------------------//
void writefile()
{
	int	i = 0;
	int k = 0;
	int L = 0;
	int key_in = 0;
	int release = 0;
	int done = 0;
	char userdata[17]="";
	char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
	char userbuff[17] = "";
	char temp[17] = "";
	alt_up_character_lcd_init (char_lcd_dev);
	alt_up_character_lcd_string(char_lcd_dev, "Enter Data:");
	userbuff[k] = alphabet[i];
	while(done == 0)
	{
	alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
			alt_up_character_lcd_string(char_lcd_dev, userbuff);
			key_in = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //read pushbuttons

			while (key_in == 15)
			{//wait for input
				key_in = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);//read pushbuttons
				release = key_in;
			}

			while(release != 15)
			{ //wait for the key to be released
				release = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);
			} //wait for key release

			switch (key_in)
			{
				case 7:
				{
					if (i<25)
						i = i+ 1;
					else
						i = 0;
					userbuff[k] = alphabet[i];
					break;
				} //end case 0
				case 11:
				{
					if (i>0)
						i = i-1;
					else
						i = 25;
					userbuff[k] = alphabet[i];
					break;
				}//end case 11
				case 13:
				{
					if (k <15)
					{
						k = k+1;
						i = 0;
						userbuff[k] = alphabet[i];
					}
					else
						printf("You have already entered the maximum number of characters.\n");
					break;
				}//end case 13
				case 14:
				{

					userbuff[k+1] = '\n';//Null Terminate the char array
					userbuff[k+2] = '\0';//Null Terminate the char array
					for(int L=0; L<=k+2; ++L)
						userdata[L] = userbuff[L];
					done = 1;
					break;
				}
			}//end switch key_in
		} //end while done == 0


	////this section to avoid username global variable being changed. Copy username to temp
	for(int j=0; j<=17; ++j)
		temp[j] = username[j];
	///////////////////////////////////////////////////////////////
	char *file=temp;
	char *ext = ".txt";
	char *filename;
	filename = malloc(strlen(file)+1+4);//make space for the new string
	strcpy(filename,file); //copy name into the new var
	strcat(filename, ext); //add the extension.

//	strncat(filename, ext,4);

	printf("The name of the file is %s: ", filename); //print the string for debug.
//check if the file already exists.
	usersdcardStorage = alt_up_sd_card_fopen(filename, false);
	if(usersdcardStorage < 0) //if it doesn't exist create it
	{
		printf("Created the file %s\n", filename);
		usersdcardStorage = alt_up_sd_card_fopen(filename, true); //create the users file
	}
	size_t length = strlen(userdata); //get the length of userdata
	printf("Data entered was: %s\n", userdata); //echo the input for debug
	alt_up_sd_card_write(usersdcardStorage, "\n"); //write the data to the buffer.
		for(int i2=0; i2<length+1; ++i2)
		{
			alt_up_sd_card_write(usersdcardStorage, userdata[i2]);
		}
		alt_up_sd_card_fclose(usersdcardStorage); //close and write to sd card
		filename = "\0"; //reset the filename
	//sdBuffer[i][0] = '\0';

}
//--------------------------------------------------------------//
void readfile()
{
	char extractChar;
	char FRDBuffer[17];
	char temp[17]="";
	int key_in = 15;
	int release = 0;
	alt_u8 row = 0;
	alt_u8 col = 0;
	for(int j=0; j<=17; ++j)
			temp[j] = username[j];
		///////////////////////////////////////////////////////////////
		char *file=temp;
		char *ext = ".txt";
		char *filename;
		filename = malloc(strlen(file)+1+4);//make space for the new string
		strcpy(filename,file); //copy name into the new var
		strcat(filename, ext); //add the extension.
		usersdcardStorage = alt_up_sd_card_fopen(filename, false);
		if(usersdcardStorage < 0) //if it doesn't exist
		{
			printf("No user file found%s\n", filename);
			alt_up_character_lcd_init (char_lcd_dev);
			alt_up_character_lcd_string(char_lcd_dev, "No User");

			alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
			alt_up_character_lcd_string(char_lcd_dev, "File Found");
		}
		else
		{
	extractChar = alt_up_sd_card_read(usersdcardStorage);//Read first character from sdcard
		while(extractChar > -1)//End of file has been reached
		{
			FRDBuffer[col] = extractChar;
			col += 1;

		extractChar = alt_up_sd_card_read(usersdcardStorage);//Read another character from sdcard
		if(extractChar == '\n')
			extractChar = 0x0d;

		}
		alt_up_character_lcd_init (char_lcd_dev);
		alt_up_character_lcd_string(char_lcd_dev, "File Content");

		alt_up_character_lcd_set_cursor_pos(char_lcd_dev, 0, 1);
		alt_up_character_lcd_string(char_lcd_dev, FRDBuffer);
	}
	printf("Press any key to continue.\n");
	key_in = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE); //read pushbuttons
	while (key_in == 15)
	{//wait for input
		key_in = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);//read pushbuttons
		release = key_in;
	}

	while(release != 15)
	{ //wait for the key to be released
		release = IORD_ALTERA_AVALON_PIO_DATA(KEY_0_BASE);
	} //wait for key release
	alt_up_sd_card_fclose(usersdcardStorage); //close and write to sd card
}
