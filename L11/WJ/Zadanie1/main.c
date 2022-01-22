#include "menu.h"

volatile struct MN *actual_node = &menu_1;

enum JOYSTICK {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3
};

void navigate_menu(enum JOYSTICK choice) {
    printf("Choice: %d\n", choice);

    switch (choice) {
        case UP:
            if(actual_node->is_inside_action == 0)
            {
                actual_node = actual_node->previous;
                display_menu(actual_node);
            }
            break;
        case DOWN:
            if(actual_node->is_inside_action == 0)
            {
                actual_node = actual_node->next;
                display_menu(actual_node);
            }
            break;
        case LEFT:
            if(actual_node->is_inside_action == 0)
            {
                if(actual_node->function) {
                    actual_node->is_inside_action = 1;
                    actual_node->function();
                }
                if(actual_node->child) {
                    actual_node = actual_node->child;
                    display_menu(actual_node);
                }
            }
            break;
        case RIGHT:
            if(actual_node->is_inside_action) {
                actual_node->is_inside_action = 0;
                display_menu(actual_node);
            }
            else if (actual_node->root) {
                actual_node = actual_node->root;
                display_menu(actual_node);
            }
            break;
    }
}

int main() {
    display_menu(actual_node);
    int choice;
    printf("Enter choice: 0-up 1-down 2-left 3-right 4-exit: ");
    scanf("%d", &choice);
    while (choice != 4) {
        navigate_menu(choice);
        printf("Enter choice: 0-up 1-down 2-left 3-right 4-exit: ");
        scanf("%d", &choice);
    }
    return 0;
}