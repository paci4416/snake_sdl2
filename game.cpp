#include "game.h"

Game::Game()
{
	this->mWidth = 640;
	this->mHeight = 480;
	this->running = false;
	sillyTime = 0;
}

Game::~Game()
{
	if (!this->running)
	{
		return ;
	}
	SDL_DestroyRenderer(this->mRenderer);
	SDL_DestroyWindow(this->mWindow);
	delete mTexture;
	this->mRenderer = NULL;
	this->mWindow = NULL;
	this->mTexture = NULL;

	IMG_Quit();
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch(e.type)
		{
			case SDL_QUIT:
				this->running = false;
				break;
		}
		mSnake->handleEvents(&e);
	}
}

void Game::update()
{
	SDL_RenderClear(this->mRenderer);
	if (sillyTime == 30)
	{
		sillyTime = 0;
		mSnake->move();
	}
	else
	{
		sillyTime++;
	}
	mSnake->render();
	SDL_RenderPresent(this->mRenderer);
}

bool Game::isRunning()
{
	return this->running;
}

bool Game::init()
{
	bool success = true;
	success = initSDL();
	if (success)
	{
		this->running = true;
		this->mTexture = new Texture();
		this->mTexture->loadFromFile(mRenderer, "snakesprite.png", true);
		mSnake = new Snake(mRenderer, mTexture, new SDL_Point{mWidth / 2, mHeight / 2});
	}
	return success;
}

bool Game::initSDL()
{
	bool success = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->mWidth, this->mHeight, SDL_WINDOW_SHOWN );
		if( mWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			mRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if( mRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
	return success;
}

