#include "Enemy.h"

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

void Enemy::Draw() {
}

void Enemy::Clean() {
}

void Enemy::UpdateMovement() {
}