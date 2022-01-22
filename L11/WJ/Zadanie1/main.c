#include "menu.h"   // Plik zawieraj�cy menu

volatile struct MN *actual_node = &menu_1;  // Zmienna wskazuj�ca na aktualny element menu

#define PIOA PMC_PCER_PIOA    // Podstawiam PIOA za PMC_PCER_PIOA - dla czytelno�ci 
#define PIOA_VEC 2            // Podstawiam PIOA_VEC za 2 - dla czytelno�ci 
#define PIOA_IMPORTANCE 1     // Podstawiam PIOA_IMPORTANCE za 1 - dla czytelno�ci 

#define DELAY 500             // Podstawiam DELAY za 500 - dla czytelno�ci 

/*  Struktura do wywo�ywania op�nie�
*   n - d�ugo�� op�nienia w milisekundach
*   nic nie zwraca
*/
void delay(int n) {
    for (int i = 3000 * n; i > 0; i--) {
        __asm__("nop");   // Wywo�uj� pust� intrukcj� dla wykonania op�nienia
    }
}

/*  Enum do odczytywanych stan�w joysticka
*   Podstawiam aliasy pin�w za odpowiednie oznaczenia dla czytelno�ci
*/
enum JOYSTICK {
    UP = PIOA_PER_P9,
    DOWN = PIOA_PER_P8,
    LEFT = PIOA_PER_P7,
    RIGHT = PIOA_PER_P14
};

/*  Funkcja do nawigowania po menu, wywo�ywana podczas obs�ugi przerwania od PIOA 
*   nic nie zwraca
*/
void navigate_menu() {
    // Pobieram informacj� o kierunku naci�ni�cia joysticka i resetuj� rejestr PIOA_ISR
    enum JOYSTICK choice = PIOA_ISR;    

    // Wykonuj� odpowiednie akcje w zale�no�ci od tego jaki by� kierunek naci�ni�cia
    switch (choice) {
        case UP:    // G�ra
            if(actual_node->is_inside_action == 0)    // Je�eli aktualnie nie jest uruchomiona jaka� funkcja
            {
                actual_node = actual_node->previous;  // Cofnij si� do poprzedniego punktu menu
                display_menu(actual_node);            // Wy�wietl menu
            }
            break;
        case DOWN:  // D�
            if(actual_node->is_inside_action == 0)    // Je�eli aktualnie nie jest uruchomiona jaka� funkcja
            {
                actual_node = actual_node->next;      // Przejd� do nast�pnego punktu menu
                display_menu(actual_node);            // Wy�wietl menu
            }
            break;
        case LEFT:  // Lewo
            if(actual_node->is_inside_action == 0)    // Je�eli aktualnie nie jest uruchomiona jaka� funkcja
            {
                if(actual_node->function) {             // Je�eli do tego elementu jest przypisana funkcja
                    actual_node->is_inside_action = 1;  // Zapami�taj �e funkcja zosta�a wywo�ana
                    actual_node->function();            // Wywo�aj funkcj�
                }
                if(actual_node->child) {                // Je�eli ten element ma element - dziecko (submenu)
                    actual_node = actual_node->child;   // Przejd� do submenu
                    display_menu(actual_node);          // Wy�wietl submenu
                }
            }
            break;
        case RIGHT: // Prawo
            if(actual_node->is_inside_action) {   // Je�eli aktualnie jest uruchomiona jaka� funkcja
                actual_node->is_inside_action = 0;      // Zapami�taj �e funkcja jest wy��czona
                if(animation_active) {            // Je�eli animacja jest aktywna
                    animation_active = 0;         // Wy��cz animacj�
                }
                display_menu(actual_node);  // Wy�wietl menu (czyli wyma� to co funkcja narysowa�a na ekranie)
            }
            else if (actual_node->root) {   // Je�eli dany element posiada rodzica (wy�szy poziom menu)
                actual_node = actual_node->root;  // Przejd� do rodzica (do wy�szego poziomu menu)
                display_menu(actual_node);        // Wy�wietl menu
            }
            break;
    }
}

/*  Funkcja do zainicjalizowania mechanizmu przerwa�
*   nic nie zwraca
*/
void interrupt_init() {

  PMC_PCER |= PIOA;   // W��czam zegar dla kontrolera PIOA
  PIOA_IER |= UP | DOWN | LEFT | RIGHT;   // W��czam obs�ug� przerwa� dla joysticka

  ctl_global_interrupts_disable();  // Wy��czam globaln� obs�ug� przerwa�
  // Ustawiam �e przerwania od wektora PIOA zostanie obs�u�one z priorytetem 1 na zboczu narastaj�cym
  // zostanie obs�u�one procedur� 'navigate_menu'. Nie chc� dosta� wska�nika do poprzedniej procedury
  // obs�uguj�cej to przerwanie, wi�c jako ostatni argument przekazuj� '0' 
  ctl_set_isr(PIOA_VEC, PIOA_IMPORTANCE, CTL_ISR_TRIGGER_POSITIVE_EDGE, navigate_menu, 0);
  ctl_unmask_isr(PIOA_VEC);       // W��czam obs�uge przerwa� dla wektora PIOA
  ctl_global_interrupts_enable(); // W��czam globaln� obs�ug� przerwa�
}

/*  Funkcja g��wna programu
*   zwraca kod wykonania: 0 - poprawne wykonanie, w innym przypadku kod b��du
*/
int main() {

    InitLCD();        // Inicjalizuj� ekran LCD
    LCDClearScreen(); // Czyszcz� ekran LCD

    interrupt_init(); // Inicjalizuj� joystick

    display_menu(actual_node);  // Wy�wietlam menu g��wne

    // Wykorzystuj� p�tl� g��wn� do obs�ugi animacji
    while(1) {
      // Je�eli animacja jest aktywna wykonuj� kolejne kroki
      if(animation_active) { show_photo(1); } // Wy�wietlam obraz 1
      if(animation_active) { delay(DELAY); }  // Czekam 500ms
      if(animation_active) { show_photo(2); } // Wy�wietlam obraz 2
      if(animation_active) { delay(DELAY); }  // Czekam 500ms
    }

    return 0;   // Zwracam kod poprawnego wykonania programu
}