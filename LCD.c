#include "Severi.h"

void LCD_Init(void)
{

    LCD_Port(0x00);
    __delay_ms(20); //wait until the display has finished its operations (use 22ms or 21ms if 20 is not enough)
	RS = 0;         // => RS = 0
    LCD_Port(0x03);  // give the init command
    EN  = 1;        // => E = 1
    __delay_ms(4);  //wait a huge time
	//we are now sure that the data has been received by the LCD
    EN  = 0;        // => E = 0
    __delay_ms(5); //wait until the display has finished its operations (use 5ms or 6ms if 5 is not enough)
    RS = 0;         // => RS = 0
    LCD_Port(0x03);  // give the init command
    EN  = 1;        // => E = 1
    __delay_ms(4);  //wait a huge time
	//we are now sure that the data has been received by the LCD
    EN  = 0;        // => E = 0
    __delay_ms(10); //wait until the display has finished its operations (use 11ms or 12ms if 9 is not enough)

    LCD_Cmd(0x32);
    LCD_Cmd(0x28);
    LCD_Cmd(0x0C);
    LCD_Cmd(0x06);
}

void LCD_Port(char nibbleOfData)
{
    /*************************************************************
    * Sends the nibble to the LCD                                *
    * The MSB bit of the data to send is the MSB of nibbleOfData *
    *                                                            *
    *************************************************************/

    if(nibbleOfData & 1)
        D4 = 1;
    else
        D4 = 0;

    if(nibbleOfData & 2)
        D5 = 1;
    else
        D5 = 0;

    if(nibbleOfData & 4)
        D6 = 1;
    else
        D6 = 0;

    if(nibbleOfData & 8)
        D7 = 1;
    else
        D7 = 0;
}



void LCD_Cmd(char cmd)
{
    //good tutorial on commands http://www.circuitstoday.com/a-note-on-character-lcd-displays



	//send the first nibble of command
    RS = 0;         // => RS = 0
    LCD_Port(cmd >> 4);  // output the data
    EN  = 1;        // => E = 1
    __delay_ms(4);  //wait a huge time
	//we are now sure that the data has been received by the LCD
    EN  = 0;        // => E = 0

	//send the second nibble of command
	RS = 0;         // => RS = 0
	LCD_Port(cmd);  // output the data
	EN  = 1;        // => E = 1
	__delay_ms(4);  //wait a huge time
	//we are now sure that the data has been received by the LCD
	EN  = 0;
}

void LCD_Clear(void)
{
    //send the two commands needed to clear the LCD
    LCD_Cmd(0x01);
}

void LCD_Set_Cursor(unsigned char row, unsigned char column)
{
	//choose one of the possibles row
	row = (row - 1) % 4;
	
    char cursorPosition = 0x00;
    //the row can be 1, 2, 3 or 4, this is a 16x4 LCD display
    switch (row) //select the row
        case 0: cursorPosition = 0x80;
				break;
		case 1: cursorPosition = 0xC0;
				break;
		case 2: cursorPosition = 0x94;
				break;
		case 3: cursorPosition = 0xD4;
				break;
	
    //else cursorPosition will have the number corresponding to the second row and first column
    cursorPosition += column - 1; //calculate the number corresponding to the specified position
        //column - 1 is necessary: the first column available is he one corresponding to the number 1
    LCD_Cmd(cursorPosition);
}

void LCD_Write_Char(char toBeDisplayed)
{
    char firstNibble, secondNibble;
    firstNibble = toBeDisplayed & 0x0F;         //prepare the first nibble to be send
    secondNibble = (toBeDisplayed & 0xF0) >> 4; //prepare the second nibble to be send
    RS = 1;                                     // => RS = 1
    LCD_Port(secondNibble);                     //transfer the fist nibble
    EN = 1;                                     // => EN = 1
    __delay_us(40);                             //wait an amount of time needed to be sure the pic has finished to store the sent data
    EN = 0;                                     // => EN = 0
    LCD_Port(firstNibble);                      //transfer the second nibble
    EN = 1;                                     // => EN = 1
    __delay_us(40);                             //wait an amount of time needed to be sure the pic has finished to store the sent data
    EN = 0;                                     // => RS = 0
}

void LCD_Write_String(char* text)
{
    /*for (int i=0; strlen(testo); i++)*/ //use this cycle if there is a strlen somewhere in your code

    for (int i=0; text[i] != /*(char)0x00*/ '\0'; i++) //start from the fist character of the string and while the current character isn't a string terminator (END OF STRING)
        //write the current character
        LCD_Write_Char(text[i]);
	//and then make the current character the following character
}

void LCD_Shift_Right(void)
{
    //send the two commands needed to perform the right shift on the LCD
    LCD_Cmd(0x1C);
}

void LCD_Shift_Left(void)
{
    //send the two commands needed to perform the left shift on the LCD
    LCD_Cmd(0x18);
}


void LCD_Power(unsigned char power_status){
    //also cursor and cursor blinking can be enabled here, but not implemented
    //command sent is 0b00001DCB where D is display on or off,C is cursor and B cursor blink

    if (power_status != true )
        LCD_Cmd(0b00001100);
    else
        LCD_Cmd(0b00001000);
}

void LCD_Upload_Custom_Char(unsigned char *pixelArray, unsigned char position)
{
	//positions start from 0 to 8
	position = position % 9;

    //use this tool to create the array http://www.quinapalus.com/hd44780udg.html
    //it is suggested that you write the array in the following manner:
    //   const unsigned char MyCustomChar[8] = {0x00,0x01,0x02,0x13,0x14,0x05,0x06,0x07,0x08}

    
    LCD_Cmd(0x40 + position*8); //send new char command starting from position
    for(unsigned char i=0; i!=9; i++)
        LCD_Write_Char(pixelArray[i]);
	
	//I think this is not necessary (try commenting it)
	LCD_Set_Cursor(1,1);
}

void LCD_Write_Custom_Char(unsigned char position)
{
	//positions start from 0 to 8
	position = position % 9;
	
	//write the custom character
	LCD_Write_Char(position);
}

void LCD_printf_position(char row, char column, char *fmt, ...)
{
    va_list va;
    va_start(va,fmt);

    //move the cursor
    LCD_Set_Cursor(row, column);
    LCD_printf(fmt, va);
}