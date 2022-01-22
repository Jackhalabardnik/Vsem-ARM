#include "PIO_library.h"    // Do��czam moj� bibliotek�

/*  Funkcja do realizowania op�nie�
*   ms - liczba milisekund, jakie trzeba odczeka�
*   Nic nie zwraca
*/
void time_delay(unsigned int ms)
{
    // Pierwsza p�tla odliczaj�ca milisekundy
    for( volatile int aa=0;aa<=ms;aa++)   
    {
        // Druga p�tla odliczaj�ca jedn� milisekund�
        for( volatile int bb=0;bb<=3000;bb++)
        {
            __asm__("NOP");
        }
    }
}

/*  Funkcja do w��czania i wy��czania zegara dla peryferi�w
*   pio_pcer - w��czenie (1) lub wy��czenie (0) zegara
*   a_b - kontroler peryferi�w: PIOA (0) lub PIOB(1)
*   Nic nie zwraca
*/
void PIO_clock_enable(unsigned int pio_pcer, unsigned int a_b)
{
    if(pio_pcer==1)
    {
        // W��czam kontroler ustawiaj�c bit nr. 2 dla PIOA lub 3 dla PIOB
        PMC_PCER = 1 << a_b + 2;
    }

    if(pio_pcer==0)
    {
        // Wy��czam kontroler ustawiaj�c bit nr. 2 dla PIOA lub 3 dla PIOB
        PMC_PCDR = 1 << a_b + 2;
    }
}

/*  Funkcja do w��czania i wy��czania obs�ugi pin�w w kontrolerze PIOB
*   pin_number - numer pinu do w��czenia w kontrolerze PIOB 
*   enable - w��czenie (1) lub wy��czenie (0) danego pinu
*   Nic nie zwraca
*/
void PIOB_enable(unsigned int pin_number, unsigned int enable) 
{
    if(enable == 1)
    {
        // W��czam obs�ug� pinu ustawiaj�c bit odpowiadaj�cy danemu pinowi
        PIOB_PER = 1 << pin_number;
    }

    if(enable == 0)
    {
        // Wy��czam obs�ug� pinu ustawiaj�c bit odpowiadaj�cy danemu pinowi
        PIOB_PDR = 1 << pin_number;
    }
}

/*  Funkcja do ustawiania pin�w w kontrolerze PIOB jako wej�cie lub wyj�cie
*   pin_number - numer pinu do skonfigurowania w kontrolerze PIOB 
*   enable - ustawianie pinu jako wyj�cie (1) lub wej�cie (0)
*   Nic nie zwraca
*/
void PIOB_output_enable(unsigned int pin_number, unsigned int enable)
{ 
    if(enable == 0)
    {
        // Ustawiam pin jako wej�cie
        PIOB_ODR = 1 << pin_number;
    }

    if(enable == 1)
    {
        // Ustawiam pin jako wyj�cie
        PIOB_OER = 1 << pin_number;
    }  
}

/*  Funkcja do ustawiania stanu pin�w w kontrolerze PIOB
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

/*  Funkcja do negowania stanu pin�w w kontrolerze PIOB
*   pin_number - numer pinu do zanegowania
*   Nic nie zwraca
*/
void PIOB_output_negate(unsigned int pin_number) 
{
    // Oznaczam piny, kt�rych stan b�d� zmienia�
    PIOB_OWER = 1 << pin_number;
    // Neguj� stan pinu
    PIOB_ODSR ^= 1 << pin_number;
}

/*  Funkcja do pobierania stanu pinu z kontrolera B
*   SW_number - numer pinu, kt�rego stan b�d� pobiera�
*   Zwraca liczb� oznaczaj�c� stan wysoki (1) lub stan niski (0)
*/
unsigned int SW_odczyt(unsigned int SW_number)
{
    // Zwracam warto�� bitu, kt�ry odpowiada danemu pinowi
    return PIOB_PDSR & 1 << SW_number;
}

/*  Funkcja do debouncingu przycisk�w
*   SW_number - numer pinu, kt�rego stan b�d� sprawdza�
*   Nic nie zwraca
*/
void SW_czytaj(unsigned int SW_number)
{
    time_delay(75); // Czekam, a� stan przycisku si� ustabilizuje
    // Czekam tak d�ugo, jak przycisk b�dzie wci�ni�ty
    while((PIOB_PDSR & 1 << SW_number) == 0);
}