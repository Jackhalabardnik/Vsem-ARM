#include <targets\AT91SAM7.h>
#include <ctl_api.h>
#include "PCF8833U8_lcd.h"

#define DOWN PIOA_PER_P8
#define LEFT PIOA_PER_P7
#define UP PIOA_PER_P9
#define RIGHT PIOA_PER_P14

#define PIOA PMC_PCER_PIOA
#define PIOA_VEC 2
#define PIOA_IMPORTANCE 1

#define DELAY 500

volatile int animation_active = 0;
volatile int menu_level = 0;
volatile int main_menu_choice = 0;
volatile int sub_menu_choice = 0;

char* main_menu_str[4]= {
    "1.Obraz",
    "2.Obraz z tekstem",
    "3.Figury",
    "4.O autorze"
};


void delay(int n) {
    for (int i = 3000 * n; i > 0; i--) {
        __asm__("nop");
    }
}

void show_author_info() {
    LCDClearScreen();
    LCDPutStr("Jacek Wojcik", 45, 15, LARGE, BLACK, WHITE);
    LCDPutStr("10", 70, 50, LARGE, BLACK, WHITE);
}

int * get_colours(int option_coloured) {
  static int tab[4];
  for(int i = 0; i < 4; i++) {
    if(i == option_coloured) {
      tab[i] = YELLOW;
    }
    else {
      tab[i] = WHITE;
     }
  }
  return tab;
}

void show_main_menu() {
    LCDClearScreen();
    int* colours = get_colours(main_menu_choice);
   
    for(int i = 0; i < 4; i++) {
      LCDPutStr(main_menu_str[i], 25+(i*25), 5, SMALL, BLACK, colours[i]);
    }
}

void handle_interrupt() {
  int choice = PIOA_ISR;
 // switch(menu_level) {
   // case 0:
      switch(choice) {
        case UP:
          if(main_menu_choice > 0)
          {
            main_menu_choice--;
          }
          show_main_menu();
          break;
         case DOWN:
          if(main_menu_choice < 4)
          {
            main_menu_choice++;
          }
          show_main_menu();
          break;
      }
     // break;
  //}
}

void interrupt_init() {

  PMC_PCER |= PIOA;
  PIOA_IER |= UP | DOWN | LEFT | RIGHT;

  ctl_global_interrupts_disable();
  ctl_set_isr(PIOA_VEC, PIOA_IMPORTANCE, CTL_ISR_TRIGGER_POSITIVE_EDGE, handle_interrupt, 0);
  ctl_unmask_isr(2);
  ctl_global_interrupts_enable();
}

int main() {
  
    InitLCD();
    LCDClearScreen();

    interrupt_init();

    show_main_menu();

    while(1) {
      if(animation_active) { show_photo(1); }
      if(animation_active) { delay(DELAY); }
      if(animation_active) { show_photo(2); }
      if(animation_active) { delay(DELAY); }
    }

    return 0;
}