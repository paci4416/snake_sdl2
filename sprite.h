#pragma once

#include <SDL2/SDL.h>
#include "texture.h"

class Sprite
{
	public:
		Sprite(Texture* sprite, SDL_Renderer* r);
		SDL_Rect* getClipRect();
		void setPos(int x, int y);
		SDL_Point getPos() {return mPos;};
		void setClipRect(SDL_Rect* rect) {this->clip = rect;}
		void setCenter(int x, int y);
		void setRotation(int rot) {this->rot = rot;}
		int getRotation() {return rot;}
		void render();
	private:
		SDL_Point mPos;
		int rot;
		Texture* mTexture;
		SDL_Point center;
		SDL_Renderer* renderer;
		SDL_Rect* clip;
};

