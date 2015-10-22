//* Class Inheritance vs Class Aggregation - Homework 7 *
#include "lib_buttons.h"
#include <stdint.h>

//* DebounceFilter *
void DebounceFilter::update(bool pressed) {
    if (pressed) {
        count_on++;
        if (count_on>threshold) { count_off = 0; state = true; }
    }
    else {
        count_off++;
        if (count_off>threshold) { count_on = 0; state = false; }
    }
}

//* AutorepeaterFilter *
void AutorepeaterFilter::update(bool pressed) {
    if (pressed) {
        state = true;
        count_on++;
        if (count_on>threshold) { count_on = 0; state = false; }
    }
    else {
        count_on = 0;
        state = false;
    }
}

//* TogglePushButton *
void TogglePushButton::update(bool pressed) {
    if (pressed != recentinput && pressed == true) {
        state = !state; // negate (flip) the state
    }
    recentinput = pressed;
}

//* DebouncedTogglePushButton *
void DebouncedTogglePushButton::update(bool pressed) {
    debouncer.update(pressed);
    TogglePushButton::update(debouncer.getState());
}

//* AutoRepeatPushButton *
void AutoRepeatPushButton::update(bool pressed)
{
    Autorepeater.update(pressed);
    TogglePushButton::update(Autorepeater.getState());
}

//* DebouncedAutoRepeatPushButton *
void DebouncedAutoRepeatPushButton::update(bool pressed) {
    debouncer.update(pressed);
    TogglePushButton::update(debouncer.getState());
}
