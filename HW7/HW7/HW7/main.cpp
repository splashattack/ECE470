//* Class Inheritance vs Class Aggregation - Homework 7 *


/*
* INSERT YOUR HW HEADER HERE
*/
#include <cstdint>
#include <string>
#include <iostream>
using namespace std;


//* DebounceFilter *


class DebounceFilter {
public:
    DebounceFilter(bool inistate = false) : state(inistate), count_off(0), count_on(0) {}
    void    update(bool pressed);
    bool    getState() const { return(state); }
private:
    bool    state;
    uint8_t count_off;
    uint8_t count_on;
    const static uint8_t threshold = 4; // warning: hardware specific
};

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


class AutorepeaterFilter {
public:
    AutorepeaterFilter(bool inistate = false) : state(inistate), count_on(0) {}
    void    update(bool pressed);
    bool    getState() const { return(state); }
private:
    bool    state;
    uint8_t count_on;
    const static uint8_t threshold = 8; // warning: sampling rate specific
                                        // Note: value reduced to 8 for easy testing in MS Visual Studio
};

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


//* PushButton *


class PushButton {
public:
    PushButton(bool inistate = false);
    virtual void update(bool pressed) = 0;
public:
    bool    getState() const { return(state); }
protected:
    bool    state;
};

PushButton::PushButton(bool inistate)
    : state(inistate) {
}


//* TogglePushButton *


class TogglePushButton : public PushButton {
public:
    TogglePushButton(bool inistate = false);
    virtual void update(bool pressed);
protected:
    bool recentinput;
};

TogglePushButton::TogglePushButton(bool inistate)
    : PushButton(inistate), recentinput(inistate) {
}

void TogglePushButton::update(bool pressed) {
    if (pressed != recentinput && pressed == true) {
        state = !state; // negate (flip) the state
    }
    recentinput = pressed;
}


//* DebouncedTogglePushButton *


class DebouncedTogglePushButton : public TogglePushButton {
public:
    DebouncedTogglePushButton(bool inistate = false);
    virtual void update(bool pressed);
protected:
    DebounceFilter debouncer;
};

DebouncedTogglePushButton::DebouncedTogglePushButton(bool inistate)
    : TogglePushButton(inistate), debouncer(inistate) {
}

void DebouncedTogglePushButton::update(bool pressed) {
    debouncer.update(pressed);
    TogglePushButton::update(debouncer.getState());
}


//* Do not modify content above *



//* AutoRepeatPushButton *


class AutoRepeatPushButton : public TogglePushButton {
public:
    AutoRepeatPushButton(bool inistate = false);
    virtual void update(bool pressed);
protected:
    AutorepeaterFilter Autorepeater;
};

AutoRepeatPushButton::AutoRepeatPushButton(bool inistate) : TogglePushButton(inistate), Autorepeater(inistate)
{
}

void AutoRepeatPushButton::update(bool pressed)
{
    Autorepeater.update(pressed);
    TogglePushButton::update(Autorepeater.getState());
}

//* DebouncedAutoRepeatPushButton *


class DebouncedAutoRepeatPushButton : public AutoRepeatPushButton {
public:
    DebouncedAutoRepeatPushButton(bool inistate = false);
    virtual void update(bool pressed);
protected:
    DebounceFilter debouncer;
};

DebouncedAutoRepeatPushButton::DebouncedAutoRepeatPushButton(bool inistate) : AutoRepeatPushButton(inistate), debouncer(inistate)
{
}

void DebouncedAutoRepeatPushButton::update(bool pressed) {
    debouncer.update(pressed);
    TogglePushButton::update(debouncer.getState());
}


int main() {
    string test = "000001011011111111111111010111001000000000000001111111111111111111111100000000000";

    PushButton* pButtons[4];
    pButtons[0] = new TogglePushButton();
    pButtons[1] = new DebouncedTogglePushButton();
    pButtons[2] = new AutoRepeatPushButton();
    pButtons[3] = new DebouncedAutoRepeatPushButton();

    for (size_t i = 0; i<test.size(); ++i) {
        cout << test[i];
        for (size_t b = 0; b<4; ++b) {
            pButtons[b]->update(test[i] == '1');
            if (pButtons[b]->getState())  cout << " 1";
            else                            cout << " 0";
        }
        cout << endl;
    }

    for (size_t b = 0; b<4; ++b) delete pButtons[b];
    return(0);
}
