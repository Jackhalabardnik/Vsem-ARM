#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000				// Ustawiam częstotliwość na zgodną z zestawem w laboratorium

#include <avr/io.h>					// Dołączam biblioteki do obsługi portów i opóźnień
#include <util/delay.h>

void LCD_CLEAR();					// Funkcja czyszcząca cały wyświetlacz

void LCD_INIT();					// Funkcja inicjalizująca wyświetlacz

void LCD_WRITE(char *str);			// Funkcja wypisująca dane na wyświetlacz
	
void LCD_XY(int x, int y);			// Funkcja ustawiająca kursor na danej pozycji na wyświetlaczu
	
void LCD_CLEAR_XY(int x, int y);	// Funkcja czyszcząca wyświetlacz od danej pozycji

#endif
