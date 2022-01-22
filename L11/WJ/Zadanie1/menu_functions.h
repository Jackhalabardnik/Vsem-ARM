#pragma once

#include <targets\AT91SAM7.h>
#include <ctl_api.h>
#include "PCF8833U8_lcd.h"

volatile int animation_active = 0;

void about_author() {
    LCDClearScreen();
    LCDPutStr("Jacek Wojcik", 45, 15, LARGE, BLACK, WHITE);
    LCDPutStr("10", 70, 50, LARGE, BLACK, WHITE);
}

void image_with_text() {
    
}

void image_1() {
    show_photo(1);
}

void image_2() {
    show_photo(2);
}

void animation() {
    animation_active = 1;
}

void square() {
    LCDClearScreen();
    LCDSetRect(20, 20, 100, 100, FILL, YELLOW);
}

void circle() {
    LCDClearScreen();
     LCDSetCircle(50, 50, 10, YELLOW); 
}

void triangle() {
    LCDClearScreen();
    LCDSetLine(20, 20, 60, 50, YELLOW); 
    LCDSetLine(20, 20, 60, 20, YELLOW); 
    LCDSetLine(60, 50, 60, 20, YELLOW); 
}

void trapeze() {
    LCDClearScreen();
    LCDSetLine(30, 50, 50, 50, YELLOW); 
    LCDSetLine(20, 20, 60, 20, YELLOW); 
    LCDSetLine(50, 50, 60, 20, YELLOW); 
    LCDSetLine(30, 50, 20, 20, YELLOW); 
}
