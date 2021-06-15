#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
class InputHandler
{
public:
	static InputHandler* GetInstance() {
		return s_Instance = (s_Instance != nullptr) ? s_Instance : new InputHandler();
	}

	void listen();
	bool GetKeyDown(SDL_Scancode key);

private:
	InputHandler();
	void KeyUp();
	void KeyDown();


	const Uint8* m_KeyStates;

	static InputHandler* s_Instance;
};

#endif // !INPUTHANDLER_H

