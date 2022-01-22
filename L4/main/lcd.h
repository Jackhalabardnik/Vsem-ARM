#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000				// Ustawiam czêstotliwoœæ na zgodn¹ z zestawem w laboratorium

#include <avr/io.h>					// Do³¹czam biblioteki do obs³ugi portów i opóŸnieñ
#include <util/delay.h>

void LCD_CLEAR();					// Funkcja czyszcz¹ca ca³y wyœwietlacz

void LCD_INIT();					// Funkcja inicjalizuj¹ca wyœwietlacz

void LCD_WRITE(char *str);			// Funkcja wypisuj¹ca dane na wyœwietlacz
	
void LCD_XY(int x, int y);			// Funkcja ustawiaj¹ca kursor na danej pozycji na wyœwietlaczu
	
void LCD_CLEAR_XY(int x, int y);	// Funkcja czyszcz¹ca wyœwietlacz od danej pozycji

#endif
