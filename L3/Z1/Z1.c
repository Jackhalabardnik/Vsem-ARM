#define F_CPU 1000000  //Deklaruj� cz�stotliwo�� zgodn� z zestawem w laboratorium
// Konieczne biblioteki
#include <avr/io.h> //Biblioteka do port�w
#include <util/delay.h> // Biblioteka do op�nie�

const int half_second = 500, second = 1000; // Zmienne przechowuj�ce warto�ci op�nie�

void task_3_1()  // Zadanie 3.1
{
	PORTA |= 0xc0;  // Ustawiam stan PORTA na pocz�tek animacji
	PORTA &= 0xc0;   // Zeruj� wszystkie pozosta�e bity
	for(int i=0; i < 3; i++)  // Wykonuj� 3 powt�rzenia
	{
		for(int j = 7; j > 1; j--)  // Dop�ki nie dojd� do ko�ca linijki zapalam kolejne LED-y
		{
			_delay_ms(half_second); // Czekam 0,5s
			PORTA ^= _BV(j) | _BV(j-2); // Przesuwam animacj�
		}
		for(int j = 0; j < 6; j++) // Dop�ki nie wr�c� na pocz�tek linijki zapalam kolejne LED-y
		{
			_delay_ms(half_second); // Czekam 0,5s
			PORTA ^= _BV(j) | _BV(j+2); // Przesuwam animacj�
		}
	}
}

void task_3_2()  // Zadanie 3.2
{
	PORTA |= 0x80;  // Ustawiam stan PORTA na pocz�tek animacji
	PORTA &= 0x80;   // Zeruj� wszystkie pozosta�e bity
	for(int i=0; i < 3; i++)  // Wykonuj� 3 powt�rzenia
	{
		for(int j = 6; j > 3; j--)  // Dop�ki nie dojd� do �rodka linijki zapalam kolejne LED-y
		{
			_delay_ms(second); // Czekam 1s
			PORTA ^= _BV(j); // Przesuwam animacj�
		}
		for(int j = 4; j < 7; j++) // Dop�ki nie wr�c� do punktu z kt�rego zacz��em gasz� kolejne LED-y
		{
			_delay_ms(second); // Czekam 1s
			PORTA ^= _BV(j); // Przesuwam animacj�
		}
	}
}

void task_3_3()  // Zadanie 3.3
{
	for(int i=0; i < 3; i++) // Wykonuj� 3 powt�rzenia
	{
		PORTA |= 0x80;  // Ustawiam stan PORTA na pocz�tek animacji
		PORTA &= 0x80;   // Zeruj� wszystkie pozosta�e bity
		_delay_ms(second); // Czekam 1s
		for(int j = 6; j > -1; j--)  // Dop�ki nie dojd� do jednego z ko�c�w linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacj�
			_delay_ms(second); // Czekam 1s
		}
	}
}

void task_3_4()  // Zadanie 3.4
{
	for(int i=0; i < 3; i++)  // Wykonuj� 3 powt�rzenia
	{
		PORTA |= 0x08;  // Ustawiam stan PORTA na pocz�tek animacji
		PORTA &= 0x08;   // Zeruj� wszystkie pozosta�e bity
		_delay_ms(second); // Czekam 1s
		for(int j = 2; j > -1; j--)  // Dop�ki nie dojd� do jednego z ko�c�w linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacj�
			_delay_ms(second); // Czekam 1s
		}
		PORTA ^= 0x1f;  //Odwracam zapalone LED-y w celu przej�cia do kolejnego kroku animacji

		_delay_ms(second); // Czekam 1s
		for(int j = 5; j < 8; j++)  // Dop�ki nie dojd� do jednego z ko�c�w linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacj�
			_delay_ms(second); // Czekam 1s
		}
	}
}

void task_3_5() // Zadanie 3.5
{
	for(int i=0; i < 3; i++) // Wykonuj� 3 powt�rzenia
	{
		PORTA |= 0x80;  // Ustawiam stan PORTA na pocz�tek animacji
		PORTA &= 0x80;   // Zeruj� wszystkie pozosta�e bity
		_delay_ms(second); // Czekam 1s
		for(int j = 6; j > 3; j--)  // Dop�ki nie dojd� do �rodka linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacj�
			_delay_ms(second); // Czekam 1s
		} 
		PORTA ^= 0xf1; //Odwracam zapalone LED-y w celu przej�cia do kolejnego kroku animacji
		_delay_ms(second); // Czekam 1s
		for(int j = 1; j <4; j++)  // Dop�ki nie dojd� do �rodka linijki zapalam kolejne LED-y
		{
			PORTA ^= _BV(j); // Przesuwam animacj�
			_delay_ms(second); // Czekam 1s
		}
	}
}

int main(void)
{
	DDRA |= 0xff;  // Ustawiam port A jako wyj�cie
    while(1) // Niesko�czona p�tla
    {
		task_3_1(); // Zadanie 3.1
		task_3_2(); // Zadanie 3.2
		task_3_3(); // Zadanie 3.3
		task_3_4(); // Zadanie 3.4
		task_3_5(); // Zadanie 3.5
    }
}
