#include "InputHandler.h"
#include "Engine.h"

InputHandler* InputHandler :: s_Instance = nullptr;

InputHandler::InputHandler() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}


void InputHandler::listen() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT: Engine::GetInstance()->Quit(); break;
			case SDL_KEYDOWN: KeyDown(); break;
			case SDL_KEYUP: KeyUp(); break;
		}
	
	}

}



bool InputHandler::GetKeyDown(SDL_Scancode key) {
	if (m_KeyStates[key] == 1) return true;
	return false;
}

void InputHandler::KeyUp() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void InputHandler::KeyDown() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}