#include "Enemy.h"
#include "TextureManager.h"

Enemy::Enemy(Properties* props):Character(props) {
	m_Animation = new Animation();
	m_RigidBody = new RigidBody();
	m_Animation = new Animation();
	m_Animation->SetProps(m_TextureID, 0, 3, 100, SDL_FLIP_NONE);
	rect.x = m_Transform->X; 
	rect.y = m_Transform->Y; 
	rect.w = 32; 
	rect.h = 64; 
	x = m_Transform->X;
	y = m_Transform->Y;
}

void Enemy::StartPosition() {
	rect.x = m_Transform->X; 
	rect.y = m_Transform->Y; 
	rect.w = 16; 
	rect.h = 16; 
	m_Transform->X = x;
	m_Transform->Y = y;
	m_RigidBody->UnSetForce();

}

void Enemy::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);
}



void Enemy::UpdateMovement() {
}

void Enemy::Clean() {
	TextureManager::GetInstance()->Clean();
}
