#pragma once
#include <dinput.h>
class input
{
public:
	input();
	~input();

	HRESULT initInput(HINSTANCE instance, HWND window, int screenWidth, int screenHeight);
	
	void readKeyboardStates();
	void readMouseState();
	bool isKeyPressed(unsigned char keycode);
	void processMouseInput();

	void getMousePos(int& mouseX, int& mouseY);

	DIMOUSESTATE getLastMouseState();

	DIMOUSESTATE getCurrentMouseState();

private:
	IDirectInput8* m_direct_input;
	IDirectInputDevice8* m_keyboard_device;
	IDirectInputDevice8* m_mouse_device;

	unsigned char m_keyboard_key_state[256];
	DIMOUSESTATE m_mouseCurrentState;
	DIMOUSESTATE m_mouseLastState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

