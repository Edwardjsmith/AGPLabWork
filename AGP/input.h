#pragma once
#include <dinput.h>
class input
{
public:
	input();
	~input();

	HRESULT initKeyboard(HINSTANCE instance, HWND window);
	void readInputStates();
	bool isKeyPressed(unsigned char keycode);

private:
	IDirectInput8* m_direct_input;
	IDirectInputDevice8* m_keyboard_device;

	unsigned char m_keyboard_key_state[256];

};

