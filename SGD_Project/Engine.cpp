#include "Engine.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL_image.h>
#include "Transform.h"
#include "BlobOne.h"
#include "InputHandler.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Collision.h"
#include "Door.h"

Engine* Engine::s_Instance = nullptr;
BlobOne* Blob_One = nullptr;
Bullet* bullet = nullptr;
Bullet* bullet2 = nullptr;
Bullet* bullet3 = nullptr;
Enemy* enemy1 = nullptr;
Enemy* enemy2 = nullptr;
Enemy* enemy3 = nullptr;
Collision* collision = nullptr;
Door* doorOne = nullptr;
Door* doorTwo = nullptr;
Door* doorThree = nullptr;
Door* doorFour = nullptr;
Door* star = nullptr;
Door* heart1 = nullptr;
Door* heart2 = nullptr;
Door* heart3 = nullptr;
Door* heart4 = nullptr;
int Map = 0;
bool enemyAlive_1 = true;
bool enemyAlive_2 = true;
bool enemyAlive_3 = true;

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
	TextureManager::GetInstance()->Load("BlobOneIdle", "Assets/BlobIdle.png");
	TextureManager::GetInstance()->Load("BlobRun", "Assets/BlobRun.png");
	TextureManager::GetInstance()->Load("Bullet", "Assets/Bullet2.png");
	TextureManager::GetInstance()->Load("DoorOne", "Assets/DoorOne.png");
	TextureManager::GetInstance()->Load("DoorTwo", "Assets/DoorTwo.png");
	TextureManager::GetInstance()->Load("DoorThree", "Assets/DoorThree.png");
	TextureManager::GetInstance()->Load("DoorFour", "Assets/DoorFour.png");
	TextureManager::GetInstance()->Load("Star", "Assets/Star.png");
	TextureManager::GetInstance()->Load("Enemy", "Assets/Enemy.png");
	TextureManager::GetInstance()->Load("Heart", "Assets/Heart.png");



	Blob_One = new BlobOne(new Properties("BlobOneIdle", 100, 100, 64, 64));
	doorOne = new Door(new Properties("DoorOne", 896, 100, 64, 64));
	doorTwo = new Door(new Properties("DoorTwo", 896, 250, 64, 64));
	doorThree = new Door(new Properties("DoorThree", 896, 400, 64, 64));
	doorFour = new Door(new Properties("DoorFour", 896, 550, 64, 64));
	star = new Door(new Properties("Star", 896, 550, 64, 64));
	heart1 = new Door(new Properties("Heart", 0, 0, 64, 64));
	heart2 = new Door(new Properties("Heart", 64, 0, 64, 64));
	heart3 = new Door(new Properties("Heart", 128, 0, 64, 64));
	heart4 = new Door(new Properties("Heart", 192, 0, 64, 64));


	bullet = new Bullet(new Properties("Bullet", 400, 400, 16, 16));
	bullet2 = new Bullet(new Properties("Bullet", 100, 400, 16, 16));
	bullet3 = new Bullet(new Properties("Bullet", 300, 550, 16, 16));

	enemy1 = new Enemy(new Properties("Enemy", 250, 400, 32, 64));
	enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
	enemy3 = new Enemy(new Properties("Enemy", 350, 100, 32, 64));



	Transform tf(1, 2);
	tf.Log();

	return m_IsRunning = true;
}

void Engine::Update() {
	Blob_One->Update(0);
	
	Blob_One->FireUpdate();
	Blob_One->FireDeleteDistance();


	MapsUpdate();
	MapsChange();
	Collisions();
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
	Blob_One->RectView();
	Blob_One->FireDraw();

	switch (Blob_One->LifeHearts()) {
	case 0:
		break;
	case 1:
		heart1->Draw();
		break;
	case 2:
		heart1->Draw();
		heart2->Draw();
		break;
	case 3:
		heart1->Draw();
		heart2->Draw();
		heart3->Draw();
		break;
	case 4:
		heart1->Draw();
		heart2->Draw();
		heart3->Draw();
		heart4->Draw();
		break;
	}
	

	
	if (Map == 0) {
		doorOne->Draw();
		doorTwo->Draw();
		doorThree->Draw();
		doorFour->Draw();
	}
	
	if (Map == 1) {
		bullet->Draw();
		bullet->RectView();

		bullet2->Draw();
		bullet2->RectView();
		
		if(enemyAlive_1){
			enemy1->Draw();
			enemy1->FireDraw();
		}
		star->Draw();
	}

	if (Map == 2) {
		bullet->Draw();
		bullet->RectView();

		bullet2->Draw();
		bullet2->RectView();

		bullet3->Draw();
		bullet3->RectView();

		if (enemyAlive_1) {
			enemy1->Draw();
			enemy1->FireDraw();
		}
		if (enemyAlive_2) {
			enemy2->Draw();
			enemy2->FireDraw();
		}
		star->Draw();
	}

	if (Map == 3) {
		bullet->Draw();
		bullet->RectView();

		bullet2->Draw();
		bullet2->RectView();

		bullet3->Draw();
		bullet3->RectView();

		if (enemyAlive_1) {
			enemy1->Draw();
			enemy1->FireDraw();
		}
		if (enemyAlive_2) {
			enemy2->Draw();
			enemy2->FireDraw();
		}
		if (enemyAlive_3) {
			enemy3->Draw();
			enemy3->FireDraw();
		}
		star->Draw();
	}

	if (Map == 4) {
		bullet->Draw();
		bullet->RectView();

		bullet2->Draw();
		bullet2->RectView();

		bullet3->Draw();
		bullet3->RectView();

		if (enemyAlive_1) {
			enemy1->Draw();
			enemy1->FireDraw();
		}
		if (enemyAlive_2) {
			enemy2->Draw();
			enemy2->FireDraw();
		}
		if (enemyAlive_3) {
			enemy3->Draw();
			enemy3->FireDraw();
		}
		star->Draw();
	}


	SDL_RenderPresent(m_Renderer);

}

void Engine::MapsUpdate() {

	heart1->Update(0);
	heart2->Update(0);
	heart3->Update(0);
	heart4->Update(0);


	if (Map == 0) {
		doorOne->Update(0);
		doorTwo->Update(0);
		doorThree->Update(0);
		doorFour->Update(0);
	}

	if (Map == 1) {
		bullet2->UpdateBot(4);
		bullet->Update(0);

		if (enemyAlive_1) {
			enemy1->UpdateMovement();
			enemy1->SeePlayer(Blob_One->rect);
			enemy1->FireUpdate();
			enemy1->FireDeleteDistance();
		}
		star->Update(0);
	}

	if (Map == 2) {
		bullet3->UpdateBot(2);
		bullet2->UpdateBot(4);
		bullet->UpdateBot(3);

		if (enemyAlive_1) {
			enemy1->UpdateMovement();
			enemy1->SeePlayer(Blob_One->rect);
			enemy1->FireUpdate();
			enemy1->FireDeleteDistance();
		}
		if (enemyAlive_2) {
			enemy2->UpdateMovement();
			enemy2->SeePlayer(Blob_One->rect);
			enemy2->FireUpdate();
			enemy2->FireDeleteDistance();
		}
		star->Update(0);
	}

	if (Map == 3) {
		bullet3->UpdateBot(2);
		bullet2->UpdateBot(4);
		bullet->UpdateBot(3);

		if (enemyAlive_1) {
			enemy1->UpdateMovement();
			enemy1->SeePlayer(Blob_One->rect);
			enemy1->FireUpdate();
			enemy1->FireDeleteDistance();
		}
		if (enemyAlive_2) {
			enemy2->UpdateMovement();
			enemy2->SeePlayer(Blob_One->rect);
			enemy2->FireUpdate();
			enemy2->FireDeleteDistance();
		}
		if (enemyAlive_3) {
			enemy3->UpdateMovement();
			enemy3->SeePlayer(Blob_One->rect);
			enemy3->FireUpdate();
			enemy3->FireDeleteDistance();
		}
		star->Update(0);
	}

	if (Map == 4) {
		bullet3->UpdateBot(4);
		bullet2->UpdateBot(3);
		bullet->UpdateBot(2);

		if (enemyAlive_1) {
			enemy1->UpdateMovement();
			enemy1->SeePlayer(Blob_One->rect);
			enemy1->FireUpdate();
			enemy1->FireDeleteDistance();
		}
		if (enemyAlive_2) {
			enemy2->UpdateMovement();
			enemy2->SeePlayer(Blob_One->rect);
			enemy2->FireUpdate();
			enemy2->FireDeleteDistance();
		}
		if (enemyAlive_3) {
			enemy3->UpdateMovement();
			enemy3->SeePlayer(Blob_One->rect);
			enemy3->FireUpdate();
			enemy3->FireDeleteDistance();
		}
		star->Update(0);
	}




}

void Engine::MapsChange() {
	// load level 1
	if (collision->CheckCollision(Blob_One->rect, doorOne->rect) && Map == 0) {
		Blob_One->StartPosition();
		Map = 1;
		bullet = new Bullet(new Properties("Bullet", 400, 400, 16, 16));
		bullet2 = new Bullet(new Properties("Bullet", 150, 400, 16, 16));
		enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
		enemyAlive_1 = true;
		delete doorOne;
		delete doorTwo;
		delete doorThree;
		delete doorFour;
	}

	if (collision->CheckCollision(Blob_One->rect, star->rect) && Map == 1) {
		Blob_One->StartPosition();
		Map = 0;
		doorOne = new Door(new Properties("DoorOne", 896, 100, 64, 64));
		doorTwo = new Door(new Properties("DoorTwo", 896, 250, 64, 64));
		doorThree = new Door(new Properties("DoorThree", 896, 400, 64, 64));
		doorFour = new Door(new Properties("DoorFour", 896, 550, 64, 64));
		delete bullet;
		delete bullet2;
		if (enemyAlive_1)delete enemy1;
		Blob_One->LifeStatus4();

	}
	// load level 2
	if (collision->CheckCollision(Blob_One->rect, doorTwo->rect) && Map == 0) {
		Blob_One->StartPosition();
		Map = 2;
		bullet = new Bullet(new Properties("Bullet", 500, 200, 16, 16));
		bullet2 = new Bullet(new Properties("Bullet", 100, 400, 16, 16));
		bullet3 = new Bullet(new Properties("Bullet", 300, 100, 16, 16));
		enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
		enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
		enemyAlive_1 = true;
		enemyAlive_2 = true;
		delete doorOne;
		delete doorTwo;
		delete doorThree;
		delete doorFour;
	}
	if (collision->CheckCollision(Blob_One->rect, star->rect) && Map == 2) {
		Blob_One->StartPosition();
		Map = 0;
		doorOne = new Door(new Properties("DoorOne", 896, 100, 64, 64));
		doorTwo = new Door(new Properties("DoorTwo", 896, 250, 64, 64));
		doorThree = new Door(new Properties("DoorThree", 896, 400, 64, 64));
		doorFour = new Door(new Properties("DoorFour", 896, 550, 64, 64));
		delete bullet;
		delete bullet2;
		delete bullet3;
		if (enemyAlive_1)delete enemy1;
		if (enemyAlive_2)delete enemy2;
		Blob_One->LifeStatus4();

	}
	// load level 3
	if (collision->CheckCollision(Blob_One->rect, doorThree->rect) && Map == 0) {
		Blob_One->StartPosition();
		Map = 3;
		bullet = new Bullet(new Properties("Bullet", 900, 250, 16, 16));
		bullet2 = new Bullet(new Properties("Bullet", 100, 400, 16, 16));
		bullet3 = new Bullet(new Properties("Bullet", 400, 250, 16, 16));
		enemy1 = new Enemy(new Properties("Enemy", 300, 400, 32, 64));
		enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
		enemy3 = new Enemy(new Properties("Enemy", 350, 100, 32, 64));
		enemyAlive_1 = true;
		enemyAlive_2 = true;
		enemyAlive_3 = true;
		delete doorOne;
		delete doorTwo;
		delete doorThree;
		delete doorFour;
	}
	if (collision->CheckCollision(Blob_One->rect, star->rect) && Map == 3) {
		Blob_One->StartPosition();
		Map = 0;
		doorOne = new Door(new Properties("DoorOne", 896, 100, 64, 64));
		doorTwo = new Door(new Properties("DoorTwo", 896, 250, 64, 64));
		doorThree = new Door(new Properties("DoorThree", 896, 400, 64, 64));
		doorFour = new Door(new Properties("DoorFour", 896, 550, 64, 64));
		delete bullet;
		delete bullet2;
		delete bullet3;
		if (enemyAlive_1)delete enemy1;
		if (enemyAlive_2)delete enemy2;
		if (enemyAlive_3)delete enemy3;
		Blob_One->LifeStatus4();
	}
	// load level 4
	if (collision->CheckCollision(Blob_One->rect, doorFour->rect) && Map == 0) {
		Blob_One->StartPosition();
		Map = 4;
		bullet = new Bullet(new Properties("Bullet", 400, 550, 16, 16));
		bullet2 = new Bullet(new Properties("Bullet", 600, 250, 16, 16));
		bullet3 = new Bullet(new Properties("Bullet", 700, 400, 16, 16));
		enemy1 = new Enemy(new Properties("Enemy", 600, 550, 32, 64));
		enemy2 = new Enemy(new Properties("Enemy", 450, 250, 32, 64));
		enemy3 = new Enemy(new Properties("Enemy", 100, 250, 32, 64));
		enemyAlive_1 = true;
		enemyAlive_2 = true;
		enemyAlive_3 = true;
		delete doorOne;
		delete doorTwo;
		delete doorThree;
		delete doorFour;
	}
	if (collision->CheckCollision(Blob_One->rect, star->rect) && Map == 4) {
		Blob_One->StartPosition();
		Map = 0;
		doorOne = new Door(new Properties("DoorOne", 896, 100, 64, 64));
		doorTwo = new Door(new Properties("DoorTwo", 896, 250, 64, 64));
		doorThree = new Door(new Properties("DoorThree", 896, 400, 64, 64));
		doorFour = new Door(new Properties("DoorFour", 896, 550, 64, 64));
		delete bullet;
		delete bullet2;
		delete bullet3;
		if (enemyAlive_1)delete enemy1;
		if (enemyAlive_2)delete enemy2;
		if (enemyAlive_3)delete enemy3;
		Blob_One->LifeStatus4();

	}


	
}


void Engine::Collisions() {
	// problem???? z bullet - if nie jest rozwi¹zaniem (tymczasowe)
	if (Map != 0) {
		if (Map == 1) {
			if (collision->CheckCollision(Blob_One->rect, bullet->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;
				}
			}
			if (collision->CheckCollision(Blob_One->rect, bullet2->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;

				}
			}
			if (collision->CheckCollision(Blob_One->rect, enemy1->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;

				}
			}

			if (enemyAlive_1 == true && enemy1->FiredCollision(Blob_One->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;
				}
			}

			if (Blob_One->FiredCollision(enemy1->rect) && enemyAlive_1 == true) {
				delete enemy1;
				enemyAlive_1 = false;
			}
		}
		if (Map == 2) {
			if (collision->CheckCollision(Blob_One->rect, bullet->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
			}
			if (collision->CheckCollision(Blob_One->rect, bullet2->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;

				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
			}

			if (collision->CheckCollision(Blob_One->rect, bullet3->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;

				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
			}

			if (collision->CheckCollision(Blob_One->rect, enemy1->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
			}

			if (enemyAlive_1 == true && enemy1->FiredCollision(Blob_One->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
			}

			if (Blob_One->FiredCollision(enemy1->rect) && enemyAlive_1 == true) {
				delete enemy1;
				enemyAlive_1 = false;
			}

			if (enemyAlive_2 == true && enemy2->FiredCollision(Blob_One->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 250, 250, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
			}

			if (Blob_One->FiredCollision(enemy2->rect) && enemyAlive_2 == true) {
				delete enemy2;
				enemyAlive_2 = false;
			}
		}
		if (Map == 3) {
			if (collision->CheckCollision(Blob_One->rect, bullet->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 300, 400, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 350, 100, 32, 64));
					enemyAlive_3 = true;
				}
			}
			if (collision->CheckCollision(Blob_One->rect, bullet2->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 300, 400, 32, 64));
					enemyAlive_1 = true;

				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 350, 100, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (collision->CheckCollision(Blob_One->rect, bullet3->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 300, 400, 32, 64));
					enemyAlive_1 = true;

				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 350, 100, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (collision->CheckCollision(Blob_One->rect, enemy1->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 300, 400, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 350, 100, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (enemyAlive_1 == true && enemy1->FiredCollision(Blob_One->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 300, 400, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 350, 100, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (Blob_One->FiredCollision(enemy1->rect) && enemyAlive_1 == true) {
				delete enemy1;
				enemyAlive_1 = false;
			}

			if (enemyAlive_2 == true && enemy2->FiredCollision(Blob_One->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 300, 400, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 350, 100, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (Blob_One->FiredCollision(enemy2->rect) && enemyAlive_2 == true) {
				delete enemy2;
				enemyAlive_2 = false;
			}

			if (enemyAlive_3 == true && enemy3->FiredCollision(Blob_One->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 300, 400, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 250, 550, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 350, 100, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (Blob_One->FiredCollision(enemy3->rect) && enemyAlive_3 == true) {
				delete enemy3;
				enemyAlive_3 = false;
			}
		}
		if (Map == 4) {
			if (collision->CheckCollision(Blob_One->rect, bullet->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 600, 550, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 450, 250, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 100, 250, 32, 64));
					enemyAlive_3 = true;
				}
			}
			if (collision->CheckCollision(Blob_One->rect, bullet2->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 600, 550, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 450, 250, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 100, 250, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (collision->CheckCollision(Blob_One->rect, bullet3->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 600, 550, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 450, 250, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 100, 250, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (collision->CheckCollision(Blob_One->rect, enemy1->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 600, 550, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 450, 250, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 100, 250, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (enemyAlive_1 == true && enemy1->FiredCollision(Blob_One->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 600, 550, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 450, 250, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 100, 250, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (Blob_One->FiredCollision(enemy1->rect) && enemyAlive_1 == true) {
				delete enemy1;
				enemyAlive_1 = false;
			}

			if (enemyAlive_2 == true && enemy2->FiredCollision(Blob_One->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 600, 550, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 450, 250, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 100, 250, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (Blob_One->FiredCollision(enemy2->rect) && enemyAlive_2 == true) {
				delete enemy2;
				enemyAlive_2 = false;
			}

			if (enemyAlive_3 == true && enemy3->FiredCollision(Blob_One->rect)) {
				Blob_One->StartPosition();
				bullet->StartPosition();
				bullet2->StartPosition();
				bullet3->StartPosition();
				if (enemyAlive_1)enemy1->StartPosition();
				else {
					enemy1 = new Enemy(new Properties("Enemy", 600, 550, 32, 64));
					enemyAlive_1 = true;
				}
				if (enemyAlive_2)enemy2->StartPosition();
				else {
					enemy2 = new Enemy(new Properties("Enemy", 450, 250, 32, 64));
					enemyAlive_2 = true;
				}
				if (enemyAlive_3)enemy3->StartPosition();
				else {
					enemy3 = new Enemy(new Properties("Enemy", 100, 250, 32, 64));
					enemyAlive_3 = true;
				}
			}

			if (Blob_One->FiredCollision(enemy3->rect) && enemyAlive_3 == true) {
				delete enemy3;
				enemyAlive_3 = false;
			}
		}
	}

	
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


