#ifndef BLOBONE_H
#define BLOBONE_H

#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"

class BlobOne: public Character {

public:
	BlobOne(Properties* props);

	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);

private:
	//int m_Row, m_Frame, m_FrameCount;
	//int m_AnimationSpeed;
	Animation* m_Animation;
	RigidBody* m_RigidBody;
};

#endif // !BLOBONE_H

