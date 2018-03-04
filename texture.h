#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture
{
	public:
		Texture();
		~Texture();
		void clear();
		bool loadFromFile(SDL_Renderer* renderer, std::string path, bool keying);
		int getHeight() { return this->mHeight; }
		int getWidth() { return this->mWidth; }
		SDL_Texture* getTexture() {return this->mTexture; }
	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};
