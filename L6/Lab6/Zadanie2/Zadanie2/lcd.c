#include "lcd.h"

void sendHalfByte(char data)
{
	PORTA |= 0x02; 								// Wysy³am flagê ENABLE
	PORTA = (PORTA & 0x0F) | (data & 0xF0);		// Wysy³am pó³ bajta
	PORTA &= 0xFD;								// Usuwam flagê ENABLE
}

void sendByte(char data)
{
	sendHalfByte(data);							// Wysy³am górn¹ po³owê bajtu
	_delay_ms(2);								// OpóŸnienie w celu wykrycia stanu "0" na pinie ENABLE
	sendHalfByte(data << 4);					// Wysy³am doln¹ po³owê bajtu
}

void sendCommand(char data)
{
	sendByte(data);								// Wysy³am komendê
	_delay_ms(5);								// Czekam na przetworzenie komendy
}

void sendChar(char data)
{
	sendByte(data);								// Wysy³am znak
	_delay_ms(2);								// Czekam na wypisanie znaku
}

void LCD_CLEAR()
{
	PORTA &= 0xFE;								// Prze³¹czam LCD w tryb wprowadzania komend
	_delay_ms(2);								// OpóŸnienie w celu wykrycia stanu "0" na pinie RS
	sendCommand(0x01);							// Czyszczê wyœwietlacz
	PORTA |= 0x01;								// Prze³¹czam LCD w tryb wprowadzania danych
}

void LCD_INIT()
{
	_delay_ms(15); 								// Czekam a¿ wyœwietlacz LCD zostanie zainicjalizowany

	DDRA |= 0xF3;								// Ustawiam czêœæ linii A
		
	// Inicjalizacja standardowymi bajtami
	sendHalfByte(0x30);							
	_delay_ms(5);								// Czekam zgodnie z dokumentacj¹
	sendHalfByte(0x30);							
	_delay_ms(1);
	sendCommand(0x32);
	
	// Inicjalizacja ustawieñ wyœwietlacza
	sendCommand(0x28);							// Ustawiam tryb 2 linii i znaków 5x8
	sendCommand(0x08);							// Wy³¹czam wyœwietlacz zgodnie z dokumentacj¹
	sendCommand(0x01);							// Czyszczê wyœwietlacz
	sendCommand(0x06);							// Ustawiam kierunek wyprowadzania tekstu i sposób wyprowadzania na wyœwietlacz
	sendCommand(0x0C);							// W³¹czam wyœwietlacz i wy³¹czam kursor
	PORTA |= 0x01;								// Prze³¹czam LCD w tryb wprowadzania danych
}

void LCD_WRITE(char *str) 
{
	while(*str)									// Dopóki nie dojdê to null terminatora wypisujê kolejne znaki
	{
		sendChar(*str++);						// Przesuwam siê do kolejnego znaku po wypisaniu go na wyœwietlaczu
	}
}

void LCD_XY(int x, int y)
{
	PORTA &= 0xFE;								// Prze³¹czam LCD w tryb wprowadzania komend
	_delay_ms(2);								// OpóŸnienie w celu wykrycia stanu "0" na pinie RS
	sendCommand(0x80 | x | y << 6);				// Ustawiam kursor na odpowowiedniej pozycji
	PORTA |= 0x01;								// Prze³¹czam LCD w tryb wprowadzania danych
}

void LCD_CLEAR_XY(int x, int y)
{
	LCD_XY(x,y);								// Ustawiam kursor na pozycji od której chcê czyœciæ
	if(y == 0)									// Sprawdzam czy to pierwsza linia
	{
		while(x++ < 16)							// Dopóki nie dojdê do koñca linii
		{
			LCD_WRITE(" ");						// Wypisujê pusty znak na wyjœcie wyœwietlacza
		}
		x = 0;									// Ustawiam pierwsz¹ sk³adow¹ adresu na pocz¹tek linii 
		y++;									// Ustawiam drug¹ sk³adow¹ adresu na drug¹ liniê
		LCD_XY(x,y);							// Ustawiam kursor na podany adres -> pocz¹tek drugiej linii
	}	
	while(x++ < 16)								// Dopóki nie dojdê do koñca linii
	{
		LCD_WRITE(" ");							// Wypisujê pusty znak na wyjœcie wyœwietlacza
	}
}
