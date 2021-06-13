#include "BlobOne.h"
#include "TextureManager.h"
#include <SDL.h>

BlobOne::BlobOne(Properties* props):Character(props){
	m_FrameCount = 4;
	m_Row = 0;
	m_AnimationSpeed = 4;
}

void BlobOne::Draw() {
	TextureManager::GetInstance()->DrawFrame(m_TextureID,m_Transform->X,m_Transform->Y,m_Width,m_Height,m_Row,m_Frame);
}


void BlobOne::Update(float dt) {
	//SDL_Log("m_Frame = " + m_Frame);
	//SDL_Log("SDL_GetTicks() = " + SDL_GetTicks());
	//SDL_Log("m_AnimationSpeed = " + m_AnimationSpeed);
	//SDL_Log("m_FrameCount = " + m_FrameCount);
	m_Frame = (SDL_GetTicks() / m_AnimationSpeed) % m_FrameCount;
}

void BlobOne::Clean() {
	TextureManager::GetInstance()->Clean();
}