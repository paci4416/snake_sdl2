#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "texture.h"

class Font
{
	public:
		Font(SDL_Renderer* renderer);
		~Font();
		bool loadFont(int size = 35, std::string font_path = "free_sans.ttf");
		bool loadText(std::string text, SDL_Color color = {0, 0, 0, 0xFF});
		void render();
		void setPos(SDL_Point pos) {mPos = pos;}
		int getWidth() {return mTexture->getWidth();}
		int getHeight() {return mTexture->getHeight();}
	private:
		TTF_Font* mFont;
		SDL_Point mPos;
		Texture* mTexture;
		SDL_Renderer* mRenderer;


};
