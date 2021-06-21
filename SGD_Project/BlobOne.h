#ifndef BLOBONE_H
#define BLOBONE_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Bullet.h"

class BlobOne: public Character{

public:
	BlobOne(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);
	virtual void StartPosition();
	virtual void RectView();
	virtual bool LifeStatus();
	virtual void LifeStatus4();
	virtual void CreateFire();
	virtual void FireDelete();
	virtual void FireDeleteDistance();
	virtual void FireUpdate();
	virtual void FireDraw();
	virtual bool FiredCollision(SDL_Rect enemies);
	virtual bool Fired();

	SDL_Rect rect;

private:
	float fireDirection = 0;
	bool fired = false;
	int m_lifePoints = 4;
	bool m_ViewRect = false;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};

#endif // !BLOBONE_H

