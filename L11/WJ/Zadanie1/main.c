#include "menu.h"

volatile struct MN *actual_node = &menu_1;

#define PIOA PMC_PCER_PIOA
#define PIOA_VEC 2
#define PIOA_IMPORTANCE 1

#define DELAY 500

void delay(int n) {
    for (int i = 3000 * n; i > 0; i--) {
        __asm__("nop");
    }
}

enum JOYSTICK {
    UP = PIOA_PER_P9,
    DOWN = PIOA_PER_P8,
    LEFT = PIOA_PER_P7,
    RIGHT = PIOA_PER_P14
};

void navigate_menu() {
    enum JOYSTICK choice = PIOA_ISR;

    switch (choice) {
        case UP:
            if(actual_node->is_inside_action == 0)
            {
                actual_node = actual_node->previous;
                display_menu(actual_node);
            }
            break;
        case DOWN:
            if(actual_node->is_inside_action == 0)
            {
                actual_node = actual_node->next;
                display_menu(actual_node);
            }
            break;
        case LEFT:
            if(actual_node->is_inside_action == 0)
            {
                if(actual_node->function) {
                    actual_node->is_inside_action = 1;
                    actual_node->function();
                }
                if(actual_node->child) {
                    actual_node = actual_node->child;
                    display_menu(actual_node);
                }
            }
            break;
        case RIGHT:
            if(actual_node->is_inside_action) {
                actual_node->is_inside_action = 0;
                if(animation_active) {
                    animation_active = 0;
                }
                display_menu(actual_node);
            }
            else if (actual_node->root) {
                actual_node = actual_node->root;
                display_menu(actual_node);
            }
            break;
    }
}

void interrupt_init() {

  PMC_PCER |= PIOA;
  PIOA_IER |= UP | DOWN | LEFT | RIGHT;

  ctl_global_interrupts_disable();
  ctl_set_isr(PIOA_VEC, PIOA_IMPORTANCE, CTL_ISR_TRIGGER_POSITIVE_EDGE, navigate_menu, 0);
  ctl_unmask_isr(2);
  ctl_global_interrupts_enable();
}

int main() {

    InitLCD();
    LCDClearScreen();

    interrupt_init();

    display_menu(actual_node);

    while(1) {
      if(animation_active) { show_photo(1); }
      if(animation_active) { delay(DELAY); }
      if(animation_active) { show_photo(2); }
      if(animation_active) { delay(DELAY); }
    }

    return 0;
}