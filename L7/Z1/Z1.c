#define F_CPU 1000000		// Ustawiam czêstotliwoœæ na tê w labolatorium
#include <avr/io.h>			// Do³¹czam potrzebne biblioteki
#include <avr/interrupt.h>

volatile char buttons = 0;	// Tworzê zmienn¹ do zapamiêtania stanu PINA

ISR (TIMER0_COMP_vect) {    // Przerwanie TIMER0 co 5ms
	buttons = ~PINA; // Zapamiêtujê zanegowany stan PIN 
}

int main(void)
{
	DDRC |= 0x03;			// Ustawiam pin 0 i 1 PORTA jako wyjscie

	PORTA |= 0x03;			// Podci¹gam przyciski pod zasilanie

	OCR0 = 5;                    // ustawienie momentu przerwania na 5 (oko³o 5ms)

	TIMSK |= 0x02;                 // w³¹czenie przerwania TIMER0

	TCCR0 |= 1 << WGM01 | 1 << CS02 | 1 << CS00;	//	W³¹cza timer 0 w trybie CTC z preskalerem 1/1024

	sei();                        // w³¹czam obs³ugê przerwañ
	
	while (1)
	{
		PORTC = (PORTC & 0xFC) | (buttons & 0x03); // Zmieniam stan tylko dwóch pod³¹czonych LEDów w PORTB
	}
}
