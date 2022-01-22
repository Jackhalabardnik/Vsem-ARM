#include <avr/io.h>				//Do³¹czam potrzebne biblioteki
#include <avr/interrupt.h>
ISR(INT0_vect) {					// Przerwanie INT0
	PORTA ^= 1 << PA0;				// Zmieniam stan LED0
}
ISR(INT2_vect) {					// Przerwanie INT2
	PORTA ^= 1 << PA2;				// Zmieniam stan LED2
}
int main(void) {
	DDRA = 1 << PA0 | 1 << PA2;		// Ustawiam pin 0 i pin 2 PORTA jako wyjœcie
	PORTB = 1 << PB2;               // Podci¹gam piny PB2 i PD2 programowo pod zasilanie
	PORTD = 1 << PD2;
	
	MCUCR |= 1 << ISC01;			// Ustawiam przerwanie INT0 na zbocze opadaj¹ce
	MCUCSR &= ~(1 << ISC2);			// Ustawiam przerwanie INT2 na zbocze opadaj¹ce
	//MCUCR |= 1 << ISC01 | 1 << ISC00; // Ustawiam przerwanie INT0 na zbocze narastaj¹ce
	//MCUCSR |= 1 << ISC2;				// Ustawiam przerwanie INT2 na zbocze narastaj¹ce
	
	
	GICR |= 1 << INT0 | 1 << INT2;	// W³¹czam przerwanie INT0 i INT2
	GIFR |= 1 << INT0 | 1 << INT2;	// Wywo³anie przerwania INT0 i INT2 kiedy to bêdzie mo¿liwe
	sei();							// W³aczenie obs³ugi przerwañ
	while(1) {
		asm volatile("nop");		// Pêtla g³ówna
	}
}