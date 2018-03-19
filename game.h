#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "texture.h"
#include "sprite.h"
#include "snake.h"
#include "font.h"
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
		const int GAME_WIDTH = 720;
		const int GAME_HEIGHT = 720;;
		const int FPS = 15;
		const Uint32 TICKS_PER_FRAME = 1000 / FPS;
		void reset();
		void placeApple();
		Snake* mSnake;
		Font* mScoreText;
		Font* mEndText;
		std::string mEndMessage;
		Sprite* mApple;
		SDL_Renderer* mRenderer;
		SDL_Window* mWindow;
		SDL_Rect mAppleClipRect;
		Texture* mTexture;
		int mScore;
		bool running;
		bool initSDL();
};
