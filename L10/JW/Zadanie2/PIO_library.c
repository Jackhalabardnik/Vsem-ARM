#include "PIO_library.h"    // Do³¹czam moj¹ bibliotekê

/*  Funkcja do realizowania opóŸnieñ
*   ms - liczba milisekund, jakie trzeba odczekaæ
*   Nic nie zwraca
*/
void time_delay(unsigned int ms)
{
    // Pierwsza pêtla odliczaj¹ca milisekundy
    for( volatile int aa=0;aa<=ms;aa++)   
    {
        // Druga pêtla odliczaj¹ca jedn¹ milisekundê
        for( volatile int bb=0;bb<=3000;bb++)
        {
            __asm__("NOP");
        }
    }
}

/*  Funkcja do w³¹czania i wy³¹czania zegara dla peryferiów
*   pio_pcer - w³¹czenie (1) lub wy³¹czenie (0) zegara
*   a_b - kontroler peryferiów: PIOA (0) lub PIOB(1)
*   Nic nie zwraca
*/
void PIO_clock_enable(unsigned int pio_pcer, unsigned int a_b)
{
    if(pio_pcer==1)
    {
        // W³¹czam kontroler ustawiaj¹c bit nr. 2 dla PIOA lub 3 dla PIOB
        PMC_PCER = 1 << a_b + 2;
    }

    if(pio_pcer==0)
    {
        // Wy³¹czam kontroler ustawiaj¹c bit nr. 2 dla PIOA lub 3 dla PIOB
        PMC_PCDR = 1 << a_b + 2;
    }
}

/*  Funkcja do w³¹czania i wy³¹czania obs³ugi pinów w kontrolerze PIOB
*   pin_number - numer pinu do w³¹czenia w kontrolerze PIOB 
*   enable - w³¹czenie (1) lub wy³¹czenie (0) danego pinu
*   Nic nie zwraca
*/
void PIOB_enable(unsigned int pin_number, unsigned int enable) 
{
    if(enable == 1)
    {
        // W³¹czam obs³ugê pinu ustawiaj¹c bit odpowiadaj¹cy danemu pinowi
        PIOB_PER = 1 << pin_number;
    }

    if(enable == 0)
    {
        // Wy³¹czam obs³ugê pinu ustawiaj¹c bit odpowiadaj¹cy danemu pinowi
        PIOB_PDR = 1 << pin_number;
    }
}

/*  Funkcja do ustawiania pinów w kontrolerze PIOB jako wejœcie lub wyjœcie
*   pin_number - numer pinu do skonfigurowania w kontrolerze PIOB 
*   enable - ustawianie pinu jako wyjœcie (1) lub wejœcie (0)
*   Nic nie zwraca
*/
void PIOB_output_enable(unsigned int pin_number, unsigned int enable)
{ 
    if(enable == 0)
    {
        // Ustawiam pin jako wejœcie
        PIOB_ODR = 1 << pin_number;
    }

    if(enable == 1)
    {
        // Ustawiam pin jako wyjœcie
        PIOB_OER = 1 << pin_number;
    }  
}

/*  Funkcja do ustawiania stanu pinów w kontrolerze PIOB
*   pin_number - numer pinu do skonfigurowania w kontrolerze PIOB 
*   enable - ustawianie pinu w stan wysoki (1) lub niski (1)
*   Nic nie zwraca
*/
void PIOB_output_state(unsigned int pin_number, unsigned int enable)
{
    if(enable == 0)
    {
        // Ustawiam pin w stan niski
        PIOB_CODR = 1 << pin_number;
    }

    if(enable == 1)
    {
        // Ustawiam pin w stan wysoki
        PIOB_SODR = 1 << pin_number;
    }  
}

/*  Funkcja do negowania stanu pinów w kontrolerze PIOB
*   pin_number - numer pinu do zanegowania
*   Nic nie zwraca
*/
void PIOB_output_negate(unsigned int pin_number) 
{
    // Oznaczam piny, których stan bêdê zmienia³
    PIOB_OWER = 1 << pin_number;
    // Negujê stan pinu
    PIOB_ODSR ^= 1 << pin_number;
}

/*  Funkcja do pobierania stanu pinu z kontrolera B
*   SW_number - numer pinu, którego stan bêdê pobiera³
*   Zwraca liczbê oznaczaj¹c¹ stan wysoki (1) lub stan niski (0)
*/
unsigned int SW_odczyt(unsigned int SW_number)
{
    // Zwracam wartoœæ bitu, który odpowiada danemu pinowi
    return PIOB_PDSR & 1 << SW_number;
}

/*  Funkcja do debouncingu przycisków
*   SW_number - numer pinu, którego stan bêdê sprawdza³
*   Nic nie zwraca
*/
void SW_czytaj(unsigned int SW_number)
{
    time_delay(75); // Czekam, a¿ stan przycisku siê ustabilizuje
    // Czekam tak d³ugo, jak przycisk bêdzie wciœniêty
    while((PIOB_PDSR & 1 << SW_number) == 0);
}