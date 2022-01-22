#include <avr/io.h>
#include "lcd.h"

void show_number(int num)		// funkcja wyœwietlaj¹ca numer
{
	LCD_CLEAR();				// czyszczê wyœwietlacz
	char buffer[5];				// tworzê bufor dla funkcji itoa
	itoa(num, buffer, 10);		// przetwarzam kod klawisza na ci¹g znaków
	buffer[4]= '\0';			// dodajê pusty znak na koniec ¿eby utworzyæ poprawny ci¹g znaków w C
	LCD_WRITE(buffer);			// wyœwietlam znak
}

int main(void)
{
	PORTB = 0x01;				// podci¹gam PINB 0 pod zasilanie
	
	LCD_INIT();					// Inicjalizuje wyœiwetlacz
	show_number(0);
	
	TCCR0 |= 0x07;				// W³¹czam timer ustawiaj¹c zród³o zegara jako zbocze narastaj¹ce
	//TCCR0 |= 0x06;				// W³¹czam timer ustawiaj¹c zród³o zegara jako zbocze opadaj¹ce
	
	while (1)
	{
		_delay_ms(200);					// Czekam 200ms
		if(TIFR & 0x01)					// Je¿eli wykryjê przepe³nienie to wy³¹czam timer
		{
			TCCR0 &= 0xFC;				// Wy³¹czam timer
		}
		else
		{
			show_number(TCNT0);			// Je¿eli nie ma przepe³nienia wyœwietlam stan licznika
		}
	}
}

