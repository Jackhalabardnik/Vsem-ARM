#include "PIO_library.h"    // Dołączam moją bibliotekę

#define LCD_BL 20   // Makro dla czytelności
#define PIOB 1      // Makro dla czytelności
#define ENABLE 1    // Makro dla czytelności
#define DISABLE 0   // Makro dla czytelności

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
        // Włączam podświetlenie ekranu
        PIOB_output_state(LCD_BL, ENABLE);
        time_delay(500); // Czekam 500ms
        // Wyłączam podświetlenie ekranu
        PIOB_output_state(LCD_BL, DISABLE);
        time_delay(500); // Czekam 500ms
    }
    return 0;   
}
