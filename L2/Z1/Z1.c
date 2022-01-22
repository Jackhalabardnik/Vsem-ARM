#include <avr/io.h>
#include "lcd.h"

int main(void)
{
	PORTB = 0x01;				// podci¹gam PINB 0 pod zasilanie
	
	TCCR0 |= 0x07;				// W³¹czam timer ustawiaj¹c zród³o zegara jako zbocze narastaj¹ce
	//TCCR0 |= 0x06;				// W³¹czam timer ustawiaj¹c zród³o zegara jako zbocze opadaj¹ce

	TCNT0 = 253;
	
	while (1)
	{
		if(TIFR & 0x01)					// Je¿eli wykryjê przepe³nienie to wy³¹czam timer
		{
			TCCR0 &= 0xFC;				// Wy³¹czam timer
		}
	}
}

