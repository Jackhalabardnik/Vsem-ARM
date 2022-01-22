#define F_CPU 1000000				// Ustawiam cz�stotliwo�� na zgodn� z zestawem w laboratorium

#include <avr/io.h>					// Do��czam biblioteki do obs�ugi port�w i op�nie�
#include <util/delay.h>

int main(void)
{
	DDRB = 0x01;					// Ustawiam PORTB jako wyj�cie
	PORTB = 0x01;				// W��czam LED
	
	OCR0 = 146;				// ustawiam timer na odliczenie 150ms
	
	TCCR0 |= 0x0D;				// W��czam timer z preskalerem 1/1024 w trybie CTC
	
	while (1)
	{
		if(TIFR & 1 << OCF0)			// Sprawdzam czy timer odliczy� wymagan� ilo�� czasu
		{
			TIFR |= 1 << OCF0;			// Zeruj� flag� por�wniania 
			if(PORTB)					// Je�eli LED jest zapalony 
			{
				PORTB = 0x00;				// Wy��czam LED
				OCR0 = 49;				// ustawiam timer na odliczenie 50ms
			}
			else
			{
				PORTB = 0x01;				// W��czam LED
				OCR0 = 146;				// ustawiam timer na odliczenie 150ms
			}
		}
	}
}

