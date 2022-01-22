#define F_CPU 1000000  //Deklaruj� cz�stotliwo�� zgodn� z zestawem w laboratorium
// Konieczne biblioteki
#include <avr/io.h> //Biblioteka do port�w
#include <util/delay.h> // Biblioteka do op�nie�

void task_3_1()  // Zadanie 3.1
{
	PORTD = 0xc0;  // Ustawiam stan PORTD na pocz�tek animacji
	for(int i=0; i < 3; i++)  // Wykonuj� 3 powt�rzenia
	{
		while(PORTD != 0x03)  // Dop�ki nie dojd� do ko�ca linijki zapalam kolejne LED-y
		{
			_delay_ms(500); // Czekam
			PORTD >>= 1; // Przesuwam animacj�
		}
		while(PORTD != 0xc0) // Dop�ki nie wr�c� na pocz�tek linijki zapalam kolejne LED-y
		{
			_delay_ms(500); // Czekam
			PORTD <<= 1; // Przesuwam animacj�
		}
	}
}

void task_3_2()  // Zadanie 3.2
{
	PORTD = 0x80;  // Ustawiam stan PORTD na pocz�tek animacji
	for(int i=0; i < 3; i++)  // Wykonuj� 3 powt�rzenia
	{
		while(PORTD != 0xf0) // Dop�ki nie dojd� do �rodka linijki zapalam kolejne LED-y
		{
			_delay_ms(500); // Czekam
			PORTD |= PORTD >> 1; // Zapalam kolejnego LED-a
		}
		while(PORTD != 0x80) // Dop�ki nie wr�c� do punktu z kt�rego zacz��em gasz� kolejne LED-y
		{
			_delay_ms(500);  // Czekam
			PORTD &= PORTD << 1;  //Gasz� kolejnego LED-a
		}
	}
}

void task_3_3()  // Zadanie 3.3
{
	for(int i=0; i < 3; i++) // Wykonuj� 3 powt�rzenia
	{
		PORTD = 0x80; // Ustawiam stan PORTD na pocz�tek animacji
		_delay_ms(500); // Czekam
		while(PORTD != 0xff) // Dop�ki nie zapal� ca�ej linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD >> 1; // Zapalam kolejnego LED-a
			_delay_ms(500); // Czekam
		}
	}
}

void task_3_4()  // Zadanie 3.4
{
	for(int i=0; i < 3; i++)  // Wykonuj� 3 powt�rzenia
	{
		PORTD = 0x08; // Ustawiam stan PORTD na pocz�tek animacji 
		_delay_ms(500); // Czekam
		while(PORTD != 0x0f) // Dop�ki nie dojd� do jednego z ko�c�w linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD >> 1; // Zapalam kolejnego LED-a
			_delay_ms(500); // Czekam
		}
		PORTD ^= 0x1f;  //Odwracam zapalone LED-y w celu przej�cia do kolejnego kroku animacji
		_delay_ms(500); // Czekam
		while(PORTD != 0xf0) // Dop�ki nie dojd� do jednego z ko�c�w linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD << 1; // Zapalam kolejnego LED-a
			_delay_ms(500); // Czekam
		}
	}
}

void task_3_5() // Zadanie 3.5
{
	for(int i=0; i < 3; i++) // Wykonuj� 3 powt�rzenia
	{
		PORTD = 0x80; // Ustawiam stan PORTD na pocz�tek animacji 
		_delay_ms(500); // Czekam
		while(PORTD != 0xf0) // Dop�ki nie dojd� do �rodka linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD >> 1; // Zapalam kolejnego LED-a
			_delay_ms(500); // Czekam
		} 
		PORTD ^= 0xf1; //Odwracam zapalone LED-y w celu przej�cia do kolejnego kroku animacji
		_delay_ms(500); // Czekam
		while(PORTD != 0x0f) // Dop�ki nie dojd� do �rodka linijki zapalam kolejne LED-y
		{
			PORTD |= PORTD << 1;
			_delay_ms(500); // Czekam
		}
	}
}

int main(void)
{
	DDRD = 0xff;  // Ustawiam port D jako wyj�cie
    while(1) // Niesko�czona p�tla
    {
		task_3_1(); // Zadanie 3.1
		task_3_2(); // Zadanie 3.2
		task_3_3(); // Zadanie 3.3
		task_3_4(); // Zadanie 3.4
		task_3_5(); // Zadanie 3.5
		_delay_ms(500); // Czekam
    }
}
