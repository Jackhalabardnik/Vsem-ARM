#define F_CPU 1000000		// Ustawiam cz�stotliwo�� na t� w labolatorium
#include <avr/io.h>			// Do��czam potrzebne biblioteki
#include <avr/interrupt.h>

volatile char buttons = 0;	// Tworz� zmienn� do zapami�tania stanu PINA

ISR (TIMER0_COMP_vect) {    // Przerwanie TIMER0 co 5ms
	buttons = ~PINA; // Zapami�tuj� zanegowany stan PIN 
}

int main(void)
{
	DDRC |= 0x03;			// Ustawiam pin 0 i 1 PORTA jako wyjscie

	PORTA |= 0x03;			// Podci�gam przyciski pod zasilanie

	OCR0 = 5;                    // ustawienie momentu przerwania na 5 (oko�o 5ms)

	TIMSK |= 0x02;                 // w��czenie przerwania TIMER0

	TCCR0 |= 1 << WGM01 | 1 << CS02 | 1 << CS00;	//	W��cza timer 0 w trybie CTC z preskalerem 1/1024

	sei();                        // w��czam obs�ug� przerwa�
	
	while (1)
	{
		PORTC = (PORTC & 0xFC) | (buttons & 0x03); // Zmieniam stan tylko dw�ch pod��czonych LED�w w PORTB
	}
}
