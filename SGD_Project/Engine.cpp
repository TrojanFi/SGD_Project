#include "Engine.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL_image.h>
#include "Transform.h"
#include "BlobOne.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "Collision.h"
#include "Door.h"

Engine* Engine::s_Instance = nullptr;
BlobOne* Blob_One = nullptr;
Bullet* bullet= nullptr;
Bullet* bullet2 = nullptr;
Bullet* bullet3 = nullptr;
Collision* collision = nullptr;
Door* doorOne = nullptr;

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

	TextureManager::GetInstance()->Load("Bg", "Assets/Bg.png");
	TextureManager::GetInstance()->Load("BlobOneIdle","Assets/BlobIdle.png");
	TextureManager::GetInstance()->Load("BlobRun", "Assets/BlobRun.png");
	TextureManager::GetInstance()->Load("Bullet", "Assets/Bullet2.png");
	TextureManager::GetInstance()->Load("DoorOne", "Assets/DoorOne.png");


	Blob_One = new BlobOne(new Properties("BlobOneIdle", 100, 100, 64, 64));

	bullet = new Bullet(new Properties("Bullet", 400, 400, 16, 16));
	bullet->Alive();
	bullet2 = new Bullet(new Properties("Bullet", 150, 400, 16, 16));
	
	doorOne = new Door(new Properties("DoorOne", 800, 100, 64, 64));

	
	
	

	Transform tf(1,2);
	tf.Log();

	return m_IsRunning = true;
}

void Engine::Update() {
	//SDL_Log("Its working in the loop...\n");
	Blob_One->Update(0);
	doorOne->Update(0);
	bullet->Update(0);
	bullet2->Update(0);
	
	if (collision->CheckCollision(Blob_One->rect, bullet->rect)) { 
		Blob_One->StartPosition(); 
		bullet->StartPosition();
		bullet2->StartPosition();
	}
	if (collision->CheckCollision(Blob_One->rect, bullet2->rect)) {
		Blob_One->StartPosition();
		bullet->StartPosition();
		bullet2->StartPosition();
	}
	if (collision->CheckCollision(Blob_One->rect, doorOne->rect)) {
		Blob_One->StartPosition();
	}
	if (!Blob_One->LifeStatus()) { 
		// reset
		Blob_One->LifeStatus4();
	}


	
}

void Engine::Render() {
//	SDL_SetRenderDrawColor(m_Renderer, 204, 255, 153, 255);
//	SDL_RenderClear(m_Renderer);

	TextureManager::GetInstance()->Draw("Bg", 0, 0, 960, 640);
	Blob_One->Draw();
	doorOne->Draw();
	bullet->Draw();
	bullet2->Draw();

	Blob_One->RectView();
	bullet->RectView();
	bullet2->RectView();
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


