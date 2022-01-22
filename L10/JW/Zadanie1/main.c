#include "PIO_library.h"    // Do³¹czam moj¹ bibliotekê
#include <ctl_api.h>        // Do³¹czam bibliotekê konieczn¹ do przerwañ

#define LCD_BACKLIGHT 20    // Podstawiam 20 za LCD_BACKLIGHT - dla czytelnoœci
#define PIOB 1              // Podstawiam 1 za PIOB - dla czytelnoœci
#define ENABLE 1            // Podstawiam 1 za ENABLE - dla czytelnoœci
#define DISABLE 0           // Podstawiam 0 za DISABLE - dla czytelnoœci
#define TIMER_COUNTER_0 12  // Podstawiam 12 za TIMER_COUNTER_0 - dla czytelnoœci
#define INT_PRIORITY 1      // Podstawiam 1 za INT_PRIORITY- dla czytelnoœci

// Procedura obs³ugi przerwania
void timer_int() {
    // Kasujê flagê przerwania poprzez pusty odczyt rejestru statusu
    TC0_SR;
    // Funkcj¹ z mojej biblioteki zmieniam stan podœwietlenia ekranu 
    PIOB_output_negate(LCD_BACKLIGHT);
}

// G³ówna funkcja
int main() {
    PIO_clock_enable(ENABLE,PIOB);        // W³¹czam zegar peryferiów dla kontrolera PIOB
    PIOB_enable(LCD_BACKLIGHT, ENABLE);         // W³¹czam pin LCD_BACKLIGHT
    PIOB_output_enable(LCD_BACKLIGHT, ENABLE);  // Ustawiam pin LCD_BACKLIGHT jako wyjœcie

    PMC_PCER |= PMC_PCER_TC0;     // W³¹czam zegar peryferiów dla timera 0

    TC0_CCR = TC0_CCR_CLKDIS;     // Wy³¹czam Timer 0
    TC0_IDR = 0xFF;               // Wy³¹czam wszystkie Ÿród³a przerwania dla Timera 0
    // Wykonujê pusty odczyt rejestru stanu Timera 0 w celu usuniêcia flagi przerwania  
    TC0_SR;                       
    // Wybieram preskaler 1/1024 (1 << 2),
    // ustawiam reset licznika po osi¹gniêciu wartoœci rejestru RC (1 << 14)
    TC0_CMR = 1<<2 | 1<<14;       
    TC0_RC=  9375;                // Ustawiam wartoœæ RC na czas 200ms
    // Ustawiam Ÿród³o przerwania jako porównanie wartoœci licznika z rejestrem RC  
    TC0_IER |= 1<<4;               
    TC0_CCR = TC0_CCR_CLKEN | TC0_CCR_SWTRG; // W³¹czam zegar i resetujê licznik

    ctl_global_interrupts_disable();  // Globalnie wy³¹czam przerwania
    // Konfigurujê przerwanie od timera, czyli ustawiam wektor przerwania jako Timer 0, 
    // z priorytetem 1, z sta³ym wyzwalaczem przerwania, z metod¹ do obs³ugi przerwania jako
    // "timer_int", i bez zwracania wska¿nika do funkcji, która poprzednio obs³ugiwa³a to
    // przerwanie (przesy³am 0). 
    ctl_set_isr(TIMER_COUNTER_0,INT_PRIORITY,CTL_ISR_TRIGGER_FIXED,timer_int,0);
    ctl_unmask_isr(TIMER_COUNTER_0);   // W³¹czam programowe przerwania od timera
    ctl_global_interrupts_enable();   // Globalnie w³¹czam przerwania

    while(1); //Nieskoñczona pêtla g³ówna
}


