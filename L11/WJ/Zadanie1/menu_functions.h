#pragma once    // Do��cz ten plik tylko raz

#include <targets\AT91SAM7.h> // Biblioteka do obs�ugi zestawu z labolarotium
#include <ctl_api.h>          // Biblioteka do obs�ugi przerwa�
#include "PCF8833U8_lcd.h"    // Biblioteka do obs�ugi wy�wietlacza LCD

volatile int animation_active = 0;  // Zmienna do stwierdzenia czy animacja jest aktywna

/*  Funkcja do wy�wietlenia informacji o autorze
*   nic nie zwraca
*/
void about_author() {
    LCDClearScreen();
    LCDPutStr("Jacek Wojcik", 45, 15, LARGE, BLACK, WHITE);
    LCDPutStr("10", 70, 50, LARGE, BLACK, WHITE);
}

/*  Funkcja do wy�wietlenia obrazu z tekstem
*   nic nie zwraca
*/
void image_with_text() {
    show_photo(2);
    LCDPutStr("WJ_10",30,30,LARGE,BLACK,TRANSPARENT);
}

/*  Funkcja do wy�wietlenia obrazu numer 1
*   nic nie zwraca
*/
void image_1() {
    show_photo(1);
}

/*  Funkcja do wy�wietlenia obrazu numer 2
*   nic nie zwraca
*/
void image_2() {
    show_photo(2);
}

/*  Funkcja do aktywacji animacji
*   nic nie zwraca
*/
void animation() {
    animation_active = 1;
}

/*  Funkcja do wy�wietlenia kwadratu
*   nic nie zwraca
*/
void square() {
    LCDClearScreen();
    LCDSetRect(20, 20, 100, 100, FILL, YELLOW);
}

/*  Funkcja do wy�wietlenia ko�a
*   nic nie zwraca
*/
void circle() {
    LCDClearScreen();
     LCDSetCircle(50, 50, 10, YELLOW); 
}

/*  Funkcja do wy�wietlenia tr�jk�ta
*   nic nie zwraca
*/
void triangle() {
    LCDClearScreen();
    LCDSetLine(20, 20, 60, 50, YELLOW); 
    LCDSetLine(20, 20, 60, 20, YELLOW); 
    LCDSetLine(60, 50, 60, 20, YELLOW); 
}

/*  Funkcja do wy�wietlenia trapezu
*   nic nie zwraca
*/
void trapeze() {
    LCDClearScreen();
    LCDSetLine(30, 50, 50, 50, YELLOW); 
    LCDSetLine(20, 20, 60, 20, YELLOW); 
    LCDSetLine(50, 50, 60, 20, YELLOW); 
    LCDSetLine(30, 50, 20, 20, YELLOW); 
}
