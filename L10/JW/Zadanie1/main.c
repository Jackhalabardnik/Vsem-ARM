#include "PIO_library.h"    // Do��czam moj� bibliotek�
#include <ctl_api.h>        // Do��czam bibliotek� konieczn� do przerwa�

#define LCD_BACKLIGHT 20    // Podstawiam 20 za LCD_BACKLIGHT - dla czytelno�ci
#define PIOB 1              // Podstawiam 1 za PIOB - dla czytelno�ci
#define ENABLE 1            // Podstawiam 1 za ENABLE - dla czytelno�ci
#define DISABLE 0           // Podstawiam 0 za DISABLE - dla czytelno�ci
#define TIMER_COUNTER_0 12  // Podstawiam 12 za TIMER_COUNTER_0 - dla czytelno�ci
#define INT_PRIORITY 1      // Podstawiam 1 za INT_PRIORITY- dla czytelno�ci

// Procedura obs�ugi przerwania
void timer_int() {
    // Kasuj� flag� przerwania poprzez pusty odczyt rejestru statusu
    TC0_SR;
    // Funkcj� z mojej biblioteki zmieniam stan pod�wietlenia ekranu 
    PIOB_output_negate(LCD_BACKLIGHT);
}

// G��wna funkcja
int main() {
    PIO_clock_enable(ENABLE,PIOB);        // W��czam zegar peryferi�w dla kontrolera PIOB
    PIOB_enable(LCD_BACKLIGHT, ENABLE);         // W��czam pin LCD_BACKLIGHT
    PIOB_output_enable(LCD_BACKLIGHT, ENABLE);  // Ustawiam pin LCD_BACKLIGHT jako wyj�cie

    PMC_PCER |= PMC_PCER_TC0;     // W��czam zegar peryferi�w dla timera 0

    TC0_CCR = TC0_CCR_CLKDIS;     // Wy��czam Timer 0
    TC0_IDR = 0xFF;               // Wy��czam wszystkie �r�d�a przerwania dla Timera 0
    // Wykonuj� pusty odczyt rejestru stanu Timera 0 w celu usuni�cia flagi przerwania  
    TC0_SR;                       
    // Wybieram preskaler 1/1024 (1 << 2),
    // ustawiam reset licznika po osi�gni�ciu warto�ci rejestru RC (1 << 14)
    TC0_CMR = 1<<2 | 1<<14;       
    TC0_RC=  9375;                // Ustawiam warto�� RC na czas 200ms
    // Ustawiam �r�d�o przerwania jako por�wnanie warto�ci licznika z rejestrem RC  
    TC0_IER |= 1<<4;               
    TC0_CCR = TC0_CCR_CLKEN | TC0_CCR_SWTRG; // W��czam zegar i resetuj� licznik

    ctl_global_interrupts_disable();  // Globalnie wy��czam przerwania
    // Konfiguruj� przerwanie od timera, czyli ustawiam wektor przerwania jako Timer 0, 
    // z priorytetem 1, z sta�ym wyzwalaczem przerwania, z metod� do obs�ugi przerwania jako
    // "timer_int", i bez zwracania wska�nika do funkcji, kt�ra poprzednio obs�ugiwa�a to
    // przerwanie (przesy�am 0). 
    ctl_set_isr(TIMER_COUNTER_0,INT_PRIORITY,CTL_ISR_TRIGGER_FIXED,timer_int,0);
    ctl_unmask_isr(TIMER_COUNTER_0);   // W��czam programowe przerwania od timera
    ctl_global_interrupts_enable();   // Globalnie w��czam przerwania

    while(1); //Niesko�czona p�tla g��wna
}


