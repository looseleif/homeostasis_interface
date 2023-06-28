#include <menu.h>

menu::menu(void){

    pinMode(UP_PIN, INPUT_PULLUP);
    pinMode(DOWN_PIN, INPUT_PULLUP);
    pinMode(LEFT_PIN, INPUT_PULLUP);
    pinMode(RIGHT_PIN, INPUT_PULLUP);
    pinMode(SELECT_PIN, INPUT_PULLUP);
    pinMode(HOME_PIN, INPUT_PULLUP);

    system_state = welcome;
    demo_state = stopped;
    home_state = false;
    printed = false;
    cursor_prev = 2;
    cursor_current = 0;

}