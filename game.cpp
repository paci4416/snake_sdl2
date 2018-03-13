#include "game.h"

Game::Game()
{
	this->mWidth = 720;
	this->mHeight = 720;
	this->running = false;
	this->mSnake = NULL;
	this->mApple = NULL;
	this->mTexture = NULL;
	this->mAppleClipRect = {0,BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE};
	srand(time(NULL));
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
	delete mApple;
	delete mSnake;
	this->mSnake = NULL;
	this->mApple = NULL;
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
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_r)
					reset();
				else if(e.key.keysym.sym == SDLK_c)
					placeApple();
				break;
		}
		if (mSnake->isAlive())
		{
			mSnake->handleEvents(&e);
		}
	}
}

void Game::update()
{
	if (mSnake->isAlive())
	{
		mSnake->move();
	}
	if (mSnake->isOnApple(mApple->getPos()))
	{
		placeApple();
		mSnake->growUp();
	}
}

void Game::draw()
{
	SDL_RenderClear(this->mRenderer);
	mSnake->render();
	mApple->render();
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
		reset();
	}
	return success;
}

void Game::placeApple()
{
	int maxBlocksInWidth = mWidth / BLOCK_SIZE;
	int maxBlocksInHeight = mHeight / BLOCK_SIZE;
	int x = (rand() % maxBlocksInWidth) * BLOCK_SIZE;
	int y = (rand() % maxBlocksInHeight) * BLOCK_SIZE;
	mApple->setPos(x,y);
}

void Game::reset()
{
	if (this->mTexture == NULL)
	{
		this->mTexture = new Texture();
		this->mTexture->loadFromFile(mRenderer, "snakesprite.png", true);
	}
	this->running = true;
	if (mSnake != NULL)
	{
		delete mSnake;
	}
	mSnake = new Snake(mRenderer, mTexture, new SDL_Point{mWidth / 2, mHeight / 2}, BLOCK_SIZE, mHeight, mWidth);
	if (mApple != NULL)
	{
		delete mApple;
	}

	mApple = new Sprite(mTexture, mRenderer);
	mApple->setClipRect(&mAppleClipRect);
	placeApple();
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

