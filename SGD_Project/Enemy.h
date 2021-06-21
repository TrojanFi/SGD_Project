#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Enemy: public Character
{
public:
	Enemy(Properties* props);
	virtual void Draw();
	virtual void Clean();
	virtual void UpdateMovement();
	SDL_Rect rect;

private:
	float x = 0;
	float y = 0;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};

#endif // !ENEMY_H
