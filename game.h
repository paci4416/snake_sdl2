#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "sprite.h"
#include "snake.h"
#include <string>
#include <stdlib.h>
#include <time.h>

class Game {
	public:
		Game();
		~Game();
		bool init();
		bool isRunning();
		void update();
		void draw();
		void handleEvents();
		int getWidth();
		int getHeight();
	private:
		const int BLOCK_SIZE = 18;
		void reset();
		void placeApple();
		Snake* mSnake;
		Sprite* mApple;
		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;
		SDL_Rect mAppleClipRect;
		Texture* mTexture;
		int mWidth;
		int mHeight;
		bool running;
		bool initSDL();
};
