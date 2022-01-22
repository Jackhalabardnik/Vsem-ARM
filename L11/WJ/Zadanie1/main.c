#include "menu.h"   // Plik zawieraj¹cy menu

volatile struct MN *actual_node = &menu_1;  // Zmienna wskazuj¹ca na aktualny element menu

#define PIOA PMC_PCER_PIOA    // Podstawiam PIOA za PMC_PCER_PIOA - dla czytelnoœci 
#define PIOA_VEC 2            // Podstawiam PIOA_VEC za 2 - dla czytelnoœci 
#define PIOA_IMPORTANCE 1     // Podstawiam PIOA_IMPORTANCE za 1 - dla czytelnoœci 

#define DELAY 500             // Podstawiam DELAY za 500 - dla czytelnoœci 

/*  Struktura do wywo³ywania opóŸnieñ
*   n - d³ugoœæ opóŸnienia w milisekundach
*   nic nie zwraca
*/
void delay(int n) {
    for (int i = 3000 * n; i > 0; i--) {
        __asm__("nop");   // Wywo³ujê pust¹ intrukcjê dla wykonania opóŸnienia
    }
}

/*  Enum do odczytywanych stanów joysticka
*   Podstawiam aliasy pinów za odpowiednie oznaczenia dla czytelnoœci
*/
enum JOYSTICK {
    UP = PIOA_PER_P9,
    DOWN = PIOA_PER_P8,
    LEFT = PIOA_PER_P7,
    RIGHT = PIOA_PER_P14
};

/*  Funkcja do nawigowania po menu, wywo³ywana podczas obs³ugi przerwania od PIOA 
*   nic nie zwraca
*/
void navigate_menu() {
    // Pobieram informacjê o kierunku naciœniêcia joysticka i resetujê rejestr PIOA_ISR
    enum JOYSTICK choice = PIOA_ISR;    

    // Wykonujê odpowiednie akcje w zale¿noœci od tego jaki by³ kierunek naciœniêcia
    switch (choice) {
        case UP:    // Góra
            if(actual_node->is_inside_action == 0)    // Je¿eli aktualnie nie jest uruchomiona jakaœ funkcja
            {
                actual_node = actual_node->previous;  // Cofnij siê do poprzedniego punktu menu
                display_menu(actual_node);            // Wyœwietl menu
            }
            break;
        case DOWN:  // Dó³
            if(actual_node->is_inside_action == 0)    // Je¿eli aktualnie nie jest uruchomiona jakaœ funkcja
            {
                actual_node = actual_node->next;      // PrzejdŸ do nastêpnego punktu menu
                display_menu(actual_node);            // Wyœwietl menu
            }
            break;
        case LEFT:  // Lewo
            if(actual_node->is_inside_action == 0)    // Je¿eli aktualnie nie jest uruchomiona jakaœ funkcja
            {
                if(actual_node->function) {             // Je¿eli do tego elementu jest przypisana funkcja
                    actual_node->is_inside_action = 1;  // Zapamiêtaj ¿e funkcja zosta³a wywo³ana
                    actual_node->function();            // Wywo³aj funkcjê
                }
                if(actual_node->child) {                // Je¿eli ten element ma element - dziecko (submenu)
                    actual_node = actual_node->child;   // PrzejdŸ do submenu
                    display_menu(actual_node);          // Wyœwietl submenu
                }
            }
            break;
        case RIGHT: // Prawo
            if(actual_node->is_inside_action) {   // Je¿eli aktualnie jest uruchomiona jakaœ funkcja
                actual_node->is_inside_action = 0;      // Zapamiêtaj ¿e funkcja jest wy³¹czona
                if(animation_active) {            // Je¿eli animacja jest aktywna
                    animation_active = 0;         // Wy³¹cz animacjê
                }
                display_menu(actual_node);  // Wyœwietl menu (czyli wyma¿ to co funkcja narysowa³a na ekranie)
            }
            else if (actual_node->root) {   // Je¿eli dany element posiada rodzica (wy¿szy poziom menu)
                actual_node = actual_node->root;  // PrzejdŸ do rodzica (do wy¿szego poziomu menu)
                display_menu(actual_node);        // Wyœwietl menu
            }
            break;
    }
}

/*  Funkcja do zainicjalizowania mechanizmu przerwañ
*   nic nie zwraca
*/
void interrupt_init() {

  PMC_PCER |= PIOA;   // W³¹czam zegar dla kontrolera PIOA
  PIOA_IER |= UP | DOWN | LEFT | RIGHT;   // W³¹czam obs³ugê przerwañ dla joysticka

  ctl_global_interrupts_disable();  // Wy³¹czam globaln¹ obs³ugê przerwañ
  // Ustawiam ¿e przerwania od wektora PIOA zostanie obs³u¿one z priorytetem 1 na zboczu narastaj¹cym
  // zostanie obs³u¿one procedur¹ 'navigate_menu'. Nie chcê dostaæ wskaŸnika do poprzedniej procedury
  // obs³uguj¹cej to przerwanie, wiêc jako ostatni argument przekazujê '0' 
  ctl_set_isr(PIOA_VEC, PIOA_IMPORTANCE, CTL_ISR_TRIGGER_POSITIVE_EDGE, navigate_menu, 0);
  ctl_unmask_isr(PIOA_VEC);       // W³¹czam obs³uge przerwañ dla wektora PIOA
  ctl_global_interrupts_enable(); // W³¹czam globaln¹ obs³ugê przerwañ
}

/*  Funkcja g³ówna programu
*   zwraca kod wykonania: 0 - poprawne wykonanie, w innym przypadku kod b³êdu
*/
int main() {

    InitLCD();        // Inicjalizujê ekran LCD
    LCDClearScreen(); // Czyszczê ekran LCD

    interrupt_init(); // Inicjalizujê joystick

    display_menu(actual_node);  // Wyœwietlam menu g³ówne

    // Wykorzystujê pêtlê g³ówn¹ do obs³ugi animacji
    while(1) {
      // Je¿eli animacja jest aktywna wykonujê kolejne kroki
      if(animation_active) { show_photo(1); } // Wyœwietlam obraz 1
      if(animation_active) { delay(DELAY); }  // Czekam 500ms
      if(animation_active) { show_photo(2); } // Wyœwietlam obraz 2
      if(animation_active) { delay(DELAY); }  // Czekam 500ms
    }

    return 0;   // Zwracam kod poprawnego wykonania programu
}