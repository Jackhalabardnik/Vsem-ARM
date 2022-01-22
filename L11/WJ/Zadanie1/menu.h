#pragma once
#include <string.h>
#include "menu_functions.h"
#include "menu_texts.h"

#define MN Menu_node
#define BUFFER_SIZE 64

struct Menu_node {
    struct MN *previous, *next, *root, *child;

    void (*function)(void);

    int node_number, is_inside_action;
    const char **menu_text;
};

void display_menu(volatile struct MN *node) {
    int i = 0;
    for (const char **text = node->menu_text; *text; text++) {
        if (i == node->node_number) {
            char choosen_pos[BUFFER_SIZE] = ">";
            strcat(choosen_pos, *text);
            LCDPutStr(choosen_pos, 25+(i*25), 5, SMALL, BLACK, WHITE);
        } else {
            LCDPutStr(*text, 25+(i*25), 5, SMALL, BLACK, WHITE);
        }
        i++;
    }
}

struct MN menu_1, menu_2, menu_3, menu_4;
struct MN menu_1_1, menu_1_2, menu_1_3;
struct MN menu_3_1, menu_3_2, menu_3_3, menu_3_4;

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