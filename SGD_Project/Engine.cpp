#include "Engine.h"
#include <iostream>

Engine* Engine::s_Instance = nullptr;

bool Engine::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	m_Window = SDL_CreateWindow("Zbudujemy dzis balwana", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_Window == nullptr) {
		SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_Renderer == nullptr) {
		SDL_Log("Fail to create Renderer: %s", SDL_GetError());
		return false;
	}

	return m_IsRunning = true;
}

void Engine::Clean() {
}

void Engine::Update() {
	SDL_Log("Its working in the loop...\n");
}

void Engine::Quit() {
	m_IsRunning = false;
}

void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 124, 213, 254, 255);
	SDL_RenderPresent(m_Renderer);
}

void Engine::Events() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		Quit();
		break;
	}
}