#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"

#define UNI_MASS 1.0f
#define GRAVITY 0.0 //9.8f

#define FORWARD 1
#define BACKWARD -1

class RigidBody
{
public:
	RigidBody() {
		m_Mass = UNI_MASS;
		m_Gravity = GRAVITY;
	}

	inline void SetMass(float mass) { m_Mass = mass; }
	inline void SetGravity(float gravity) { m_Gravity = gravity; }

	inline void ApplyForce(Vector2D force) { m_Force = force; }
	inline void ApplyForceX(float forceX) { m_Force.X = forceX; }
	inline void ApplyForceY(float forceY) { m_Force.Y = forceY; }
	inline void UnSetForce() { m_Force = Vector2D(0, 0); }

	inline void ApplyFriction(Vector2D friction) { m_Friction = friction; }
	inline float GetForceX() { return m_Force.X; }
	inline void UnSetFriction() { m_Friction = Vector2D(0, 0); }

	inline float GetMass() { return m_Mass; }
	inline int GetLevel() { return m_Level; }
	inline Vector2D Position() { return m_Position; }
	inline Vector2D Velocity() { return m_Velocity; }
	inline Vector2D Acceleration() { return m_Acceleration; }


	inline void SetLevel0() {
		m_Level = 3;
	}

	inline void SetPositionDown() { 
		m_Position.Log("Dane = "); 
		m_Level -= 1;
	}

	inline void SetPositionUp() {
		m_Position.Log("Dane = ");
		m_Level += 1;
	}


	void Update(float dt) {
		m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
		m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass;
		m_Velocity = m_Acceleration * dt;
		m_Position = m_Velocity * dt;
	}


private:
	int m_Level = 3;

	float m_Mass;
	float m_Gravity;

	Vector2D m_Force;
	Vector2D m_Friction;

	Vector2D m_Position;
	Vector2D m_Velocity;
	Vector2D m_Acceleration;

};

#endif // RIGIDBODY_H

