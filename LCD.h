#ifndef __LCD_SEVERI__
#define __LCD_SEVERI__

#include "Severi.h"

/*****************************************************************
* change the I/O data lines if you aren't not using a demo-board *
* according to your own configuration                            *
*****************************************************************/
#define RS RB5
#define EN RB4
#define D4 RB0
#define D5 RB1
#define D6 RB2
#define D7 RB3
#define DDR TRISB
/* don't forget to change the DDR initialization inside the subroutine LCD_Init(void) !!! */

//LCD Functions Developed by electroSome


//Internal use only
void LCD_Port(char); //avoid to use this subroutine if it is unnecessary to send a command to the LCD without waiting the LCD to complete its internal operations
// ! BEWARE ! Use LCD_Cmd instead


//Gives a command to the LCD. See datasheet for a list of available commands
void LCD_Cmd(char);

//Clears the content of the LCD (memory and view)
void LCD_Clear(void);

//Moves the cursor of the LCD display
void LCD_Set_Cursor(char, char);

//Initializes the LCD and the DDR of the PIC
void LCD_Init(void);

//Writes a single character
void LCD_Write_Char(char);

//Splits the string in characters and then print them one by one
void LCD_Write_String(char*);

//Moves each character on the LCD to its right position
void LCD_Shift_Right(void);

//Moves each character on the LCD to its left position
void LCD_Shift_Left(void);

#endif // __LCD_SEVERI__
