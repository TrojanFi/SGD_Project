#include "BlobOne.h"
#include "TextureManager.h"
#include <SDL.h>

BlobOne::BlobOne(Properties* props):Character(props){
	//m_FrameCount = 16;
	//m_Row = 0;
	//m_AnimationSpeed = 100;
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 16, 100, SDL_FLIP_NONE);
}

void BlobOne::Draw() {
	//TextureManager::GetInstance()->DrawFrame(m_TextureID,m_Transform->X,m_Transform->Y,m_Width,m_Height,m_Row,m_Frame);
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}


void BlobOne::Update(float dt) {
	//m_Frame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;
	m_Animation->Update();
}

void BlobOne::Clean() {
	TextureManager::GetInstance()->Clean();
}