#include "texture.h"

Texture::Texture()
{
	mTexture = NULL;
}

Texture::~Texture()
{
	clear();
}

bool Texture::loadFromFile(SDL_Renderer* renderer, std::string path, bool keying)
{
	clear();
	bool success = true;
	SDL_Texture* texture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load %s to surface.\nError %s\n", path.c_str(), IMG_GetError());
		success = false;
	}
	else
	{
		/* if (keying) */
		/* { */
		/* 	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xff, 0, 0xff)); */
		/* } */

		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from surface %s.\nError %s\n", path.c_str(), IMG_GetError());
			success = false;
		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}

	mTexture = texture;
	return success;
}

void Texture::clear()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}
