#include "lcd.h"					// Do��czam moj� bibliotek�

int main(void)
{
    LCD_INIT();						// Inicjalizuj� wy�wietlacz
	char *imie = "Jacek Wojcik";	// Zapisuj� swoje imi� w zmiennej
	LCD_WRITE(imie);				// Wy�wietlam imi� na wy�wietlaczu
    while (1) 
    {
		asm volatile("nop");		// Wykonuj� nieko�czon� p�tl� przez reszt� czasu
    }
}

