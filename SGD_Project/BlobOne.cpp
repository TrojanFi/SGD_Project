#include "BlobOne.h"
#include "TextureManager.h"
#include <SDL.h>
#include "InputHandler.h"

#include <chrono>
#include <thread>

#include "Engine.h"


BlobOne::BlobOne(Properties* props):Character(props){
	m_RigidBody = new RigidBody();
	m_Animation = new Animation();

	m_Animation->SetProps(m_TextureID, 0, 3, 100, SDL_FLIP_NONE);
	rect.x = 100;
	rect.y = 100;
	rect.w = 64;
	rect.h = 64; // 36
}

void BlobOne::StartPosition() {
	m_lifePoints += -1;
	rect.x = 100;
	rect.y = 100;
	rect.w = 64;
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

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D) && m_Transform->X < 900) {
		m_RigidBody->ApplyForceX(4*FORWARD);
		rect.x = m_Transform->X;
		m_Animation->SetProps("BlobRun", 0, 6, 100, SDL_FLIP_NONE);
	}

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A) && m_Transform->X > 0) {
		m_RigidBody->ApplyForceX(4*BACKWARD);
		rect.x = m_Transform->X;
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

	


	//m_Transform->X += m_RigidBody->Position().X;
	m_Transform->TranslateX(m_RigidBody->Position().X);
	m_Transform->TranslateY(m_RigidBody->Position().Y);

	m_Animation->Update();

}
void BlobOne::Boom(BlobOne bullet) {
	
	if (rect.x + rect.w < bullet.rect.x || rect.x > bullet.rect.x + bullet.rect.x || 
		rect.y + rect.h < bullet.rect.y || rect.y > bullet.rect.y + bullet.rect.h) {
		SDL_Log("No collision");
	}
	else {
		SDL_Log("Collision");
	}

}

void BlobOne::Clean() {
	TextureManager::GetInstance()->Clean();
}