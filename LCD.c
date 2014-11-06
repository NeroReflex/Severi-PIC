#include "lcd.h"

void LCD_Port(char a)
{
    if(a & 1)
        D4 = 1;
    else
        D4 = 0;
		
    if(a & 2)
        D5 = 1;
    else
        D5 = 0;
		
    if(a & 4)
        D6 = 1;
    else
        D6 = 0;
		
    if(a & 8)
        D7 = 1;
    else
        D7 = 0;
}

void LCD_Cmd(char cmd)
{
    RS = 0;             // => RS = 0
    LCD_Port(cmd);        // output the data
    EN  = 1;            // => E = 1
    __delay_ms(4);      //wait a huge time
	//we are now sure that the data has been received by the LCD
    EN  = 0;             // => E = 0
}

void LCD_Clear(void)
{
	//send the two commands needed to clear the LCD
    LCD_Cmd(0x00);
    LCD_Cmd(0x01);
}

void LCD_Set_Cursor(char riga, char column)
{
    char temp,z,y;
    //the row can be 1 or 2
	if (row) //row == 1
    { //the selected row is the first one (the upper one)
		temp = 0x80 + column - 1;
		z = temp >> 4;
		y = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(y);
	} else { //the selected row is the second one
		temp = 0xC0 + column - 1;
		z = temp >> 4;
		y = temp & 0x0F;
		LCD_Cmd(z);
		LCD_Cmd(y);
    }
}

void LCD_Init(void)
{
	//configuration of the DDR
    DDR = 0x00;
	
	/**************************************************************************
	* If you need to use the unused pins of the selected port,                *
	* use them freely.                                                        *
	* If you don't like to see DDR = 0x00; change with:                       *
	*                                                                         *
	* TRISBbits_t.TRISB0 = 0;                                                 *
	* TRISBbits_t.TRISB1 = 0;                                                 *
	* TRISBbits_t.TRISB2 = 0;                                                 *
	* TRISBbits_t.TRISB3 = 0;                                                 *
	* TRISBbits_t.TRISB4 = 0;                                                 *
	* TRISBbits_t.TRISB5 = 0;                                                 *
	*                                                                         *
	* Please, keep in mind that this solution is program-memory-space wasting *
	* since you can change the DDR of the port to use it in anything else     *
	**************************************************************************/
	//end of the DDR configuration
	
    LCD_Port(0x00);
    __delay_ms(20); //wait until the display has finished its operations (use 22ms or 21ms if 20 is not enough)
    LCD_Cmd(0x03);
    __delay_ms(5); //wait until the display has finished its operations (use 5ms or 6ms if 5 is not enough)
    LCD_Cmd(0x03);
    __delay_ms(10); //wait until the display has finished its operations (use 11ms or 12ms if 9 is not enough)
    LCD_Cmd(0x03);
    LCD_Cmd(0x02);
    LCD_Cmd(0x02);
    LCD_Cmd(0x08);
    LCD_Cmd(0x00);
    LCD_Cmd(0x0C);
    LCD_Cmd(0x00);
    LCD_Cmd(0x06);
}

void LCD_Write_Char(char a)
{
    char temp,y;
    temp = a & 0x0F;    //prepare to transfer the first nibble
    y = a & 0xF0;
    RS = 1;             // => RS = 1
    LCD_Port(y>>4);     //transfer the fist nibble
    EN = 1;             // => EN = 1
    __delay_us(40);     //wait an amount of time needed to be sure the pic has finished to store the sent data
    EN = 0;             // => EN = 0
    LCD_Port(temp);     //transfer the second nibble
    EN = 1;             // => EN = 1
    __delay_us(40);     //wait an amount of time needed to be sure the pic has finished to store the sent data
    EN = 0;             // => RS = 0
}

void LCD_Write_String(char* testo)
{
    /*for (int i=0; strlen(testo); i++)*/ //use this cycle if there is a strlen somewhere in your code
    
	for (int i=0; testo[i] != (char)0x00; i++) //start from the fist character of the string and while the current character isn't a string terminator (END OF STRING)
        LCD_Write_Char(testo[i]); //write the current character
	//and then make the current character the following character
}

void LCD_Shift_Right(void)
{
	//send the two commands needed to perform the right shift to the LCD
    LCD_Cmd(0x01);
    LCD_Cmd(0x0C);
}

void LCD_Shift_Left(void)
{
	//send the two commands needed to perform the left shift to the LCD
    LCD_Cmd(0x01);
    LCD_Cmd(0x08);
}
