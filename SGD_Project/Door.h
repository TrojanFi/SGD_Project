#ifndef DOOR_H
#define DOOR_H

#include "Character.h"
#include "Animation.h"


class Door:public Character
{
public:
	Door(Properties* props);
	virtual void Draw();
	virtual void Clean();
	virtual void Update(float dt);
	SDL_Rect rect;

private:
	Animation* m_Animation;
};

#endif // !DOOR_H

