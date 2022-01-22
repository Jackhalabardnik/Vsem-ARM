#include "lcd.h"					// Do³¹czam moj¹ bibliotekê

int main(void)
{
    LCD_INIT();						// Inicjalizujê wyœwietlacz
	char *imie = "Jacek Wojcik";	// Zapisujê swoje imiê w zmiennej
	LCD_WRITE(imie);				// Wyœwietlam imiê na wyœwietlaczu
    while (1) 
    {
		asm volatile("nop");		// Wykonujê niekoñczon¹ pêtlê przez resztê czasu
    }
}

