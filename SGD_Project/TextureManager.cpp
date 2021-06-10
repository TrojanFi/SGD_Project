#include "TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Engine.h"

TextureManager* TextureManager::s_Instance = nullptr;

bool TextureManager::Load(std::string id,std::string filename) {
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(filename.c_str());

	if (loadedSurface == nullptr) {
		SDL_Log("Unable to load image %s! SDL_image Error: %s\n", filename.c_str(), SDL_GetError());
		return false;
	}

	// create image
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(),loadedSurface);
	if (texture == nullptr) {
		SDL_Log("Unable to create image %s! SDL_image Error: %s\n", filename.c_str(), SDL_GetError());
		return false;
	}

	// load terxture to map
	m_TextureMap[id] = texture;
	SDL_Log("Image loaded and created successfull", SDL_GetError());
	return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { 0, 0, width, height };
	SDL_Rect dstRect = { x, y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}
// Animacja
void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip) {
	SDL_Rect srcRect = { width*frame, height*row, width, height };
	SDL_Rect dstRect = { x, y, width, height };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::Drop(std::string id) {
	// desroy texture and remove from the map
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);

}

void TextureManager::Clean(){
	// clear map
	std::map < std::string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
		SDL_DestroyTexture(it->second);
	m_TextureMap.clear();

	SDL_Log("Texture map cleaned!!!");
}



