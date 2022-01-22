#define F_CPU 1000000				// Ustawiam czêstotliwoœæ na zgodn¹ z zestawem w laboratorium

#include <avr/io.h>					// Do³¹czam biblioteki do obs³ugi portów i opóŸnieñ
#include <util/delay.h>

int main(void)
{
	DDRB = 0x01;					// Ustawiam PORTB jako wyjœcie
	PORTB = 0x01;				// W³¹czam LED
	
	OCR0 = 146;				// ustawiam timer na odliczenie 150ms
	
	TCCR0 |= 0x0D;				// W³¹czam timer z preskalerem 1/1024 w trybie CTC
	
	while (1)
	{
		if(TIFR & 1 << OCF0)			// Sprawdzam czy timer odliczy³ wymagan¹ iloœæ czasu
		{
			TIFR |= 1 << OCF0;			// Zerujê flagê porówniania 
			if(PORTB)					// Je¿eli LED jest zapalony 
			{
				PORTB = 0x00;				// Wy³¹czam LED
				OCR0 = 49;				// ustawiam timer na odliczenie 50ms
			}
			else
			{
				PORTB = 0x01;				// W³¹czam LED
				OCR0 = 146;				// ustawiam timer na odliczenie 150ms
			}
		}
	}
}

