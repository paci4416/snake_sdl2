#include "sprite.h"

Sprite::Sprite(Texture* sprite, SDL_Renderer* r)
{
	mTexture = sprite;
	clip = NULL;
	mPos.x = 0;
	mPos.y = 0;
	renderer = r;
	rot = 0;
	center = {0, 0};
}

void Sprite::setPos(int x, int y)
{
	mPos.x = x;
	mPos.y = y;
}

void Sprite::setCenter(int x, int y)
{
	center.x = x;
	center.y = y;
}
void Sprite::render()
{
	SDL_Rect rect = {mPos.x, mPos.y, clip->w, clip->h};
	SDL_RenderCopyEx(renderer, mTexture->getTexture(), clip, &rect, rot, &center, SDL_FLIP_NONE);
}

SDL_Rect* Sprite::getClipRect()
{
	return clip;
}
