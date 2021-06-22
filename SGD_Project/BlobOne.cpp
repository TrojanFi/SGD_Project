#include "BlobOne.h"
#include "TextureManager.h"
#include <SDL.h>
#include "InputHandler.h"

#include <chrono>
#include <thread>

#include "Engine.h"

Bullet* fire = nullptr;

BlobOne::BlobOne(Properties* props):Character(props){
	m_RigidBody = new RigidBody();
	m_Animation = new Animation();

	m_Animation->SetProps(m_TextureID, 0, 3, 100, SDL_FLIP_NONE);
	rect.x = 120;
	rect.y = 100;
	rect.w = 34;
	rect.h = 64; // 36
}

void BlobOne::StartPosition() {
	m_lifePoints += -1;
	rect.x = 120;
	rect.y = 100;
	rect.w = 34;
	rect.h = 64; // 36
	m_Transform->X = 100;
	m_Transform->Y = 100;
	m_RigidBody->SetLevel0();
}

void BlobOne::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	
}

void BlobOne::RectView() {
	if (m_ViewRect) {
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &rect);
	}
}

bool BlobOne::LifeStatus() {
	if (m_lifePoints == 0)return false;
	return true;
	 
}

void BlobOne::LifeStatus4() {
	m_lifePoints = 1;

}



void BlobOne::Update(float dt) {
	//m_Frame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;

	m_RigidBody->Update(0.8);

	m_Animation->SetProps("BlobOneIdle", 0, 3, 100, SDL_FLIP_NONE);
	m_RigidBody->UnSetForce();
	rect.x = m_Transform->X + 20;

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && m_Transform->X < 900) {
		m_RigidBody->ApplyForceX(4*FORWARD);
		rect.x = m_Transform->X + 20;
		m_Animation->SetProps("BlobRun", 0, 6, 100, SDL_FLIP_NONE);
	}

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && m_Transform->X > 0) {
		m_RigidBody->ApplyForceX(4*BACKWARD);
		rect.x = m_Transform->X + 20;
		m_Animation->SetProps("BlobRun", 0, 6, 100, SDL_FLIP_HORIZONTAL);
	}

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_S) && m_RigidBody->GetLevel() <= 3 && m_RigidBody->GetLevel() > 0) {
		m_RigidBody->SetPositionDown();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		m_Transform->Y += 150;
		rect.y = m_Transform->Y;
		std::cout << "Level =" << m_RigidBody->GetLevel() << std::endl;

	}
	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_RigidBody->Position().Y >= 0 && m_RigidBody->GetLevel() < 3) {
		m_RigidBody->SetPositionUp();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		m_Transform->Y -= 150;
		rect.y = m_Transform->Y;
		std::cout << "Level =" << m_RigidBody->GetLevel() << std::endl;

	}

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_X) && m_ViewRect == false) {

		m_ViewRect = true;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	else if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_X) && m_ViewRect == true) {

		m_ViewRect = false;
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE)) {
		CreateFire();
	}


	//m_Transform->X += m_RigidBody->Position().X;
	m_Transform->TranslateX(m_RigidBody->Position().X);
	m_Transform->TranslateY(m_RigidBody->Position().Y);

	m_Animation->Update();

}

void BlobOne::CreateFire() {
	if (!fired) {
		fired = true;
		fireDirection = m_RigidBody->GetForceX();
		if (fireDirection >= 0) {
			fire = new Bullet(new Properties("Bullet", rect.x + 50, rect.y + 20, 16, 16));
		}
		else {
			fire = new Bullet(new Properties("Bullet", rect.x + 10, rect.y + 20, 16, 16));
		}
	}
}

void BlobOne::FireUpdate() {
	if (fired)fire->UpdateFire(fireDirection);
}

void BlobOne::FireDraw() {
	if(fired)fire->Draw();
}

void BlobOne::FireDelete() {
	delete fire;
	fired = false;
}

void BlobOne::FireDeleteDistance() {
	if (fired) {
		if (fire->BulletPositionX() > fire->BulletStartPositionX() + 300) {
			delete fire;
			fired = false;
		}
		else if (fire->BulletPositionX() < fire->BulletStartPositionX() - 300) {
			delete fire;
			fired = false;
		}
	}
}


bool BlobOne::Fired() {
	return fire;
}

bool BlobOne::FiredCollision(SDL_Rect enemies) {
	if (fired) {
		if (fire->rect.x + fire->rect.w < enemies.x || fire->rect.x > enemies.x + enemies.w ||
			fire->rect.y + fire->rect.h < enemies.y || fire->rect.y > enemies.y + enemies.h) {
			return false;
		}
		else {
			return true;
		}
	}
}

void BlobOne::Clean() {
	TextureManager::GetInstance()->Clean();
}