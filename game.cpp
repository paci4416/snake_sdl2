#include "game.h"

Game::Game()
{
	this->running = false;
	this->mScoreText = NULL;
	this->mEndText = NULL;
	this->mSnake = NULL;
	this->mApple = NULL;
	this->mTexture = NULL;
	this->mMusic = NULL;
	this->mEatSound = NULL;
	this->mDieSound = NULL;
	this->mAppleClipRect = {0,BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE};
	mMuted = false;
	mEndMessage = "Press 'R' to play again";
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
	delete mScoreText;
	delete mEndText;
	this->mScoreText = NULL;
	this->mEndText = NULL;
	this->mSnake = NULL;
	this->mApple = NULL;
	this->mRenderer = NULL;
	this->mWindow = NULL;
	this->mTexture = NULL;

	TTF_Quit();
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
				switch(e.key.keysym.sym)
				{
					case SDLK_r:
						reset();
						break;
					case SDLK_c:
						placeApple();
						break;
					case SDLK_m:
						toggleMute();
						break;
				}
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

	Uint32 startTicks = SDL_GetTicks();
	if (mSnake->isAlive())
	{
		mSnake->move();
		mScoreText->loadText(std::to_string(mScore));
	}
	else
	{
		if (!mDieSoundPlayed)
		{
			playSound(mDieSound);
			mDieSoundPlayed = true;
		}
		mScoreText->loadText(std::string("Score: ") + std::to_string(mScore));
		mScoreText->setPos({(GAME_WIDTH - mScoreText->getWidth()) / 2,
				(GAME_HEIGHT - mScoreText->getHeight()) / 2 - mScoreText->getHeight()});
	}
	if (mSnake->isOnApple(mApple->getPos()))
	{
		playSound(mEatSound);
		placeApple();
		mSnake->growUp();
		mScore += 1;
	}
	Uint32 ticks = SDL_GetTicks();
	if ((ticks - startTicks) <  TICKS_PER_FRAME && mSnake->isAlive())
	{
		SDL_Delay(TICKS_PER_FRAME - (ticks - startTicks));
	}

}

void Game::draw()
{
	SDL_RenderClear(this->mRenderer);
	mSnake->render();
	mApple->render();
	mScoreText->render();
	if (!mSnake->isAlive())
	{
		mEndText->render();
	}
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
		success = reset();
	}
	return success;
}

void Game::placeApple()
{
	int maxBlocksInWidth = GAME_WIDTH / BLOCK_SIZE;
	int maxBlocksInHeight = GAME_HEIGHT / BLOCK_SIZE;
	int x = (rand() % maxBlocksInWidth) * BLOCK_SIZE;
	int y = (rand() % maxBlocksInHeight) * BLOCK_SIZE;
	mApple->setPos(x,y);
}

void Game::toggleMute()
{
	if (mMuted)
	{
		Mix_ResumeMusic();
		mMuted = false;
	}
	else
	{
		Mix_PauseMusic();
		mMuted = true;
	}
}

void Game::playSound(Mix_Chunk* sound)
{
	if (!mMuted)
	{
		Mix_PlayChannel(-1, sound, 0);
	}
}

bool Game::reset()
{
	bool success = true;

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
	mSnake = new Snake(mRenderer, mTexture, new SDL_Point{GAME_WIDTH / 2, GAME_HEIGHT / 2}, BLOCK_SIZE, GAME_HEIGHT, GAME_WIDTH);
	if (mApple != NULL)
	{
		delete mApple;
	}
	mApple = new Sprite(mTexture, mRenderer);
	mApple->setClipRect(&mAppleClipRect);
	if (mScoreText != NULL)
	{
		delete mScoreText;
	}
	mScoreText = new Font(mRenderer);
	mScoreText->loadFont();
	if (mEndText == NULL)
	{
		mEndText = new Font(mRenderer);
		mEndText->loadFont();
		mEndText->loadText(mEndMessage);
		mEndText->setPos({(GAME_WIDTH - mEndText->getWidth()) / 2, (GAME_HEIGHT - mEndText->getHeight()) / 2});
	}
	if (mMusic == NULL)
	{
		mMusic = Mix_LoadMUS("Farty-McSty.mp3");
		success = mixerErrCheck(mMusic);
		Mix_PlayMusic(mMusic, -1);
	}
	if (mEatSound == NULL)
	{
		mEatSound = Mix_LoadWAV("eatSound.ogg");
		success = mixerErrCheck(mEatSound);
	}
	if (mDieSound == NULL)
	{
		mDieSound = Mix_LoadWAV("dieSound.ogg");
		success = mixerErrCheck(mDieSound);
	}
	mDieSoundPlayed = false;
	Mix_HaltChannel(-1);
	placeApple();
	mScore = 0;
	return success;
}

bool Game::initSDL()
{
	bool success = true;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
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
		mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN );
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
				SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xC0, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				if ( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

				if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}
	return success;
}

bool Game::mixerErrCheck(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Failed to load mixer object! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	return true;
}
