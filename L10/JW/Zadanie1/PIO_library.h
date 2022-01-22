#include <targets\AT91SAM7.h> // Dołączam biliotekę dla zestawu w labolatorium

/*  Funkcja do realizowania opóźnień
*   ms - liczba milisekund, jakie trzeba odczekać
*   Nic nie zwraca
*/
void time_delay(unsigned int ms);

/*  Funkcja do włączania i wyłączania zegara dla peryferiów
*   pio_pcer - włączenie (1) lub wyłączenie (0) zegara
*   a_b - kontroler peryferiów: PIOA (0) lub PIOB(1)
*   Nic nie zwraca
*/
void PIO_clock_enable(unsigned int pio_pcer, unsigned int a_b);

/*  Funkcja do włączania i wyłączania obsługi pinów w kontrolerze PIOB
*   pin_number - numer pinu do włączenia w kontrolerze PIOB 
*   enable - włączenie (1) lub wyłączenie (0) danego pinu
*   Nic nie zwraca
*/
void PIOB_enable(unsigned int pin_number, unsigned int enable);

/*  Funkcja do ustawiania pinów w kontrolerze PIOB jako wejście lub wyjście
*   pin_number - numer pinu do skonfigurowania w kontrolerze PIOB 
*   enable - ustawianie pinu jako wyjście (1) lub wejście (0)
*   Nic nie zwraca
*/
void PIOB_output_enable(unsigned int pin_number, unsigned int enable);

/*  Funkcja do ustawiania stanu pinów w kontrolerze PIOB
*   pin_number - numer pinu do skonfigurowania w kontrolerze PIOB 
*   enable - ustawianie pinu w stan wysoki (1) lub niski (1)
*   Nic nie zwraca
*/
void PIOB_output_state(unsigned int pin_number, unsigned int enable);

/*  Funkcja do negowania stanu pinów w kontrolerze PIOB
*   pin_number - numer pinu do zanegowania
*   Nic nie zwraca
*/
void PIOB_output_negate(unsigned int pin_number);

/*  Funkcja do pobierania stanu pinu z kontrolera B
*   SW_number - numer pinu, którego stan będę pobierał
*   Zwraca liczbę oznaczającą stan wysoki (1) lub stan niski (0)
*/
unsigned int SW_odczyt(unsigned int SW_number);

/*  Funkcja do debouncingu przycisków
*   SW_number - numer pinu, którego stan będę sprawdzał
*   Nic nie zwraca
*/
void SW_czytaj(unsigned int SW_number);