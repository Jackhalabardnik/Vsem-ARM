#include "PIO_library.h"    // Do��czam moj� bibliotek�
#include <ctl_api.h>        // Do��czam bibliotek� konieczn� do przerwa�

#define LCD_BACKLIGHT 20    // Podstawiam 20 za LCD_BACKLIGHT - dla czytelno�ci
#define BUTTON_SW1 24       // Podstawiam 24 za BUTTON_SW1 - dla czytelno�ci
#define BUTTON_SW2 25       // Podstawiam 25 za BUTTON_SW2 - dla czytelno�ci
#define PIOB 1              // Podstawiam 1 za PIOB - dla czytelno�ci
#define ENABLE 1            // Podstawiam 1 za ENABLE - dla czytelno�ci
#define DISABLE 0           // Podstawiam 0 za DISABLE - dla czytelno�ci
#define PIO_CONTROLLER_B 3 // Podstawiam 3 za PIO_CONTROLLER_B - dla czytelno�ci
#define INT_PRIORITY 1      // Podstawiam 1 za INT_PRIORITY - dla czytelno�ci

// Procedura obs�ugi przerwania
void button_int() {
  // Zapami�tuj� stan rejestru statusu przerwa� w kontrolerze PIOB
  int interrupt_status = PIOB_ISR;
  if(interrupt_status & (1 << BUTTON_SW1)) { // Je�eli wcisn��em przycisk SW1
    PIOB_output_state(LCD_BACKLIGHT, ENABLE);   // W��cz pod�wietlenie
  }
  else if(interrupt_status & (1 << BUTTON_SW2)) {  // Je�eli wcisn��em przycisk SW2
    PIOB_output_state(LCD_BACKLIGHT, DISABLE);  // Wy��cz pod�wietlenie
  }
}
// G��wna funkcja
int main(void) {
  PIO_clock_enable(ENABLE,PIOB);              // W��czam zegar peryferi�w dla kontrolera PIOB
  PIOB_enable(LCD_BACKLIGHT, ENABLE);         // W��czam pin LCD_BACKLIGHT
  PIOB_output_enable(LCD_BACKLIGHT, ENABLE);  // Ustawiam pin LCD_BACKLIGHT jako wyj�cie
  PIOB_IER = 1<<BUTTON_SW1 | 1<<BUTTON_SW2;   // W��czam przerwania dla przycisk�w SW1 i SW2

  ctl_global_interrupts_disable();  // Globalnie wy��czam przerwania
  // Konfiguruj� przerwanie od kontrolera PIOB, czyli ustawiam wektor przerwania jako PIOB,
  // z priorytetem 1, z sta�ym wektorem przerwania, z metod� do obs�ugi przerwania jako
  // "button_int", i bez zwracania wska�nika do funkcji, kt�ra poprzednio obs�ugiwa�a to
  // przerwanie (przesy�am 0).
  ctl_set_isr(PIO_CONTROLLER_B,INT_PRIORITY,CTL_ISR_TRIGGER_FIXED,button_int,0);
  ctl_unmask_isr(PIO_CONTROLLER_B); // W��czam programowe przerwania od timera
  ctl_global_interrupts_enable();   // Globalnie w��czam przerwania
 
  while(1); //Niesko�czona p�tla g��wna
}