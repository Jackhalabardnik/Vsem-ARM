#include "lcd.h"					// Dołączam moją bibliotekę

int main(void)
{
    LCD_INIT();						// Inicjalizuję wyświetlacz
	char *imie = "Jacek Wojcik";	// Zapisuję swoje imię w zmiennej
	LCD_WRITE(imie);				// Wyświetlam imię na wyświetlaczu
    while (1) 
    {
		asm volatile("nop");		// Wykonuję niekończoną pętlę przez resztę czasu
    }
}

