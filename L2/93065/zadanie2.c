#define F_CPU 1000000 // Ustalenie częstotliwości zegara na zgodny z zestawem w laboratorium
// Konieczne biblioteki
#include <avr/io.h> // Obsługa portów
#include <util/delay.h> // Obsługa opóźnień
 
unsigned long pczekaj=1500; // zmienna zawierająca wartość opóźnienia
 
int main(void) //program główny 
{ 
	 DDRB=0xff;  //konfiguracja wszystkich wyprowadzeń portu B jako wyjścia
	  
	 while(1)    //nieskończona pętla główna programu 
	 { 
		  //efekt węża 
		  for(unsigned char licznik=0;licznik<10;licznik++) //pętla długości trwania efektu (liczba cykli danego efektu) 
		  { 
			   PORTB=0;  //wygaś LED-y 
			   _delay_ms(pczekaj); //opóźnij o zadany czas
			   for(int i=7;i>=0;i--) //pętla zmieniająca fazę efektu 
			   { 
				    PORTB|=_BV(i); //wysteruj (zapal) pojedynczego LED-a 
				    _delay_ms(pczekaj); //opóźnij o zadany czas
			   } 
			   for(int i=7;i>=0;i--)   //pętla zmieniająca fazę efektu 
			   { 
				   PORTB&=~_BV(i); //wysteruj (zgaś) pojedynczego LED-a 
				   _delay_ms(pczekaj); //opóźnij o zadany czas
			   } 
		  } 

		  //efekt biegnącego punktu 
		  for(unsigned char licznik=0;licznik<10;licznik++)  //pętla długości trwania efektu (liczba cykli danego efektu) 
		  { 
			   for(unsigned char ledy=0x7f;ledy!=0xff;ledy=(ledy>>1) + 128) //pętla zmieniająca fazę efektu 
			   { 
				    PORTB=ledy; //wysterowanie LED-ów zgodne z wartością zmiennej ledy 
				    _delay_ms(pczekaj); //opóźnij o zadany czas
			   } 
		  } 
	 } 
}
