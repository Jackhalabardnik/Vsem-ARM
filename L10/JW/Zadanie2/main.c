#include "PIO_library.h"    // Do³¹czam moj¹ bibliotekê
#include <ctl_api.h>        // Do³¹czam bibliotekê konieczn¹ do przerwañ

#define LCD_BACKLIGHT 20    // Podstawiam 20 za LCD_BACKLIGHT - dla czytelnoœci
#define BUTTON_SW1 24       // Podstawiam 24 za BUTTON_SW1 - dla czytelnoœci
#define BUTTON_SW2 25       // Podstawiam 25 za BUTTON_SW2 - dla czytelnoœci
#define PIOB 1              // Podstawiam 1 za PIOB - dla czytelnoœci
#define ENABLE 1            // Podstawiam 1 za ENABLE - dla czytelnoœci
#define DISABLE 0           // Podstawiam 0 za DISABLE - dla czytelnoœci
#define PIO_CONTROLLER_B 3 // Podstawiam 3 za PIO_CONTROLLER_B - dla czytelnoœci
#define INT_PRIORITY 1      // Podstawiam 1 za INT_PRIORITY - dla czytelnoœci

// Procedura obs³ugi przerwania
void button_int() {
  // Zapamiêtujê stan rejestru statusu przerwañ w kontrolerze PIOB
  int interrupt_status = PIOB_ISR;
  if(interrupt_status & (1 << BUTTON_SW1)) { // Je¿eli wcisn¹³em przycisk SW1
    PIOB_output_state(LCD_BACKLIGHT, ENABLE);   // W³¹cz podœwietlenie
  }
  else if(interrupt_status & (1 << BUTTON_SW2)) {  // Je¿eli wcisn¹³em przycisk SW2
    PIOB_output_state(LCD_BACKLIGHT, DISABLE);  // Wy³¹cz podœwietlenie
  }
}
// G³ówna funkcja
int main(void) {
  PIO_clock_enable(ENABLE,PIOB);              // W³¹czam zegar peryferiów dla kontrolera PIOB
  PIOB_enable(LCD_BACKLIGHT, ENABLE);         // W³¹czam pin LCD_BACKLIGHT
  PIOB_output_enable(LCD_BACKLIGHT, ENABLE);  // Ustawiam pin LCD_BACKLIGHT jako wyjœcie
  PIOB_IER = 1<<BUTTON_SW1 | 1<<BUTTON_SW2;   // W³¹czam przerwania dla przycisków SW1 i SW2

  ctl_global_interrupts_disable();  // Globalnie wy³¹czam przerwania
  // Konfigurujê przerwanie od kontrolera PIOB, czyli ustawiam wektor przerwania jako PIOB,
  // z priorytetem 1, z sta³ym wektorem przerwania, z metod¹ do obs³ugi przerwania jako
  // "button_int", i bez zwracania wska¿nika do funkcji, która poprzednio obs³ugiwa³a to
  // przerwanie (przesy³am 0).
  ctl_set_isr(PIO_CONTROLLER_B,INT_PRIORITY,CTL_ISR_TRIGGER_FIXED,button_int,0);
  ctl_unmask_isr(PIO_CONTROLLER_B); // W³¹czam programowe przerwania od timera
  ctl_global_interrupts_enable();   // Globalnie w³¹czam przerwania
 
  while(1); //Nieskoñczona pêtla g³ówna
}