#ifndef BULLET_H
#define BULLET_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class Bullet: public Character {

public:
	Bullet(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);
	virtual void UpdateBot(int type);
	virtual void UpdateFire(float direction);
	virtual void StartPosition();
	virtual void RectView();
	virtual float BulletStartPositionX();
	virtual float BulletPositionX();
	SDL_Rect rect;

private:
	bool m_ViewRect = false;
	float x = 0;
	float y = 0;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};


#endif // !BULLET_H
