#include "Engine.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL_image.h>
//#include "Vector2D.h" test vektor
#include "Transform.h"
#include "BlobOne.h"
#include "InputHandler.h"
Engine* Engine::s_Instance = nullptr;
BlobOne* Blob_One = nullptr;

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

	TextureManager::GetInstance()->Load("BlobOneIdle","Assets/BlobIdle.png");
	Blob_One = new BlobOne(new Properties("BlobOneIdle", 100, 100, 64, 64));
	// test wektor
	/*
	Vector2D v1(1,1), v2(1,1), v3;
	v3 = v1 + v2;
	v3.Log("V3:");
	*/

	Transform tf(1,2);
	tf.Log();

	return m_IsRunning = true;
}

void Engine::Update() {
	//SDL_Log("Its working in the loop...\n");
	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		SDL_Log("Key A pushed");
	}
	Blob_One->Update(0);
}

void Engine::Render() {
	SDL_SetRenderDrawColor(m_Renderer, 204, 255, 153, 255);
	SDL_RenderClear(m_Renderer);

	//TextureManager::GetInstance()->Draw("BlobOneIdle", 0, 0, 960, 640);
	Blob_One->Draw();
	SDL_RenderPresent(m_Renderer);

}


void Engine::Events() {
	InputHandler::GetInstance()->listen();
}

bool Engine::Clean() {
	TextureManager::GetInstance()->Clean();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	IMG_Quit();
	SDL_Quit();
	return true;
}


void Engine::Quit() {
	m_IsRunning = false;
}


