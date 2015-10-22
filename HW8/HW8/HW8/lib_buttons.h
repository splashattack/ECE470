#include <stdint.h>

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

class PushButton {
	public:
	PushButton(bool inistate = false) : state(inistate) {}
	virtual void update(bool pressed) = 0;
	public:
	bool    getState() const { return(state); }
	protected:
	bool    state;
};

class TogglePushButton : public PushButton {
	public:
	TogglePushButton(bool inistate = false) : PushButton(inistate), recentinput(inistate) {}
	virtual void update(bool pressed);
	protected:
	bool recentinput;
};

class DebouncedTogglePushButton : public TogglePushButton {
	public:
	DebouncedTogglePushButton(bool inistate = false) : TogglePushButton(inistate), debouncer(inistate) {}
	virtual void update(bool pressed);
	protected:
	DebounceFilter debouncer;
};

class AutoRepeatPushButton : public TogglePushButton {
	public:
	AutoRepeatPushButton(bool inistate = false) : TogglePushButton(inistate), Autorepeater(inistate) {}
	virtual void update(bool pressed);
	protected:
	AutorepeaterFilter Autorepeater;
};

class DebouncedAutoRepeatPushButton : public AutoRepeatPushButton {
	public:
	DebouncedAutoRepeatPushButton(bool inistate = false) : AutoRepeatPushButton(inistate), debouncer(inistate) {}
	virtual void update(bool pressed);
	protected:
	DebounceFilter debouncer;
};