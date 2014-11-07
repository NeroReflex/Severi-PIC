#include "Severi.h"

// BEGIN CONFIG
#pragma config FOSC = XT // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG

int main()
{
  //counter for various uses
  unsigned int a;

  //initialize display
  LCD_Init();
  while(1)
  {
    //clear display
    LCD_Clear();
	
    //set cursor to row 1 and column 2
    LCD_Set_Cursor(1,2);

    //write a string
    LCD_Write_String("Severi-PIC/LCD");

    //keep the display readable for 1s
    __delay_ms(1000);

    //writing other nice stuff
    LCD_Set_Cursor(2,5);
    LCD_Write_String("2014/2015");
    __delay_ms(1000);
    LCD_Clear();
    LCD_Set_Cursor(1,3);
    LCD_Write_String("You'll find");
    LCD_Set_Cursor(2,5);
    LCD_Write_String("meaning");
    __delay_ms(1000);
    LCD_Clear();
    LCD_Set_Cursor(1,5);
    LCD_Write_String("in love");
    __delay_ms(1000);

    //a cycle that will shift the "in love" string left (5 times)
    for(a=0;a!=5;a++)
    {
        __delay_ms(300);
        LCD_Shift_Left();
    }

    //a cycle that will shift the "in love" string right (5 times)
    for(a=0;a!=5;a++)
    {
        __delay_ms(300);
        LCD_Shift_Right();
    }
	
	//keep the display readable for 1s
    __delay_ms(1000);
  }
  return 0;
}