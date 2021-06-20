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
	virtual void Boom(BlobOne b);
	virtual void StartPosition();
	virtual void RectView();
	virtual bool LifeStatus();
	virtual void LifeStatus4();

	SDL_Rect rect;

private:
	int m_lifePoints = 4;
	bool m_ViewRect = false;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};

#endif // !BLOBONE_H

