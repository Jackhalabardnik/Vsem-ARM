#pragma once    // Do³¹cz ten plik tylko raz
#include <string.h>         // Biblioteka do funkcji strcat
#include "menu_functions.h" // Funkcje menu
#include "menu_texts.h"     // Teksty menu

#define MN Menu_node    // Alias dla czytelnoœci
#define BUFFER_SIZE 64  // Alias rozmiaru bufora dla czytelnoœci

/*  Struktura do przechowywania pojedynczego elementu menu
*   previous - adres poprzedniego elementu, NULL - brak poprzedniego elementu
*   next - adres nastêpnego elementu, NULL - brak nastêpnego elementu
*   root - adres elementu - rodzica, NULL - brak elementu - rodzica
*   child - adres elementu - dziecka, NULL - brak elementu - dziecka (za to musi byæ funkcja)
*   function - funkcja do wykonania, NULL - brak funkcji (za to musi byæ element - dziecko)
*   node_number - numer opcji w menu
*   is_inside_action - czy zosta³a wykonana funkcja okreœlona w danym elemencie
*   menu_text - adres menu tekstowego do wyœwietlenia
*/
struct Menu_node {
    struct MN *previous, *next, *root, *child;

    void (*function)(void);

    int node_number, is_inside_action;
    char **menu_text;
};

/*  Struktura do wyœwietlania menu
*   node - aktualny element menu
*   nic nie zwraca
*/
void display_menu(volatile struct MN *node) {
    int i = 0;    // Zmienna dla pamiêtania numeru opcji który jest wyœwietlany
    for (char **text = node->menu_text; *text; text++) {  // iterujê po ka¿dej opcji do wyœwietlenia
        // Je¿eli wyœwietlam tekst danej opcji to dodajê znak '>' w celu zaznaczenia ¿e to ta opcja
        if (i == node->node_number) {   
            char choosen_pos[BUFFER_SIZE] = ">";    // Muszê daæ odpowiednio du¿y bufor dla funkcji strcat
            strcat(choosen_pos, *text);             // Dodajê znak '>' przed nazwê opcji
            LCDPutStr(choosen_pos, 25+(i*25), 5, SMALL, BLACK, WHITE);  // Wyœwietlam opcjê menu na ekranie
        } else {
            LCDPutStr(*text, 25+(i*25), 5, SMALL, BLACK, WHITE);  // Wyœwietlam opcjê menu na ekranie
        }
        i++;  // Zwiêkszam licznik
    }
}

// Definicje wyprzedzaj¹ce elementów menu
struct MN menu_1, menu_2, menu_3, menu_4;
struct MN menu_1_1, menu_1_2, menu_1_3;
struct MN menu_3_1, menu_3_2, menu_3_3, menu_3_4;

/*  Okreœlenie elementów menu
*   Jest to zwyczajne po³¹czenie ze sob¹ kolejnych elementów menu
*   i przypisanie im odpowiednich funkcji i linków do odpowiedniego
*   tekstu do wyœwietlenia. Nic do komentowania.
*/

struct MN menu_1 = {
        &menu_4,
        &menu_2,
        NULL,
        &menu_1_1,
        NULL,
        0,
        0,
        main_menu_texts
};

struct MN menu_2 = {
        &menu_1,
        &menu_3,
        NULL,
        NULL,
        &image_with_text,
        1,
        0,
        main_menu_texts
};

struct MN menu_3 = {
        &menu_2,
        &menu_4,
        NULL,
        &menu_3_1,
        NULL,
        2,
        0,
        main_menu_texts
};

struct MN menu_4 = {
        &menu_3,
        &menu_1,
        NULL,
        NULL,
        &about_author,
        3,
        0,
        main_menu_texts
};

struct MN menu_1_1 = {
        &menu_1_3,
        &menu_1_2,
        &menu_1,
        NULL,
        &image_1,
        0,
        0,
        sub_menu_1_texts
};

struct MN menu_1_2 = {
        &menu_1_1,
        &menu_1_3,
        &menu_1,
        NULL,
        &image_2,
        1,
        0,
        sub_menu_1_texts
};

struct MN menu_1_3 = {
        &menu_1_2,
        &menu_1_1,
        &menu_1,
        NULL,
        &animation,
        2,
        0,
        sub_menu_1_texts
};

struct MN menu_3_1 = {
        &menu_3_4,
        &menu_3_2,
        &menu_3,
        NULL,
        &square,
        0,
        0,
        sub_menu_3_texts
};

struct MN menu_3_2 = {
        &menu_3_1,
        &menu_3_3,
        &menu_3,
        NULL,
        &circle,
        1,
        0,
        sub_menu_3_texts
};

struct MN menu_3_3 = {
        &menu_3_2,
        &menu_3_4,
        &menu_3,
        NULL,
        &triangle,
        2,
        0,
        sub_menu_3_texts
};

struct MN menu_3_4 = {
        &menu_3_3,
        &menu_3_1,
        &menu_3,
        NULL,
        &trapeze,
        3,
        0,
        sub_menu_3_texts
};