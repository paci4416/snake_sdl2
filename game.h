#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"
#include "sprite.h"
#include "snake.h"
#include <string>

class Game {
	public:
		Game();
		~Game();
		bool init();
		bool isRunning();
		void update();
		void handleEvents();
		int getWidth();
		int getHeight();
	private:
		void reset();
		SDL_Rect snakeClip[4];
		Snake* mSnake;
		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;
		Texture* mTexture;
		int mWidth;
		int sillyTime;
		int mHeight;
		bool running;
		bool initSDL();
};
