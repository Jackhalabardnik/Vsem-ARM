#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000				// Ustawiam cz�stotliwo�� na zgodn� z zestawem w laboratorium

#include <avr/io.h>					// Do��czam biblioteki do obs�ugi port�w i op�nie�
#include <util/delay.h>

void LCD_CLEAR();					// Funkcja czyszcz�ca ca�y wy�wietlacz

void LCD_INIT();					// Funkcja inicjalizuj�ca wy�wietlacz

void LCD_WRITE(char *str);			// Funkcja wypisuj�ca dane na wy�wietlacz
	
void LCD_XY(int x, int y);			// Funkcja ustawiaj�ca kursor na danej pozycji na wy�wietlaczu
	
void LCD_CLEAR_XY(int x, int y);	// Funkcja czyszcz�ca wy�wietlacz od danej pozycji

#endif
