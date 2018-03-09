#pragma once

#include <list>
#include "sprite.h"

enum {
	SNAKE_HEAD,
	SNAKE_BODY,
	SNAKE_ROT_A,
	SNAKE_ROT_B,
	SNAKE_TAIL,
};

enum {
	DIR_LEFT,
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN
};

class Snake
{
	public:
		Snake(SDL_Renderer* r, Texture* t, SDL_Point* startPos, int screenHeight, int screenWidth);
		~Snake();
		void handleEvents(SDL_Event* e);
		void move();
		void render();
		bool isAlive() {return this->mAlive;}
	private:
		bool isOutOfScreen();
		bool mAlive;
		bool turned;
		int screenHeight;
		int screenWidth;
		int oldDirection;
		int getRotateTexture();
		Sprite* createSnakePart(SDL_Point* pos, int snake_part);
		const int DIR_MULT = 90;
		int direction;
		const int BLOCK_SIZE = 18;
		SDL_Point mPos;
		std::list<Sprite*> mSprites;
		Texture* mTexture;
		SDL_Renderer* mRenderer;
		SDL_Rect mSnakeClips[5];
};
