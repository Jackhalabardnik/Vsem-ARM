#include <avr/io.h>
#include "lcd.h"

void show_number(int num)		// funkcja wy�wietlaj�ca numer
{
	LCD_CLEAR();				// czyszcz� wy�wietlacz
	char buffer[5];				// tworz� bufor dla funkcji itoa
	itoa(num, buffer, 10);		// przetwarzam kod klawisza na ci�g znak�w
	buffer[4]= '\0';			// dodaj� pusty znak na koniec �eby utworzy� poprawny ci�g znak�w w C
	LCD_WRITE(buffer);			// wy�wietlam znak
}

int main(void)
{
	PORTB = 0x01;				// podci�gam PINB 0 pod zasilanie
	
	LCD_INIT();					// Inicjalizuje wy�iwetlacz
	show_number(0);
	
	TCCR0 |= 0x07;				// W��czam timer ustawiaj�c zr�d�o zegara jako zbocze narastaj�ce
	//TCCR0 |= 0x06;				// W��czam timer ustawiaj�c zr�d�o zegara jako zbocze opadaj�ce
	
	while (1)
	{
		_delay_ms(200);					// Czekam 200ms
		if(TIFR & 0x01)					// Je�eli wykryj� przepe�nienie to wy��czam timer
		{
			TCCR0 &= 0xFC;				// Wy��czam timer
		}
		else
		{
			show_number(TCNT0);			// Je�eli nie ma przepe�nienia wy�wietlam stan licznika
		}
	}
}

