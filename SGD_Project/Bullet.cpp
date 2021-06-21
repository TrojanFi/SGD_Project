#include "Bullet.h"
#include "TextureManager.h"
#include <SDL.h>
#include "InputHandler.h"

#include <chrono>
#include <thread>

#include "Engine.h"


Bullet::Bullet(Properties* props) :Character(props) {
	m_RigidBody = new RigidBody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 3, 100, SDL_FLIP_NONE);
	rect.x = m_Transform->X; //250 // 273
	rect.y = m_Transform->Y; // 250 // 271
	rect.w = 16; // 64 // 16
	rect.h = 16; //64 //16
	x = m_Transform->X;
	y = m_Transform->Y;

}

void Bullet::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}

void Bullet::StartPosition() {
	rect.x = m_Transform->X; //250 // 273
	rect.y = m_Transform->Y; // 250 // 271
	rect.w = 16; // 64 // 16
	rect.h = 16; //64 //16
	m_Transform->X = x;
	m_Transform->Y = y;
	m_RigidBody->UnSetForce();
	
}


void Bullet::RectView() {
	if (m_ViewRect) {
		SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &rect);
	}
}

void Bullet::UpdateBot(int type) {
	m_RigidBody->Update(0.8);
	// Horizontal move 
	if (type == 1) {
		if (m_Transform->X < x+1) {
			m_RigidBody->ApplyForceX(4 * FORWARD);
			rect.x = m_Transform->X;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		}
		else if (m_Transform->X > x+350)
		{
			m_RigidBody->ApplyForceX(4 * BACKWARD);
			rect.x = m_Transform->X;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		}
		else {
			rect.x = m_Transform->X;
		}
	}
	// Vertical move
	else if (type == 2) {
		if (m_Transform->Y < y + 1) {
			m_RigidBody->ApplyForceY(4 * FORWARD);
			rect.y = m_Transform->Y;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		}
		else if (m_Transform->Y > y + 150)
		{
			m_RigidBody->ApplyForceY(4 * BACKWARD);
			rect.y = m_Transform->Y;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		}
		else {
			rect.y = m_Transform->Y;
		}
	}
	// Rectangle move
	else if (type == 3) {
		if (m_Transform->X < x + 1 &&  m_Transform->Y > y - 1) {
			m_RigidBody->UnSetForce();
			m_RigidBody->ApplyForceX(4 * FORWARD);
			rect.x = m_Transform->X;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		}
		else if (m_Transform->X > x + 350 && m_Transform->Y > y - 150)
		{
			m_RigidBody->UnSetForce();
			m_RigidBody->ApplyForceY(4 * BACKWARD);
			rect.y = m_Transform->Y;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		}
		else if (m_Transform->Y < y - 150 && m_Transform->X > x + 1) {
			m_RigidBody->UnSetForce();
			m_RigidBody->ApplyForceX(4 * BACKWARD);
			rect.x = m_Transform->X;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		}
		else if (m_Transform->X < x + 1 )
		{
			m_RigidBody->UnSetForce();
			m_RigidBody->ApplyForceY(4 * FORWARD);
			rect.y = m_Transform->Y;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		}
		else {
			rect.x = m_Transform->X;
			rect.y = m_Transform->Y;
		}
	}

	m_Transform->TranslateX(m_RigidBody->Position().X);
	m_Transform->TranslateY(m_RigidBody->Position().Y);

	m_Animation->Update();
}

void Bullet::Update(float dt) {
	//m_Frame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;

	m_RigidBody->Update(0.8);

		m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		m_RigidBody->UnSetForce();

		rect.x = m_Transform->X;
		rect.y = m_Transform->Y;

		if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_K) && m_Transform->X < 900) {
			m_RigidBody->ApplyForceX(4 * FORWARD);
			rect.x = m_Transform->X;
			rect.y = m_Transform->Y;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_NONE);
		}

		if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_H) && m_Transform->X > 0) {
			m_RigidBody->ApplyForceX(4 * BACKWARD);
			rect.x = m_Transform->X;
			rect.y = m_Transform->Y;
			m_Animation->SetProps("Bullet", 0, 3, 100, SDL_FLIP_HORIZONTAL);
		}

		if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_J) && m_Transform->Y < 620) {
			m_RigidBody->ApplyForceY(4 * FORWARD);
			rect.x = m_Transform->X;
			rect.y = m_Transform->Y;
		}
		if (InputHandler::GetInstance()->GetKeyDown(SDL_SCANCODE_U) && m_Transform->Y > 0) {
			m_RigidBody->ApplyForceY(4 * BACKWARD);
			rect.x = m_Transform->X;
			rect.y = m_Transform->Y;
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

void Bullet::Clean() {
	TextureManager::GetInstance()->Clean();
}