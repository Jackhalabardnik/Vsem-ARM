#define F_CPU 1000000		// Ustawiam cz�stotliwo�� na t� z labolatorium
#include <avr/io.h>		// Do��czam potrzebne biblioteki
#include <avr/interrupt.h>

volatile char number = 1;	// Inicjalizuj� licznik cykli timera

ISR (TIMER0_COMP_vect) {    // Przerwanie TIMER0 co 100ms
	PORTA ^= 0x01;			// Migam LED0 co 100 milisekund
	if(number == 10)			// Odliczam 10 kolejnych cykli timera
	{
		PORTA ^= 0x02;		// Migam LED1 co 1 sekund�
		number = 1;
	}
	else
	{
		number++;				// Odliczam kolejny cykl
	}
}

int main(void)
{
	DDRA = 0x03;	// Ustawiam pin 0 i 1 PORTA jako wyjscie

	OCR0 = 98;      // ustawienie momentu przerwania na 98 (oko�o 0,1s)

    TIMSK |= 0x02;  // w��czenie przerwania TIMER0

	//	W��czam timer 0 w trybie CTC z preskalerem 1/1024
	TCCR0 |= 1 << WGM01 | 1 << CS02 | 1 << CS00;	

	sei();                        // w��czam obs�ug� przerwa�
	
	
	while (1)
	{
		asm volatile("nop");
	}
}



