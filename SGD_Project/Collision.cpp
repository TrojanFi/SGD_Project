#include "Collision.h"

bool Collision::CheckCollision(SDL_Rect blo, SDL_Rect bullet)
{
	if (blo.x + blo.w < bullet.x || blo.x > bullet.x + bullet.w ||
		blo.y + blo.h < bullet.y || blo.y > bullet.y + bullet.h) {
		//SDL_Log("No collision");
		//std::cout << "b x = " << blo.x << std::endl;
		//std::cout << "b w = " << blo.w << std::endl;
		//std::cout << "b y = " << blo.y << std::endl;
		//std::cout << "b h = " << blo.h << std::endl;
		return false;
	}
	else {
		//SDL_Log("Collision");
		return true;
	}

}
