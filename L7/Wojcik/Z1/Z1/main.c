#include <avr/io.h>				//Do��czam potrzebne biblioteki
#include <avr/interrupt.h>
ISR(INT0_vect) {					// Przerwanie INT0
	PORTA ^= 1 << PA0;				// Zmieniam stan LED0
}
ISR(INT2_vect) {					// Przerwanie INT2
	PORTA ^= 1 << PA2;				// Zmieniam stan LED2
}
int main(void) {
	DDRA = 1 << PA0 | 1 << PA2;		// Ustawiam pin 0 i pin 2 PORTA jako wyj�cie
	PORTB = 1 << PB2;               // Podci�gam piny PB2 i PD2 programowo pod zasilanie
	PORTD = 1 << PD2;
	
	MCUCR |= 1 << ISC01;			// Ustawiam przerwanie INT0 na zbocze opadaj�ce
	MCUCSR &= ~(1 << ISC2);			// Ustawiam przerwanie INT2 na zbocze opadaj�ce
	//MCUCR |= 1 << ISC01 | 1 << ISC00; // Ustawiam przerwanie INT0 na zbocze narastaj�ce
	//MCUCSR |= 1 << ISC2;				// Ustawiam przerwanie INT2 na zbocze narastaj�ce
	
	
	GICR |= 1 << INT0 | 1 << INT2;	// W��czam przerwanie INT0 i INT2
	GIFR |= 1 << INT0 | 1 << INT2;	// Wywo�anie przerwania INT0 i INT2 kiedy to b�dzie mo�liwe
	sei();							// W�aczenie obs�ugi przerwa�
	while(1) {
		asm volatile("nop");		// P�tla g��wna
	}
}