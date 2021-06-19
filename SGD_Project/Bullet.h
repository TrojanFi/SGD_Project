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
	virtual void StartPosition();
	virtual void RectView();
	virtual void Alive();
	SDL_Rect rect;

private:
	bool m_ViewRect = false;
	bool m_Alive = false;
	float x = 0;
	float y = 0;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};


#endif // !BULLET_H
