#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

class Enemy: public Character
{
public:
	Enemy(Properties* props);
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);
	virtual void UpdateMovement();
	virtual void SeePlayer(SDL_Rect player);
	virtual void StartPosition();
	virtual void CreateFire();
	virtual void FireDelete();
	virtual void FireDeleteDistance();
	virtual void FireUpdate();
	virtual void FireDraw();
	virtual bool FiredCollision(SDL_Rect enemies);
	
	SDL_Rect rect;

private:
	float fireDirection = 0;
	bool fired = false;
	float x = 0;
	float y = 0;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};

#endif // !ENEMY_H
