#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "IObject.h"

class GameObject {

	public:
		GameObject() {}
		
		virtual void Draw() = 0;
		virtual void Update(float dt) = 0;
		virtual void Clean() = 0;

	protected:

};

#endif