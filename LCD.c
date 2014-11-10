#include "Severi.h"

void LCD_Init(void)
{
    //configuration of the DDRs
    DDR = 0x00;

/*****************************************************************************
* If you need to use the unused pins of the selected port,                   *
* use them freely.                                                           *
* If you don't like to see DDR = 0x00; change with:                          *
*                                                                            *
* TRISBbits_t.TRISB0 = 0;                                                    *
* TRISBbits_t.TRISB1 = 0;                                                    *
* TRISBbits_t.TRISB2 = 0;                                                    *
* TRISBbits_t.TRISB3 = 0;                                                    *
* TRISBbits_t.TRISB4 = 0;                                                    *
* TRISBbits_t.TRISB5 = 0;                                                    *
*                                                                            *
* Please, keep in mind that this solution is a waste of program-memory-space *
* since you can change the DDR of the port to use it in anything else        *
*****************************************************************************/

    //end of the DDRs configuration

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
    LCD_Cmd(0x23);
    LCD_Cmd(0x82);
    LCD_Cmd(0xC0);
    LCD_Cmd(0x60);
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
	//send the first nibble of command
    RS = 0;         // => RS = 0
    LCD_Port(cmd);  // output the data
    EN  = 1;        // => E = 1
    __delay_ms(4);  //wait a huge time
	//we are now sure that the data has been received by the LCD
    EN  = 0;        // => E = 0
	
	//send the second nibble of command
	RS = 0;         // => RS = 0
	LCD_Port(cmd >> 4);  // output the data
	EN  = 1;        // => E = 1
	__delay_ms(4);  //wait a huge time
	//we are now sure that the data has been received by the LCD
	EN  = 0;
}

void LCD_Clear(void)
{
    //send the two commands needed to clear the LCD
    LCD_Cmd(0x10);
    /* LCD_Cmd(0x01); */
}

void LCD_Set_Cursor(char row, char column)
{
    char cursorPosition = 0xC0;
    //the row can be 1 or 2
    if (row == 1) //the selected row is the first one (the upper one)
        cursorPosition = 0x80; //in fact 0x80 is the number corresponding to the first row and column
    //else cursorPosition will have the number corresponding to the second row and first column
    cursorPosition += column - 1; //calculate the number corresponding to the specified position
        //column - 1 is necessary: the first column available is he one corresponding to the number 1
    /* LCD_Cmd(cursorPosition >> 4);
    LCD_Cmd(cursorPosition & 0x0F); */
	LCD_Cmd(((cursorPosition >> 4) & 0x0f) | ((cursorPosition << 4) & 0xf0));
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
    LCD_Cmd(0xC1);
    /* LCD_Cmd(0x0C); */
}

void LCD_Shift_Left(void)
{
    //send the two commands needed to perform the left shift on the LCD
    LCD_Cmd(0x81);
    /* LCD_Cmd(0x08); */
}
