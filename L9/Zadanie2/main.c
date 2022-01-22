#include "PIO_library.h"    // Dołączam moją bibliotekę

#define LCD_BL 20       // Makro dla czytelności
#define BUTTON_SW1 24   // Makro dla czytelności
#define BUTTON_SW2 25   // Makro dla czytelności
#define PIOB 1          // Makro dla czytelności
#define ENABLE 1        // Makro dla czytelności
#define DISABLE 0       // Makro dla czytelności

int main() // Funkcja główna
{
    // Włączam zegar dla kontrolera PIOB
    PIO_clock_enable(ENABLE,PIOB);
    // Włączam obsługę pinu 20 w kontrolerze PIOB 
    PIOB_enable(LCD_BL, ENABLE);
    // Ustawiam pin 20 jako wyjście
    PIOB_output_enable(LCD_BL, ENABLE);
  
    while(1) // Nieskończona pętla
    {
        // Jeżeli przycisk SW1 jest wciśnięty
        if(SW_odczyt(BUTTON_SW1)
        {
            // Włączam podświetlenie ekranu
            PIOB_output_state(LCD_BL, ENABLE);
            // Czekam aż użytkownik puści przycisk
            SW_czytaj(BUTTON_SW1);
        }
        // Jeżeli natomiast przycisk SW2 jest wciśnięty
        else if(SW_odczyt(BUTTON_SW2)
        {
            // Wyłączam podświetlenie ekranu
            PIOB_output_state(LCD_BL, DISABLE);
            // Czekam aż użytkownik puści przycisk
            SW_czytaj(BUTTON_SW2);
        }
    }
    return 0;
}
