#include <avr/io.h>
#include "lcd.h"

int main(void)
{
	PORTB = 0x01;				// podci�gam PINB 0 pod zasilanie
	
	TCCR0 |= 0x07;				// W��czam timer ustawiaj�c zr�d�o zegara jako zbocze narastaj�ce
	//TCCR0 |= 0x06;				// W��czam timer ustawiaj�c zr�d�o zegara jako zbocze opadaj�ce

	TCNT0 = 253;
	
	while (1)
	{
		if(TIFR & 0x01)					// Je�eli wykryj� przepe�nienie to wy��czam timer
		{
			TCCR0 &= 0xFC;				// Wy��czam timer
		}
	}
}

