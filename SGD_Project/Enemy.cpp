#include "Enemy.h"
#include "TextureManager.h"
#include "Engine.h"
#include "Bullet.h"

Bullet* enemyfire = nullptr;

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
	rect.w = 32; 
	rect.h = 64; 
	m_Transform->X = x;
	m_Transform->Y = y;
	m_RigidBody->UnSetForce();

}

void Enemy::Draw() {
	m_Animation->Draw(m_Transform->X, m_Transform->Y, m_Width, m_Height);

	//SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &rect);
}

void Enemy::SeePlayer(SDL_Rect player) {
	if (!fired)fireDirection = m_RigidBody->GetForceX();
	if (player.x > rect.x&& fireDirection > 0 && player.y == rect.y) {
		CreateFire();
	}
	else if (player.x < rect.x && fireDirection < 0 && player.y == rect.y) {
		CreateFire();
	}
}


void Enemy::UpdateMovement() {
	m_RigidBody->Update(0.8);

	if (m_Transform->X < x + 1) {
		m_RigidBody->ApplyForceX(4 * FORWARD);
		rect.x = m_Transform->X;
		rect.y = m_Transform->Y;
		m_Animation->SetProps("Enemy", 0, 7, 100, SDL_FLIP_NONE);
	}
	else if (m_Transform->X > x + 350)
	{
		m_RigidBody->ApplyForceX(4 * BACKWARD);
		rect.x = m_Transform->X;
		rect.y = m_Transform->Y;
		m_Animation->SetProps("Enemy", 0, 7, 100, SDL_FLIP_HORIZONTAL);
	}
	else {
		rect.x = m_Transform->X;
		rect.y = m_Transform->Y;
	}


	m_Transform->TranslateX(m_RigidBody->Position().X);
	m_Transform->TranslateY(m_RigidBody->Position().Y);

	m_Animation->Update();
}

void Enemy::CreateFire() {
	if (!fired) {
		fired = true;
		//fireDirection = m_RigidBody->GetForceX();
		if (fireDirection >= 0) {
			enemyfire = new Bullet(new Properties("Bullet", rect.x + 20, rect.y + 20, 16, 16));
		}
		else {
			enemyfire = new Bullet(new Properties("Bullet", rect.x, rect.y + 20, 16, 16));
		}
	}
}

void Enemy::FireUpdate() {
	if (fired)enemyfire->UpdateFire(fireDirection);
}

void Enemy::FireDraw() {
	if (fired)enemyfire->Draw();
}

void Enemy::FireDelete() {
	delete enemyfire;
	fired = false;
}

void Enemy::FireDeleteDistance() {
	if (fired) {
		if (enemyfire->BulletPositionX() > enemyfire->BulletStartPositionX() + 300) {
			delete enemyfire;
			fired = false;
		}
		else if (enemyfire->BulletPositionX() < enemyfire->BulletStartPositionX() - 300) {
			delete enemyfire;
			fired = false;
		}
	}
}



bool Enemy::FiredCollision(SDL_Rect enemies) {
	if (fired) {
		if (enemyfire->rect.x + enemyfire->rect.w < enemies.x || enemyfire->rect.x > enemies.x + enemies.w ||
			enemyfire->rect.y + enemyfire->rect.h < enemies.y || enemyfire->rect.y > enemies.y + enemies.h) {
			return false;
		}
		else {
			return true;
		}
	}
}

void Enemy::Update(float dt) {
}

void Enemy::Clean() {
	TextureManager::GetInstance()->Clean();
}
