#include <avr/io.h> // Konieczne biblioteki
 
unsigned long pczekaj=1500; // zmienna zawierająca wartość opóźnienia
 
void czekaj(unsigned long pt)  //procedura  opóźnienia  o  zadany  czas pt
{ 
 	for(;pt>0;pt--) //główna pętla opóźnienia
 	{ 
  		for(unsigned char tp1=255;tp1!=0;tp1--) // druga pętla opóźnienia
  			asm volatile("nop");  // Instrukcja konieczna do działania programu na fizycznej atmedze a nie tylko w HAPSIM
	} 
} 
 
int main(void) //program główny 
{ 
	 unsigned char ledy,i,licznik; // deklaracja zmiennych
	 DDRB=0xff;  //konfiguracja wszystkich wyprowadzeń portu B jako wyjścia
	  
	 while(1)    //nieskończona pętla główna programu 
	 { 
		  //efekt węża 
		  for(licznik=0;licznik<10;licznik++) //pętla długości trwania efektu (liczba cykli danego efektu) 
		  { 
			   PORTB=0;  //wygaś LED-y 
			   czekaj(pczekaj); //opóźnij o zadany czas
			   for(i=0;i<8;i++) //pętla zmieniająca fazę efektu 
			   { 
				    PORTB|=_BV(i); //wysteruj (zapal) pojedynczego LED-a 
				    czekaj(pczekaj); //opóźnij o zadany czas
			   } 
			   for(i=0;i<8;i++)   //pętla zmieniająca fazę efektu 
			   { 
				   PORTB&=~_BV(i); //wysteruj (zgaś) pojedynczego LED-a 
				   czekaj(pczekaj);  //opóźnij o zadany czas 
			   } 
		  } 
 
		  //efekt biegnącego punktu 
		  for(licznik=0;licznik<10;licznik++)  //pętla długości trwania efektu (liczba cykli danego efektu) 
		  { 
			   for(ledy=0xfe;ledy!=0xff;ledy=(ledy<<=1)+1) //pętla zmieniająca fazę efektu 
			   { 
				    PORTB=ledy; //wysterowanie LED-ów zgodne z wartością zmiennej ledy 
				    czekaj(pczekaj);  //opóźnij o zadany czas 
			   } 
		  } 
	 } 
}
