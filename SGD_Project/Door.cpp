#include "Door.h"
#include "Engine.h"
#include "TextureManager.h"

Door::Door(Properties* props) : Character(props) {
	m_Animation = new Animation();
	rect.x = m_Transform->X;
	rect.y = m_Transform->Y;
	rect.w = 64;
	rect.h = 64;
}

void Door::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &rect);
}

void Door::Update(float dt) {

	m_Animation->SetProps(m_TextureID, 0, 3, 100, SDL_FLIP_NONE);
	m_Animation->Update();
}

void Door::Clean() {
	TextureManager::GetInstance()->Clean();
}

