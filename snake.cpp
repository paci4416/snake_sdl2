#include "snake.h"

Snake::Snake(SDL_Renderer* r, Texture* t, SDL_Point* startPos)
{
	mRenderer = r;
	mTexture = t;
	mSnakeClips[SNAKE_HEAD] = {0, 0, BLOCK_SIZE, BLOCK_SIZE};
	mSnakeClips[SNAKE_BODY] = {BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE};
	mSnakeClips[SNAKE_ROT_A] = {BLOCK_SIZE*2, 0, BLOCK_SIZE, BLOCK_SIZE};
	mSnakeClips[SNAKE_ROT_B] = {BLOCK_SIZE*2, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
	mSnakeClips[SNAKE_TAIL] = {BLOCK_SIZE*3, 0, BLOCK_SIZE, BLOCK_SIZE};
	mPos.x = startPos->x;
	mPos.y = startPos->y;
	direction = DIR_LEFT;
	turned = false;

	SDL_Point pos;
	pos.x = startPos->x;
	pos.y = startPos->y;
	mSprites.push_back(createSnakePart(&pos, SNAKE_HEAD));
	pos.x += BLOCK_SIZE;
	mSprites.push_back(createSnakePart(&pos, SNAKE_BODY));
	pos.x += BLOCK_SIZE;
	mSprites.push_back(createSnakePart(&pos, SNAKE_BODY));
	pos.x += BLOCK_SIZE;
	mSprites.push_back(createSnakePart(&pos, SNAKE_TAIL));
}

Sprite* Snake::createSnakePart(SDL_Point* pos, int snake_part)
{
	Sprite* s = new Sprite(mTexture, mRenderer);
	s->setPos(pos->x, pos->y);
	s->setClipRect(&mSnakeClips[snake_part]);
	s->setCenter(BLOCK_SIZE / 2, BLOCK_SIZE / 2);
	return s;
}

void Snake::handleEvents(SDL_Event* e)
{
	if (e->type == SDL_KEYDOWN && e->key.repeat == 0 && turned == false)
	{
		oldDirection = direction;
		switch(e->key.keysym.sym)
		{
			case SDLK_a:
				if (direction == DIR_UP || direction == DIR_DOWN)
				{
					direction = DIR_LEFT;
					turned = true;
				}
				break;
			case SDLK_w:
				if (direction == DIR_LEFT || direction == DIR_RIGHT)
				{
					direction = DIR_UP;
					turned = true;
				}
				break;
			case SDLK_d:
				if (direction == DIR_UP || direction == DIR_DOWN)
				{
					direction = DIR_RIGHT;
					turned = true;
				}
				break;
			case SDLK_s:
				if (direction == DIR_LEFT || direction == DIR_RIGHT)
				{
					direction = DIR_DOWN;
					turned = true;
				}
				break;
		}
	}
}

void Snake::move()
{
	SDL_Point oldPos = mPos;
	switch(direction)
	{
		case DIR_UP:
			mPos.y -= BLOCK_SIZE;
			break;
		case DIR_DOWN:
			mPos.y += BLOCK_SIZE;
			break;
		case DIR_LEFT:
			mPos.x -= BLOCK_SIZE;
			break;
		case DIR_RIGHT:
			mPos.x += BLOCK_SIZE;
			break;
	}

	Sprite* head = mSprites.front();
	head->setPos(mPos.x, mPos.y);
	head->setRotation(direction*DIR_MULT);
	mSprites.pop_front();

	Sprite* tail = mSprites.back();
	mSprites.pop_back();
	tail->setPos(oldPos.x, oldPos.y);
	tail->setRotation(head->getRotation());
	if (turned == true)
	{
		turned = false;
		tail->setClipRect(&mSnakeClips[getRotateTexture()]);
	}
	else
	{
		tail->setClipRect(&mSnakeClips[SNAKE_BODY]);
	}
	mSprites.push_front(tail);
	mSprites.push_front(head);
	mSprites.back()->setClipRect(&mSnakeClips[SNAKE_TAIL]);
}

int Snake::getRotateTexture()
{
	if ((oldDirection == DIR_DOWN && direction == DIR_LEFT) ||
			(oldDirection == DIR_UP && direction == DIR_RIGHT) ||
			(oldDirection == DIR_LEFT && direction == DIR_UP) ||
			(oldDirection == DIR_RIGHT && direction == DIR_DOWN))
		return SNAKE_ROT_B;
	return SNAKE_ROT_A;
}

void Snake::render()
{
	for(auto &value: this->mSprites)
	{
		value->render();
	}
}



