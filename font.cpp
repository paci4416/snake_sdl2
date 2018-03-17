#include "font.h"

Font::Font(SDL_Renderer* renderer)
{
	mTexture = new Texture();
	mRenderer = renderer;
	mPos = {0, 0};
};

Font::~Font()
{
	delete mTexture;
	TTF_CloseFont(mFont);
}

bool Font::loadFont(int size, std::string font_path)
{
	bool success = true;
	mFont = TTF_OpenFont(font_path.c_str(), size);
	if (mFont == NULL)
	{
		printf( "Failed to load %s!\n SDL_ttf Error: %s\n", font_path.c_str(), TTF_GetError());
		success = false;
	}
	return success;
}

bool Font::loadText(std::string text, SDL_Color color)
{
	bool success = true;
	if (!mFont)
	{
		printf("Error: No font has been loaded\n");
		success = false;
	}
	else
	{
		if (!mTexture->loadFromRenderedText(mRenderer, mFont, text, color))
		{
			printf("Failed to load rendered text!\n");
			success = false;
		}
		
	}
	return success;
}

void Font::render()
{
	SDL_Rect rect = {mPos.x, mPos.y, mTexture->getWidth(), mTexture->getHeight()};
	SDL_RenderCopy(mRenderer, mTexture->getTexture(), NULL, &rect);
}
