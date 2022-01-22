#define F_CPU 1000000  //Deklarujê czêstotliwoœæ zgodn¹ z zestawem w laboratorium
// Konieczne biblioteki
#include <avr/io.h> //Biblioteka do portów
#include <util/delay.h> // Biblioteka do opóŸnieñ

const int half_second = 500, second = 1000; // Zmienne przechowuj¹ce wartoœci opóŸnieñ

void task_3_1()  // Zadanie 3.1
{
	PORTA |= 0xc0;  // Ustawiam stan PORTA na pocz¹tek animacji
	PORTA &= 0xc0;   // Zerujê wszystkie pozosta³e bity
	for(int i=0; i < 3; i++)  // Wykonujê 3 powtórzenia
	{
		for(int j = 7; j > 1; j--)  // Dopóki nie dojdê do koñca linijki zapalam kolejne LED-y
		{
			_delay_ms(half_second); // Czekam 0,5s
			PORTA ^= _BV(j) | _BV(j-2); // Przesuwam animacjê
		}
		for(int j = 0; j < 6; j++) // Dopóki nie wrócê na pocz¹tek linijki zapalam kolejne LED-y
		{
			_delay_ms(half_second); // Czekam 0,5s
			PORTA ^= _BV(j) | _BV(j+2); // Przesuwam animacjê
		}
	}
}

void task_3_2()  // Zadanie 3.2
{
	PORTA |= 0x80;  // Ustawiam stan PORTA na pocz¹tek animacji
	PORTA &= 0x80;   // Zerujê wszystkie pozosta³e bity
	for(int i=0; i < 3; i++)  // Wykonujê 3 powtórzenia
	{
		for(int j = 6; j > 3; j--)  // Dopóki nie dojdê do œrodka linijki zapalam kolejne LED-y
		{
			_delay_ms(second); // Czekam 1s
			PORTA ^= _BV(j); // Przesuwam animacjê
		}
		for(int j = 4; j < 7; j++) // Dopóki nie wrócê do punktu z którego zacz¹³em gaszê kolejne LED-y
		{
			_delay_ms(second); // Czekam 1s
			PORTA ^= _BV(j); // Przesuwam animacjê
		}
	}
}

void task_3_3()  // Zadanie 3.3
{
	for(int i=0; i < 3; i++) // Wykonujê 3 powtórzenia
	{
		PORTA |= 0x80;  // Ustawiam stan PORTA na pocz¹tek animacji
		PORTA &= 0x80;   // Zerujê wszystkie pozosta³e bity
		_delay_ms(second); // Czekam 1s
		for(int j = 6; j > -1; j--)  // Dopóki nie dojdê do jednego z koñców linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacjê
			_delay_ms(second); // Czekam 1s
		}
	}
}

void task_3_4()  // Zadanie 3.4
{
	for(int i=0; i < 3; i++)  // Wykonujê 3 powtórzenia
	{
		PORTA |= 0x08;  // Ustawiam stan PORTA na pocz¹tek animacji
		PORTA &= 0x08;   // Zerujê wszystkie pozosta³e bity
		_delay_ms(second); // Czekam 1s
		for(int j = 2; j > -1; j--)  // Dopóki nie dojdê do jednego z koñców linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacjê
			_delay_ms(second); // Czekam 1s
		}
		PORTA ^= 0x1f;  //Odwracam zapalone LED-y w celu przejœcia do kolejnego kroku animacji

		_delay_ms(second); // Czekam 1s
		for(int j = 5; j < 8; j++)  // Dopóki nie dojdê do jednego z koñców linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacjê
			_delay_ms(second); // Czekam 1s
		}
	}
}

void task_3_5() // Zadanie 3.5
{
	for(int i=0; i < 3; i++) // Wykonujê 3 powtórzenia
	{
		PORTA |= 0x80;  // Ustawiam stan PORTA na pocz¹tek animacji
		PORTA &= 0x80;   // Zerujê wszystkie pozosta³e bity
		_delay_ms(second); // Czekam 1s
		for(int j = 6; j > 3; j--)  // Dopóki nie dojdê do œrodka linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacjê
			_delay_ms(second); // Czekam 1s
		} 
		PORTA ^= 0xf1; //Odwracam zapalone LED-y w celu przejœcia do kolejnego kroku animacji
		_delay_ms(second); // Czekam 1s
		for(int j = 1; j <4; j++)  // Dopóki nie dojdê do œrodka linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacjê
			_delay_ms(second); // Czekam 1s
		}
	}
}

int main(void)
{
	DDRA |= 0xff;  // Ustawiam port A jako wyjœcie
    while(1) // Nieskoñczona pêtla
    {
		task_3_1(); // Zadanie 3.1
		task_3_2(); // Zadanie 3.2
		task_3_3(); // Zadanie 3.3
		task_3_4(); // Zadanie 3.4
		task_3_5(); // Zadanie 3.5
    }
}
