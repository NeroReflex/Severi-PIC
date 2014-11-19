#include "Severi.h"


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
    LCD_printf("Severi-PIC/LCD");

    //keep the display readable for 1s
    __delay_ms(1000);

    //build the version string
    /*char SeveriVersion[10] = "\0";
    sprintf(SeveriVersion, "%d.%d%c", SEVERI_MAJOR_VERSION, SEVERI_MINOR_VERSION, SEVERI_STATUS_VERSION);*/

    //display the version of the severi software library
    LCD_Set_Cursor(2,3);
    LCD_printf("%d.%d%c", SEVERI_MAJOR_VERSION, SEVERI_MINOR_VERSION, SEVERI_STATUS_VERSION);
    __delay_ms(1000);

    //write other nice stuff
    LCD_Clear();
    LCD_Set_Cursor(1,3);
    LCD_printf("You'll find");
    LCD_Set_Cursor(2,5);
    LCD_printf("meaning");
    __delay_ms(1000);
    LCD_Clear();
    LCD_Set_Cursor(1,5);
    LCD_printf("in love");
    __delay_ms(1000);

    //a cycle that will shift the "in love" string left (5 times)
    for(a=0;a!=4;a++)
    {
        __delay_ms(300);
        LCD_Shift_Left();
    }

    //a cycle that will shift the "in love" string right (5 times)
    for(a=0;a!=4;a++)
    {
        __delay_ms(300);
        LCD_Shift_Right();
    }

    //a cycle that will shift the "in love" string right (5 times)
    for(a=0;a!=5;a++)
    {
        __delay_ms(300);
        LCD_Shift_Right();
    }

    //a cycle that will shift the "in love" string right (5 times)
    for(a=0;a!=4;a++)
    {
        __delay_ms(300);
        LCD_Shift_Left();
    }
	
    //keep the display readable for 1s
    __delay_ms(1000);
  }
  return 0;
}