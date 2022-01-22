#include "lcd.h"

void sendHalfByte(char data)
{
	PORTA |= 0x02; 								// Wysy�am flag� ENABLE
	PORTA = (PORTA & 0x0F) | (data & 0xF0);		// Wysy�am p� bajta
	PORTA &= 0xFD;								// Usuwam flag� ENABLE
}

void sendByte(char data)
{
	sendHalfByte(data);							// Wysy�am g�rn� po�ow� bajtu
	_delay_ms(2);								// Op�nienie w celu wykrycia stanu "0" na pinie ENABLE
	sendHalfByte(data << 4);					// Wysy�am doln� po�ow� bajtu
}

void sendCommand(char data)
{
	sendByte(data);								// Wysy�am komend�
	_delay_ms(5);								// Czekam na przetworzenie komendy
}

void sendChar(char data)
{
	sendByte(data);								// Wysy�am znak
	_delay_ms(2);								// Czekam na wypisanie znaku
}

void LCD_CLEAR()
{
	PORTA &= 0xFE;								// Prze��czam LCD w tryb wprowadzania komend
	_delay_ms(2);								// Op�nienie w celu wykrycia stanu "0" na pinie RS
	sendCommand(0x01);							// Czyszcz� wy�wietlacz
	PORTA |= 0x01;								// Prze��czam LCD w tryb wprowadzania danych
}

void LCD_INIT()
{
	_delay_ms(15); 								// Czekam a� wy�wietlacz LCD zostanie zainicjalizowany

	DDRA |= 0xF3;								// Ustawiam cz�� linii A
		
	// Inicjalizacja standardowymi bajtami
	sendHalfByte(0x30);							
	_delay_ms(5);								// Czekam zgodnie z dokumentacj�
	sendHalfByte(0x30);							
	_delay_ms(1);
	sendCommand(0x32);
	
	// Inicjalizacja ustawie� wy�wietlacza
	sendCommand(0x28);							// Ustawiam tryb 2 linii i znak�w 5x8
	sendCommand(0x08);							// Wy��czam wy�wietlacz zgodnie z dokumentacj�
	sendCommand(0x01);							// Czyszcz� wy�wietlacz
	sendCommand(0x06);							// Ustawiam kierunek wyprowadzania tekstu i spos�b wyprowadzania na wy�wietlacz
	sendCommand(0x0C);							// W��czam wy�wietlacz i wy��czam kursor
	PORTA |= 0x01;								// Prze��czam LCD w tryb wprowadzania danych
}

void LCD_WRITE(char *str) 
{
	while(*str)									// Dop�ki nie dojd� to null terminatora wypisuj� kolejne znaki
	{
		sendChar(*str++);						// Przesuwam si� do kolejnego znaku po wypisaniu go na wy�wietlaczu
	}
}

void LCD_XY(int x, int y)
{
	PORTA &= 0xFE;								// Prze��czam LCD w tryb wprowadzania komend
	_delay_ms(2);								// Op�nienie w celu wykrycia stanu "0" na pinie RS
	sendCommand(0x80 | x | y << 6);				// Ustawiam kursor na odpowowiedniej pozycji
	PORTA |= 0x01;								// Prze��czam LCD w tryb wprowadzania danych
}

void LCD_CLEAR_XY(int x, int y)
{
	LCD_XY(x,y);								// Ustawiam kursor na pozycji od kt�rej chc� czy�ci�
	if(y == 0)									// Sprawdzam czy to pierwsza linia
	{
		while(x++ < 16)							// Dop�ki nie dojd� do ko�ca linii
		{
			LCD_WRITE(" ");						// Wypisuj� pusty znak na wyj�cie wy�wietlacza
		}
		x = 0;									// Ustawiam pierwsz� sk�adow� adresu na pocz�tek linii 
		y++;									// Ustawiam drug� sk�adow� adresu na drug� lini�
		LCD_XY(x,y);							// Ustawiam kursor na podany adres -> pocz�tek drugiej linii
	}	
	while(x++ < 16)								// Dop�ki nie dojd� do ko�ca linii
	{
		LCD_WRITE(" ");							// Wypisuj� pusty znak na wyj�cie wy�wietlacza
	}
}
