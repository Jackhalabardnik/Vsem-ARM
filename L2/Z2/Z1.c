#define F_CPU 1000000  //Deklarujê czêstotliwoœæ zgodn¹ z zestawem w laboratorium
// Konieczne biblioteki
#include <avr/io.h> //Biblioteka do portów
#include <util/delay.h> // Biblioteka do opóŸnieñ

void task_3_1()  // Zadanie 3.1
{
	PORTD = 0xc0;  // Ustawiam stan PORTD na pocz¹tek animacji
	for(int i=0; i < 3; i++)  // Wykonujê 3 powtórzenia
	{
		while(PORTD != 0x03)  // Dopóki nie dojdê do koñca linijki zapalam kolejne LED-y
		{
			_delay_ms(500); // Czekam
			PORTD >>= 1; // Przesuwam animacjê
		}
		while(PORTD != 0xc0) // Dopóki nie wrócê na pocz¹tek linijki zapalam kolejne LED-y
		{
			_delay_ms(500); // Czekam
			PORTD <<= 1; // Przesuwam animacjê
		}
	}
}

void task_3_2()  // Zadanie 3.2
{
	PORTD = 0x80;  // Ustawiam stan PORTD na pocz¹tek animacji
	for(int i=0; i < 3; i++)  // Wykonujê 3 powtórzenia
	{
		while(PORTD != 0xf0) // Dopóki nie dojdê do œrodka linijki zapalam kolejne LED-y
		{
			_delay_ms(500); // Czekam
			PORTD |= PORTD >> 1; // Zapalam kolejnego LED-a
		}
		while(PORTD != 0x80) // Dopóki nie wrócê do punktu z którego zacz¹³em gaszê kolejne LED-y
		{
			_delay_ms(500);  // Czekam
			PORTD &= PORTD << 1;  //Gaszê kolejnego LED-a
		}
	}
}

void task_3_3()  // Zadanie 3.3
{
	for(int i=0; i < 3; i++) // Wykonujê 3 powtórzenia
	{
		PORTD = 0x80; // Ustawiam stan PORTD na pocz¹tek animacji
		_delay_ms(500); // Czekam
		while(PORTD != 0xff) // Dopóki nie zapalê ca³ej linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD >> 1; // Zapalam kolejnego LED-a
			_delay_ms(500); // Czekam
		}
	}
}

void task_3_4()  // Zadanie 3.4
{
	for(int i=0; i < 3; i++)  // Wykonujê 3 powtórzenia
	{
		PORTD = 0x08; // Ustawiam stan PORTD na pocz¹tek animacji 
		_delay_ms(500); // Czekam
		while(PORTD != 0x0f) // Dopóki nie dojdê do jednego z koñców linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD >> 1; // Zapalam kolejnego LED-a
			_delay_ms(500); // Czekam
		}
		PORTD ^= 0x1f;  //Odwracam zapalone LED-y w celu przejœcia do kolejnego kroku animacji
		_delay_ms(500); // Czekam
		while(PORTD != 0xf0) // Dopóki nie dojdê do jednego z koñców linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD << 1; // Zapalam kolejnego LED-a
			_delay_ms(500); // Czekam
		}
	}
}

void task_3_5() // Zadanie 3.5
{
	for(int i=0; i < 3; i++) // Wykonujê 3 powtórzenia
	{
		PORTD = 0x80; // Ustawiam stan PORTD na pocz¹tek animacji 
		_delay_ms(500); // Czekam
		while(PORTD != 0xf0) // Dopóki nie dojdê do œrodka linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD >> 1; // Zapalam kolejnego LED-a
			_delay_ms(500); // Czekam
		} 
		PORTD ^= 0xf1; //Odwracam zapalone LED-y w celu przejœcia do kolejnego kroku animacji
		_delay_ms(500); // Czekam
		while(PORTD != 0x0f) // Dopóki nie dojdê do œrodka linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD << 1;
			_delay_ms(500); // Czekam
		}
	}
}

int main(void)
{
	DDRD = 0xff;  // Ustawiam port D jako wyjœcie
    while(1) // Nieskoñczona pêtla
    {
		task_3_1(); // Zadanie 3.1
		task_3_2(); // Zadanie 3.2
		task_3_3(); // Zadanie 3.3
		task_3_4(); // Zadanie 3.4
		task_3_5(); // Zadanie 3.5
		_delay_ms(500); // Czekam
    }
}
