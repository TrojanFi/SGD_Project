#ifdef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

class RigidBody
{
public:
	RigidBody() {}
	

private:
	float m_Mass;
	float m_Gravity;

	Vector2D m_Force;

};

#endif // RIGIDBODY_H

