#include "BlobOne.h"
#include "TextureManager.h"
#include <SDL.h>
#include "InputHandler.h"

#include <chrono>
#include <thread>



BlobOne::BlobOne(Properties* props):Character(props){
	m_RigidBody = new RigidBody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 3, 100, SDL_FLIP_NONE);
}

void BlobOne::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}




void BlobOne::Update(float dt) {
	//m_Frame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;

	m_RigidBody->Update(0.8);

	m_Animation->SetProps("BlobOneIdle", 0, 3, 100, SDL_FLIP_NONE);
	m_RigidBody->UnSetForce();

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		m_RigidBody->ApplyForceX(4*FORWARD);
		m_Animation->SetProps("BlobRun", 0, 6, 100, SDL_FLIP_NONE);
	}

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		m_RigidBody->ApplyForceX(4*BACKWARD);
		m_Animation->SetProps("BlobRun", 0, 6, 100, SDL_FLIP_HORIZONTAL);
	}

	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_S) && m_RigidBody->GetLevel() <= 3 && m_RigidBody->GetLevel() > 0) {
		m_RigidBody->SetPositionDown();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Level =" << m_RigidBody->GetLevel() << std::endl;

	}
	if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_RigidBody->Position().Y >= 0 && m_RigidBody->GetLevel() < 3) {
		m_RigidBody->SetPositionUp();
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		std::cout << "Level =" << m_RigidBody->GetLevel() << std::endl;

	}


	//m_Transform->X += m_RigidBody->Position().X;
	m_Transform->TranslateX(m_RigidBody->Position().X);
	m_Transform->TranslateY(m_RigidBody->Position().Y);

	m_Animation->Update();

}

void BlobOne::Clean() {
	TextureManager::GetInstance()->Clean();
}