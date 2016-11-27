#pragma once
#include <vector>
#include <algorithm> 
#define VK_MULTIPLEKEYSDOWN 0x99

enum KEYSTROKES {
	left = VK_LEFT,
	right = VK_RIGHT,
	duck = VK_CONTROL,
	jump = VK_SPACE,
	multikeys = VK_MULTIPLEKEYSDOWN,
	undefined = 0x100,
	released = 0
};

class Keyboard {

public:
	Keyboard();
	void pop(WPARAM wParam);
	inline std::vector<KEYSTROKES> getPressedKeys();
	KEYSTROKES handleInput(WPARAM wParam);

private:
	KEYSTROKES previousKey, pressedKey;
	int keys[127];
	//vois k‰ytt‰‰ queue/st‰kki‰ VAI setti‰?
	std::vector<KEYSTROKES> keysBeingPressed;
};

Keyboard::Keyboard() {
	previousKey = KEYSTROKES::undefined;
	for (int i = 0; i < 127; i++) {
		keys[i] = i;
	}
}

void Keyboard::pop(WPARAM wParam) {
	auto elem = std::find(keysBeingPressed.begin(), keysBeingPressed.end(), wParam);
	if (elem != keysBeingPressed.end())
		keysBeingPressed.erase(elem);
}

std::vector<KEYSTROKES> Keyboard::getPressedKeys() {
	return keysBeingPressed;
}

KEYSTROKES Keyboard::handleInput(WPARAM wParam) {
	switch (wParam) {
		case KEYSTROKES::left:
		{
			pressedKey = KEYSTROKES::left;
			break;
		}
		case KEYSTROKES::right:
		{
			pressedKey = KEYSTROKES::right;
			break;
		}

		case KEYSTROKES::duck:
		{
			pressedKey = KEYSTROKES::duck;
			break;
		}
		case KEYSTROKES::jump:
		{
			pressedKey = KEYSTROKES::jump;
			break;
		}
	}

	//kamoon
	keysBeingPressed.push_back(pressedKey);
	keysBeingPressed.erase(std::unique(keysBeingPressed.begin(), keysBeingPressed.end()), keysBeingPressed.end());

	if (keysBeingPressed.size() > 1) {
		pressedKey = KEYSTROKES::multikeys;

	}
	return pressedKey;
}